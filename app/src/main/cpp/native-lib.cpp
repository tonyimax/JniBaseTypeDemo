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

struct OneKeyVideoExport {
    //jvm 不支持uint32_t
    int32_t percent;
    int32_t assaint_mode;
    int32_t assaint_state;
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnibasetypedemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    int x[] = {};
    double y[]={};
    bool z[] ={};
    char c[] = {};
    short s[]={};
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
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getIntValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getIntValueFromJNI()
    jint val = 111111;
    return val;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getBoolValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getBoolValueFromJNI()
    jboolean _bool = true;
    return _bool;
}
extern "C"
JNIEXPORT jbyte JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getByteValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getByteValueFromeJNI()
    jbyte  _byte = 0xf0;
    return _byte;

}
extern "C"
JNIEXPORT jchar JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getCharValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getCharValueFromJNI()
    jchar  _char = 'a';
    return _char;
}
extern "C"
JNIEXPORT jshort JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getShortValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getShortValueFromJNI()
    jshort  _short = 0xFFFFFF;
    return _short;
}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getLongValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getLongValueFromJNI()
    jlong _long = 0xFFFFFFFF;
    return _long;
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getFloatValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getFloatValueFromJNI()
    float _float=0.9999f;
    return _float;
}
extern "C"
JNIEXPORT jdouble JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getDoubleValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getDoubleValueFromJNI()
    double _double=0.9090909090;
    return _double;
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getObjectValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getObjectValueFromJNI()
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getStringValueFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement getStringValueFromJNI()
    jstring _string = env->NewStringUTF("HelloWorld");
    return _string;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getAnimalsNameFromJNI(JNIEnv *env, jobject thiz,
                                                               jobjectArray animals) {
    jobject animalObj;
    int len = env->GetArrayLength(animals);//获取数组长度
    jclass animalClass = env->FindClass("com/example/jnibasetypedemo/Animal");//获取类对象
    //获取类字段
    jfieldID animalClassNameFiels = env->GetFieldID(animalClass, //类对象
                                   "name", //字段名
                                   "Ljava/lang/String;");//字段签名
    jstring _jni_string;
    const char *cplusplus_string;
    //遍历数组
    for (int i = 0; i < len; ++i) {
        animalObj = env->GetObjectArrayElement(animals, i);//取得元素
        //取类对象字段
        _jni_string = (jstring) (env->GetObjectField(animalObj, //类对象
                                              animalClassNameFiels));//类对字段对象
        //jstring转char*
        cplusplus_string = env->GetStringUTFChars(_jni_string, NULL);
        if (cplusplus_string == NULL) {
            continue;
        }
        LOGD("===>Animal类字段name值:%s", cplusplus_string);
        //释放内存
        env->ReleaseStringUTFChars(_jni_string, cplusplus_string);
    }
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jnibasetypedemo_MainActivity_getOneKeyVideoExportObjectFromJNI(JNIEnv *env, jobject thiz) {
    OneKeyVideoExport _one{0};
    _one.percent=90;
    _one.assaint_mode=1;
    _one.assaint_state=2;

    jclass clazz = env->FindClass("com/example/jnibasetypedemo/OneKeyVideoExport");
    jmethodID constructor = env->GetMethodID(clazz, "<init>", "()V");
    jobject jobj = env->NewObject(clazz, constructor);
    // 注意：这里的jobj是一个局部引用，如果你需要全局引用，请使用
    // jobject globalRef = env->NewGlobalRef(jobj);

    jfieldID percent = env->GetFieldID(clazz, "percent", "I");
    jfieldID assaint_mode = env->GetFieldID(clazz, "assaint_mode", "I");
    jfieldID assaint_state = env->GetFieldID(clazz, "assaint_state", "I");
    jobject OneKeyVideoExport_JavaObject = env->AllocObject(clazz);
    env->SetIntField(OneKeyVideoExport_JavaObject, percent, _one.percent);
    env->SetIntField(OneKeyVideoExport_JavaObject, assaint_mode, _one.assaint_mode);
    env->SetIntField(OneKeyVideoExport_JavaObject, assaint_state, _one.assaint_state);

    env->DeleteLocalRef(jobj);
    //env->DeleteGlobalRef(globalRef);
    env->DeleteLocalRef(clazz);

    return OneKeyVideoExport_JavaObject;
}