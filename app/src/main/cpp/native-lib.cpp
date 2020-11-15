#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_testjni2_DataProvider_add(JNIEnv *env, jobject thiz, jint x, jint y) {
    // TODO: implement add()
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_testjni2_DataProvider_sayHelloInC(JNIEnv *env, jobject thiz, jstring s) {
    // TODO: implement sayHelloInC()
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_testjni2_DataProvider_modifyIntArray(JNIEnv *env, jobject thiz, jintArray arr) {
    // TODO: implement modifyIntArray()
}