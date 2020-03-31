#include <malloc.h>   
#include <string.h>   
#include <stdlib.h>   
#include "jni.h"
#include <stdio.h>

// using namespace System;   
// using namespace System::Text;  


void WriteLog(char *strFmt, ...);

// String^ jstringToStr(JNIEnv* env, jstring jstr);
char* jstringTostring(JNIEnv* env, jstring jstr);   
// jstring strTojstring(JNIEnv* env, String^ rtn);
jstring stringTojstring(JNIEnv* env, const char* pat);  
char* BytesToUtf8(char* src, char* dst, int* nout) ;


