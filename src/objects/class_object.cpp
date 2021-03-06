#include <cassert>
#include "../metadata/class.h"
#include "class_object.h"
#include "class_loader.h"

ClassObject::ClassObject(Class *c): Object(g_class_class), jvm_mirror(c)
{
    assert(g_class_class != nullptr);
    assert(jvm_mirror != nullptr);

    data = (slot_t *) (this + 1);
    // private final ClassLoader classLoader;
    setRefField("classLoader", S(sig_java_lang_ClassLoader), c->loader);
}

Object *ClassObject::clone() const
{
    jvm_abort("ClassObject don't support clone"); // todo
}

ClassObject *generateClassObject(Class *c)
{
    assert(c != nullptr);
    if (c->java_mirror != nullptr)
        return c->java_mirror;


    assert(g_class_class != nullptr);
    size_t size = sizeof(ClassObject) + g_class_class->inst_field_count * sizeof(slot_t);
    return new (calloc(1, size)) ClassObject(c);
}