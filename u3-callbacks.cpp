// u3-callbacks.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream> // cout, cin, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H> // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser
// Programmes locaux
#include "u1-interface.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

bool Flip_left_is_touched =false;
bool Flip_right_is_touched =false;
int Flip_left_wait =0;
int Flip_right_wait =0;

// TraiterCycle
void TraiterCycleCB()
{
    //if(gDonnees.Boule.X!=412){
    //printf("vitesse x = %f\n",gDonnees.Boule.VX);
    //printf("vitesse y = %f\n",gDonnees.Boule.VY*DUREE_CYCLE);}
    //if(gDonnees.Boule.X!=412){
    //printf("x = %f\n",gDonnees.Boule.X);
    //printf("y = %f\n",gDonnees.Boule.Y);}
    if (Flip_left_is_touched && gDonnees.FlipG.angle<1)
    {
        //MoveFlip(&(gDonnees.FlipD),0.005);
        MoveFlip(&(gDonnees.FlipG),+0.25);
    }
    else if (!Flip_left_is_touched && gDonnees.FlipG.angle>0)// && Flip_left_wait>=10)
    {
        MoveFlip(&(gDonnees.FlipG),-0.25);
        //Flip_left_wait =0;
    }
    /*else
{
Flip_left_wait +=1;
}*/
    if (Flip_right_is_touched && gDonnees.FlipD.angle>-1)
    {
        //MoveFlip(&(gDonnees.FlipD),0.005);
        MoveFlip(&(gDonnees.FlipD),-0.25);
    }
    else if (!Flip_right_is_touched && gDonnees.FlipD.angle<0)// && Flip_right_wait>=10)
    {
        MoveFlip(&(gDonnees.FlipD),+0.25);
        //int Flip_right_wait =0;
    }
    /*else
{
Flip_right_wait +=1;
}*/
    //Flip_left_is_touched=false;
    // Trace pour bien montrer que la fonction est appelee cycliquement
    // printf(""Appel de TraiterCycleCB");
    /*if(Flip_left_is_touched)
{
Flip_wait=0;
gDonnees.Flip.angle+=50*DUREE_CYCLE;//*(gDonnees.Flip.angle<0.80);
if (gDonnees.Flip.angle>0.95)
{
gDonnees.Flip.angle=0.95;
//Flip_wait+=1;
Flip_left_is_touched=false;
//gDonnees.Flip.angle+=25*DUREE_CYCLE;
}
}
//else// if (gDonnees.Flip.angle>=0.90 && gDonnees.Flip.angle>0)
//{
Flip_wait+=1;
gDonnees.Flip.angle-=25*DUREE_CYCLE*(Flip_wait>4 && gDonnees.Flip.angle>0);
if (gDonnees.Flip.angle<0)
{
gDonnees.Flip.angle=0;
}*/

    //}
    /*else
{
gDonnees.Flip.angle=0;
}*/
    // Deplacement de la boule
    DeplacerBouleAvecRebonds() ;

    // On redessine la zone
    gInterface.ZoneDessin->redraw() ;
    gInterface.ZoneScore->redraw() ;
    gInterface.ValueScore->redraw() ;
    gInterface.Nb_billes->redraw() ;


    // Code a activer en cas de probleme pour saisir les evenements du clavier
    // Probleme : si les evenements du clavier ne sont pas bien pris en compte pour agir sur la zone de dessin.
    // Solution : On ramene systematiquement le focus des evenements sur la zone de dessin
    // Attention, cela peut perturber certains elements d'interface comme des champs de saisie texte ou numerique

    // Fl::focus(gInterface.ZoneDessin);

    // Fin code a activer en cas de probleme
}

// ZoneDessinSourisCB
void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    if ( Fl::event() == FL_PUSH )
    {
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());

        // On repositionne la boule a l'endroit du clic avec une vitesse nulle
        gDonnees.Boule.X = Fl::event_x() - X_ZONE ;
        gDonnees.Boule.Y = Fl::event_y() - Y_ZONE ;
        gDonnees.Boule.VX=0;
        gDonnees.Boule.VY=0;
    }

    //if ( Fl::event() == FL_MOVE )
    //{
    // printf("Mouse move : x = %i y = %i\n", Fl::event_x(), Fl::event_y());
    //}
}

// ZoneDessinClavierCB
void ZoneDessinClavierCB( Fl_Widget* widget, void* data, bool key_is_down)
{
    // Definition des variables
    int Touche ;

    // Recuperation de la touche clavier activee
    Touche = Fl::event_key() ;

    // Traitement de la touche
    switch ( Touche )
    {
        // Touches speciales
        case FL_Left :
            if(key_is_down) printf("Appui sur la touche Gauche\n");
            else printf("Relachement de la touche Gauche\n");
            Flip_left_is_touched = key_is_down;
            break;
        case FL_Right :
            if(key_is_down) printf("Appui sur la touche Droite\n");
            else printf("Relachement de la touche Droite\n");
            Flip_right_is_touched = key_is_down;
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            break ;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            break ;
        // Caracteres
        case ' ' :
            printf("Appui sur la touche Espace\n");
            if(gDonnees.Boule.X >=L_ZONE-RAYON_BOULE-8 && gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE-46)
            {
                gDonnees.Boule.VY=-6000; //5000-6000
            }
         //gDonnees.Valeur2 = gDonnees.Valeur2 + 1 ;
         //gInterface.Nb_billes->value(gDonnees.Valeur2) ;
            break ;
        case 'a' :
            printf("Appui sur le caractere a\n");
            break ;
        case 'b' :
            printf("Appui sur le caractere b\n");
            break ;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break ;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break ;
    }
}

void BoutonQuitterCB(Fl_Widget* w, void* data)
{
    // Fin du programme
    exit(0) ;
}

/*void CaseRebondCB(Fl_Widget* w, void* data)
{
gDonnees.Rebond = gInterface.CaseRebond->value() ;
}*/

void BoutonActionCB(Fl_Widget* w, void* data)
{
     printf("BoutonActionCB\n");
}

