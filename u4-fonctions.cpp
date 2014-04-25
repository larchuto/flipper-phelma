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

void InitialiserPieBB(struct Boule* pie, float x, float y, float rayon)
{
	pie->X = x;
    pie->Y = y;
	pie->rayon=rayon;
}

void InitialiserOBB(struct Obb* obb, float x, float y, float tailleX, float tailleY, float angle)
{
	obb->X=x;
	obb->Y=y;
	obb->TX=tailleX;
	obb->TY=tailleY;
	obb->angle=angle;
}
// Initialiser
void InitialiserDonnees()
{
    // On initialise le generateur de nombres aleatoires
    //srand(time(NULL));

    // On initialise la boule
    gDonnees.Boule.X = L_ZONE-RAYON_BOULE-6;
    gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-50;
	gDonnees.Boule.rayon=RAYON_BOULE;
    gDonnees.Boule.VX = 0 ;
    gDonnees.Boule.VY = 0 ;

    // On initialise le score et le nombre de billes
    gDonnees.Valeur = 0 ;
    gDonnees.Valeur2 = 1 ;
    gInterface.Nb_billes->value(gDonnees.Valeur2) ;

    //Bumpers
	InitialiserPieBB(&gDonnees.Pieh,214,215,211);
	InitialiserPieBB(&gDonnees.Bp1,115+25,98+25,25);
	InitialiserPieBB(&gDonnees.Bp2,265+25,98+25,25);
	InitialiserPieBB(&gDonnees.Bp3,189+25,163+25,25);

	//Lanceur
	InitialiserOBB(&gDonnees.Lanceur,L_ZONE-31-3-1,H_ZONE-433/2,8,433,0);

	//Pentes
	InitialiserOBB(&gDonnees.PenteG,58,529,135,20,-35.0/180*3.14159);
	InitialiserOBB(&gDonnees.PenteD,354,542,94,20,35.0/180*3.14159);

	//Triangles
		//gauche
	InitialiserPieBB(&gDonnees.TriGC1,73,403,10);
	InitialiserPieBB(&gDonnees.TriGC2,111,501,10);
	InitialiserPieBB(&gDonnees.TriGC3,76,474,12.5);
	InitialiserOBB(&gDonnees.TriGL1,64+5,437.5,10,75,0);
	InitialiserOBB(&gDonnees.TriGL2,87.5+4,494,10,42,54.5/180*3.14159);
	InitialiserOBB(&gDonnees.TriGL3,98,451,10,105,21.25/180*3.14159);
		//droit
	InitialiserPieBB(&gDonnees.TriDC1,355,403,10);
	InitialiserPieBB(&gDonnees.TriDC2,317,501,10);
	InitialiserPieBB(&gDonnees.TriDC3,352.5,474,12.5);
	InitialiserOBB(&gDonnees.TriDL1,360,437.5,10,75,0);
	InitialiserOBB(&gDonnees.TriDL2,340,493,10,42,-54.5/180*3.14159);
	InitialiserOBB(&gDonnees.TriDL3,332,451,10,105,-21.25/180*3.14159);
	//Flipper gauche
//L(120,560,179,601) L(111,582,170,615)

//Flipper droit
//L(309,560,250,601) L(318,582,259,615)
	//Flip
		//gauche
	InitialiserPieBB(&gDonnees.FliGC1,115,571,12);
	InitialiserPieBB(&gDonnees.FliGC2,175,608,8.5);
	InitialiserOBB(&gDonnees.FliGL1,150,585,67,7,-35.0/180*3.14159);
	InitialiserOBB(&gDonnees.FliGL2,142,596,67,7,-29.2/180*3.14159);
		//droit
	InitialiserPieBB(&gDonnees.FliDC1,314,571,12);
	InitialiserPieBB(&gDonnees.FliDC2,254,608,8.5);
	InitialiserOBB(&gDonnees.FliDL1,279,585.5,67,7,35.0/180*3.14159);
	InitialiserOBB(&gDonnees.FliDL2,290-3.5,597,65,7,29.0/180*3.14159);
	/*gDonnees.Flip.X=100-20;
	gDonnees.Flip.Y=550-20;
	gDonnees.Flip.TX=100;
	gDonnees.Flip.TY=20;
	gDonnees.Flip.angle=0;*/

	
    // Exemple son
    //JouerSon("media/r2d2.mp3");
}

