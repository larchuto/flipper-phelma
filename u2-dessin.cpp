// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Librairies fltk
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>     // fonctions de dessin
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"




// Declaration pour utiliser iostream
using namespace std;

// DessinerZone
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    fl_color(FL_BLACK);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);

    //Zone de score
    fl_color(FL_BORDER_BOX);
    fl_rectf(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);

    // On dessine la boule
    Fl_GIF_Image Imagebille("media/bille.gif") ;
    Imagebille.draw(X_ZONE + gDonnees.Boule.X - RAYON_BOULE, Y_ZONE + gDonnees.Boule.Y - RAYON_BOULE);
    //Imagebille.draw(X_ZONE, Y_ZONE);
}
