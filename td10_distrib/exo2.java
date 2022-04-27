public class exo2 {
    public native static long getPid();

    static {
        System.loadLibrary("exo2");
    }

    public static void main(String[] args) {
        System.out.println("Affichage PID en API Java 9+ : " + ProcessHandle.current().pid());
        System.out.println("Affichage PID avec la JNI : " + getPid());
    }
}
