public class exo4 {
    public native static int myFork();

    public native static int myWait();

    public native static void myExit(int status);

    public native static int mySleep(int seconds);

    static {
        System.loadLibrary("exo4");
    }

    public static void main(String[] args) {
        System.out.println("Lancement exo 1 et 2:");
        exo1and2();

        System.out.println("Lancement exo 3 :");
        exo3();
    }

    public static void exo1and2() {
        int i = 0;
        int nbFils = 10;

        for (int j = 0; j < nbFils; j++) {
            switch (myFork()) {
                case -1:
                    System.err.println("fork");
                    myExit(1);
                    break;
                case 0:
                    ++i;
                    for (int k = 0; k < 10; k++)
                        System.out.printf("fils: %d\n", j);
                    myExit(0);
                    break;
            }
        }

        for (int j = 0; j < nbFils; j++) {
            myWait();
        }
    }

    public static void exo3() {
        switch (myFork()) {
            case -1:
                System.err.println("fork");
                myExit(1);
                break;
            case 0:
                for (int k = 0; k < 10; k++)
                    System.out.printf("fils: %d\n", 1);

                myExit(0);
                break;
            default:
                mySleep(10);
                break;
        }
    }
}
