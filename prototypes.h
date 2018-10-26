#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

//#include <allegro.h>

typedef struct enemy
{
    int dtx;
    int dty;
    int ddeplacement;
    int ddirection;
    int dposx;
    int dposy;
    int alive;
    int resetdir;
    int compteur_enemy;

} t_enemy;




#endif // PROTOTYPES_H_INCLUDED
