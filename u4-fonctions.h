// u4-fonctions.h
// Sentinelle d'inclusion
#ifndef _u4_fonctions_h
#define _u4_fonctions_h

// Definition des constantes
#define DUREE_CYCLE 0.015    // 0.500 secondes, depend du materiel utilise
#define RAYON_BOULE  12
//#include "aabb.h"

// Declaration des donnees du projet

// Structure de definition de la boule
struct Boule
{
    float X;
    float Y;
    float VX;
    float VY;
	float rayon;
} ;
struct Obb
{
	float X;
	float Y;
	float TX;
	float TY;
	float angle;
};

// Structure globale pour les variables fonctionnelles
struct Donnees
{
    struct Boule    Boule ;
    unsigned int    Valeur ;
    unsigned int    Valeur2 ;

	struct Obb Barre;
	struct Obb los;
	struct Boule Pie;
	struct Boule Pieh;
	struct Obb haut;
	struct Obb Flip;
	struct Obb Lanceur;
	struct Boule Bp1;
	struct Boule Bp2;
	struct Boule Bp3;
	struct Obb PenteG;
	struct Obb PenteD;
};


extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserDonnees() ;
void rotation(float angle, float* x, float* y);
bool Touche_pie(struct Pie barre,struct Boule bille,float* ximp,float* yimp);
bool Touche_aabb(struct Obb barre,struct Boule bille,float* ximp,float* yimp);
bool Touche_obb(struct Obb barre,struct Boule bille,float* ximp,float* yimp);
void Rebond(Boule* bille,float ximp,float yimp);
//void Rebond(float* VX,float* VY,float ux,float uy);
void DeplacerBouleAvecRebonds() ;
// Utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
