// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream> // cout, cin, ...
#include <stdlib.h> // exit, rand
#include <time.h> // time
#include <string.h> // strcpy
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
// Programmes locaux
#include "u1-interface.h"
#include "u4-fonctions.h"
#include "u5-parametres.h"
#include "u2-dessin.h"
#include <math.h>

//to clean
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H> // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser


// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;
float gravite= GRAVITE;
int temp=0 , temp1=0 ,temp2=0, temp3=0, temp4=0, temp5=0, temp6=0, temp_portails=0;
int ballispushed=0, ballintrounoir=0, temptrounoir;

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
	srand(time(NULL));

	// On initialise la boule
	gDonnees.Boule.X = L_ZONE-RAYON_BOULE-6;
	gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-47;
	gDonnees.Boule.rayon=RAYON_BOULE;
	gDonnees.Boule.VX = 0 ;
	gDonnees.Boule.VY = 0 ;

	// On initialise le score et le nombre de billes
	gDonnees.Valeur = 0 ;
	gDonnees.Valeur2 = 1 ;
	gInterface.Nb_billes->value(gDonnees.Valeur2) ;
	
	//courbe haut du plateau
	InitialiserPieBB(&gDonnees.Pieh,214,215,211);

	//Bumpers
	InitialiserPieBB(&gDonnees.Bp1,115+25,98+25+30,25);
	InitialiserPieBB(&gDonnees.Bp2,265+25,98+25+30,25);
	InitialiserPieBB(&gDonnees.Bp3,189+25,163+25+30,25);

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
/*
	//Flip
		//gauche
	InitialiserPieBB(&gDonnees.FlipG.C1,115,571,12);
	InitialiserPieBB(&gDonnees.FlipG.C2,175,608,8.5);
	InitialiserOBB(&gDonnees.FlipG.L1,150,585,67,7,-35.0/180*3.14159);
	InitialiserOBB(&gDonnees.FlipG.L2,142,596,67,7,-29.2/180*3.14159);
	gDonnees.FlipG.angle=0;
		//droit
	InitialiserPieBB(&gDonnees.FlipD.C1,314,571,12);
	InitialiserPieBB(&gDonnees.FlipD.C2,254,608,8.5);
	InitialiserOBB(&gDonnees.FlipD.L1,279,585.5,67,7,35.0/180*3.14159);
	InitialiserOBB(&gDonnees.FlipD.L2,290-3.5,597,65,7,29.0/180*3.14159);
	gDonnees.FlipD.angle=0;
*/
	//Flip
		//gauche
	InitialiserPieBB(&gDonnees.FlipG.C1,115,571,12);
	InitialiserPieBB(&gDonnees.FlipG.C2,175,608,8.5);
	InitialiserOBB(&gDonnees.FlipG.L1,150-3,585+2,67,12,-35.0/180*3.14159);
	//InitialiserOBB(&gDonnees.FlipG.L2,142+3,596-2,67,12,-29.2/180*3.14159);
	InitialiserOBB(&gDonnees.FlipG.L2,142,596,67,7,-29.2/180*3.14159);
	InitialiserOBB(&gDonnees.FlipG.L3,150-3-14,585+2+21,67,12+50,-35.0/180*3.14159);
	gDonnees.FlipG.angle=0;
		//droit
	InitialiserPieBB(&gDonnees.FlipD.C1,314,571,12);
	InitialiserPieBB(&gDonnees.FlipD.C2,254,608,8.5);
	InitialiserOBB(&gDonnees.FlipD.L1,279+3,585.5+2,67,12,35.0/180*3.14159);
	//InitialiserOBB(&gDonnees.FlipD.L2,290-3.5-3,597-2,65,12,29.0/180*3.14159);
	InitialiserOBB(&gDonnees.FlipD.L2,290-3.5,597,65,7,29.0/180*3.14159);
	InitialiserOBB(&gDonnees.FlipD.L3,279+3+14,585.5+2+19,67,12+50,35.0/180*3.14159);
	gDonnees.FlipD.angle=0;

	//Ressort
	InitialiserOBB(&gDonnees.Ressort,L_ZONE-12-6,H_ZONE-20.5-6,24,41,0);
	gDonnees.CompressionRessort=0;

	//Teleporteurs
	InitialiserPieBB(&gDonnees.PortailG,38.5,239+30,8);
	InitialiserPieBB(&gDonnees.PortailD,346,271+30,8);

	//Trou Noir
	InitialiserPieBB(&gDonnees.TrouNoir,214,104,1);

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
			*yimp=y1;//-bille.rayon;
			return true;
		}

		if(bille.Y>=barre.Y)
		{
			*ximp=bille.X;
			*yimp=y2;//+bille.rayon;
			return true;
		}
	}

	if(bille.Y>=y1 && bille.Y<=y2)
	{
		if(bille.X<=barre.X)
		{
			*ximp=x1;//-bille.rayon;
			*yimp=bille.Y;
			return true;
		}

		if(bille.X>=barre.X)
		{
			*ximp=x2;//+bille.rayon;
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
	/*
	// /!\ experimental
	if(abs(bille.VX*DUREE_CYCLE)>barre.TX)
	{
	if(bille.X<=x1)
	{
	*ximp=x1;
	*yimp=bille.Y;
	}
	else
	{
	*ximp=x2;
	*yimp=bille.Y;
	}
	return true;
	}
	if(abs(bille.VY*DUREE_CYCLE)>barre.TY)
	{
	if(bille.Y<=y1)
	{
	*ximp=bille.X;
	*yimp=y1;
	}
	else
	{
	*ximp=bille.X;
	*yimp=y2;
	}
	return true;
	}*/
	return false;
}

void MoveFlip(struct Flip* flip, float angle)
{
	flip->angle+=angle;
	float x0loc=flip->C1.X;
	float y0loc=flip->C1.Y;
	flip->L1.angle+=angle;
	flip->L2.angle+=angle;
	flip->L3.angle+=angle;
	flip->C2.X-=x0loc;
	flip->C2.Y-=y0loc;
	rotation(angle,&(flip->C2.X),&(flip->C2.Y));
	flip->C2.X+=x0loc;
	flip->C2.Y+=y0loc;
	flip->L1.X-=x0loc;
	flip->L1.Y-=y0loc;
	rotation(angle,&(flip->L1.X),&(flip->L1.Y));
	flip->L1.X+=x0loc;
	flip->L1.Y+=y0loc;
	flip->L2.X-=x0loc;
	flip->L2.Y-=y0loc;
	rotation(angle,&(flip->L2.X),&(flip->L2.Y));
	flip->L2.X+=x0loc;
	flip->L2.Y+=y0loc;
	flip->L3.X-=x0loc;
	flip->L3.Y-=y0loc;
	rotation(angle,&(flip->L3.X),&(flip->L3.Y));
	flip->L3.X+=x0loc;
	flip->L3.Y+=y0loc;
}

void ReplaceBille(struct Boule* bille, struct Obb obb)
{
	bille->X=bille->X-obb.X;
	bille->Y=bille->Y-obb.Y;
	rotation(-obb.angle,&(bille->X),&(bille->Y));

	if(2*bille->X>=-obb.TX && 2*bille->X<=obb.TX && bille->Y<=obb.Y-obb.TY/2)
	{
	   
			bille->Y=-obb.TY/2-bille->rayon;
	}
	rotation(obb.angle,&(bille->X),&(bille->Y));
	bille->X=bille->X+obb.X;
	bille->Y=bille->Y+obb.Y;
}

void CompressionRessort()
{
	if(gDonnees.Ressort.TY>11)
	{
		gDonnees.Ressort.TY-=10;
		gDonnees.Ressort.Y+=5;
		gDonnees.CompressionRessort+=1;
		//gDonnees.Boule.Y+=9;
		if(gDonnees.Boule.Y==gDonnees.Ressort.Y-gDonnees.Ressort.TY/2-gDonnees.Boule.rayon && L_ZONE-gDonnees.Boule.rayon-8)
		{
			gDonnees.Boule.Y-=10;
		}
	}
	DessineRessort(gDonnees.CompressionRessort);
}

void RelachementRessort()
{
	if(gDonnees.Boule.X >=L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-2*RAYON_BOULE-46)
	{
		gDonnees.Boule.VY=-1000-75*float(gDonnees.CompressionRessort);//-10*float(gDonnees.CompressionRessort)/DUREE_CYCLE/COEFF_PERTES*PIXEL_TO_M;//-10*float(gDonnees.CompressionRessort)/DUREE_CYCLE; //5000-6000 //1000 //1200
		gDonnees.Boule.Y=H_ZONE-41-6-RAYON_BOULE-10;
	}
	gDonnees.CompressionRessort=0;
	InitialiserOBB(&gDonnees.Ressort,L_ZONE-12-6,H_ZONE-20.5-6,24,41,0);
	//gDonnees.Boule.Y=100;//H_ZONE-20.5-6-RAYON_BOULE;
	//DessineRessort(gDonnees.CompressionRessort);
	//Display_OBB(gDonnees.Ressort);
}

bool Touche_obb(struct Obb barre,struct Boule bille, float* ximp,float* yimp)
{
	struct Boule bille_loc=bille;
	bille_loc.X=bille.X-barre.X;
	bille_loc.Y=bille.Y-barre.Y;
	rotation(-barre.angle,&(bille_loc.X),&(bille_loc.Y));
	bille_loc.X=bille_loc.X+barre.X;
	bille_loc.Y=bille_loc.Y+barre.Y;
	//bool retour=Touche_aabb(barre,bille_loc,ximp,yimp);

	if (Touche_aabb(barre,bille_loc,ximp,yimp))
	{
		*ximp-=barre.X;
		*yimp-=barre.Y;
		rotation(barre.angle,ximp,yimp);
		*ximp+=barre.X;
		*yimp+=barre.Y;
		return true;
	}

	return false;
	//return retour;
}

void Rebond(Boule *bille,float ximp,float yimp)
{
	float ux=(bille->X-ximp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
	float uy=(bille->Y-yimp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
	float prod_scal = (bille->VX *ux + bille->VY *uy);
	//à tester voir comportement avec les ronds
	bille->X = ximp+bille->rayon*(bille->X-ximp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
	bille->Y = yimp+bille->rayon*(bille->Y-yimp)/sqrt((bille->X-ximp)*(bille->X-ximp)+(bille->Y-yimp)*(bille->Y-yimp));
	bille->VX = (bille->VX -2*prod_scal*ux);
	bille->VY = (bille->VY -2*prod_scal*uy);
}

void PushBall(struct Flip* Flip, struct Boule* bille)
{
	float ximp, yimp;
	if((Touche_obb(Flip->L1,*bille,&ximp,&yimp)
	&& Touche_obb(Flip->L3,*bille,&ximp,&yimp)))
	{
		ReplaceBille(bille,Flip->L3);
		Rebond(bille,ximp,yimp);
		float coeff_gain=((Flip->C1.X-ximp)*(Flip->C1.X-ximp)+(Flip->C1.Y-yimp)*(Flip->C1.Y-yimp))/((Flip->C1.X-Flip->C2.X)*(Flip->C1.X-Flip->C2.X)+(Flip->C1.Y-Flip->C2.Y)*(Flip->C1.Y-Flip->C2.Y)+Flip->C2.rayon);
		bille->VX+=PROPULSIONFLIP*sin(Flip->L1.angle)*coeff_gain;
		bille->VY-=PROPULSIONFLIP*cos(Flip->L1.angle)*coeff_gain;
	}
	ballispushed=1;
}

void TrouNoir(struct Boule* bille)
{
	//gDonnees.AfficherBille=0;
	ballintrounoir=1;
	temptrounoir+=1;
	bille->X=214;
	bille->Y=104;
	int sortie=rand()%4;
	float anglesortie=float(rand()%361)/180*3.14159;
	cout<<sortie<<endl;
cout<<anglesortie<<endl;
	if(sortie=1 || temptrounoir>TROUNOIR_NBRCYCLEMAX)
	{
		ballintrounoir=0;
		temptrounoir=0;
		bille->VX=cos(anglesortie)*TROUNOIRVITESSE;
		bille->VY=sin(anglesortie)*TROUNOIRVITESSE;
		//gDonnees.AfficherBille=1;
	}

}

void DeplacerBouleAvecRebonds()
{
	if ( gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-5)
	{
		gDonnees.Boule.X = L_ZONE-RAYON_BOULE-5 ;
		gDonnees.Boule.VX = -1*COEFF_PERTES*gDonnees.Boule.VX ;
	}


	if ( gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE)
	{
		//perdu !
		gDonnees.Boule.X = L_ZONE-RAYON_BOULE-6;
		gDonnees.Boule.Y = gDonnees.Boule.Y=H_ZONE-47-RAYON_BOULE;
		gDonnees.Boule.VX=0;
		gDonnees.Boule.VY=0;
		gDonnees.Valeur2 = gDonnees.Valeur2 + 1 ;
		gInterface.Nb_billes->value(gDonnees.Valeur2) ;

		if (gDonnees.Valeur2==4)
		{
            // On initialise la boule
            gDonnees.Boule.X = L_ZONE-RAYON_BOULE-6;
            gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-47;
            gDonnees.Boule.rayon=RAYON_BOULE;
            gDonnees.Boule.VX = 0 ;
            gDonnees.Boule.VY = 0 ;

            // On initialise le score et le nombre de billes
            gDonnees.Valeur = 0 ;
            gDonnees.Valeur2 = 1 ;
            gInterface.ValueScore->value(gDonnees.Valeur) ;
            gInterface.Nb_billes->value(gDonnees.Valeur2) ;

            fl_message("Baaaah! T'as perdu!");

		}

	}

	if ( gDonnees.Boule.X <= RAYON_BOULE+5)
	{
		gDonnees.Boule.X = RAYON_BOULE+5 ;
		gDonnees.Boule.VX = -1*COEFF_PERTES*gDonnees.Boule.VX ;
	}

	if ( gDonnees.Boule.Y <= RAYON_BOULE)
	{
		gDonnees.Boule.Y = RAYON_BOULE ;
		gDonnees.Boule.VY = -1*COEFF_PERTES*gDonnees.Boule.VY ;
		gDonnees.Boule.VX = 1*COEFF_PERTES*gDonnees.Boule.VX;
	}
	float pertes=COEFF_PERTES;
	float ximp;
	float yimp;
	bool rebond=
		Touche_obb(gDonnees.PenteG,gDonnees.Boule,&ximp,&yimp)
		|| Touche_obb(gDonnees.PenteD,gDonnees.Boule,&ximp,&yimp)
		|| (gDonnees.Boule.Y<215-RAYON_BOULE&&Touche_pie_int(gDonnees.Pieh,gDonnees.Boule,&ximp,&yimp))
		|| Touche_obb(gDonnees.Lanceur,gDonnees.Boule,&ximp,&yimp)
		|| Touche_obb(gDonnees.Ressort,gDonnees.Boule,&ximp,&yimp)
		//|| Touche_obb(gDonnees.FlipG.L2,gDonnees.Boule,&ximp,&yimp)
		//|| Touche_obb(gDonnees.FlipD.L2,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.FlipG.C1,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.FlipG.C2,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.FlipD.C1,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.FlipD.C2,gDonnees.Boule,&ximp,&yimp);
		if (gDonnees.Boule.Y<215-RAYON_BOULE&&Touche_pie_int(gDonnees.Pieh,gDonnees.Boule,&ximp,&yimp))
		{
			pertes=0.6;
		}
	//flips
	if(Touche_obb(gDonnees.FlipG.L3,gDonnees.Boule,&ximp,&yimp))
	{
		//ReplaceBille(&(gDonnees.Boule),gDonnees.FlipG.L3);
	}
	if(Touche_obb(gDonnees.FlipD.L3,gDonnees.Boule,&ximp,&yimp))
	{
		//ReplaceBille(&(gDonnees.Boule),gDonnees.FlipD.L3);	
	}
	if((Touche_pie(gDonnees.FlipG.C1,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.FlipG.C2,gDonnees.Boule,&ximp,&yimp)
		|| (Touche_obb(gDonnees.FlipG.L1,gDonnees.Boule,&ximp,&yimp) && Touche_obb(gDonnees.FlipG.L3,gDonnees.Boule,&ximp,&yimp)))
		//|| Touche_obb(gDonnees.FlipG.L2,gDonnees.Boule,&ximp,&yimp))
		&& !ballispushed)
	{
		rebond=true;
	}
	if((Touche_pie(gDonnees.FlipD.C1,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.FlipD.C2,gDonnees.Boule,&ximp,&yimp)
		|| (Touche_obb(gDonnees.FlipD.L1,gDonnees.Boule,&ximp,&yimp) && Touche_obb(gDonnees.FlipD.L3,gDonnees.Boule,&ximp,&yimp)))
		//|| Touche_obb(gDonnees.FlipD.L2,gDonnees.Boule,&ximp,&yimp))
		&& !ballispushed)
	{
		rebond=true;
	}
	ballispushed=0;

	//Gestion Trou Noir
	if (Touche_pie(gDonnees.TrouNoir,gDonnees.Boule,&ximp,&yimp))
	{
		TrouNoir(&(gDonnees.Boule));
	}
	//Gestion bumpers
        if(Touche_pie(gDonnees.Bp1,gDonnees.Boule,&ximp,&yimp))
        {
                rebond=true;
                gDonnees.Valeur += SCORE_BUMPER ;
                gInterface.ValueScore->value(gDonnees.Valeur) ;
                temp=1;
        }

        if(Touche_pie(gDonnees.Bp2,gDonnees.Boule,&ximp,&yimp))
        {
                rebond=true;
                gDonnees.Valeur += SCORE_BUMPER ;
                gInterface.ValueScore->value(gDonnees.Valeur) ;
                temp1=1;
        }
        if(Touche_pie(gDonnees.Bp3,gDonnees.Boule,&ximp,&yimp))
        {
                rebond=true;
                gDonnees.Valeur += SCORE_BUMPER ;
                gInterface.ValueScore->value(gDonnees.Valeur) ;
                temp2=1;
	}
	if (temp<NB_CYCLE_ALLUMAGE && temp>0)
	{
		gInterface.Imagevert->draw(115+20, 98+20+30, 50, 50);
		temp+=1;
		temp%=NB_CYCLE_ALLUMAGE;
	}
	if (temp1<NB_CYCLE_ALLUMAGE && temp1>0)
	{
		gInterface.Imagebleu->draw(265+20, 98+20+30, 50, 50);
		temp1+=1;
		temp1%=NB_CYCLE_ALLUMAGE;
	}
	if (temp2<NB_CYCLE_ALLUMAGE && temp2>0)
	{
		gInterface.Imagerouge->draw(190+20, 163+20+30, 50, 50);
		temp2+=1;
		temp2%=NB_CYCLE_ALLUMAGE;
	}

	//Gestion Teleporteurs
	if(Touche_pie(gDonnees.PortailG,gDonnees.Boule,&ximp,&yimp) && temp_portails==0)
	{
		gDonnees.Boule.X=gDonnees.PortailD.X;
		gDonnees.Boule.Y=gDonnees.PortailD.Y;
                gDonnees.Valeur += SCORE_TELEPORTEUR ;
                gInterface.ValueScore->value(gDonnees.Valeur) ;
		temp_portails=1;
	}
	if(Touche_pie(gDonnees.PortailD,gDonnees.Boule,&ximp,&yimp) && temp_portails==0)
	{
		gDonnees.Boule.X=gDonnees.PortailG.X;
		gDonnees.Boule.Y=gDonnees.PortailG.Y;
                gDonnees.Valeur += SCORE_TELEPORTEUR ;
                gInterface.ValueScore->value(gDonnees.Valeur) ;
		temp_portails=1;
		
	}

	if(temp_portails!=0)
	{
		temp_portails+=1;
		temp_portails%=15;
		gInterface.Imageteleporteur->draw(21+20, 222+20+30, 35, 35);
		gInterface.Imageteleporteur->draw(329+20, 254+20+30, 35, 35);
	}


	//Gestion triangles
	if( Touche_pie(gDonnees.TriGC1,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.TriGC2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_pie(gDonnees.TriGC3,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriGL1,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriGL2,gDonnees.Boule,&ximp,&yimp)
	|| Touche_obb(gDonnees.TriGL3,gDonnees.Boule,&ximp,&yimp))
	{
		rebond=true;
		temp3=1;
                gDonnees.Valeur = gDonnees.Valeur + SCORE_TRIANGLE ;
                gInterface.ValueScore->value(gDonnees.Valeur) ;
	}

	if (temp3<NB_CYCLE_ALLUMAGE && temp3>0)
	{
		gInterface.Imagetriangleg->draw(64+20, 394+20, 58, 118);
		temp3+=1;
		temp3%=NB_CYCLE_ALLUMAGE;
	}

	if(Touche_pie(gDonnees.TriDC1,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.TriDC2,gDonnees.Boule,&ximp,&yimp)
		|| Touche_pie(gDonnees.TriDC3,gDonnees.Boule,&ximp,&yimp)
		|| Touche_obb(gDonnees.TriDL1,gDonnees.Boule,&ximp,&yimp)
		|| Touche_obb(gDonnees.TriDL2,gDonnees.Boule,&ximp,&yimp)
		|| Touche_obb(gDonnees.TriDL3,gDonnees.Boule,&ximp,&yimp))
	{
		rebond=true;
		temp4=1;
		gDonnees.Valeur = gDonnees.Valeur + SCORE_TRIANGLE ;
                gInterface.ValueScore->value(gDonnees.Valeur) ;
	}

	if (temp4<NB_CYCLE_ALLUMAGE && temp4>0)
	{
		gInterface.Imagetriangled->draw(308+20, 394+20, 58, 118);
		temp4+=1;
		temp4%=NB_CYCLE_ALLUMAGE;
	}

	float oldvx=gDonnees.Boule.VX;
	float oldvy=gDonnees.Boule.VY;

	// Nouvelle position de la boule ...
	if(rebond && !ballintrounoir)
	{
		Rebond(&(gDonnees.Boule),ximp,yimp);
		gDonnees.Boule.VY = gDonnees.Boule.VY + sin(INCLINAISON)*gravite*DUREE_CYCLE;
		gDonnees.Boule.X +=gDonnees.Boule.VX*DUREE_CYCLE;
		gDonnees.Boule.Y +=gDonnees.Boule.VY*DUREE_CYCLE + sin(INCLINAISON)/2*gravite*DUREE_CYCLE*DUREE_CYCLE;

	}
	else if (!ballintrounoir)
	{
		//gDonnees.Boule.Y += gDonnees.Boule.VY*DUREE_CYCLE + sin(INCLINAISON)*0.5*gravite*DUREE_CYCLE*DUREE_CYCLE;
		gDonnees.Boule.VY = gDonnees.Boule.VY + sin(INCLINAISON)*gravite*DUREE_CYCLE;
		gDonnees.Boule.X += gDonnees.Boule.VX*DUREE_CYCLE;
		gDonnees.Boule.Y += gDonnees.Boule.VY*DUREE_CYCLE + sin(INCLINAISON)/2*gravite*DUREE_CYCLE*DUREE_CYCLE;
		gravite=GRAVITE;
	}

		//gestion des pertes
	//on teste si la bille n'est simplement pas en train de rouler
	if (oldvx*oldvy*gDonnees.Boule.VX*gDonnees.Boule.VY<0 && rebond && !ballintrounoir)
	{
		gDonnees.Boule.VX *= pertes;
		gDonnees.Boule.VY *= pertes;
	}

	if(gDonnees.Boule.VX*DUREE_CYCLE>RAYON_BOULE)
	{
		gDonnees.Boule.VX=RAYON_BOULE/DUREE_CYCLE;
	}

	if(gDonnees.Boule.VY*DUREE_CYCLE>RAYON_BOULE)
	{
		gDonnees.Boule.VY=RAYON_BOULE/DUREE_CYCLE;
	}
}

// Utilitaires

// Joue le fichier son passe en parametre, mp3, etc...
void JouerSon(const char * FichierSon)
{
	// Musique de fond
	FMOD_SYSTEM *system;
	FMOD_SOUND *sound;
	FMOD_CHANNEL *channel = 0;
	FMOD_RESULT result;
	int key;
	unsigned int version;
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
