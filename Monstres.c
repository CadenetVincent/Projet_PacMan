#include "prototypes.h"


t_enemy * initialiserenemy()
{
    t_enemy *mmonstre;
    mmonstre=(t_enemy*) malloc(1 * sizeof(t_enemy));

    mmonstre->dposx= 0;
    mmonstre->dposy= 0;
    mmonstre->ddeplacement=2;
    mmonstre->ddirection = rand()%4;
    mmonstre->alive = 1;
    mmonstre->dtx=25;
    mmonstre->dty=25;
    mmonstre->resetdir=0;
    mmonstre->compteur_enemy = 0;


    return mmonstre;
}

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





