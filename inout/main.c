#include <stdio.h>

enum {
	MAX_ETUDIANTS = 100,
	MAX_CHAR = 31
};

typedef struct {
	char prenom[MAX_CHAR];
	char nom[MAX_CHAR];
} Etudiant;

typedef struct {
	int nbEtudiants;
	Etudiant etudiants[MAX_ETUDIANTS];
} Promotion;

int main() {
	Promotion p;
	p.nbEtudiants = 0;
	
	char cde[MAX_CHAR] = " "; // oups , ne serait - ce un nombre magique ?
	do {
		scanf(" % s ", cde);
		if (strcmp(cde, " INSCRIRE ") == 0) // C1
		{
		} // TODO
		else if (strcmp(cde, " NOTE ") == 0) // C2
		{
		} // TODO
		else if (strcmp(cde, " CURSUS ") == 0) // C3
		{
		} // TODO
		else if (strcmp(cde, " ETUDIANTS ") == 0) // C4
		{
		} // TODO
		else if (strcmp(cde, " DEMISSION ") == 0) // C5
		{
		} // TODO
		else if (strcmp(cde, " DEFAILLANCE ") == 0) // C6
		{
		} // TODO
		else if (strcmp(cde, " JURY ") == 0) // C7
		{
		} // TODO
		else if (strcmp(cde, " BILAN ") == 0) // C8
		{
		} // TODO
	} while (strcmp(cde, " EXIT ") != 0); // C0
}