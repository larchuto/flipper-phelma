// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
#include <stdlib.h>     // exit, rand
#include <time.h>       // time
#include <string.h>     // strcpy
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
// Programmes locaux
#include "u1-interface.h"
#include "u4-fonctions.h"
#include "u5-parametres.h"
#include <math.h>

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;

// Initialiser
void InitialiserDonnees()
{
    // On initialise le generateur de nombres aleatoires
    srand(time(NULL));
    // Initialisation de Rebond
    gDonnees.Rebond = 0 ;
    // On initialise la boule
    gDonnees.Boule.X = L_ZONE / 2 ;
    gDonnees.Boule.Y = L_ZONE / 2 ;
    gDonnees.Boule.VX = 0 ;
    gDonnees.Boule.VY = 0 ;

    // Exemple son
    // JouerSon("media/r2d2.mp3");
}

void DeplacerBouleSansRebond()
{
    // Nouvelle position de la boule ...
    //double inclinaison = INCLINAISON;
    gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX;//*DUREE_CYCLE;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY;//+sin(INCLINAISON)/2*GRAVITE*DUREE_CYCLE)*DUREE_CYCLE;


    // ... ramenee sur la sphere
    if ( gDonnees.Boule.X > L_ZONE )
        gDonnees.Boule.X = gDonnees.Boule.X - L_ZONE;

    if ( gDonnees.Boule.X < 0 )
        gDonnees.Boule.X = L_ZONE + gDonnees.Boule.X ;

    if ( gDonnees.Boule.Y > H_ZONE )
        gDonnees.Boule.Y = gDonnees.Boule.Y - gDonnees.Boule.Y;

    if ( gDonnees.Boule.Y < 0 )
        gDonnees.Boule.Y = H_ZONE + gDonnees.Boule.Y ;
}


void DeplacerBouleAvecRebonds()
{
    gDonnees.Boule.VX = gDonnees.Boule.VX;
    //printf("x : %d",gDonnees.Boule.VX);
    gDonnees.Boule.VY = gDonnees.Boule.VY+sin(INCLINAISON)*GRAVITE*DUREE_CYCLE;
    // Nouvelle position de la boule ...
    gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX;
    //printf("x : %d",gDonnees.Boule.X);
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY;//+(sin(INCLINAISON)/2*GRAVITE*DUREE_CYCLE)*DUREE_CYCLE;
    // Gestion des rebonds sur les bords du rectangle


    if ( gDonnees.Boule.X >= L_ZONE-RAYON_BOULE)
    {
        gDonnees.Boule.X = L_ZONE-RAYON_BOULE ;
        gDonnees.Boule.VX = -1 * gDonnees.Boule.VX ;
    }

    if ( gDonnees.Boule.Y >= H_ZONE-RAYON_BOULE)
    {
        gDonnees.Boule.Y = H_ZONE-RAYON_BOULE ;
        gDonnees.Boule.VY = -1 * gDonnees.Boule.VY ;
    }

    if ( gDonnees.Boule.X <= RAYON_BOULE)
    {
        gDonnees.Boule.X = RAYON_BOULE ;
        gDonnees.Boule.VX = -1 * gDonnees.Boule.VX ;
    }

    if ( gDonnees.Boule.Y <= RAYON_BOULE)
    {
        gDonnees.Boule.Y = RAYON_BOULE ;
        gDonnees.Boule.VY = -1 * gDonnees.Boule.VY ;
    }
}

// Utilitaires

// Joue le fichier son passe en parametre, mp3, etc...
void JouerSon(char * FichierSon)
{
    // Musique de fond
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    result = FMOD_System_GetVersion(system, &version);
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    result = FMOD_System_CreateSound(system, FichierSon, FMOD_SOFTWARE, 0, &sound);
    result = FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds )
{
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}
