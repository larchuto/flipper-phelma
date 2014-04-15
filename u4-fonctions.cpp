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
float gravite= GRAVITE;

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
	gDonnees.Boule.rayon=RAYON_BOULE;
    gDonnees.Boule.VX = 0 ;
    gDonnees.Boule.VY = 0 ;
	gDonnees.Barre.X=200;
	gDonnees.Barre.Y=300;
	gDonnees.Barre.TX=100;
	gDonnees.Barre.TY=100;
    gDonnees.Pie.X = 350;
    gDonnees.Pie.Y = 350;
	gDonnees.Pie.rayon=20;
    // Exemple son
    // JouerSon("media/r2d2.mp3");
}
bool Touche_pie(struct Boule pie,struct Boule bille,float* ximp,float* yimp)
{
	float dist=pie.rayon+bille.rayon;
	if(bille.X<pie.X-dist || bille.X>pie.X+dist || bille.Y<pie.Y-dist || bille.Y>pie.Y+dist)
	{
		return false;
	}
	if(((bille.X-pie.X)*(bille.X-pie.X)+(bille.Y-pie.Y)*(bille.Y-pie.Y))>(dist*dist))
	{
		return false;
	}
	*ximp= bille.X+(pie.X-bille.X)*bille.rayon/dist;
	*yimp= bille.Y+(pie.Y-bille.Y)*bille.rayon/dist;
	return true;	
}

bool Touche_aabb(struct Aabb barre,struct Boule bille,float* ximp,float* yimp)
{
	float x1=barre.X-barre.TX/2;
	float x2=barre.X+barre.TX/2;
	float y1=barre.Y-barre.TY/2;
	float y2=barre.Y+barre.TY/2;

	if(bille.X<x1-bille.rayon
	|| bille.X>x2+bille.rayon
	|| bille.Y<y1-bille.rayon
	|| bille.Y>y2+bille.rayon)
	{
		return false;
	}
	if(bille.X>=x1 && bille.X<=x2)
	{
		if(bille.Y>=y1-bille.rayon)
		{
			*ximp=bille.X;
			*yimp=y1-bille.rayon;
			return true;
			
		}
		if(bille.Y<=y2+bille.rayon)
		{
			*ximp=bille.X;
			*yimp=y2+bille.rayon;
			return true;
		}
	}
	if(bille.Y>=y1 && bille.Y<=y2)
	{
		if(bille.X>=x1-bille.rayon)
		{
			*ximp=x1-bille.rayon;
			*yimp=bille.Y;
			return true;
		}
		if(bille.X<=x2+bille.rayon)
		{
			*ximp=x2+bille.rayon;
			*yimp=bille.Y;
			return true;
		}
	}
	if((bille.X-x1)*(bille.X-x1)+(bille.Y-y1)*(bille.Y-y1)<=bille.rayon*bille.rayon)
	{
		*ximp=x1;
		*yimp=y1;
		return true;
	}
	if((bille.X-x2)*(bille.X-x2)+(bille.Y-y2)*(bille.Y-y2)<=bille.rayon*bille.rayon)
	{
		*ximp=x2;
		*yimp=y2;
		return true;
	}
	if((bille.X-x1)*(bille.X-x1)+(bille.Y-y2)*(bille.Y-y2)<=bille.rayon*bille.rayon)
	{
		*ximp=x1;
		*yimp=y2;
		return true;
	}
	if((bille.X-x2)*(bille.X-x2)+(bille.Y-y1)*(bille.Y-y1)<=bille.rayon*bille.rayon)
	{
		*ximp=x2;
		*yimp=y1;
		return true;
	}
	return false;
}
void Rebond(Boule *bille,float ximp,float yimp)
{
	float ux=(bille->X-ximp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
	float uy=(bille->Y-yimp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
  	float prod_scal = (bille->VX *ux + bille->VY *uy);
  	bille->VX = bille->VX -2*prod_scal*ux;
  	bille->VY = bille->VY -2*prod_scal*uy;
}
/*void Rebond(float* VX,float* VY,float ux,float uy)
{
  	float prod_scal = (VX *ux+ VY *uy);
  	VX = VX -2*prod_scal*ux;
  	VY = VY -2*prod_scal*uy;
}*/

void DeplacerBouleAvecRebonds()
{
	//bool rebond=false;
    if ( gDonnees.Boule.X >= L_ZONE-RAYON_BOULE)
    {
        gDonnees.Boule.X = L_ZONE-RAYON_BOULE ;
        gDonnees.Boule.VX = -1*COEFF_PERTES*gDonnees.Boule.VX ;
        //gDonnees.Boule.VY = 1*COEFF_PERTES*gDonnees.Boule.VY;
        //gravite =0;
        //rebond=true;
    }

    if ( gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE)
    {
        gDonnees.Boule.Y = H_ZONE-RAYON_BOULE ;
        gDonnees.Boule.VY = -1*COEFF_PERTES*gDonnees.Boule.VY ;
        gDonnees.Boule.VX = 1*COEFF_PERTES*gDonnees.Boule.VX;
        //gravite =0;
        //rebond=true;
    }

    if ( gDonnees.Boule.X <= RAYON_BOULE)
    {
        gDonnees.Boule.X = RAYON_BOULE ;
        gDonnees.Boule.VX = -1*COEFF_PERTES*gDonnees.Boule.VX ;
        //gDonnees.Boule.VY = 1*COEFF_PERTES*gDonnees.Boule.VY;
        //gravite =0;
        //rebond=true;
    }

    if ( gDonnees.Boule.Y <= RAYON_BOULE)
    {
        gDonnees.Boule.Y = RAYON_BOULE ;
        gDonnees.Boule.VY = -1*COEFF_PERTES*gDonnees.Boule.VY ;
        gDonnees.Boule.VX = 1*COEFF_PERTES*gDonnees.Boule.VX;
        //gravite =0;
        //rebond=true;
    }
	float ximp;
	float yimp;
	if(Touche_aabb(gDonnees.Barre,gDonnees.Boule,&ximp,&yimp))
	{
        //gDonnees.Boule.Y = yimp;//250-RAYON_BOULE ;
        //gDonnees.Boule.X = ximp;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
        //rebond=true;
	}
	if(Touche_pie(gDonnees.Pie,gDonnees.Boule,&ximp,&yimp))
	{
        //gDonnees.Boule.Y = yimp;//-RAYON_BOULE;//318;//250-RAYON_BOULE ;
		//gDonnees.Boule.X = ximp;//350;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
        //rebond=true;
	}
	    // Nouvelle position de la boule ...
    gDonnees.Boule.VX = gDonnees.Boule.VX;
    gDonnees.Boule.VY = gDonnees.Boule.VY + sin(INCLINAISON)*gravite*DUREE_CYCLE;
	gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY + sin(INCLINAISON)/2*gravite*DUREE_CYCLE*DUREE_CYCLE;
    gravite=GRAVITE;
    

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
