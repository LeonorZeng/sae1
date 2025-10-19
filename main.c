#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <string.h>
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
} Promotion;

int Verifie_id(Promotion* promo, int id);

void INSCRIRE(Promotion *promo, char nom, char prenom);
void CURSUS(Etudiant* etudiant, int id);
void NOTE(Etudiant* etudiant, int ue, float note);
void ETUDIANTS(const Promotion* promo);
void DEFAILLANCE(Etudiant* etudiant, int id);
void DEMISSION(Etudiant* etudiant, int id);

int main() {
	Promotion p;
	p.nbEtudiants = 0;
	
	char cde[MAX_CHAR] = " ";
	do {
		scanf("%s", cde);
		if (strcmp(cde, "INSCRIRE") == 0){ // C1 
			char nom[MAX_CHAR];
			char prenom[MAX_CHAR];
			scanf("%s %s", nom, prenom);
			INSCRIRE(&p, nom, prenom);
		}

		else if (strcmp(cde, "NOTE") == 0) { // C2
			int nb,competence;
			float note;
			//Des scanf pour recuperer les valeurs envoyer par l'utilisateur
			scanf("%u", &nb);
			scanf("%u", &competence);
			scanf("%f", &note);
			//Test pour voir si l'etudiant est enregistrer
			if (Verifie_id(&p, nb)){
			//Test pour voir si l'etudiant etudit toujours à l'IUT
				if (strcmp(p.etudiants[nb].etat, "en cours") != 0)
					printf("Etudiant hors formation");
				else
					NOTE(&p.etudiants[nb-1], competence, note);  // -1 car tableau commence à 0 alors que les identifiants à 1
			}
		}

		else if (strcmp(cde, "CURSUS") == 0) {// C3
			int nb;
			scanf("%u", &nb);
			//Test pour voir si l'etudiant est enregistrer
			//Peut-être creer une fonction pour ça
			if (Verifie_id(&p, nb))
				CURSUS(&p.etudiants[nb-1], nb-1);
		}

		else if (strcmp(cde, "ETUDIANTS") == 0) { // C4
			ETUDIANTS(&p);
		}

		else if (strcmp(cde, "DEMISSION") == 0) { // C5
			int nb;
			scanf("%d", &nb);
			if (Verifie_id(&p, nb))
				DEMISSION(&p.etudiants[nb - 1], nb-1);
		}
	
		else if (strcmp(cde, "DEFAILLANCE") == 0) { // C6
			int nb;
			scanf("%d", &nb);
			DEFAILLANCE(&p.etudiants[nb-1], nb - 1);
		}

		else if (strcmp(cde, "JURY") == 0) { // C7
		
		} // TODO
		else if (strcmp(cde, "BILAN") == 0) { // C8
		
		 } // TODO
	} while (strcmp(cde, "EXIT") != 0); // C0
}


//verifie que l'identifiant utilisateur est correct
int Verifie_id(Promotion* promo, int id) {
	if (id < 1 || id > promo->nbEtudiants){
		printf("Identifiant incorrect\n");
		return 0;
	}
	else
		return 1;
}


//initilialise le tableau de note d'un etudiant avec la valeur -1
void Init_tabNotes(Promotion* promo, int nb) {
	Etudiant* etu = &promo->etudiants[nb];
	for (Annee s = S1; s <= B3; ++s) {
		for (int i = 0; i < NB_UE; ++i) {
			etu->notes[s][i] = -1.f;
		}
	}
}

//inscrit un etudiant dans la promo
void INSCRIRE(Promotion *promo, char nom, char prenom) {
	for (int i = 0; i < promo->nbEtudiants; ++i) {
		if (strcmp(promo->etudiants[i].nom, nom) == 0 && strcmp(promo->etudiants[i].prenom, prenom) == 0)
			printf("Nom incorrect\n");
	}

	//if (Verifie_prenomEtnom(promo, nom, prenom)){
		Etudiant *e = &promo->etudiants[promo->nbEtudiants];

		//remplie la structure etudiant
		strcpy(e->nom, nom);
		strcpy(e->prenom, prenom);
		e->ans = S1;
		strcpy(e->etat, "en cours");
		Init_tabNotes(promo, (*promo).nbEtudiants);


		promo->nbEtudiants+=1; //incremente le compteur d'etudiant
		printf("Inscription enregistree (%d)\n", promo->nbEtudiants);
	//}
}

//ajoute la note d'un etudiant pour une UE
void NOTE(Etudiant *etudiant, int ue, float note) {
	//Verifie si la note et l'UE donner sont correctes (peut-être le mettre dans le main)
	if (ue < 1 || ue > NB_UE)
		printf("UE incorrecte");
	else if (note < NOTE_MIN || note > NOTE_MAX)
		printf("Note incorrecte");
	else {
		etudiant->notes[etudiant->ans][ue-1] = note;
		printf("Note enregistree");
	}
}

//permet de voir tout le cursus d'un etudiant donc toutes ses notes depuis la premiere annee
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

void ETUDIANTS(const Promotion *promo) {
	for (int i = 0; i < promo->nbEtudiants; ++i) {
		const Etudiant e = promo->etudiants[i];
		printf("%d %s %s %s\n", (i + 1), e.nom, e.prenom, e.etat);
	}
}

//
void DEMISSION(Etudiant* etudiant, int id) {
	if (strcmp(etudiant->etat, "en cours") != 0)
		printf("Etudiant hors formation\n");
	else{
		strcpy(etudiant->etat, "demission");
		printf("Demission enregistree\n");
	}
}

//declare qu'un etudiant est defaillant
void DEFAILLANCE(Etudiant* etudiant, int id) {
	if (strcmp(etudiant->etat, "en cours") != 0)
		printf("Etudiant hors formation\n");

	strcpy(etudiant->etat, "defaillance");
	printf("Defaillance enregistree\n");
}
