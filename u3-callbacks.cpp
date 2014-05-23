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
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>

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
		//printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
		// On repositionne la boule a l'endroit du clic avec une vitesse nulle
		gDonnees.Boule.X = Fl::event_x() - X_ZONE ;
		gDonnees.Boule.Y = Fl::event_y() - Y_ZONE ;
		gDonnees.Boule.VX=0;
		gDonnees.Boule.VY=0;
	}
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
			//on indique si la touche est appuyée ou relachée
			gDonnees.FlipG.isTouched = key_is_down;
			break;
		case FL_Right :
			//on indique si la touche est appuyée ou relachée
			gDonnees.FlipD.isTouched = key_is_down;
			break;
		// Caracteres
		case ' ' :
		if(key_is_down){CompressionRessort();}
		else{RelachementRessort();}
			break ;

        case 't' :
            //déclanchement du TROLOLOLOLOL
            FMOD_Channel_Stop(gInterface.channelmusic1); //Stop la première musique
            FMOD_Channel_Stop(gInterface.channelmusic2); //Stop la deuxième musique bonus
            FMOD_Channel_Stop(gInterface.channelmusic3); //Stop la troisième musique
            FMOD_Channel_Stop(gInterface.channelmusic4); //Stop la quatrième musique
            FMOD_System_PlaySound(gInterface.system, (FMOD_CHANNELINDEX) 5, gInterface.music5, 0, &gInterface.channelmusic5);
            FMOD_System_Update(gInterface.system);
            break;

        case 'y' :
             //Stop tous les sons CE TRUC BUG PAS TOUCHEZ pas TAPPEZ SISISIi
            FMOD_ChannelGroup_Stop(gInterface.channelmaster);
            //Chargement de la musique correspond au score
                if (gDonnees.Points < LIMITEPOINT1 )
                {
                    FMOD_System_PlaySound(gInterface.system, (FMOD_CHANNELINDEX) 1, gInterface.music1, 0, &gInterface.channelmusic1);
                    FMOD_System_Update(gInterface.system);
                }
                if ((gDonnees.Points>=LIMITEPOINT1) && (gDonnees.Points<LIMITEPOINT2) )
                {
                    FMOD_System_PlaySound(gInterface.system, (FMOD_CHANNELINDEX) 2, gInterface.music2, 0, &gInterface.channelmusic2);
                    FMOD_System_Update(gInterface.system);
                }
                if ((gDonnees.Points>=LIMITEPOINT2) && (gDonnees.Points<LIMITEPOINT3) )
                {
                    FMOD_System_PlaySound(gInterface.system, (FMOD_CHANNELINDEX) 3, gInterface.music3, 0, &gInterface.channelmusic3);
                    FMOD_System_Update(gInterface.system);
                }
                if  (gDonnees.Points>=LIMITEPOINT3)
                {
                    FMOD_System_PlaySound(gInterface.system, (FMOD_CHANNELINDEX) 4, gInterface.music4, 0, &gInterface.channelmusic4);
                    FMOD_System_Update(gInterface.system);
                }
            break;

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

 char message[150];
 char buffer[150];
 char ent[10];
 snprintf(message,150,"\t\t\tMeilleurs Scores\n\n");
 for(int i=0;i<5;i++)
 {
 	if (gDonnees.score[i]==0) snprintf (buffer,150,"%s\t%d.\n",message,i+1);
 	else snprintf(buffer,150,"%s\t%d. %s\t\t\t%d\t\n",message,i+1,gDonnees.nom[i],gDonnees.score[i]);
 	strcpy(message,buffer);
 }
 if (gDonnees.score[0]==0) snprintf(message,150,"aucun meilleur score");
 fl_message("%s",message);
}

