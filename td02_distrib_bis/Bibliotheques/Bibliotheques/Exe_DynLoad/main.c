#include <Windows.h>
#include <stdio.h>
// d�crire le prototype de la proc�dure : proto_convert est le type d�fini par typedef,
// c�est un pointeur sur fonction int (int).
typedef void(*proto_convert) (char*);
int main()
{
	proto_convert convert = NULL;
	// Attention : le chemin du fichier est en Unicode si votre projet est configur�
	// comme tel, la chaine doit alors �tre d�clar�e comme : L"..."
	// Attention : pas de \ dans le chemin, sinon c�est un caract�re d��chappement
	void* hinstDLL = LoadLibrary(L"C:/Users/Florian/Documents/GitHub/PNS-S6-ProgSys/td02_distrib_bis/Bibliotheques/Bibliotheques/x64/Debug/Bibliotheques.dll");
	if (!hinstDLL) // Erreur lors du chargement de la biblioth�que ?
		printf("Impossible de charger la biblioth�que.");
	else // On r�cup�re l'adresse de la fonction
		convert = (proto_convert)GetProcAddress(hinstDLL, "PrintStop");
	char* a = "dynload";
	convert(a);
	FreeLibrary(hinstDLL);
	//convert(a); // qu'arrive-t�il?
}