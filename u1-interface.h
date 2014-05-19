// u1-interface.h
// Sentinelle d'inclusion
#ifndef _u1_interface_h
#define _u1_interface_h

// Declarations externes - inclusion des fichiers d'entete
#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_GIF_Image.H>

// Declaration des objets de l'interface
struct Interface
{
    Fl_Double_Window* Fenetre ;
    DrawingArea* ZoneDessin ;
    DrawingArea* ZoneMenu ;
    DrawingArea* ZoneScore ;
    Fl_Button* BoutonQuitter ;
    Fl_Check_Button* CaseRebond ;

    Fl_Button* BoutonAction ;
    Fl_Button* BoutonNouvellePartie ;
    Fl_Value_Output* ValueScore;
    Fl_Value_Output* Nb_billes;

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
    Fl_GIF_Image* Imageflipg;
    Fl_GIF_Image* Imageflipd;
    Fl_GIF_Image* Imagetrou;
    
} ;

// Declaration des objets de l'interface generale - ne pas supprimer
extern struct Interface gInterface ;


// Declaration des sous-programmes
void CreerInterface();
void ActualiserInterface();

#endif // _u1_interface_h
