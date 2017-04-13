#include <string.h>
#include <jni.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

jint Java_mobile_android_word_count_ndk_WordCountNDKTestMain_readWordCountFromDev(
        JNIEnv* env, jobject thiz)
{

	int dev;
	jint wordcount = 0;
	unsigned char buf[4];

	dev = open("/dev/wordcount", O_RDONLY);

	read(dev, buf, 4);

	int n = 0;
	n = ((int) buf[0]) << 24 | ((int) buf[1]) << 16 | ((int) buf[2]) << 8
	        | ((int) buf[3]);
	wordcount = (jint) n;
	close(dev);
	return wordcount;
}
char* jstring_to_pchar(JNIEnv* env, jstring str)
{
	char* pstr = NULL;
	jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	jstring strencode = (*env)->NewStringUTF(env, "utf-8");
	jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes",
		        "(Ljava/lang/String;)[B");
	jbyteArray byteArray = (jbyteArray)(
		        (*env)->CallObjectMethod(env, str, mid, strencode));
	jsize size = (*env)->GetArrayLength(env, byteArray);
	jbyte* pbyte = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);
	if (size > 0)
	{
		pstr = (char*) malloc(size);
		memcpy(pstr, pbyte, size);
	}
	return pstr;
}
void Java_mobile_android_word_count_ndk_WordCountNDKTestMain_writeStringToDev(
        JNIEnv* env, jobject thiz, jstring str)
{

	int dev;
	dev = open("/dev/wordcount", O_WRONLY);
	char* pstr = jstring_to_pchar(env, str);
	if (pstr != NULL)
	{
		write(dev,pstr, strlen(pstr));
	}
	close(dev);
}
