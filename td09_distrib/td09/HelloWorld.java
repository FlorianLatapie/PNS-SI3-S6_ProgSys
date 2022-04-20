import java.util.Scanner;

public class HelloWorld {
    public static native void printCpp(); // Déclaration prototype méthode native

    static {
        System.loadLibrary("HelloWorld"); // Chargement de la bibliothèque
    }

    public static void main(String args[]) {
        System.out.print("Hello "); // Affiche Hello en Java
        HelloWorld.printCpp(); // Affiche World en C/C++
        Scanner sc = new Scanner(System.in);
        sc.next();
    }
}