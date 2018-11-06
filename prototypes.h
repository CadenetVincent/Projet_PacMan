#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    int last_posx;
    int last_posy;
    int vies;

    //Sprites change
    int compteur;
    int temporiseur;
    int image_actuelle;
    int turn_img;
    int direction;
    int last_direction;
    int get_Sun;

    int score;

}t_PacMan;

typedef struct Diamant
{
    int posx;
    int posy;
    int boolean;
}t_Diamant;

typedef struct Sun
{
    BITMAP * SOLEIL[6];
    BITMAP * actuel_map;
    int posx;
    int posy;
    int boolean;
}t_Sun;

t_Diamant * initialiserDiamants();

void gestionDiamant(BITMAP * dbbuffer, t_Diamant* Diamant,BITMAP * front, int *stop);

void supressionDiamant(BITMAP * dbbuffer, t_Diamant * Diamant,t_PacMan * PacMan);

t_Sun * initialiserSun();
t_enemy * initialiserenemy();
t_map * initialisermap();
t_map * choix_map(t_map * changemap);
t_PacMan * intialisationSubPacMan();

BITMAP* call_monster(BITMAP*dbbuffer,t_enemy * monenemy, t_PacMan *PacMan);
BITMAP* deplacementPacMan(BITMAP *dbbuffer, t_PacMan *PacMan, int *a);
BITMAP* action_sprite_pacman(t_PacMan*PacMan, BITMAP*mabitmap[], int taille_max);
void follow_monster(t_enemy * monenemy, t_PacMan *PacMan, BITMAP*dbbuffer);
void mort(t_enemy *monenemy, t_PacMan * PacMan, int * compteur, BITMAP *dbbuffer);
time_t gestionSun(BITMAP* map,BITMAP * dbbuffer, t_Sun* Sun, t_PacMan* PacMan, BITMAP*front, time_t start);

//Version fonctionnelle
int death(t_enemy *monenemy[4], t_PacMan *PacMan, int compteur, BITMAP *dbbuffer);
void score(t_Diamant *Diamant[], t_PacMan *PacMan, int * compteur, int niveau);
void sauvegarde1( t_enemy *monenemy[],t_PacMan * PacMan, t_map * gestion_map);
void recuperation(t_enemy *enemy[], t_PacMan * PacMan, t_map * gestion_map,int choise_map);
void load_map(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[], int *fermeture);
void load_map1(int i,int niveau, int choise_map, int score_limit , int score_max, int * a, int stop, int  compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[], int *fermeture);




#endif // PROTOTYPES_H_INCLUDED
