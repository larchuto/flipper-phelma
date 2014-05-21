// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream> // cin, cout, ...
#include <unistd.h>
#include <stdio.h>
// Librairies fltk
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H> // fonctions de dessin
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"
#include "u5-parametres.h"


// Declaration pour utiliser iostream
using namespace std;
int last_i_bip;

void Display_PieBB(struct Boule CBB)
{
	fl_color(FL_GREEN);
	fl_circle(CBB.X+20,CBB.Y+20,CBB.rayon);
}

void Display_OBB(struct Obb OBB)
{
	fl_color(FL_GREEN);
	fl_translate(OBB.X+20,OBB.Y+20);
	fl_rotate(OBB.angle/3.14159*180);
	fl_begin_loop();
	fl_vertex(-OBB.TX/2,OBB.TY/2);
	fl_vertex(OBB.TX/2,OBB.TY/2);
	fl_vertex(OBB.TX/2,-OBB.TY/2);
	fl_vertex(-OBB.TX/2,-OBB.TY/2);
	fl_end_loop();
	fl_rotate(-OBB.angle/3.14159*180);
	fl_translate(-OBB.X-20,-OBB.Y-20);
}

void DisplayCollisionBoxes()
{
	Display_PieBB(gDonnees.TriG.C1);
	Display_PieBB(gDonnees.TriG.C2);
	Display_PieBB(gDonnees.TriG.C3);
	Display_PieBB(gDonnees.Pieh);
	Display_PieBB(gDonnees.Bp1);
	Display_PieBB(gDonnees.Bp2);
	Display_PieBB(gDonnees.Bp3);
	Display_OBB(gDonnees.Lanceur);
	Display_OBB(gDonnees.TriG.L1);
	Display_OBB(gDonnees.TriG.L2);
	Display_OBB(gDonnees.TriG.L3);
	Display_OBB(gDonnees.PenteG);
	Display_OBB(gDonnees.PenteD);
	Display_PieBB(gDonnees.TriD.C1);
	Display_PieBB(gDonnees.TriD.C2);
	Display_PieBB(gDonnees.TriD.C3);
	Display_OBB(gDonnees.TriD.L1);
	Display_OBB(gDonnees.TriD.L2);
	Display_OBB(gDonnees.TriD.L3);
	Display_PieBB(gDonnees.FlipG.C1);
	Display_PieBB(gDonnees.FlipG.C2);
	Display_OBB(gDonnees.FlipG.L1);
	Display_OBB(gDonnees.FlipG.L2);
	Display_OBB(gDonnees.FlipG.L3);
	Display_PieBB(gDonnees.FlipD.C1);
	Display_PieBB(gDonnees.FlipD.C2);
	Display_OBB(gDonnees.FlipD.L1);
	Display_OBB(gDonnees.FlipD.L2);
	Display_OBB(gDonnees.FlipD.L3);
	Display_OBB(gDonnees.Ressort);
	Display_PieBB(gDonnees.PortailG);
	Display_PieBB(gDonnees.PortailD);
	Display_PieBB(gDonnees.TrouNoir);
}

void DessineRessort(unsigned int compression)
{
	compression=compression % 7;
	char path[] = "media/ressort0.gif";
	path[13]='0'+(char)compression;
	Fl_GIF_Image Imageressort(path) ;
	Imageressort.draw(421, 624+5*compression, 24, 41-5*compression);
}

void DessineFlip(struct Flip flip)
{
	fl_color(246,111,25);
	float x1=-flip.L1.TX/2,
		y1=-flip.L1.TY/2,
		x2= flip.L1.TX/2,
		y2=-flip.L1.TY/2,
		x3= flip.L2.TX/2,
		y3= flip.L2.TY/2,
		x4=-flip.L2.TX/2,
		y4= flip.L2.TY/2;
	rotation(flip.L1.angle,&x1,&y1);
	rotation(flip.L1.angle,&x2,&y2);
	rotation(flip.L2.angle,&x3,&y3);
	rotation(flip.L2.angle,&x4,&y4);
	x1+=flip.L1.X+20;
	y1+=flip.L1.Y+20;
	x2+=flip.L1.X+20;
	y2+=flip.L1.Y+20;
	x3+=flip.L2.X+20;
	y3+=flip.L2.Y+20;
	x4+=flip.L2.X+20;
	y4+=flip.L2.Y+20;
	fl_polygon(x1,y1,x2,y2,x3,y3,x4,y4);
	fl_pie(flip.C1.X+20-flip.C1.rayon,flip.C1.Y+20-flip.C1.rayon+1,2*flip.C1.rayon+1,2*flip.C1.rayon+1,0,360);
	fl_pie(flip.C2.X+20-flip.C2.rayon,flip.C2.Y+20-flip.C2.rayon+1,2*flip.C2.rayon+1,2*flip.C2.rayon+1,0,360);
}

void DessineEntier(int valeur, int posx, int posy)
{
	char valeurtxt[20];
	sprintf(valeurtxt, "%d", valeur);
	int longeur, hauteur;
	fl_color(FL_WHITE);
	fl_font(FL_HELVETICA_BOLD,30);   
	fl_measure(valeurtxt,longeur,hauteur);
	fl_draw(valeurtxt, float(posx-longeur), float(posy)); 
}

void ZoneScoreDessinerCB( Fl_Widget* widget, void* data )
{
		//Zone de score
	gInterface.Imagescore->draw(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);
	//dessin des points et du numéro de bille
	DessineEntier(gDonnees.NumBille,681,350);
	DessineEntier(gDonnees.Points,690,403);
}

void ZoneMenuDessinerCB( Fl_Widget* widget, void* data )
{
		//Zone de menu
	gInterface.Imagemenu->draw(X_MENU, Y_MENU, L_MENU, H_MENU);
}

void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
	
	gInterface.Imagescore->draw(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);
	gInterface.Imagemenu->draw(X_MENU, Y_MENU, L_MENU, H_MENU); //pourrais ne pas être affiché en permanence
	// On efface toute la zone ( en dessinant dessus l'image de fond )
	gInterface.Imagefond->draw(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
	//Attente(0.03); //wtf ?

	//dessin trou noir
	gInterface.Imagetrou->draw(115+20, 5+20, 200, 200);

	// On dessine la bille
	gInterface.Imagebille->draw(X_ZONE + gDonnees.Boule.X - RAYON_BOULE, Y_ZONE + gDonnees.Boule.Y - RAYON_BOULE);

	//dessin decors
	gInterface.Imagedecor->draw(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
	DessineFlip(gDonnees.FlipG);
	DessineFlip(gDonnees.FlipD);

	//dessin rampe de lancement
	if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113+20 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113-40*6)
	{
		int i_bip=((H_ZONE-RAYON_BOULE-46-113+20-int(gDonnees.Boule.Y))/40)%7;
		gInterface.Imagebip[i_bip]->draw(392+20, 457+20-40*i_bip, 9, 40);
		char path[]="media/Sons/bips/rampe/bip_1.mp3";
		path[26]=i_bip+'1';
		last_i_bip=i_bip;
	}

	//dessin ressort
	DessineRessort(gDonnees.CompressionRessort);

	//dessin bounding boxes
	//DisplayCollisionBoxes();
}
