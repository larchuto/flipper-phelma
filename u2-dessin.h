// u2-dessin.h
// Sentinelle d'inclusion
#ifndef _u2_dessin_h
#define _u2_dessin_h

// Declaration des sous-programmes
void Display_PieBB(struct Boule CBB);
void Display_OBB(struct Obb OBB);
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data ) ;
void ZoneMenuDessinerCB( Fl_Widget* widget, void* data ) ;
void ZoneScoreDessinerCB( Fl_Widget* widget, void* data ) ;

#endif // _u2_dessin_h
