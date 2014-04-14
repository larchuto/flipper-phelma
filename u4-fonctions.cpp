// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
#include <stdlib.h>     // exit, rand
#include <time.h>       // time
#include <string.h>     // strcpy
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
// Programmes locaux
#include "u1-interface.h"
#include "u4-fonctions.h"
#include "u5-parametres.h"
#include "u2-dessin.h"
#include <math.h>


// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;

// Initialiser
void InitialiserDonnees()
{
    // On initialise le generateur de nombres aleatoires
    //srand(time(NULL));
    // Initialisation de Rebond
    //gDonnees.Rebond = 0 ;
    // On initialise la boule
//
    gDonnees.Boule.X = L_ZONE-RAYON_BOULE;
    gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-5;
    gDonnees.Boule.VX = 0 ;
    gDonnees.Boule.VY = 0 ;
	gDonnees.Barre.X=200;
	gDonnees.Barre.Y=300;
	gDonnees.Barre.TX=100;
	gDonnees.Barre.TY=100;
    // Exemple son
    // JouerSon("media/r2d2.mp3");
}


bool Touche_aabb(struct Aabb barre,struct Boule bille)
{
	float x1=barre.X-barre.TX/2;
	float x2=barre.X+barre.TX/2;
	float y1=barre.Y-barre.TY/2;
	float y2=barre.Y+barre.TY/2;
    /*if ((bille.X>=x1 && bille.X<=x2) && (bille.Y>=y1 && bille.Y<=y2))
    {
        return true;
    }*/
    //return false;
	if(bille.X<x1-RAYON_BOULE
	|| bille.X>x2+RAYON_BOULE
	|| bille.Y<y1-RAYON_BOULE
	|| bille.Y>y2+RAYON_BOULE)
	{
		return false;
	}
	if(bille.X>=x1 && bille.X<=x2)
	{
		if(bille.Y>=y1-RAYON_BOULE || bille.Y<=y2+RAYON_BOULE)
		{
			return true;
		}
	}
	if(bille.Y>=y1 && bille.Y<=y2)
	{
		if(bille.X>=x1-RAYON_BOULE || bille.X<=x2+RAYON_BOULE)
		{
			return true;
		}
	}
	if((bille.X-x1)*(bille.X-x1)+(bille.Y-y1)*(bille.Y-y1)>RAYON_BOULE*RAYON_BOULE
	|| (bille.X-x2)*(bille.X-x2)+(bille.Y-y2)*(bille.Y-y2)>RAYON_BOULE*RAYON_BOULE
	|| (bille.X-x1)*(bille.X-x1)+(bille.Y-y2)*(bille.Y-y2)>RAYON_BOULE*RAYON_BOULE
	|| (bille.X-x2)*(bille.X-x2)+(bille.Y-y1)*(bille.Y-y1)>RAYON_BOULE*RAYON_BOULE)
	{
		return false;
	}
	return true;
}

void DeplacerBouleAvecRebonds()
{


    if ( gDonnees.Boule.X >= L_ZONE-RAYON_BOULE)
    {
        gDonnees.Boule.X = L_ZONE-RAYON_BOULE ;
        gDonnees.Boule.VX = -1 *COEFF_PERTES* gDonnees.Boule.VX ;
    }

    if ( gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE)
    {
        gDonnees.Boule.Y = H_ZONE-RAYON_BOULE ;
        gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
    }

    if ( gDonnees.Boule.X <= RAYON_BOULE)
    {
        gDonnees.Boule.X = RAYON_BOULE ;
        gDonnees.Boule.VX = -1*COEFF_PERTES * gDonnees.Boule.VX ;
    }

    if ( gDonnees.Boule.Y <= RAYON_BOULE)
    {
        gDonnees.Boule.Y = RAYON_BOULE ;
        gDonnees.Boule.VY = -1*COEFF_PERTES * gDonnees.Boule.VY ;
    }
	if(Touche_aabb(gDonnees.Barre,gDonnees.Boule))
	{
        gDonnees.Boule.Y = 250-RAYON_BOULE ;
        gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
	}
    // Nouvelle position de la boule ...
    gDonnees.Boule.VX = gDonnees.Boule.VX;
    gDonnees.Boule.VY = gDonnees.Boule.VY + sin(INCLINAISON)*GRAVITE*DUREE_CYCLE;
    gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY - sin(INCLINAISON)/2*GRAVITE*DUREE_CYCLE*DUREE_CYCLE;

}

// Utilitaires

// Joue le fichier son passe en parametre, mp3, etc...
void JouerSon(char * FichierSon)
{
    // Musique de fond
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    result = FMOD_System_GetVersion(system, &version);
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    result = FMOD_System_CreateSound(system, FichierSon, FMOD_SOFTWARE, 0, &sound);
    result = FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds )
{
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}
