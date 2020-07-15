/*
 * Author: Yo Ka
 */

#include "../../jni_inner.h"
#include "../../../objects/object.h"
#include "../../../jvmstd.h"
#include "../../../runtime/frame.h"
#include "../../../runtime/vm_thread.h"
#include "../../../metadata/class.h"


// public static native Class<?> getCallerClass(int level)
static jclass getCallerClass0(jint level)
{
    jvm_abort("getCallerClass0");
}

// public static native Class<?> getCallerClass()
static jclass getCallerClass()
{
    // top0, current frame is executing getCallerClass()
    // top1, who called getCallerClass, the one who wants to know his caller.
    // top2, the caller of top1, the result.
    Frame *frame = (Frame *) getCurrentThread()->getTopFrame();
    Frame *top1 = frame->prev;
    assert(top1 != nullptr);

    Frame *top2 = top1->prev;
    assert(top2 != nullptr);

    jclass o = top2->method->clazz->java_mirror;
    return o;
}

// public static native int getClassAccessFlags(Class<?> type)
static jint getClassAccessFlags(jclass type)
{
    return type->clazz->accsee_flags; // todo
}

static JNINativeMethod methods[] = {
        JNINativeMethod_registerNatives,
        { "getCallerClass", "()Ljava/lang/Class;", (void *) getCallerClass },
        { "getCallerClass", "(I)Ljava/lang/Class;", (void *) getCallerClass0 },
        { "getClassAccessFlags", "(Ljava/lang/Class;)I", (void *) getClassAccessFlags },
};

void sun_reflect_Reflection_registerNatives()
{
    registerNatives("sun/reflect/Reflection", methods, ARRAY_LENGTH(methods));
}