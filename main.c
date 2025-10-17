#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#pragma warning(disable: 4996 6031)

enum {
	MAX_ETUDIANTS = 100,
	NB_UE = 6, NB_SEMESTRES = 6,
	MAX_CHAR = 31, NB_ANNEE =3
};
const float NOTE_MIN = 0.f, NOTE_MAX = 20.f;

typedef enum {S1,S2,B1,S3,S4,B2,S5,S6,B3} Annee; //pour definir chaque semestre et annee
typedef enum { ADM,AJ } Code;

typedef struct {
	char prenom[MAX_CHAR];
	char nom[MAX_CHAR];
	float notes[NB_SEMESTRES+ NB_ANNEE][NB_UE];
	Code codes[NB_SEMESTRES + NB_ANNEE][NB_UE];
	char etat[MAX_CHAR];
	Annee ans;
} Etudiant;

typedef struct {
	int nbEtudiants;
	Etudiant etudiants[MAX_ETUDIANTS];
	//float notes[MAX_ETUDIANTS][MAX_UE];
} Promotion;

void CURSUS(Etudiant* etudiant, int id);
void NOTE(Etudiant* etudiant, int ue, float note);

int main() {
	Promotion p;
	p.nbEtudiants = 0;
	
	char cde[MAX_CHAR] = " ";
	do {
		scanf("%s", cde);
		if (strcmp(cde, "INSCRIRE") == 0) // C1
		{
		} // TODO
		else if (strcmp(cde, "NOTE") == 0) {// C2
			int nb,competence;
			float note;
			scanf("%u", &nb);
			scanf("%u", &competence);
			scanf("%f", &note);
			if (nb > p.nbEtudiants)
				printf("Identifiant incorrect");
			else
				NOTE(&p.etudiants[nb], competence, note);
		} // TODO
		else if (strcmp(cde, "CURSUS") == 0) {// C3
			int nb;
			scanf("%u", &nb);
			if (nb > p.nbEtudiants)
				printf("Identifiant incorrect");
			else
				CURSUS(&p.etudiants[nb], nb);
		} // TODO
		else if (strcmp(cde, "ETUDIANTS") == 0) // C4
		{
		} // TODO
		else if (strcmp(cde, "DEMISSION") == 0) // C5
		{
		} // TODO
		else if (strcmp(cde, "DEFAILLANCE") == 0) // C6
		{
		} // TODO
		else if (strcmp(cde, "JURY") == 0) // C7
		{
		} // TODO
		else if (strcmp(cde, "BILAN") == 0) // C8
		{
		 } // TODO
	} while (strcmp(cde, "EXIT") != 0); // C0
}

void Init_tabNotes(Promotion* promo, int nb) {
	Etudiant *etu  = &promo->etudiants[nb];
	for (Annee s = S1; s <= B3; ++s){
		for (int i = 0; i < NB_UE; ++i) {
			etu->notes[s][i] = -1;
		}
	}
}

void NOTE(Etudiant* etudiant, int ue, float note) {

}

void CURSUS(Etudiant *etudiant, int id) {
	printf("%u %s %s \n", id, etudiant->nom, etudiant->prenom);
	Annee semestre = etudiant->ans; 
	Annee s = S1;
	for (; s <= semestre; ++s) {
		for (int i = 0; i < NB_UE; ++i) {
			float note = etudiant->notes[s][i];
			Code c = etudiant->codes[s][i];
			if (note == -1)
				printf("* - ");
			else
				printf("%.1f - ", floorf(note * 10.f) / 10.f);
			switch (c) {
			case ADM:
				printf("(ADM) - ");
				break;
			case AJ:
				printf("(AJ) - ");
				break;
			default:
				printf("(*) - ");
			}
		}
	}
	printf("%s \n", etudiant->etat);
}
