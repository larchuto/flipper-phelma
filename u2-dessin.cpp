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
    Fl_GIF_Image Imagefond("media/fond1.gif") ;
    Imagefond.draw(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);

    //Zone de score
    Fl_GIF_Image Imagescore("media/score.gif") ;
    Imagescore.draw(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);
    //fl_color(FL_BORDER_BOX);
    //fl_rectf(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);
        //Zone de menu
    Fl_GIF_Image Imagemenu("media/menu.gif") ;
    Imagemenu.draw(X_MENU, Y_MENU, L_MENU, H_MENU);

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
    fl_arc(20, 20,430,430,0,180);
    fl_rectf(150+20, 250+20, 100, 100);
    fl_polygon(300,500,350,550,300,600,250,550);
    /*float x1=-25;
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
    fl_polygon(x1,y1,x2,y2,x3,y3,x4,y4);*/
    float x1h=-50;
    float y1h=5;
    float x2h=50;
    float y2h=5;
    float x3h=50;
    float y3h=-5;
    float x4h=-50;
    float y4h=-5;
    rotation(-0.78,&x1h,&y1h);
    rotation(-0.78,&x2h,&y2h);
    rotation(-0.78,&x3h,&y3h);
    rotation(-0.78,&x4h,&y4h);
    x1h+=430;
    y1h+=55;
    x2h+=430;
    y2h+=55;
    x3h+=430;
    y3h+=55;
    x4h+=430;
    y4h+=55;
    fl_polygon(x1h,y1h,x2h,y2h,x3h,y3h,x4h,y4h);
    float x1f=-gDonnees.Flip.TX/2;
    float y1f=-gDonnees.Flip.TY/2;
    float x2f=gDonnees.Flip.TX/2;
    float y2f=-gDonnees.Flip.TY/2;
    float x3f=gDonnees.Flip.TX/2;
    float y3f=gDonnees.Flip.TY/2;
    float x4f=-gDonnees.Flip.TX/2;
    float y4f=gDonnees.Flip.TY/2;
    rotation(gDonnees.Flip.angle,&x1f,&y1f);
    rotation(gDonnees.Flip.angle,&x2f,&y2f);
    rotation(gDonnees.Flip.angle,&x3f,&y3f);
    rotation(gDonnees.Flip.angle,&x4f,&y4f);
    x1f+=gDonnees.Flip.X+20;
    y1f+=gDonnees.Flip.Y+20;
    x2f+=gDonnees.Flip.X+20;
    y2f+=gDonnees.Flip.Y+20;
    x3f+=gDonnees.Flip.X+20;
    y3f+=gDonnees.Flip.Y+20;
    x4f+=gDonnees.Flip.X+20;
    y4f+=gDonnees.Flip.Y+20;
    fl_polygon(x1f,y1f,x2f,y2f,x3f,y3f,x4f,y4f);
    //Zone de menu
    //fl_color(FL_DARK_MAGENTA);
    //fl_rectf(470, 440, 230, 230);

}
