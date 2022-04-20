import java.util.Scanner;

public class HelloWorld {
    public static native void printCpp(); // Déclaration prototype méthode native
    public static native void printStringToCpp(String str); 
    public native String stringFromCpp();

    static {
        System.loadLibrary("HelloWorld"); // Chargement de la bibliothèque
    }

    public static void main(String args[]) {
        System.out.print("Hello "); // Affiche Hello en Java
        HelloWorld.printCpp(); // Affiche World en C/C++
        
        System.out.println("\n\nExo 3 :");
        printStringToCpp("printStringToCpp");
        HelloWorld hw = new HelloWorld();
        System.out.println("string from cpp : " + hw.stringFromCpp());
    }
}