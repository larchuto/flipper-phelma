// u1-interface.h
// Sentinelle d'inclusion
#ifndef _u1_interface_h
#define _u1_interface_h

// Declarations externes - inclusion des fichiers d'entete
#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
//#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_GIF_Image.H>
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>

// Declaration des objets de l'interface
struct Interface
{
	Fl_Double_Window* Fenetre ;
	DrawingArea* ZoneDessin ;
	DrawingArea* ZoneMenu ;
	DrawingArea* ZoneScore ;
	Fl_Button* BoutonQuitter ;

	Fl_Button* BoutonAction ;
	Fl_Button* BoutonNouvellePartie ;
	Fl_Button* BoutonMeilleursScores ;

	Fl_GIF_Image* Imagescore;
	Fl_GIF_Image* Imagemenu;
	Fl_GIF_Image* Imagefond;
	Fl_GIF_Image* Imagedecor;
	Fl_GIF_Image* Imagebille;
	Fl_GIF_Image* Imagevert;
	Fl_GIF_Image* Imagerouge;
	Fl_GIF_Image* Imagebleu;
	Fl_GIF_Image* Imagetriangleg;
	Fl_GIF_Image* Imagetriangled;
	Fl_GIF_Image* Imagebip[7];
	Fl_GIF_Image* Imageteleporteur;
	Fl_GIF_Image* Imagetrou;
    FMOD_SYSTEM* system;
 	FMOD_SOUND* bip_1 ;
 	FMOD_SOUND* bip_2 ;
 	FMOD_SOUND* bip_3 ;
 	FMOD_SOUND* bip_4 ;
 	FMOD_SOUND* bip_5 ;
 	FMOD_SOUND* bip_6 ;
 	FMOD_SOUND* bip_7 ;
 	FMOD_SOUND* trounoir ;
 	FMOD_SOUND* teleporteur ;
 	FMOD_SOUND* bumper ;
 	FMOD_SOUND* triangle ;
 	FMOD_SOUND* music1;
 	FMOD_SOUND* music2;
 	FMOD_SOUND* music3;
 	FMOD_SOUND* music4;
 	FMOD_SOUND* music5;
 	FMOD_SOUND* collision;
 	FMOD_SOUND* meilleurs_scores;
 	FMOD_SOUND* WTFBOOM;

    FMOD_CHANNEL* channelmusic1;
    FMOD_CHANNEL* channelmusic2;
    FMOD_CHANNEL* channelmusic3;
    FMOD_CHANNEL* channelmusic4;
    FMOD_CHANNEL* channelmusic5;
    FMOD_CHANNELGROUP* channelmaster;


} ;

// Declaration des objets de l'interface generale - ne pas supprimer
extern struct Interface gInterface ;


// Declaration des sous-programmes
void CreerInterface();
//void ActualiserInterface();

#endif // _u1_interface_h
