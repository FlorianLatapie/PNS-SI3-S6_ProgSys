#include "exo3.h"

#include <jni.h>
#include <sys/types.h>
#include <unistd.h>

JNIEXPORT jint JNICALL Java_exo3_fork
  (JNIEnv *, jclass)
{
  return fork();
}