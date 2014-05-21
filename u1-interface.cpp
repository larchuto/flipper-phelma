// u1-interface.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream> // cin, cout, ...
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"
#include "u5-parametres.h"

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees de l'interface - structure globale de variables
struct Interface gInterface ;

// CreerInterface
void CreerInterface()
{
	// Creation de la fenetre principale
	gInterface.Fenetre = new Fl_Double_Window(720,690);
	gInterface.Fenetre->label("Flipper Phelma") ;
	gInterface.Fenetre->begin() ;

	// Creation de la zone de score
	gInterface.Imagescore= new Fl_GIF_Image("media/score.gif") ;
	gInterface.ZoneScore = new DrawingArea(X_SCORE,Y_SCORE,L_SCORE,H_SCORE);
	gInterface.ZoneScore->draw_callback( ZoneScoreDessinerCB, NULL ) ;
	gInterface.ZoneScore->keyboard_callback( ZoneDessinClavierCB, NULL) ;

	// Creation de la zone de menu
	gInterface.Imagemenu= new Fl_GIF_Image("media/menu.gif") ;
	gInterface.ZoneMenu = new DrawingArea(X_MENU,Y_MENU,L_MENU,H_MENU);
	gInterface.ZoneMenu->draw_callback( ZoneMenuDessinerCB, NULL ) ;
	gInterface.ZoneMenu->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

	// Creation de la zone de dessin
	gInterface.Imagefond= new Fl_GIF_Image("media/fond.gif") ;
	gInterface.Imagedecor= new Fl_GIF_Image("media/decor.gif") ;
	gInterface.Imagebille= new Fl_GIF_Image("media/bille.gif") ;
	gInterface.Imagevert= new Fl_GIF_Image("media/vert.gif") ;
	gInterface.Imagerouge= new Fl_GIF_Image("media/rouge.gif") ;
	gInterface.Imagebleu= new Fl_GIF_Image("media/bleu.gif") ;
	gInterface.Imagebip[1-1]= new Fl_GIF_Image("media/bip1.gif") ;
	gInterface.Imagebip[2-1]= new Fl_GIF_Image("media/bip2.gif") ;
	gInterface.Imagebip[3-1]= new Fl_GIF_Image("media/bip3.gif") ;
	gInterface.Imagebip[4-1]= new Fl_GIF_Image("media/bip4.gif") ;
	gInterface.Imagebip[5-1]= new Fl_GIF_Image("media/bip5.gif") ;
	gInterface.Imagebip[6-1]= new Fl_GIF_Image("media/bip6.gif") ;
	gInterface.Imagebip[7-1]= new Fl_GIF_Image("media/bip7.gif") ;
	gInterface.Imagetriangleg= new Fl_GIF_Image("media/triangle_gauche.gif") ;
	gInterface.Imagetriangled= new Fl_GIF_Image("media/triangle_droit.gif") ;
	gInterface.Imageteleporteur= new Fl_GIF_Image("media/teleporteur.gif") ;
	gInterface.Imageflipg= new Fl_GIF_Image("media/flipperg.gif") ;
	gInterface.Imageflipd= new Fl_GIF_Image("media/flipperd.gif") ;
	gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
	gInterface.Imagetrou= new Fl_GIF_Image("media/trounoir.gif");
	gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
	//gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
	gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

	// Creation du bouton Quitter
	gInterface.BoutonQuitter = new Fl_Button(485, 620, 200, 40, "Quitter") ;
	gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

	// Creation du bouton MeilleursScores
	gInterface.BoutonMeilleursScores = new Fl_Button(485, 620-45, 200, 40, "Meilleurs Scores") ;
	gInterface.BoutonMeilleursScores->callback( BoutonMeilleursScoresCB, NULL ) ;

	// Creation du bouton NouvellePartie
	gInterface.BoutonNouvellePartie = new Fl_Button(485, 620-90, 200, 40, "Nouvelle Partie") ;
	gInterface.BoutonNouvellePartie->callback( BoutonNouvellePartieCB, NULL ) ;

	// Affichage de la fenetre
	gInterface.Fenetre->end();
	gInterface.Fenetre->show();
}

/*
void ActualiserInterface()
{
	// Actualisation de Rebond
	//gInterface.CaseRebond->value( gDonnees.Rebond ) ;
}*/
