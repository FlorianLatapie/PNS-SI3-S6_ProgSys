#include "exo4.h"

#include <jni.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

JNIEXPORT jint JNICALL Java_exo4_myFork(JNIEnv *, jclass)
{
  return fork();
}

JNIEXPORT jint JNICALL Java_exo4_myWait(JNIEnv *, jclass)
{
  return wait(NULL);
}

JNIEXPORT void JNICALL Java_exo4_myExit(JNIEnv *, jclass, jint status)
{
  exit(status);
}

JNIEXPORT jint JNICALL Java_exo4_mySleep(JNIEnv *, jclass, jint seconds){
  return sleep(seconds);
}