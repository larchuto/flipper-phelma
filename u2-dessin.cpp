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
    Fl_GIF_Image Imagefond("media/fond.gif") ;
    Imagefond.draw(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);

    //Zone de score
    Fl_GIF_Image Imagescore("media/score.gif") ;
    Imagescore.draw(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);
    //fl_color(FL_BORDER_BOX);
    //fl_rectf(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);

    // On dessine la boule
    Fl_GIF_Image Imagebille("media/bille.gif") ;
    Imagebille.draw(X_ZONE + gDonnees.Boule.X - RAYON_BOULE, Y_ZONE + gDonnees.Boule.Y - RAYON_BOULE);
    //Imagebille.draw(X_ZONE, Y_ZONE);
    //(/*"media/bille.gif"*/);
    //bille ball;
    //ball.trace();
    //ball.rebond();
    //ball.move();
    //dessin collision boxes
    fl_color(FL_WHITE);
    fl_arc(350, 350,40,40,0,360);
    fl_rectf(150+20, 250+20, 100, 100);

    //Zone de menu
    fl_color(FL_DARK_MAGENTA);
    fl_rectf(470, 440, 230, 230);

}
