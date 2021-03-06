#include <cassert>
#include "../../jni_inner.h"
#include "../../../jvmstd.h"
#include "../../../objects/object.h"
#include "../../../objects/array_object.h"
#include "../../../metadata/class.h"
#include "../../../objects/prims.h"
#include "../../../interpreter/interpreter.h"
#include "../../../metadata/descriptor.h"

/*
 * Author: Yo Ka
 */

using namespace std;

// private static native Object invoke0(Method method, Object o, Object[] os);
static jobject invoke0(jobject method, jobject o, jobjectArray os)
{
    assert(method != nullptr);
    // If method is static, o is nullptr.

    // private Class<?>   clazz;
    // private String     name;
    // private Class<?>   returnType;
    // private Class<?>[] parameterTypes;
    Class *c = method->getRefField<ClassObject>(S(clazz), S(sig_java_lang_Class))->jvm_mirror;
    jstrref name = method->getRefField(S(name), S(sig_java_lang_String));
    auto rtype = method->getRefField<ClassObject>(S(returnType), S(sig_java_lang_Class));
    auto ptypes = method->getRefField<Array>(S(parameterTypes), S(array_java_lang_Class));

    string desc = unparseMethodDescriptor(ptypes, rtype);
    Method *m = c->lookupMethod(name->toUtf8(), desc.c_str());
    if (m == nullptr) {
        jvm_abort("error"); // todo
    }

    slot_t *result = execJavaFunc(m, o, os);
    switch (m->ret_type) {
    case Method::RET_VOID:
        return voidBox();
    case Method::RET_BYTE:
        return byteBox(jint2jbyte(ISLOT(result)));
    case Method::RET_BOOL:
        return boolBox(jint2jbool(ISLOT(result)));
    case Method::RET_CHAR:
        return charBox(jint2jchar(ISLOT(result)));
    case Method::RET_SHORT:
        return shortBox(jint2jshort(ISLOT(result)));
    case Method::RET_INT:
        return intBox(ISLOT(result));
    case Method::RET_FLOAT:
        return floatBox(FSLOT(result));
    case Method::RET_LONG:
        return longBox(LSLOT(result));
    case Method::RET_DOUBLE:
        return doubleBox(DSLOT(result));
    case Method::RET_REFERENCE:
        return RSLOT(result);
    default:
        jvm_abort("never go here\n"); // todo
    }
}

static JNINativeMethod methods[] = {
        JNINativeMethod_registerNatives,
        { "invoke0", "(Ljava/lang/reflect/Method;" OBJ "[Ljava/lang/Object;)" OBJ, (void *) invoke0 },
};

void sun_reflect_NativeMethodAccessorImpl_registerNatives()
{
    registerNatives("sun/reflect/NativeMethodAccessorImpl", methods, ARRAY_LENGTH(methods));
}
