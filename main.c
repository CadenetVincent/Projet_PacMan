//#include <stdio.h>
//#include <stdlib.h>
//#include <allegro.h>
#include "prototypes.h"

//Test push

void lancerAllegro()
{
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}





int main()
{
    int posx,posy;    // coordonnées
    int tx,ty;        // taille (largeur et hauteur)
    int deplacement;  // amplitude absolu des déplacements
    int pos_enemy[2][4]={{255,497,255,497},{283,283,640,640}};
    int i = 0;

    t_enemy * monenemy[4];

    BITMAP *test;
    BITMAP *map;
    BITMAP *perso_img;
    BITMAP * enemy;
    BITMAP * front;
    BITMAP * dbbuffer;

    lancerAllegro();
    int a = 0;
    int compteur_death = 80;

    /*tx=25;
    ty=25;
    posx=SCREEN_W/2-tx/2;
    posy=SCREEN_H/2-ty/2;
    deplacement=4;*/

    t_PacMan *bob;
    t_PacMan PacMan;
    bob = &PacMan;

    intialisationPacMan(bob);


    /*PacMan.tx = 25;
    PacMan.ty = 25;
    PacMan.posx = SCREEN_W/2-PacMan.tx/2;
    PacMan.posy = SCREEN_H/2-PacMan.ty/2;
    PacMan.deplacement = 4;*/



    srand(time(NULL));

    map = create_bitmap(SCREEN_W,SCREEN_H);
    dbbuffer = create_bitmap(SCREEN_W,SCREEN_H);
    front = load_bitmap("map_pac_man.bmp",NULL);
    //perso_img = load_bitmap("bonhomme_pc.bmp",NULL);
    test = load_bitmap("bufferpc.bmp",NULL);
    enemy = load_bitmap("enemy.bmp",NULL);

    if(!test)
    {
        printf("Erreur buffer !");
    }

for(i=0; i<4; i++)
{
monenemy[i] = initialiserenemy();
monenemy[i]->dposx= pos_enemy[0][i];
monenemy[i]->dposy= pos_enemy[1][i];
}

    while(!key[KEY_ESC])
    {
        stretch_blit(test, dbbuffer,0,0,test->w,test->h,0,0,SCREEN_W,SCREEN_H);

        //stretch_blit(test, map, 0,0,test->w,test->h,0,0,SCREEN_W,SCREEN_H);

        rectfill(dbbuffer, PacMan.posx,PacMan.posy, PacMan.posx+25, PacMan.posy+22, makecol(255,255,255));

        stretch_blit(front, map, 0,0,front->w,front->h,0,0,SCREEN_W,SCREEN_H);


       perso_img = deplacementPacMan(dbbuffer, &PacMan, &a);

       masked_blit(perso_img, map, 0,0,PacMan.posx,PacMan.posy,perso_img->w,perso_img->h);
       //draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
 //mort(&monenemy, &PacMan, &compteur,dbbuffer);

/// 47-40

        for(i=0; i<4; i++)
        {

        monenemy[i]->compteur_enemy++;

        if(monenemy[i]->compteur_enemy == 100)
        {
        monenemy[i]->resetdir=0;
        monenemy[i]->compteur_enemy=0;
        //mort(&monenemy[i], &PacMan, &compteur, dbbuffer);
        }

        call_monster(dbbuffer,enemy,monenemy[i],&PacMan);


        masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);

        }

 blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

 compteur_death++;

 compteur_death = death(monenemy, &PacMan, compteur_death,dbbuffer);







        rest(20);




    }

    return 0;
}
END_OF_MAIN();

