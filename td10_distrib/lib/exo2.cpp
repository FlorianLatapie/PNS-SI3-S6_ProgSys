#include "exo2.h"

#include <jni.h>
#include <sys/types.h>
#include <unistd.h>

JNIEXPORT jlong JNICALL Java_exo2_getPid
  (JNIEnv *, jclass)
{
  return getpid();
}