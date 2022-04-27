public class exo1{
    public static void main(String[] args) {
    System.out.println("Affichage PID en API Java 8  : " + java.lang.management.ManagementFactory.getRuntimeMXBean().getName());
    System.out.println("Affichage PID en API Java 9+ : " + ProcessHandle.current().pid());
    }
}