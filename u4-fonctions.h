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
struct Flip
{
	struct Boule C1;
	struct Boule C2;
	struct Obb L1;
	struct Obb L2;
};

// Structure globale pour les variables fonctionnelles
struct Donnees
{
    struct Boule    Boule ;
    unsigned int    Valeur ;
    unsigned int    Valeur2 ;

	//struct Obb Barre;
	struct Boule Pieh;
	//struct Obb Flip;
	struct Obb Lanceur;
	struct Boule Bp1;
	struct Boule Bp2;
	struct Boule Bp3;
	struct Obb PenteG;
	struct Obb PenteD;
	//Triangle Gauche
	struct Boule TriGC1;
	struct Boule TriGC2;
	struct Boule TriGC3;
	struct Obb TriGL1;
	struct Obb TriGL2;
	struct Obb TriGL3;
	//Triangle Droit
	struct Boule TriDC1;
	struct Boule TriDC2;
	struct Boule TriDC3;
	struct Obb TriDL1;
	struct Obb TriDL2;
	struct Obb TriDL3;
	//Flip Gauche
	struct Flip FlipG;
	//Flip Droit
	struct Flip FlipD;

};


extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserPieBB(struct Boule* pie, float x, float y, float rayon);
void InitialiserOBB(struct Obb* obb, float x, float y, float tailleX, float tailleY, float angle);
void InitialiserDonnees();
void rotation(float angle, float* x, float* y);
bool Touche_pie(struct Pie barre,struct Boule bille,float* ximp,float* yimp);
bool Touche_aabb(struct Obb barre,struct Boule bille,float* ximp,float* yimp);
bool Touche_obb(struct Obb barre,struct Boule bille,float* ximp,float* yimp);
void MoveFlip(struct Flip* flip, float angle);
void Rebond(Boule* bille,float ximp,float yimp);
//void Rebond(float* VX,float* VY,float ux,float uy);
void DeplacerBouleAvecRebonds() ;
// Utilitaires
void JouerSon(char *) ;         // Jouer un son
void Attente(double Seconds);   // Procedure d'attente

#endif // _u4_fonctions_h
