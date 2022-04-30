#include <jni.h> /* where everything is defined */
JavaVM *jvm;     /* denotes a Java VM */
JNIEnv *env;     /* pointer to native method interface */
JavaVMInitArgs vm_args = {
    /* JDK/JRE 10 VM initialization arguments */
    .version = JNI_VERSION_10,
    .nOptions = 0,
    .options = NULL,
    .ignoreUnrecognized = false,
};
int main()
{
  /* load and initialize a Java VM, return a JNI interface pointer in env */
  JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
  /* invoke the Main.testmethod using the JNI */
  jclass cls = env->FindClass("exo1");
  jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
  env->CallStaticVoidMethod(cls, mid, NULL);
  /* We are done. */
  jvm->DestroyJavaVM();
  return 0;
}