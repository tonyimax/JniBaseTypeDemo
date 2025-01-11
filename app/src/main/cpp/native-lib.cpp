#include <jni.h>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <android/log.h>
#define LOGOPEN 1 //日志开关，1为开，其它为关

#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,    LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR,   LOG_TAG, __VA_ARGS__))

#if (LOGOPEN == 1)
#define LOG_TAG "JNI_LOG"
#define LOGV(...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG,   LOG_TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,    LOG_TAG, __VA_ARGS__))
#else
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#endif

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnibasetypedemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnibasetypedemo_MainActivity_CheckJNIBaseType(JNIEnv *env, jobject thiz) {

    jboolean _jbool= false;//uint8_t %u 无符号8位整数
    jbyte _byte=0xff;//int8_t; %d 有符号8位整数
    jchar _char=0xffff;//uint16_t; %u 无符号16位整数
    jshort _short=0xff00;//int16_t; %d 有符号16位整数
    jint _int=0xffffffff;//int32_t; %d 有符号32位整数
    jlong _long=0xffffffffffffffff;//int64_t %ld 有符号64位整数
    jfloat _float=0.9999f;//float %f    32位
    jdouble _double=0.9999;//double %lf  64位
    jstring _string=env->NewStringUTF("helloworld");
    auto str = env->GetStringUTFChars(_string, &_jbool);

    LOGD("===>布尔类型:%b 8位整数:%02x 字符类型:%c 16位整数:%hd 32位整数:%d "
         "64位整数:%lld 单精度浮点数%f 双精度浮点数:%lf  指定小数位数%.16f "
         "无符号32位整数:%u  十六进制:0x%08x  八进制:%o 字符串转换为jstring:%s 地址:%p 科学计数: %e "
         "jstring转换为const char* :%s\n",
         _jbool,_byte,_char,_short,_int,_long,
         _float,_double,_float,
         _char,_long,_byte,_string, _string,_float,str);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnibasetypedemo_MainActivity_JNIReadIntArrayData(JNIEnv *env, jobject thiz,
                                                                   jintArray arr_int) {
    jint *jintArr=env->GetIntArrayElements(arr_int, nullptr);//取数组首地址
    if (nullptr==jintArr){ return 0;}

    int length = env->GetArrayLength(arr_int);//取数组长度
    int sum=0;
    for (int i = 0; i < length; ++i) {
        LOGD("===>GetArrayLength  Java输入的数组索引: %d 值%d\n",i,jintArr[i]);//使用数组下标来取
        sum+=jintArr[i];
    }

    jint buf[length];
    env->GetIntArrayRegion(arr_int,0,length,buf);
    for (int i = 0; i < length; ++i) {
        LOGD("===>GetIntArrayRegion  Java输入的数组索引: %d 值%d\n",i,jintArr[i]);//使用数组下标来取
    }
    env->ReleaseIntArrayElements(arr_int,jintArr,JNI_OK);//释放内存
    return sum;
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_jnibasetypedemo_MainActivity_JNIGetIntArrayDate(JNIEnv *env, jobject thiz) {
    int len=30;
    jintArray  arr = env->NewIntArray(len);//分配数组内存
    //创建填充数据
    jint buf[len];
    srand((unsigned)time(NULL));
    for (int i = 0; i < len; ++i) {
        buf[i]=random()%100;//生成100以内的随机数据
    }
    env->SetIntArrayRegion(arr,0,len,buf);//复制数据到数组
    return arr;
}