#include "HelloWorld.h"
#include <stdio.h>
JNIEXPORT void JNICALL Java_HelloWorld_printCpp(JNIEnv *env, jclass cls)
{
    printf("World !\n");
}