#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct gestion_map
{
    BITMAP * buffer_pc[4];
    BITMAP * buffer_pc_nb[4];
    BITMAP * map_pac_man[4];
    BITMAP * noborder_pac_man[4];
    BITMAP * actual_front;
    BITMAP * actual_test;
    int choix;
    int border;
} t_map;

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
    int turn_img;

}t_PacMan;

t_enemy * initialiserenemy();
t_map * initialisermap();

t_map * choix_map(t_map * changemap);
BITMAP* call_monster(BITMAP*dbbuffer,t_enemy * monenemy, t_PacMan *PacMan);
BITMAP* deplacementPacMan(BITMAP *dbbuffer, t_PacMan *PacMan, int *a);
BITMAP* action_sprite_pacman(t_PacMan*PacMan, BITMAP*mabitmap[], int taille_max);
void follow_monster(t_enemy * monenemy, t_PacMan *PacMan, BITMAP*dbbuffer);
void mort(t_enemy *monenemy, t_PacMan * PacMan, int * compteur, BITMAP *dbbuffer);

//Version fonctionnelle
int death(t_enemy *monenemy[4], t_PacMan *PacMan, int compteur, BITMAP *dbbuffer);




#endif // PROTOTYPES_H_INCLUDED
