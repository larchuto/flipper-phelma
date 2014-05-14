// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream> // cin, cout, ...
// Librairies fltk
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H> // fonctions de dessin
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"



// Declaration pour utiliser iostream
using namespace std;

void Display_PieBB(struct Boule CBB)
{
    fl_color(FL_GREEN);
    //fl_arc(CBB.X/*+CBB.rayon*/, CBB.Y/*+CBB.rayon*/, 2*CBB.rayon, 2*CBB.rayon, 0,360);
    fl_circle(CBB.X+20,CBB.Y+20,CBB.rayon);
}
void Display_OBB(struct Obb OBB)
{
    fl_color(FL_GREEN);
    float x1=-OBB.TX/2;
    float y1=OBB.TY/2;
    float x2=OBB.TX/2;
    float y2=OBB.TY/2;
    float x3=OBB.TX/2;
    float y3=-OBB.TY/2;
    float x4=-OBB.TX/2;
    float y4=-OBB.TY/2;
    rotation(OBB.angle,&x1,&y1);
    rotation(OBB.angle,&x2,&y2);
    rotation(OBB.angle,&x3,&y3);
    rotation(OBB.angle,&x4,&y4);
    x1+=OBB.X+20;
    y1+=OBB.Y+20;
    x2+=OBB.X+20;
    y2+=OBB.Y+20;
    x3+=OBB.X+20;
    y3+=OBB.Y+20;
    x4+=OBB.X+20;
    y4+=OBB.Y+20;
    //fl_polygon(x1,y1,x2,y2,x3,y3,x4,y4);
    fl_line(x1,y1,x2,y2);
    fl_line(x2,y2,x3,y3);
    fl_line(x3,y3,x4,y4);
    fl_line(x4,y4,x1,y1);
}
void DessineRessort(unsigned int compression)
{
    compression=compression % 4;
    char path[] = "media/ressort0.gif";
    path[13]='0';//+(char)compression;
    Fl_GIF_Image Imageressort(path) ;
    Imageressort.draw(421, 624+10*compression, 24, 41-10*compression);
}

void ZoneScoreDessinerCB( Fl_Widget* widget, void* data )
{
        //Zone de score
    gInterface.Imagescore->draw(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);
}
void ZoneMenuDessinerCB( Fl_Widget* widget, void* data )
{
        //Zone de menu
    gInterface.Imagemenu->draw(X_MENU, Y_MENU, L_MENU, H_MENU);
}

// DessinerZone
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    // On efface toute la zone ( en dessinant dessus l'image de fond )
    //Fl_GIF_Image Imagefond("media/fondgif.gif") ;
    gInterface.Imagefond->draw(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
    //Attente(0.00005);


    //fl_color(FL_BORDER_BOX);
    //fl_rectf(X_SCORE, Y_SCORE, L_SCORE, H_SCORE);


    // On dessine la boule
    //Fl_GIF_Image Imagebille("media/bille.gif") ;
    gInterface.Imagebille->draw(X_ZONE + gDonnees.Boule.X - RAYON_BOULE, Y_ZONE + gDonnees.Boule.Y - RAYON_BOULE);
    //Imagebille.draw(X_ZONE, Y_ZONE);
    //(/*"media/bille.gif"*/);
    //bille ball;
    //ball.trace();
    //ball.rebond();
    //ball.move();
    //dessin collision boxes
    gInterface.Imagedecor->draw(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);

    if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113 && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113+20)
            {
                gInterface.Imagebip1->draw(392+20, 457+20, 9, 40);
                //JouerSon("media/Sons/bips/rampe/bip_1.mp3");
            }
    if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113-(40*1) && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113-20)
            {
                gInterface.Imagebip2->draw(392+20, 457-(40*1)+20, 9, 40);
                //JouerSon("media/Sons/bips/rampe/bip_2.mp3");
            }
    if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113-(40*2) && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113-20-(40*1))
            {
                gInterface.Imagebip3->draw(392+20, 457-(40*2)+20, 9, 40);
                //JouerSon("media/Sons/bips/rampe/bip_3.mp3");
            }
    if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113-(40*3) && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113-20-(40*2))
            {
                gInterface.Imagebip4->draw(392+20, 457-(40*3)+20, 9, 40);
                //JouerSon("media/Sons/bips/rampe/bip_4.mp3");
            }
    if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113-(40*4) && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113-20-(40*3))
            {
                gInterface.Imagebip5->draw(392+20, 457-(40*4)+20, 9, 40);
                //JouerSon("media/Sons/bips/rampe/bip_5.mp3");
            }
    if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113-(40*5) && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113-20-(40*4))
            {
                gInterface.Imagebip6->draw(392+20, 457-(40*5)+20, 9, 40);
                //JouerSon("media/Sons/bips/rampe/bip_6.mp3");
            }
    if(gDonnees.Boule.X >= L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46-113-(40*6) && gDonnees.Boule.Y <= H_ZONE-RAYON_BOULE-46-113-20-(40*5))
            {
                gInterface.Imagebip7->draw(392+20, 457-(40*6)+20, 9, 40);
                //JouerSon("media/Sons/bips/rampe/bip_7.mp3");
            }


    DessineRessort(gDonnees.CompressionRessort);
    fl_color(FL_WHITE);
    //fl_rectf(150+20, 250+20, 100, 100);
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
    /*float x1h=-50;
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
fl_polygon(x1h,y1h,x2h,y2h,x3h,y3h,x4h,y4h);*/
    /*float x1f=-gDonnees.Flip.TX/2;
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
fl_polygon(x1f,y1f,x2f,y2f,x3f,y3f,x4f,y4f);*/
    //Zone de menu
    //fl_color(FL_DARK_MAGENTA);
    //fl_rectf(470, 440, 230, 230);
    Display_PieBB(gDonnees.TriGC1);
    Display_PieBB(gDonnees.TriGC2);
    Display_PieBB(gDonnees.TriGC3);
    Display_PieBB(gDonnees.Pieh);
    Display_PieBB(gDonnees.Bp1);
    Display_PieBB(gDonnees.Bp2);
    Display_PieBB(gDonnees.Bp3);
    Display_OBB(gDonnees.Lanceur);
    Display_OBB(gDonnees.TriGL1);
    Display_OBB(gDonnees.TriGL2);
    Display_OBB(gDonnees.TriGL3);
    Display_OBB(gDonnees.PenteG);
    Display_OBB(gDonnees.PenteD);
    Display_PieBB(gDonnees.TriDC1);
    Display_PieBB(gDonnees.TriDC2);
    Display_PieBB(gDonnees.TriDC3);
    Display_OBB(gDonnees.TriDL1);
    Display_OBB(gDonnees.TriDL2);
    Display_OBB(gDonnees.TriDL3);
    Display_PieBB(gDonnees.FlipG.C1);
    Display_PieBB(gDonnees.FlipG.C2);
    Display_OBB(gDonnees.FlipG.L1);
    Display_OBB(gDonnees.FlipG.L2);
    Display_PieBB(gDonnees.FlipD.C1);
    Display_PieBB(gDonnees.FlipD.C2);
    Display_OBB(gDonnees.FlipD.L1);
    Display_OBB(gDonnees.FlipD.L2);
	Display_OBB(gDonnees.Ressort);
}
