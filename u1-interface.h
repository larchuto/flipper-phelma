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

// Definition des constantes
#define X_ZONE  20      // X de la zone
#define Y_ZONE  20      // Y de la zone
#define L_ZONE  430     // Largeur de la zone
#define H_ZONE  650     // Hauteur de la zone

#define X_SCORE 470
#define Y_SCORE 40
#define L_SCORE 230
#define H_SCORE 400

#define L_ZONE2 700


// Declaration des objets de l'interface
struct Interface
{
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    DrawingArea*        ZoneDessin2 ;
    Fl_Button*          BoutonQuitter ;
    Fl_Check_Button*    CaseRebond ;

    Fl_Button*          BoutonAction ;
    Fl_Value_Output*    Score;
    Fl_Value_Output*    Nb_billes;
} ;

// Declaration des objets de l'interface generale - ne pas supprimer
extern struct Interface gInterface ;


// Declaration des sous-programmes
void CreerInterface();
void ActualiserInterface();

#endif // _u1_interface_h
