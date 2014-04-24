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
    gDonnees.Boule.X = L_ZONE-RAYON_BOULE-5;
    gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-50;
	gDonnees.Boule.rayon=RAYON_BOULE;
    gDonnees.Boule.VX = 0 ;
    gDonnees.Boule.VY = 0 ;

    // On initialise Valeur
    gDonnees.Valeur = 0 ;
    gDonnees.Valeur2 = 1 ;
    gInterface.Nb_billes->value(gDonnees.Valeur2) ;

	gDonnees.Barre.X=200;
	gDonnees.Barre.Y=300;
	gDonnees.Barre.TX=100;
	gDonnees.Barre.TY=100;
	gDonnees.Barre.angle=0;

    	gDonnees.Pie.X = 350;
    	gDonnees.Pie.Y = 350;
	gDonnees.Pie.rayon=20;
	gDonnees.los.X=300-20;
	gDonnees.los.Y=550-20;
	gDonnees.los.TX=50*sqrt(2);
	gDonnees.los.TY=50*sqrt(2);
	gDonnees.los.angle=0.7853975;
	gDonnees.haut.X=430-20;
	gDonnees.haut.Y=55-20;
	gDonnees.haut.TX=10;
	gDonnees.haut.TY=100;
	gDonnees.haut.angle=-0.78;
	gDonnees.Pieh.X = 215;//-2*RAYON_BOULE;
    	gDonnees.Pieh.Y = 220;//-2*RAYON_BOULE;
	gDonnees.Pieh.rayon=210;
	gDonnees.Flip.X=100-20;
	gDonnees.Flip.Y=550-20;
	gDonnees.Flip.TX=100;
	gDonnees.Flip.TY=20;
	gDonnees.Flip.angle=0;
	gDonnees.Lanceur.X=L_ZONE-31-2;//+20;
	gDonnees.Lanceur.Y=H_ZONE-433/2;//399;//+20;//H_ZONE-433/2-20;
	gDonnees.Lanceur.TX=5;
	gDonnees.Lanceur.TY=433;
	gDonnees.Bp1.X = 115+25;//+0.5?
    	gDonnees.Bp1.Y = 98+25;//+0.5?
	gDonnees.Bp1.rayon=25;
	gDonnees.Bp2.X = 265+25;//+0.5?
    	gDonnees.Bp2.Y = 98+25;//+0.5?
	gDonnees.Bp2.rayon=25;
	gDonnees.Bp3.X = 189+25;//+0.5?
    	gDonnees.Bp3.Y = 163+25;//+0.5?
	gDonnees.Bp3.rayon=25;
	gDonnees.PenteG.X=66;
	gDonnees.PenteG.Y=530;
	gDonnees.PenteG.TX=135;
	gDonnees.PenteG.TY=20;
	gDonnees.PenteG.angle=-35.0/180*3.14159;
	gDonnees.PenteD.X=354;
	gDonnees.PenteD.Y=540;
	gDonnees.PenteD.TX=100;
	gDonnees.PenteD.TY=20;
	gDonnees.PenteD.angle=35.0/180*3.14159;
	//Triangle gauche
	gDonnees.TriGC1.X=73;
	gDonnees.TriGC1.Y=403;
	gDonnees.TriGC1.rayon=10;
	gDonnees.TriGC2.X=111;
	gDonnees.TriGC2.Y=501;
	gDonnees.TriGC2.rayon=10;
	gDonnees.TriGC3.X=76;
	gDonnees.TriGC3.Y=474;
	gDonnees.TriGC3.rayon=12.5;
	/*
	gDonnees.TriGL1.X;
	gDonnees.TriGL1.Y;
	gDonnees.TriGL1.TX;
	gDonnees.TriGL1.TY;
	gDonnees.TriGL1.angle;
	gDonnees.TriGL2.X;
	gDonnees.TriGL2.Y;
	gDonnees.TriGL2.TX;
	gDonnees.TriGL2.TY;
	gDonnees.TriGL2.angle;
	gDonnees.TriGL3.X;
	gDonnees.TriGL3.Y;
	gDonnees.TriGL3.TX;
	gDonnees.TriGL3.TY;
	gDonnees.TriGL3.angle;
	*/
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
	//float xlocb=bille.X-barre.X;
	//float ylocb=bille.Y-barre.Y;
	//rotation(0,&(xlocb),&(ylocb));
	//bille.X=xlocb+barre.X;
	//bille.Y=xlocb+barre.Y;
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
		if(bille.Y>=barre.Y)
		{
			*ximp=bille.X;
			*yimp=y1-bille.rayon;
			return true;

		}
		if(bille.Y<=barre.Y)
		{
			*ximp=bille.X;
			*yimp=y2+bille.rayon;
			return true;
		}
	}
	if(bille.Y>=y1 && bille.Y<=y2)
	{
		if(bille.X>=barre.X)
		{
			*ximp=x1-bille.rayon;
			*yimp=bille.Y;
			return true;
		}
		if(bille.X<=barre.X)
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
	//rotation(-0,ximp,yimp);
	//rotation(-0,&(xlocb),&(ylocb));
	//bille.X=xlocb+barre.X;
	//bille.Y=ylocb+barre.Y;
}
/*
bool Touche_aabb(struct Obb barre,struct Boule bille,float* ximp,float* yimp)
{
	float x1loc=-barre.TX/2;
	float y1loc=-barre.TY/2;
	float x2loc=+barre.TX/2;
	float y2loc=+barre.TY/2;
	//float xlocb=bille.X-barre.X;
	//float ylocb=bille.Y-barre.Y;
	//rotation(0,&(xlocb),&(ylocb));
	//bille.X=xlocb+barre.X;
	//bille.Y=xlocb+barre.Y;
	float x1=barre.X+x1loc;
	float x2=barre.X+x2loc;
	float y1=barre.Y+y1loc;
	float y2=barre.Y+y2loc;


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
	//rotation(-0,ximp,yimp);
	//rotation(-0,&(xlocb),&(ylocb));
	//bille.X=xlocb+barre.X;
	//bille.Y=ylocb+barre.Y;
}*/

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
/*void Rebond(float* VX,float* VY,float ux,float uy)
{
  	float prod_scal = (VX *ux+ VY *uy);
  	VX = VX -2*prod_scal*ux;
  	VY = VY -2*prod_scal*uy;
}*/

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
    	gDonnees.Boule.X = L_ZONE-RAYON_BOULE-5;
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
	if(Touche_obb(gDonnees.PenteD,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
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
	if(Touche_pie(gDonnees.Bp1,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_pie(gDonnees.Bp2,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_pie(gDonnees.Bp3,gDonnees.Boule,&ximp,&yimp))
	{
        Rebond(&(gDonnees.Boule),ximp,yimp);
        gravite =0;
	}
	if(Touche_pie_int(gDonnees.Pieh,gDonnees.Boule,&ximp,&yimp)&&gDonnees.Boule.Y<215-RAYON_BOULE)
	{
        //gDonnees.Boule.Y = 215;//-RAYON_BOULE;//318;//250-RAYON_BOULE ;
		//gDonnees.Boule.X = 215;//350;
        //gDonnees.Boule.VY = -1 *COEFF_PERTES* gDonnees.Boule.VY ;
        Rebond(&(gDonnees.Boule),ximp,yimp);
       	//gravite =0;
        //rebond=true;
    }
	if(Touche_obb(gDonnees.haut,gDonnees.Boule,&ximp,&yimp))
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
	if (Touche_obb(gDonnees.Lanceur,gDonnees.Boule,&ximp,&yimp))
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
