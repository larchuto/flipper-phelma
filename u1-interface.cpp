// u1-interface.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

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
    gInterface.ZoneScore = new DrawingArea(X_SCORE,Y_SCORE,L_SCORE,H_SCORE);
    gInterface.ZoneScore->draw_callback( ZoneScoreDessinerCB, NULL ) ;
    //gInterface.ZoneScore->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneScore->keyboard_callback( ZoneDessinClavierCB, NULL) ;
    gInterface.Imagescore= new Fl_GIF_Image("media/score.gif") ;

    // Creation de la zone de menu
    gInterface.ZoneMenu = new DrawingArea(X_MENU,Y_MENU,L_MENU,H_MENU);
    gInterface.ZoneMenu->draw_callback( ZoneMenuDessinerCB, NULL ) ;
    //gInterface.ZoneMenu->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneMenu->keyboard_callback( ZoneDessinClavierCB, NULL ) ;
    gInterface.Imagemenu= new Fl_GIF_Image("media/menu.gif") ;

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;
    gInterface.Imagefond= new Fl_GIF_Image("media/fondgif.gif") ;
    gInterface.Imagebille= new Fl_GIF_Image("media/bille.gif") ;

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(590, 640, 100, 20, "Quitter") ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

    // Creation de la case a cocher Rebond
    //gInterface.CaseRebond = new Fl_Check_Button(570, 500, 100, 20, "Rebond") ;
    //gInterface.CaseRebond->callback( CaseRebondCB, NULL ) ;

    // Creation du bouton Action
    gInterface.BoutonAction = new Fl_Button(480, 640, 100, 20, "Action") ;
    gInterface.BoutonAction->callback( BoutonActionCB, NULL ) ;

    //Score
    gInterface.ValueScore = new Fl_Value_Output(475, 393-20, 220, 42, "") ;
    gInterface.ValueScore->box(FL_THIN_DOWN_FRAME);
    gInterface.ValueScore->textcolor(FL_WHITE);
    gInterface.ValueScore->textsize(30);
    gInterface.ValueScore->textfont(FL_HELVETICA_BOLD);

    //Nombre billes
    gInterface.Nb_billes = new Fl_Value_Output(653, 340-20, 42, 42, "") ;
    gInterface.Nb_billes->box(FL_THIN_DOWN_FRAME);
    gInterface.Nb_billes->textcolor(FL_WHITE);
    gInterface.Nb_billes->textsize(30);
    gInterface.Nb_billes->textfont(FL_HELVETICA_BOLD);

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{
    // Actualisation de Rebond
    //gInterface.CaseRebond->value( gDonnees.Rebond ) ;
}
