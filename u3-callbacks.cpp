// u3-callbacks.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream> // cout, cin, ...
//#include <stdio.h>
//#include <stdlib.h>
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H> // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser
// Programmes locaux
#include "u1-interface.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"
#include "u5-parametres.h"

// Declaration pour utiliser iostream
using namespace std;

// TraiterCycle
void TraiterCycleCB()
{
    //Deplacement des Flip
    if (gDonnees.FlipG.isTouched && gDonnees.FlipG.angle<MAX_ANGLE_FLIP)
    {
        MoveFlip(&(gDonnees.FlipG),+FLIP_ANGLE_PER_STEP);
        PushBall(&(gDonnees.FlipG), &(gDonnees.Boule));

    }
    else if (!gDonnees.FlipG.isTouched && gDonnees.FlipG.angle>0)
    {
        MoveFlip(&(gDonnees.FlipG),-FLIP_ANGLE_PER_STEP);
    }

    if (gDonnees.FlipD.isTouched && gDonnees.FlipD.angle>-MAX_ANGLE_FLIP)
    {
        MoveFlip(&(gDonnees.FlipD),-FLIP_ANGLE_PER_STEP);
        PushBall(&(gDonnees.FlipD), &(gDonnees.Boule));

    }
    else if (!gDonnees.FlipD.isTouched && gDonnees.FlipD.angle<0)
    {
        MoveFlip(&(gDonnees.FlipD),+FLIP_ANGLE_PER_STEP);
    }

    // Deplacement de la boule
    DeplacerBouleAvecRebonds();

    // On redessine la zone
    gInterface.ZoneDessin->redraw();
    gInterface.ZoneScore->redraw();


    // Code a activer en cas de probleme pour saisir les evenements du clavier
    // Probleme : si les evenements du clavier ne sont pas bien pris en compte pour agir sur la zone de dessin.
    // Solution : On ramene systematiquement le focus des evenements sur la zone de dessin
    // Attention, cela peut perturber certains elements d'interface comme des champs de saisie texte ou numerique

     Fl::focus(gInterface.ZoneDessin);

    // Fin code a activer en cas de probleme
}

void BoutonNouvellePartieCB(Fl_Widget* w, void* data)
{
            // On initialise la boule
            gDonnees.Boule.X = L_ZONE-RAYON_BOULE-6;
            gDonnees.Boule.Y = H_ZONE-RAYON_BOULE-47;
            gDonnees.Boule.rayon=RAYON_BOULE;
            gDonnees.Boule.VX = 0 ;
            gDonnees.Boule.VY = 0 ;

            // On initialise le score et le nombre de billes
            gDonnees.Points = 0 ;
            gDonnees.NumBille = 1 ;

     printf("BoutonNouvellePartieCB\n");
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
            gDonnees.FlipG.isTouched = key_is_down;
            break;
        case FL_Right :
            if(key_is_down) printf("Appui sur la touche Droite\n");
            else printf("Relachement de la touche Droite\n");
            gDonnees.FlipD.isTouched = key_is_down;
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
		if(key_is_down){CompressionRessort();}
		else{RelachementRessort();}
         //gDonnees.NumBille = gDonnees.NumBille + 1 ;
         //gInterface.Nb_billes->value(gDonnees.NumBille) ;
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
    //On sauvegarde les meilleurs scores
    SaveBestScores();
    // Fin du programme
    exit(0);
}



void BoutonMeilleursScoresCB(Fl_Widget* w, void* data)
{
	char buffer[150],ent[10];
	for(int i=0;i<5;i++)
	{
		if (gDonnees.score[i]==0) break;
		strncat(buffer,gDonnees.nom[i],150);
		strncat(buffer,"	",150);
		snprintf(ent,10,"%d",gDonnees.score[i]);
		strncat(buffer,ent,150);
		strncat(buffer,"\n",150);
	}
	fl_message(buffer);

/*
     if(gDonnees.score[1]==0)
     {
      fl_message("\t\t\tMeilleurs Scores\n\n1.  %s\t\n2.  %s\t\n3.  %s\t\n4.  %s\t\n5.  %s\t",gDonnees.nom1,gDonnees.nom2,gDonnees.nom3,gDonnees.nom4,gDonnees.nom5);
     }
     else if(gDonnees.score2==0)
     {
      fl_message("\t\t\tMeilleurs Scores\n\n1.  %s\t%d\n2.  %s\t\n3.  %s\t\n4.  %s\t\n5.  %s\t",gDonnees.nom1,gDonnees.score1,gDonnees.nom2,gDonnees.nom3,gDonnees.nom4,gDonnees.nom5);
     }
     else if (gDonnees.score3==0)
     {
      fl_message("\t\t\tMeilleurs Scores\n\n1.  %s\t%d\n2.  %s\t%d\n3.  %s\t\n4.  %s\t\n5.  %s\t",gDonnees.nom1,gDonnees.score1,gDonnees.nom2,gDonnees.score2,gDonnees.nom3,gDonnees.nom4,gDonnees.nom5);
     }
     else if(gDonnees.score4==0)
     {
      fl_message("\t\t\tMeilleurs Scores\n\n1.  %s\t%d\n2.  %s\t%d\n3.  %s\t%d\n4.  %s\t\n5.  %s\t",gDonnees.nom1,gDonnees.score1,gDonnees.nom2,gDonnees.score2,gDonnees.nom3,gDonnees.score3,gDonnees.nom4,gDonnees.nom5);
     }
     else if(gDonnees.score5==0)
     {
      fl_message("\t\t\tMeilleurs Scores\n\n1.  %s\t%d\n2.  %s\t%d\n3.  %s\t%d\n4.  %s\t%d\n5.  %s\t",gDonnees.nom1,gDonnees.score1,gDonnees.nom2,gDonnees.score2,gDonnees.nom3,gDonnees.score3,gDonnees.nom4,gDonnees.score4,gDonnees.nom5);
     }
     else
     {
     fl_message("\t\t\tMeilleurs Scores\n\n1.  %s\t%d\n2.  %s\t%d\n3.  %s\t%d\n4.  %s\t%d\n5.  %s\t%d",gDonnees.nom1,gDonnees.score1,gDonnees.nom2,gDonnees.score2,gDonnees.nom3,gDonnees.score3,gDonnees.nom4,gDonnees.score4,gDonnees.nom5,gDonnees.score5);
    }*/
}

