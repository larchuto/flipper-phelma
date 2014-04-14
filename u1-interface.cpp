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
    gInterface.Fenetre = new Fl_Double_Window(720,720);
    gInterface.Fenetre->label("Flipper Phelma") ;
    gInterface.Fenetre->begin() ;

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE2,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(570, 670, 100, 20, "Quitter") ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

    // Creation de la case a cocher Rebond
    //gInterface.CaseRebond = new Fl_Check_Button(570, 500, 100, 20, "Rebond") ;
    //gInterface.CaseRebond->callback( CaseRebondCB, NULL ) ;

    // Creation du bouton Action
    gInterface.BoutonAction = new Fl_Button(570, 450, 100, 20, "Action") ;
    gInterface.BoutonAction->callback( BoutonActionCB, NULL ) ;

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{
    // Actualisation de Rebond
    //gInterface.CaseRebond->value( gDonnees.Rebond ) ;
}
