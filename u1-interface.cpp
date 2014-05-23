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
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>

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
	gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
	gInterface.Imagetrou= new Fl_GIF_Image("media/trounoir.gif");
	gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
	gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
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

	// Création de l'interface sonore: chargement de tous les sons et musique

    //Création du système de son : 60 sons possibles en même temps
    FMOD_System_Create(&gInterface.system);
    FMOD_System_Init(gInterface.system, 12, FMOD_INIT_NORMAL, NULL);

    //Création et chargement des sons
    //Sons de la rampe
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bip_1.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bip_1);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bip_2.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bip_2);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bip_3.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bip_3);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bip_4.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bip_4);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bip_5.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bip_5);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bip_6.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bip_6);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bip_7.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bip_7);
    //Son des collisions classiques
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/collision.mp3", FMOD_CREATESAMPLE, 0, &gInterface.collision);
    //Meilleur score
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/meilleurs_scores.mp3", FMOD_CREATESAMPLE, 0, &gInterface.meilleurs_scores);
    //Son des triangles
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/triangle.mp3", FMOD_CREATESAMPLE, 0, &gInterface.triangle);
    //Son du trou noir
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/trounoir.mp3", FMOD_CREATESAMPLE, 0, &gInterface.trounoir);
    //Son des bumpers
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/bumper.mp3", FMOD_CREATESAMPLE, 0, &gInterface.bumper);
    //Son du téléporteur
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/teleporteur.mp3", FMOD_CREATESAMPLE, 0, &gInterface.teleporteur);

    //Chargement de la musique
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/MusicScore1.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &gInterface.music1);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/MusicScore2.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &gInterface.music2);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/MusicScore3.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &gInterface.music3);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/MusicScore4.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &gInterface.music4);
    FMOD_System_CreateSound(gInterface.system, "media/Sons/listsons/Trololosong.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &gInterface.music5);

    FMOD_Sound_SetLoopCount(gInterface.music1, -1);
    FMOD_Sound_SetLoopCount(gInterface.music2, -1);
    FMOD_Sound_SetLoopCount(gInterface.music3, -1);
    FMOD_Sound_SetLoopCount(gInterface.music4, -1);
    FMOD_System_GetChannel(gInterface.system,1, &gInterface.channelmusic1);
    FMOD_System_GetChannel(gInterface.system,2, &gInterface.channelmusic2);
    FMOD_System_GetChannel(gInterface.system,3, &gInterface.channelmusic3);
    FMOD_System_GetChannel(gInterface.system,4, &gInterface.channelmusic4);
    FMOD_System_GetChannel(gInterface.system,5, &gInterface.channelmusic5);
    FMOD_System_GetMasterChannelGroup(gInterface.system, &gInterface.channelmaster);
}

/*
void ActualiserInterface()
{
	// Actualisation de Rebond
	//gInterface.CaseRebond->value( gDonnees.Rebond ) ;
}*/
