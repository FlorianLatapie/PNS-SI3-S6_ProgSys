import java.util.Scanner;

public class HelloWorld {
    // Méthodes natives
    public static native void printCpp(); // Déclaration prototype méthode native
    public static native void printStringToCpp(String str); 
    public native String stringFromCpp();
    public native void callJavaMethod();
    @Override
    public native String toString();

    // Chargement du fichier .so
    static {
        System.loadLibrary("HelloWorld"); // Chargement de la bibliothèque
    }

    // Méthodes Java
    int entier = 10;

    public static void test(String entree){
        System.out.println("Méthode test : " + entree);
    }

    public static void main(String args[]) {
        System.out.println("Exo 1 & 2");
        System.out.print("Hello "); // Affiche Hello en Java
        HelloWorld.printCpp(); // Affiche World en C/C++
        
        System.out.println("\nExo 3 :");
        printStringToCpp("printStringToCpp");

        HelloWorld hw = new HelloWorld();
        System.out.println("string from cpp : " + hw.stringFromCpp());

        System.out.println("\nExo 4 :");
        hw.callJavaMethod();

        System.out.println("\nExo 5 :");
        System.out.println(hw.toString());
    }
}