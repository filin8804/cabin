cmake_minimum_required(VERSION 3.9)
project(yovm)

set(CMAKE_C_FLAGS "-std=c11 -m64 -Wall")
set(CMAKE_CXX_FLAGS "-std=c++17 -m64 -Wall -lz -lminizip -llibffi") # lz: link zlip

add_subdirectory(test) 

add_library(libyovm STATIC
        src/jvm.cpp src/platform/sysinfo_win.cpp src/platform/sysinfo_linux.cpp
        src/interpreter/interpreter.cpp src/metadata/descriptor.cpp
        src/util/encoding.cpp src/util/convert.cpp src/classfile/attributes.cpp
        src/runtime/frame.cpp src/runtime/vm_thread.cpp src/runtime/monitor.cpp
        src/memory/heap.cpp src/memory/gc.cpp
        src/native/java/io/FileDescriptor.cpp src/native/java/io/FileInputStream.cpp
        src/native/java/io/FileOutputStream.cpp src/native/java/lang/Class.cpp
        src/native/java/lang/Double.cpp src/native/java/lang/Float.cpp
        src/native/java/lang/Object.cpp src/native/java/lang/String.cpp
        src/native/java/lang/Module.cpp src/native/java/lang/StringUTF16.cpp
        src/native/java/lang/System.cpp src/native/java/lang/Thread.cpp
        src/native/java/lang/Throwable.cpp src/native/java/security/AccessController.cpp
        src/native/sun/misc/Unsafe.cpp src/native/sun/misc/VM.cpp
        src/native/sun/reflect/Reflection.cpp src/native/java/lang/Shutdown.cpp
        src/native/sun/reflect/NativeConstructorAccessorImpl.cpp
        src/native/sun/reflect/NativeMethodAccessorImpl.cpp
        src/native/sun/reflect/ConstantPool.cpp src/native/java/util/TimeZone.cpp
        src/native/java/util/concurrent/atomic/AtomicLong.cpp src/native/java/io/WinNTFileSystem.cpp
        src/native/java/lang/ClassLoader.cpp src/native/java/lang/ClassLoader-NativeLibrary.cpp
        src/native/sun/misc/Signal.cpp src/native/sun/io/Win32ErrorMode.cpp
        src/native/java/lang/Runtime.cpp src/native/sun/misc/Version.cpp
        src/native/java/lang/reflect/Field.cpp src/native/java/lang/reflect/Executable.cpp
        src/native/java/nio/Bits.cpp src/symbol.cpp 
        src/native/sun/misc/URLClassPath.cpp src/native/java/util/zip/ZipFile.cpp
        src/native/sun/misc/Perf.cpp src/native/java/lang/Package.cpp
        src/native/java/io/RandomAccessFile.cpp src/native/java/lang/invoke/MethodHandleNatives.cpp
        src/native/java/lang/reflect/Array.cpp src/native/java/lang/reflect/Proxy.cpp
        src/native/java/lang/invoke/MethodHandle.cpp
        src/native/java/net/AbstractPlainDatagramSocketImpl.cpp src/native/java/net/AbstractPlainSocketImpl.cpp
        src/native/java/net/NetworkInterface.cpp src/native/java/net/PlainSocketImpl.cpp
        src/native/java/net/InetAddress.cpp src/native/java/net/Inet4Address.cpp src/native/java/net/Inet6Address.cpp
        src/native/java/net/InetAddressImplFactory.cpp
        src/native/sun/management/VMManagementImpl.cpp src/native/sun/management/ThreadImpl.cpp
        src/native/jdk/internal/misc/VM.cpp
        src/native/jdk/internal/misc/Unsafe.cpp src/native/jdk/internal/util/SystemProps-Raw.cpp
        src/metadata/method.cpp src/metadata/field.cpp src/metadata/constant_pool.cpp src/native/jni.cpp
        src/objects/array_object.cpp src/objects/string_object.cpp 
        src/objects/class_loader.cpp src/objects/prims.cpp src/objects/mh.cpp
        src/objects/object.cpp src/metadata/class.cpp src/objects/class_object.cpp src/objects/java_classes.cpp src/objects/java_classes.h)

add_executable(yovm src/main.cpp)

target_link_libraries(libyovm libz)
target_link_libraries(libyovm libminizip)
target_link_libraries(libyovm libffi)
target_link_libraries(yovm libyovm)

