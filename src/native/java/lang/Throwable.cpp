/*
 * Author: Yo Ka
 */

#include "../../jni_inner.h"
#include "../../../objects/object.h"
#include "../../../objects/array_object.h"
#include "../../../runtime/vm_thread.h"
#include "../../../symbol.h"
#include "../../../runtime/frame.h"
#include "../../../metadata/class.h"
#include "../../../objects/class_loader.h"

using namespace std;

// private native Throwable fillInStackTrace(int dummy);
static jobject fillInStackTrace(jobject _this, jint dummy)
{
    Thread *thread = getCurrentThread();

    Frame *frame = thread->getTopFrame();
    int num = thread->countStackFrames();
    /*
     * 栈顶两帧正在执行 fillInStackTrace(int) 和 fillInStackTrace() 方法，所以需要跳过这两帧。
     * 这两帧下面的几帧正在执行异常类的构造函数，所以也要跳过。
     * 具体要跳过多少帧数则要看异常类的继承层次。
     *
     * (RuntimeException extends Exception extends Throwable extends Object)
     *
     * 比如一个异常抛出示例
     * java.lang.RuntimeException: BAD!
     * at exception/UncaughtTest.main(UncaughtTest.java:6)
     * at exception/UncaughtTest.foo(UncaughtTest.java:10)
     * at exception/UncaughtTest.bar(UncaughtTest.java:14)
     * at exception/UncaughtTest.bad(UncaughtTest.java:18)
     * at java/lang/RuntimeException.<init>(RuntimeException.java:62)
     * at java/lang/Exception.<init>(Exception.java:66)
     * at java/lang/Throwable.<init>(Throwable.java:265)
     * at java/lang/Throwable.fillInStackTrace(Throwable.java:783)
     * at java/lang/Throwable.fillInStackTrace(Native Method)
     */
    Frame *f = frame->prev->prev;
    num -= 2;

    for (Class *c = _this->clazz; c != nullptr; c = c->super_class) {
        f = f->prev; // jump 执行异常类的构造函数的frame
        num--;
        if (utf8::equals(c->class_name, S(java_lang_Throwable))) {
            break; // 可以了，遍历到 Throwable 就行了，因为现在在执行 Throwable 的 fillInStackTrace 方法。
        }
    }

    auto backtrace = newArray(loadArrayClass(S(array_java_lang_Object)), num);
    auto trace = (Object **) backtrace->data;

    Class *c = loadBootClass(S(java_lang_StackTraceElement));
    for (int i = 0; f != nullptr; f = f->prev) {
        Object *o = newObject(c);
        assert(i < num);
        trace[i++] = o;

        // public StackTraceElement(String declaringClass, String methodName, String fileName, int lineNumber)
        // may be should call <init>, but 直接赋值 is also ok. todo

        auto fileName = f->method->clazz->source_file_name != nullptr 
                        ? newString(f->method->clazz->source_file_name) 
                        : nullptr;
        auto className = newString(f->method->clazz->class_name);
        auto methodName = newString(f->method->name);
        auto lineNumber = f->method->getLineNumber(f->reader.pc - 1); // todo why 减1？ 减去opcode的长度

        o->setRefField("fileName", "Ljava/lang/String;", fileName);
        o->setRefField("declaringClass", "Ljava/lang/String;", className);
        o->setRefField("methodName", "Ljava/lang/String;", methodName);
        o->setIntField("lineNumber", S(I), lineNumber);
    }

    /*
     * Native code saves some indication of the stack backtrace in this slot.
     *
     * private transient Object backtrace;
     */
    _this->setRefField(S(backtrace), S(sig_java_lang_Object), backtrace);

    return _this;
}

// native StackTraceElement getStackTraceElement(int index);
static jobject getStackTraceElement(jobject _this, jint index)
{
    auto backtrace = (Array *) _this->getRefField(S(backtrace), S(sig_java_lang_Object));
    assert(backtrace != nullptr);
    return backtrace->get<jobject>(index);
}

// native int getStackTraceDepth();
static jint getStackTraceDepth(jobject _this)
{
    auto backtrace = (Array *) _this->getRefField(S(backtrace), S(sig_java_lang_Object));
    assert(backtrace != nullptr);
    return backtrace->len;
}

static JNINativeMethod methods[] = {
        JNINativeMethod_registerNatives,
        { "fillInStackTrace", "(I)Ljava/lang/Throwable;", (void *) fillInStackTrace },
        { "getStackTraceElement", "(I)Ljava/lang/StackTraceElement;", (void *) getStackTraceElement },
        { "getStackTraceDepth", "()I", (void *) getStackTraceDepth },
};

void java_lang_Throwable_registerNatives()
{
    registerNatives("java/lang/Throwable", methods, ARRAY_LENGTH(methods));
}
