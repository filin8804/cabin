/*
 * Author: Yo Ka
 */

#ifndef JVM_CONFIG_H
#define JVM_CONFIG_H

// jvm 最大支持的classfile版本
#define JVM_MUST_SUPPORT_CLASSFILE_MAJOR_VERSION 57
#define JVM_MUST_SUPPORT_CLASSFILE_MINOR_VERSION 65535

// size of heap
#define VM_HEAP_SIZE (128*1024*1024) // 128Mb

// every thread has a vm stack
#define VM_STACK_SIZE (128*1024)     // 128Kb

#endif //JVM_CONFIG_H
