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
    fl_polygon(300,500,350,550,300,600,250,550);
    float x1=-25;
    float y1=25;
    float x2=25;
    float y2=25;
    float x3=25;
    float y3=-25;
    float x4=-25;
    float y4=-25;
    rotation(1,&x1,&y1);
    rotation(1,&x2,&y2);
    rotation(1,&x3,&y3);
    rotation(1,&x4,&y4);
    x1+=100;
    y1+=500;
    x2+=100;
    y2+=500;
    x3+=100;
    y3+=500;
    x4+=100;
    y4+=500;
    fl_polygon(x1,y1,x2,y2,x3,y3,x4,y4);

    //Zone de menu
    fl_color(FL_DARK_MAGENTA);
    fl_rectf(470, 440, 230, 230);

}
