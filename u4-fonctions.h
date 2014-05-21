// u4-fonctions.h
// Sentinelle d'inclusion
#ifndef _u4_fonctions_h
#define _u4_fonctions_h

// Declaration des donnees du projet

// Structure de definition de la boule
struct Boule
{
    float X;
    float Y;
    float VX;
    float VY;
	float rayon;
};

// Structure de definition d'obstacles rectangulaires
struct Obb
{
	float X;
	float Y;
	float TX;
	float TY;
	float angle;
};

// Structure de definition des leviers
struct Flip
{
	struct Boule C1;
	struct Boule C2;
	struct Obb L1;
	struct Obb L2;
	struct Obb L3;
	float angle;
	bool isTouched;
};

// Structure de definition des triangles rebondissants
struct Triangle
{
	struct Boule C1;
	struct Boule C2;
	struct Boule C3;
	struct Obb L1;
	struct Obb L2;
	struct Obb L3;
};

// Structure globale pour les variables fonctionnelles
struct Donnees
{
    struct Boule Boule ;
    unsigned int Points ;
    unsigned int NumBille ;
    unsigned int CompressionRessort;
    int score[5];
 	char nom[5][20];

	struct Boule Pieh;
	struct Boule Bp1;
	struct Boule Bp2;
	struct Boule Bp3;
	struct Boule PortailG;
	struct Boule PortailD;
	struct Boule TrouNoir;
	struct Obb PenteG;
	struct Obb PenteD;
	struct Obb Ressort;
	struct Obb Lanceur;

	//Triangle
		//Gauche
	struct Triangle TriG;
		//Droit
	struct Triangle TriD;

	//Flip
		//Gauche
	struct Flip FlipG;
		//Droit
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
void PushBall(struct Flip* Flip, struct Boule* bille);
void DeplacerBouleAvecRebonds();

// Utilitaires
void JouerSon(const char *) ; // Jouer un son
void Attente(double Seconds); // Procedure d'attente
void CompressionRessort();
void RelachementRessort();
void InitialiserScore();
void SaveBestScores();
void ChargeBestScores();

#endif // _u4_fonctions_h

