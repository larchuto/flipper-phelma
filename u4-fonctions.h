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
struct Aabb
{
	int X;
	int Y;
	int TX;
	int TY;
};

// Structure globale pour les variables fonctionnelles
struct Donnees
{
	struct Boule Boule;
	struct Aabb Barre;
	struct Boule Pie;
};


extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserDonnees() ;
bool Touche_pie(struct Pie barre,struct Boule bille,float* ximp,float* yimp);
bool Touche_aabb(struct Aabb barre,struct Boule bille,float* ximp,float* yimp);
void DeplacerBouleAvecRebonds() ;
// Utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
