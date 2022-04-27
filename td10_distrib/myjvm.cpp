#include <jni.h> /* where everything is defined */
int main(int argc, char const *argv[])
{
    JavaVM *jvm; /* denotes a Java VM */
    JNIEnv *env; /* pointer to native method interface */
    JavaVMInitArgs vm_args = {
        /* JDK/JRE 10 VM initialization arguments */
        .version = JNI_VERSION_10,
        .nOptions = 0,
        .options = NULL,
        .ignoreUnrecognized = false,
    };
    /* load and initialize a Java VM, return a JNI interface pointer in env */
    JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
    /* invoke the Main.test method using the JNI */
    jclass cls = env->FindClass("Main");
    jmethodID mid = env->GetStaticMethodID(cls, "test", "(I)V");
    env->CallStaticVoidMethod(cls, mid, 100);
    /* We are done. */
    jvm->DestroyJavaVM();
    return 0;
}
