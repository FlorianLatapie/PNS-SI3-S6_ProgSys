#include "HelloWorld.h"
#include <stdio.h>
JNIEXPORT void JNICALL Java_HelloWorld_printCpp(JNIEnv *env, jclass cls)
{
    printf("World !\n");
}

JNIEXPORT void JNICALL
Java_HelloWorld_printStringToCpp(JNIEnv *env, jclass cl, jstring str)
{
    // Construction d'une chaîne C/C++ à partir d'une chaîne Java
    const char *cStr = env->GetStringUTFChars(str, 0);
    // Affichage de la chaîne C++
    printf("%s\n", cStr);
    // Libération de la chaîne C++
    env->ReleaseStringUTFChars(str, cStr);
}

JNIEXPORT jstring JNICALL
Java_HelloWorld_stringFromCpp(JNIEnv *env, jobject obj)
{
    // Construction d'une chaîne Java à partir d'une chaîne C/C++
    return env->NewStringUTF("Chaîne en C");
}