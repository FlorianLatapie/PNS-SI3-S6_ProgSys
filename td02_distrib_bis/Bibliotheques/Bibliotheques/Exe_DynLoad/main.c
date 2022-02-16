#include <Windows.h>
#include <stdio.h>
// décrire le prototype de la procédure : proto_convert est le type défini par typedef,
// c’est un pointeur sur fonction int (int).
typedef void(*proto_convert) (char*);
int main()
{
	proto_convert convert = NULL;
	// Attention : le chemin du fichier est en Unicode si votre projet est configuré
	// comme tel, la chaine doit alors être déclarée comme : L"..."
	// Attention : pas de \ dans le chemin, sinon c’est un caractère d’échappement
	void* hinstDLL = LoadLibrary(L"C:/Users/Florian/Documents/GitHub/PNS-S6-ProgSys/td02_distrib_bis/Bibliotheques/Bibliotheques/x64/Debug/Bibliotheques.dll");
	if (!hinstDLL) // Erreur lors du chargement de la bibliothèque ?
		printf("Impossible de charger la bibliothèque.");
	else // On récupère l'adresse de la fonction
		convert = (proto_convert)GetProcAddress(hinstDLL, "PrintStop");
	char* a = "dynload";
	convert(a);
	FreeLibrary(hinstDLL);
	//convert(a); // qu'arrive-t’il?
}