#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>



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

typedef struct PacMan
{
    int tx ;
    int ty;
    int deplacement;
    int posx;
    int posy;
    int vies;

}t_PacMan;

t_enemy * initialiserenemy();
void call_monster(BITMAP*dbbuffer, BITMAP*enemy,t_enemy * monenemy, t_PacMan *PacMan, int *compteur);
void deplacementPacMan(BITMAP *dbbuffer, t_PacMan *PacMan, int *a);
void mort(t_enemy *monenemy, t_PacMan * PacMan, int * compteur, BITMAP *dbbuffer);


#endif // PROTOTYPES_H_INCLUDED