void rotation(float angle, float* x, float* y)
{
	float xtmp=*x;
	float ytmp=*y;
	*x=xtmp*cos(angle)+ytmp*sin(angle);
	*y=ytmp*cos(angle)-xtmp*sin(angle);
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
bool Touche_pie_int(struct Boule pie,struct Boule bille,float* ximp,float* yimp)
{
	float dist=pie.rayon-bille.rayon;
	/*if(bille.X<pie.X-dist || bille.X>pie.X+dist || bille.Y<pie.Y-dist || bille.Y>pie.Y+dist)
	{
		return false;
	}*/
	if(((bille.X-pie.X)*(bille.X-pie.X)+(bille.Y-pie.Y)*(bille.Y-pie.Y))<(dist*dist))
	{
		return false;
	}
	*ximp=bille.X+(pie.X-bille.X)*bille.rayon/dist;
	*yimp=bille.Y+(pie.Y-bille.Y)*bille.rayon/dist;
	return true;
}
bool Touche_aabb(struct Obb barre,struct Boule bille,float* ximp,float* yimp)
{
	float x1loc=-barre.TX/2;
	float y1loc=-barre.TY/2;
	float x2loc=+barre.TX/2;
	float y2loc=+barre.TY/2;
	float x1=barre.X+x1loc;
	float x2=barre.X+x2loc;
	float y1=barre.Y+y1loc;
	float y2=barre.Y+y2loc;


	if(bille.X<=x1-bille.rayon
	|| bille.X>=x2+bille.rayon
	|| bille.Y<=y1-bille.rayon
	|| bille.Y>=y2+bille.rayon)
	{
		return false;
	}
	if(bille.X>=x1 && bille.X<=x2)
	{
		if(bille.Y<=barre.Y)
		{
			*ximp=bille.X;
			*yimp=y1-bille.rayon;
			return true;

		}
		if(bille.Y>=barre.Y)
		{
			*ximp=bille.X;
			*yimp=y2+bille.rayon;
			return true;
		}
	}
	if(bille.Y>=y1 && bille.Y<=y2)
	{
		if(bille.X<=barre.X)
		{
			*ximp=x1-bille.rayon;
			*yimp=bille.Y;
			return true;
		}
		if(bille.X>=barre.X)
		{
			*ximp=x2+bille.rayon;
			*yimp=bille.Y;
			return true;
		}
	}
	if((bille.X-x1)*(bille.X-x1)+(bille.Y-y1)*(bille.Y-y1)<bille.rayon*bille.rayon)
	{
		*ximp=x1;
		*yimp=y1;
		return true;
	}
	if((bille.X-x2)*(bille.X-x2)+(bille.Y-y2)*(bille.Y-y2)<bille.rayon*bille.rayon)
	{
		*ximp=x2;
		*yimp=y2;
		return true;
	}
	if((bille.X-x1)*(bille.X-x1)+(bille.Y-y2)*(bille.Y-y2)<bille.rayon*bille.rayon)
	{
		*ximp=x1;
		*yimp=y2;
		return true;
	}
	if((bille.X-x2)*(bille.X-x2)+(bille.Y-y1)*(bille.Y-y1)<bille.rayon*bille.rayon)
	{
		*ximp=x2;
		*yimp=y1;
		return true;
	}
	return false;
}

bool Touche_obb(struct Obb barre,struct Boule bille, float* ximp,float* yimp)
{
	struct Boule bille_loc=bille;
	bille_loc.X=bille.X-barre.X;
	bille_loc.Y=bille.Y-barre.Y;
	rotation(-barre.angle,&(bille_loc.X),&(bille_loc.Y));
	bille_loc.X=bille_loc.X+barre.X;
	bille_loc.Y=bille_loc.Y+barre.Y;
	bool retour=Touche_aabb(barre,bille_loc,ximp,yimp);
	*ximp-=barre.X;
	*yimp-=barre.Y;
	rotation(barre.angle,ximp,yimp);
	*ximp+=barre.X;
	*yimp+=barre.Y;
	return retour;
}

void Rebond(Boule *bille,float ximp,float yimp)
{
	float ux=(bille->X-ximp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
	float uy=(bille->Y-yimp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
  	float prod_scal = (bille->VX *ux + bille->VY *uy);
  	bille->VX = (bille->VX -2*prod_scal*ux);
  	bille->VY = (bille->VY -2*prod_scal*uy);
}

void DeplacerBouleAvecRebonds()
{
	//bool rebond=false;
    if ( gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-5)
    {
        gDonnees.Boule.X = L_ZONE-RAYON_BOULE-5 ;
        gDonnees.Boule.VX = -1*COEFF_PERTES*gDonnees.Boule.VX ;
        //gDonnees.Boule.VY = 1*COEFF_PERTES*gDonnees.Boule.VY;
        //gravite =0;
        //rebond=true;
    }
    if ( gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46
	&& gDonnees.Boule.X<=L_ZONE-RAYON_BOULE-4 
	&& gDonnees.Boule.X>=L_ZONE-RAYON_BOULE-8)
    {
        gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-46 ;
        gDonnees.Boule.VY = -1 /**COEFF_PERTES*/* gDonnees.Boule.VY ;
        gDonnees.Boule.VX = 1*COEFF_PERTES*gDonnees.Boule.VX;

    }
    if ( gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE)
    {
	//perdu !
	/*
        gDonnees.Boule.Y = H_ZONE-RAYON_BOULE ;
        gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        if (gDonnees.Boule.VY < -1,0 )
        {
        gDonnees.Valeur = gDonnees.Valeur + 1 ;
        gInterface.Score->value(gDonnees.Valeur) ;
        //JouerSon("media/Sons/bips/bip6.mp3");
        }
        //gDonnees.Boule.VY = -1*COEFF_PERTES*gDonnees.Boule.VY ;
        gDonnees.Boule.VX = 1*COEFF_PERTES*gDonnees.Boule.VX;
        //gravite =0;
        //rebond=true;
	*/
    	gDonnees.Boule.X = L_ZONE-RAYON_BOULE-6;
    	gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-50;
	gDonnees.Boule.VX=0;
	gDonnees.Boule.VY=0;
        gDonnees.Valeur2 = gDonnees.Valeur2 + 1 ;
        gInterface.Nb_billes->value(gDonnees.Valeur2) ;
    }

    if ( gDonnees.Boule.X <= RAYON_BOULE+5)
    {
        gDonnees.Boule.X = RAYON_BOULE+5 ;
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
	bool rebond=
	//Touche_aabb(gDonnees.Barre,gDonnees.Boule,&ximp,&yimp)
	Touche_obb(gDonnees.PenteG,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.PenteD,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.Bp1,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.Bp2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.Bp3,gDonnees.Boule,&ximp,&yimp)
	|| (Touche_pie_int(gDonnees.Pieh,gDonnees.Boule,&ximp,&yimp)&&gDonnees.Boule.Y<215-RAYON_BOULE)
	|| Touche_obb(gDonnees.Lanceur,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.TriGC1,gDonnees.Boule,&ximp,&yimp)
    || Touche_pie(gDonnees.TriGC2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.TriGC3,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriGL1,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriGL2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriGL3,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.TriDC1,gDonnees.Boule,&ximp,&yimp)
    || Touche_pie(gDonnees.TriDC2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.TriDC3,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriDL1,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriDL2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriDL3,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.FliGC1,gDonnees.Boule,&ximp,&yimp)
    || Touche_pie(gDonnees.FliGC2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.FliGL1,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.FliGL2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.FliDC1,gDonnees.Boule,&ximp,&yimp)
    || Touche_pie(gDonnees.FliDC2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.FliDL1,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.FliDL2,gDonnees.Boule,&ximp,&yimp);

	if(rebond)
	{
		Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
		// Nouvelle position de la boule ...
    gDonnees.Boule.VX = gDonnees.Boule.VX;
    gDonnees.Boule.VY = gDonnees.Boule.VY + sin(INCLINAISON)*gravite*DUREE_CYCLE;
	gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY + sin(INCLINAISON)/2*gravite*DUREE_CYCLE*DUREE_CYCLE;
    gravite=GRAVITE;
/*
	if(Touche_aabb(gDonnees.Barre,gDonnees.Boule,&ximp,&yimp))
	{
        //gDonnees.Boule.Y = yimp;//250-RAYON_BOULE ;
        //gDonnees.Boule.X = ximp;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
        //rebond=true;
	}
	if(Touche_obb(gDonnees.los,gDonnees.Boule,&ximp,&yimp))
	{
        //gDonnees.Boule.Y = yimp;//250-RAYON_BOULE ;
        //gDonnees.Boule.X = ximp;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
        //gDonnees.Boule.Y = yimp;
        //gDonnees.Boule.X = ximp;
        gravite =0;
        //rebond=true;
	}
	if(Touche_obb(gDonnees.PenteG,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_obb(gDonnees.PenteD,gDonnees.Boule,&ximp,&yimp))//
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_pie(gDonnees.Bp1,gDonnees.Boule,&ximp,&yimp))//
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_pie(gDonnees.Bp2,gDonnees.Boule,&ximp,&yimp))//
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_pie(gDonnees.Bp3,gDonnees.Boule,&ximp,&yimp))//
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_pie_int(gDonnees.Pieh,gDonnees.Boule,&ximp,&yimp)&&gDonnees.Boule.Y<215-RAYON_BOULE)//
	{
        //gDonnees.Boule.Y = 215;//-RAYON_BOULE;//318;//250-RAYON_BOULE ;
		//gDonnees.Boule.X = 215;//350;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
       	//gravite =0;
        //rebond=true;
    }
	if (Touche_obb(gDonnees.Lanceur,gDonnees.Boule,&ximp,&yimp))//
	{
        //gDonnees.Boule.Y = yimp;//250-RAYON_BOULE ;
        //gDonnees.Boule.X = ximp;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
        //gDonnees.Boule.Y = yimp;
        //gDonnees.Boule.X = ximp;
        gravite =0;
        //rebond=true;
	}/*
	if(Touche_obb(gDonnees.Flip,gDonnees.Boule,&ximp,&yimp))
	{
        //gDonnees.Boule.Y = yimp;//250-RAYON_BOULE ;
        //gDonnees.Boule.X = ximp;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
        //gDonnees.Boule.Y = yimp;
        //gDonnees.Boule.X = ximp;
        gravite =0;
        //rebond=true;
	}
	//test triangle gauche
	
	if(Touche_pie(gDonnees.TriGC1,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
    }
    if(Touche_pie(gDonnees.TriGC2,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
    }
    if(Touche_pie(gDonnees.TriGC3,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
    }
    if(Touche_obb(gDonnees.TriGL1,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_obb(gDonnees.TriGL2,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_obb(gDonnees.TriGL3,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}*/
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
