#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>



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
    BITMAP * pacman_bot[2];
    BITMAP * pacman_right[8];
    BITMAP * pacman_up[3];

    int tx ;
    int ty;
    int deplacement;
    int posx;
    int posy;
    int vies;

    //Sprites change
    int compteur;
    int temporiseur;
    int image_actuelle;

}t_PacMan;

t_enemy * initialiserenemy();

BITMAP* call_monster(BITMAP*dbbuffer,t_enemy * monenemy, t_PacMan *PacMan);
BITMAP* deplacementPacMan(BITMAP *dbbuffer, t_PacMan *PacMan, int *a);
BITMAP* action_sprite_pacman(t_PacMan*PacMan, BITMAP*mabitmap[], int taille_max);
void mort(t_enemy *monenemy, t_PacMan * PacMan, int * compteur, BITMAP *dbbuffer);
//Version fonctionnelle
int death(t_enemy *monenemy[4], t_PacMan *PacMan, int compteur, BITMAP *dbbuffer);


#endif // PROTOTYPES_H_INCLUDED
