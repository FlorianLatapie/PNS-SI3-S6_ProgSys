public class exo3 {
    public native static int fork();

    static {
        System.loadLibrary("exo3");
    }

    public static void main(String[] args) {
        System.out.println("lancement du fork " + fork());
    }
}
