#include <jni.h>
#include <string>
#include <android/log.h>


// Android log function wrappers
static const char *kTAG = "TestJNI2";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

char *Jstring2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //new char[alen+1];
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);

    return rtn;
}

jstring CStr2Jstring(JNIEnv *env, const char *pat) {
    // 定义java String类 strClass
    jclass strClass = (env)->FindClass("java/lang/String");
    // 获取java String类方法String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    // 建立byte数组
    jbyteArray bytes = (env)->NewByteArray((jsize) strlen(pat));
    // 将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, (jsize) strlen(pat), (jbyte *) pat);
    //设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("GB2312");
    //将byte数组转换为java String,并输出
    return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_testjni2_DataProvider_add(JNIEnv *env, jobject thiz, jint x, jint y) {
    LOGI("jni add 被执行%d\n", x + y);
    return x + y;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_testjni2_DataProvider_sayHelloInC(JNIEnv *env, jobject thiz, jstring s) {
    // TODO: implement sayHelloInC()
    char *cstr = Jstring2CStr(env, s);
    //C中字符串都以 \0 结尾
    char arr[6] = {'h', 'h', 'h', 'h', 'h', '\0'};
    strcat(cstr, arr);
    LOGI("sayHelloInC", cstr);
    return CStr2Jstring(env, cstr);
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_testjni2_DataProvider_modifyIntArray(JNIEnv *env, jobject thiz, jintArray arr) {
    int len = (*env).GetArrayLength(arr);
    LOGI("数组长度%d", len);
    jint* intarr = (*env).GetIntArrayElements(arr, 0);
    for (int i = 0; i < len; i++) {
//        *(intarr+i) += 100;
        intarr[i] += 10;
        LOGI("for循环里的值%d", intarr[i]);
        (*env).SetIntArrayRegion(arr,i,1,&intarr[i]);
//        env->SetIntArrayRegion(arr,i,1,&intarr[i]);
    }
    LOGI("arr%d", &arr);
    LOGI("intarr%d", &intarr);

    env->ReleaseIntArrayElements(arr,intarr,0);
    return arr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjni2_DataProvider_callHelloFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement callHelloFromJNI()
    jclass providerCls = env -> FindClass("com/example/testjni2/DataProvider");
    if (providerCls == 0){
        LOGI("jclass DataProvider not found");
        return;
    }
    jmethodID jmethodId = env->GetMethodID(providerCls,"helloFromJNI","()V");
    if (jmethodId == 0){
        LOGI("jmethodID helloFromJNI not found");
        return;
    }
    env->CallVoidMethod(thiz,jmethodId);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjni2_DataProvider_callAdd2(JNIEnv *env, jobject thiz, jint x, jint y) {
    jclass providerCls = env -> FindClass("com/example/testjni2/DataProvider");
    if (providerCls == 0){
        LOGI("jclass DataProvider not found");
        return;
    }
    jmethodID jmethodId = env->GetMethodID(providerCls,"add2","(II)I");
    if (jmethodId == 0){
        LOGI("jmethodID add2 not found");
        return;
    }
    env->CallIntMethod(thiz,jmethodId,x,y);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjni2_DataProvider_callPrintString(JNIEnv *env, jobject thiz, jstring s) {
    jclass providerCls = env -> FindClass("com/example/testjni2/DataProvider");
    if (providerCls == 0){
        LOGI("jclass DataProvider not found");
        return;
    }
    jmethodID jmethodId = env->GetMethodID(providerCls,"printString", "(Ljava/lang/String;)V");
    if (jmethodId == 0){
        LOGI("jmethodID printString not found");
        return;
    }
//    env->CallVoidMethod(thiz,jmethodId,s);
    env->CallVoidMethod(thiz,jmethodId,env->NewStringUTF("call me xiao xuan"));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjni2_DataProvider_callStaticPrintString(JNIEnv *env, jobject thiz) {
    jclass providerCls = env -> FindClass("com/example/testjni2/DataProvider");
    if (providerCls == 0){
        LOGI("jclass DataProvider not found");
        return;
    }
    jmethodID jmethodId = env->GetStaticMethodID(providerCls,"staticPrintString", "(Ljava/lang/String;)V");
    if (jmethodId == 0){
        LOGI("jmethodID printString not found");
        return;
    }
    env->CallStaticVoidMethod(providerCls,jmethodId,env->NewStringUTF("static call me lao er"));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjni2_MainActivity_callDataProvider_1helloFromJNI(JNIEnv *env, jobject thiz) {
    jclass providerCls = env -> FindClass("com/example/testjni2/DataProvider");
    if (providerCls == 0){
        LOGI("jclass DataProvider not found");
        return;
    }
    jmethodID jmethodId = env->GetMethodID(providerCls,"helloFromJNI","()V");
    if (jmethodId == 0){
        LOGI("jmethodID helloFromJNI not found");
        return;
    }
    jobject providerObject = env->AllocObject(providerCls);
    env->CallVoidMethod(providerObject,jmethodId);
}