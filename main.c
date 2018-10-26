#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "prototypes.h"


t_enemy * initialiserenemy();
void call_monster(BITMAP*dbbuffer, BITMAP*enemy,t_enemy * monenemy);



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
    BITMAP *map1;
    BITMAP * enemy;
    BITMAP * front;
    BITMAP * dbbuffer;
    lancerAllegro();
    int a = 0;

    tx=25;
    ty=25;
    posx=SCREEN_W/2-tx/2;
    posy=SCREEN_H/2-ty/2;
    deplacement=4;



    srand(time(NULL));

    map = create_bitmap(SCREEN_W,SCREEN_H);
    dbbuffer = create_bitmap(SCREEN_W,SCREEN_H);
    front = load_bitmap("map_pac_man.bmp",NULL);
    map1 = load_bitmap("bonhomme_pc.bmp",NULL);
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

        stretch_blit(front, map, 0,0,front->w,front->h,0,0,SCREEN_W,SCREEN_H);

        masked_blit(map1, map, 0,0,posx,posy,map1->w,map1->h);




        for(i=0; i<4; i++)
        {

        monenemy[i]->compteur_enemy++;

        if(monenemy[i]->compteur_enemy == 100)
        {
        monenemy[i]->resetdir=0;
        monenemy[i]->compteur_enemy=0;
        }

        call_monster(dbbuffer,enemy,monenemy[i]);


        masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);

        }

         blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);



        if (key[KEY_UP])
        {
            a = 1;
        }
        if (key[KEY_DOWN])
        {
            a = 2;
        }
        if (key[KEY_LEFT])
        {
            a = 3;
        }
        if (key[KEY_RIGHT])
        {
            a = 4;
        }

        if ( a == 1 && getpixel(dbbuffer,posx,posy-deplacement ) != makecol(255,00,00))
        {
            posy = posy-deplacement;// mouvement négatif en ordonnées
        }
        else
        {
            posy = posy;
        }
        if (a == 2 && getpixel(dbbuffer,posx,posy+ty+deplacement ) != makecol(255,00,00))
        {
            posy = posy+deplacement;// mouvement positif en ordonnées

        }
        else
        {
            posy = posy;
        }
        if (a == 3 && getpixel(dbbuffer,posx-deplacement,posy) != makecol(255,00,00))
        {
            posx = posx-deplacement; // mouvement négatif en abscisses
        }
        else
        {
            posx = posx;
        }
        if (a == 4 && getpixel(dbbuffer,posx+tx+deplacement,posy ) != makecol(255,00,00))
        {
            posx = posx+deplacement; // mouvement positif en abscisses
        }
        else
        {
         posx = posx;
        }

        // contrôle des bords
        if (posx+tx<0)
            posx = SCREEN_W+posx+tx;
        if (posx>=SCREEN_W)
            posx = posx-SCREEN_W-tx;
        if (posy+ty<0)
            posy = SCREEN_H+posy+ty;
        if (posy>=SCREEN_H)
            posy = posy-SCREEN_H-ty;

        // 3) AFFICHAGE NOUVELLE POSITION
        //rectfill(screen,posx,posy,posx+tx,posy+ty,makecol(255,128,128));


        // 4) ON FAIT UNE PETITE PAUSE à chaque fois sinon ça va trop vite...
        rest(20);



/*
        if (getpixel(map,posx,posy-deplacement ) == makecol(255,0,0))
        {
            printf("%d \n", i);
            i++;
        }
*/

    }
    // paramètres de l'élément à animer




    // initialisation des variables de la forme

    // tailles et position initiale au centre


    // mouvements :
    // se déplacera de 5 pixels à chaque étape de déplacement


    // Boucle interactive

    return 0;
}
END_OF_MAIN();

void call_monster(BITMAP*dbbuffer, BITMAP*enemy,t_enemy * monenemy)
{

    if(monenemy->alive == 1)
    {
        if(monenemy->ddirection == 0)
        {

        if(monenemy->resetdir !=1 && getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-monenemy->ddeplacement-5) != makecol(121,255,63))
        {
            monenemy->ddirection= rand()%4;
            monenemy->resetdir=1;

        }else if (getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-monenemy->ddeplacement ) != makecol(255,00,00))
        {
            monenemy->dposy = monenemy->dposy-monenemy->ddeplacement;
        }else
        {
            monenemy->ddirection = 2;
            monenemy->resetdir=0;

        }

        }

        if(monenemy->ddirection == 1)
        {

        if(monenemy->resetdir !=1 && getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+monenemy->dty+monenemy->ddeplacement+5) != makecol(121,255,63))
        {
            monenemy->ddirection= rand()%4;
            monenemy->resetdir=1;

        }else if(getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+monenemy->dty+monenemy->ddeplacement) != makecol(255,00,00))
        {

          monenemy->dposy = monenemy->dposy+monenemy->ddeplacement;


        }else
        {
            monenemy->ddirection = 3;
            monenemy->resetdir=0;
        }

        }

        if(monenemy->ddirection == 2)
        {

        if(monenemy->resetdir !=1 && getpixel(dbbuffer,monenemy->dposx-monenemy->ddeplacement-5,monenemy->dposy) != makecol(121,255,63))
        {
            monenemy->ddirection= rand()%4;
            monenemy->resetdir=1;

        }else if (getpixel(dbbuffer,monenemy->dposx-monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
        {
            monenemy->dposx = monenemy->dposx-monenemy->ddeplacement; // mouvement négatif en abscisses
        }else
        {
            monenemy->ddirection = 0;
            monenemy->resetdir=0;
        }

        }

        if(monenemy->ddirection == 3)
        {

        if(monenemy->resetdir !=1 && getpixel(dbbuffer,monenemy->dposx+monenemy->dtx+monenemy->ddeplacement+5,monenemy->dposy) != makecol(121,255,63))
        {
            monenemy->ddirection= rand()%4;
            monenemy->resetdir=1;

        }else if (getpixel(dbbuffer,monenemy->dposx+monenemy->dtx+monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
        {
            monenemy->dposx = monenemy->dposx+monenemy->ddeplacement; // mouvement négatif en abscisses
        }else
        {
            monenemy->ddirection = 1;
            monenemy->resetdir=0;
        }
        }

    }
printf("%d",monenemy->resetdir);

        if (monenemy->dposx+monenemy->dtx<0)
            monenemy->dposx = SCREEN_W+monenemy->dposx+monenemy->dtx;
        if (monenemy->dposx>=SCREEN_W)
            monenemy->dposx = monenemy->dposx-SCREEN_W-monenemy->dtx;
        if (monenemy->dposy+monenemy->dty<0)
            monenemy->dposy = SCREEN_H+monenemy->dposy+monenemy->dty;
        if (monenemy->dposy>=SCREEN_H)
            monenemy->dposy = monenemy->dposy-SCREEN_H-monenemy->dty;
}

