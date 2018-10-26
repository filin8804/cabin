/*
 * Author: Jia Yang
 */

#ifndef JVM_RTCP_H
#define JVM_RTCP_H

#include "../../jtypes.h"
#include "../../jvm.h"

struct field_ref;
struct method_ref;
struct method_handle;
struct invoke_dynamic_ref;
struct bootstrap_methods_attribute;

/*
 * RunTime Constant
 */
struct rtc {
    u1 t; // type of constant, defined in 'constant.h'

    union {
        jint i;
        jfloat f;
        jlong l;
        jdouble d;
//            struct name_and_type nt;
        void *p;
    } v;
};

/*
 * RunTime Constant Pool
 */
struct rtcp {
    struct rtc *pool;
    size_t count;
};

struct rtcp* rtcp_create(void **cfcp, size_t count, const struct bootstrap_methods_attribute *bootstrap_methods_attribute);
void rtcp_destroy(struct rtcp *rtcp);

const u1 rtcp_get_type(const struct rtcp *rtcp, int index);

jint rtcp_get_int(const struct rtcp *rtcp, int index);

jfloat rtcp_get_float(const struct rtcp *rtcp, int index);

jlong rtcp_get_long(const struct rtcp *rtcp, int index);

jdouble rtcp_get_double(const struct rtcp *rtcp, int index);

const char* rtcp_get_str(const struct rtcp *rtcp, int index);

/*
 * todo 返回值可否为 NULL
 */
const char* rtcp_get_class_name(const struct rtcp *rtcp, int index);

const struct name_and_type* rtcp_get_name_and_type(const struct rtcp *rtcp, int index);

struct field_ref* rtcp_get_field_ref(const struct rtcp *rtcp, int index);

struct method_ref* rtcp_get_method_ref(const struct rtcp *rtcp, int index);

struct method_ref* rtcp_get_interface_method_ref(const struct rtcp *rtcp, int index);

struct method_handle* rtcp_get_method_handle(const struct rtcp *rtcp, int index);

/*
 * 返回方法的描述符
 */
const char* rtcp_get_method_type(const struct rtcp *rtcp, int index);

struct invoke_dynamic_ref* rtcp_get_invoke_dynamic(const struct rtcp *rtcp, int index);


#endif //JVM_RTCP_H
