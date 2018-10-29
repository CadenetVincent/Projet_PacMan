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

void call_monster(BITMAP*dbbuffer, BITMAP*enemy,t_enemy * monenemy, t_PacMan *PacMan, int *compteur )
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
            monenemy->dposx = monenemy->dposx-monenemy->ddeplacement; // mouvement n�gatif en abscisses
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
            monenemy->dposx = monenemy->dposx+monenemy->ddeplacement; // mouvement n�gatif en abscisses
        }else
        {
            monenemy->ddirection = 1;
            monenemy->resetdir=0;
        }
        }

    }

    /*if(getpixel(dbbuffer,monenemy->dposx-5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx+5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+5) == makecol(255,255,255) ||getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-5) == makecol(255,255,255)  )
    {


    }
/*printf("%d",monenemy->resetdir);*/

mort(&monenemy, &PacMan, &compteur, dbbuffer);

        if (monenemy->dposx+monenemy->dtx<0)
            monenemy->dposx = SCREEN_W+monenemy->dposx+monenemy->dtx;
        if (monenemy->dposx>=SCREEN_W)
            monenemy->dposx = monenemy->dposx-SCREEN_W-monenemy->dtx;
        if (monenemy->dposy+monenemy->dty<0)
            monenemy->dposy = SCREEN_H+monenemy->dposy+monenemy->dty;
        if (monenemy->dposy>=SCREEN_H)
            monenemy->dposy = monenemy->dposy-SCREEN_H-monenemy->dty;
}


void deplacementPacMan(BITMAP *dbbuffer, t_PacMan *PacMan, int *a)
{

    if (key[KEY_UP] && getpixel(dbbuffer,PacMan->posx,PacMan->posy-PacMan->deplacement -7 ) != makecol(255,0,0) && getpixel(dbbuffer,PacMan->posx+25,PacMan->posy-PacMan->deplacement - 7 ) != makecol(255,0,0) )
        {
            *a = 1;

        }
        if (key[KEY_DOWN] && getpixel(dbbuffer,PacMan->posx,PacMan->posy+PacMan->ty+PacMan->deplacement + 13 ) != makecol(255,00,00)&& getpixel(dbbuffer,PacMan->posx + 25,PacMan->posy+PacMan->ty+PacMan->deplacement+13 ) != makecol(255,00,00))
        {
            *a = 2;
        }
        if (key[KEY_LEFT] && getpixel(dbbuffer,PacMan->posx-PacMan->deplacement -20,PacMan->posy) != makecol(255,00,00)&& getpixel(dbbuffer,PacMan->posx-PacMan->deplacement - 20,PacMan->posy + 22) != makecol(255,00,00))
        {
            *a = 3;
        }
        if (key[KEY_RIGHT] && getpixel(dbbuffer,PacMan->posx+PacMan->tx+PacMan->deplacement +25,PacMan->posy ) != makecol(255,00,00)&& getpixel(dbbuffer,PacMan->posx+PacMan->tx+PacMan->deplacement + 25,PacMan->posy + 22) != makecol(255,00,00))
        {
            *a = 4;
        }

        if ( *a == 1 && getpixel(dbbuffer,PacMan->posx,PacMan->posy-PacMan->deplacement ) != makecol(255,00,00))
        {
            PacMan->posy = PacMan->posy-PacMan->deplacement;// mouvement n�gatif en ordonn�es
            //printf("%d \n", a);
        }
        else
        {
            PacMan->posy = PacMan->posy;
        }
        if (*a == 2 && getpixel(dbbuffer,PacMan->posx,PacMan->posy+PacMan->ty+PacMan->deplacement + 13 ) != makecol(255,0,0))
        {
            PacMan->posy = PacMan->posy+PacMan->deplacement;// mouvement positif en ordonn�es


        }
        else
        {
            PacMan->posy = PacMan->posy;

        }
        if (*a == 3 && getpixel(dbbuffer,PacMan->posx-PacMan->deplacement,PacMan->posy) != makecol(255,00,00))
        {
            PacMan->posx = PacMan->posx-PacMan->deplacement; // mouvement n�gatif en abscisses
        }
        else
        {
            PacMan->posx = PacMan->posx;
        }
        if (*a == 4 && getpixel(dbbuffer,PacMan->posx+PacMan->tx+PacMan->deplacement + 25,PacMan->posy  ) != makecol(255,00,00))
        {
            PacMan->posx = PacMan->posx+PacMan->deplacement; // mouvement positif en abscisses
        }
        else
        {
         PacMan->posx = PacMan->posx;
        }

        // contr�le des bords
        if (PacMan->posx+PacMan->tx<0)
            PacMan->posx = SCREEN_W+PacMan->posx+PacMan->tx;
        if (PacMan->posx>=SCREEN_W)
            PacMan->posx = PacMan->posx-SCREEN_W-PacMan->tx;
        if (PacMan->posy+PacMan->ty<0)
            PacMan->posy = SCREEN_H+PacMan->posy+PacMan->ty;
        if (PacMan->posy>=SCREEN_H)
            PacMan->posy = PacMan->posy-SCREEN_H-PacMan->ty;


            //printf("%d \n", PacMan->vies);
}

void intialisationPacMan(t_PacMan *PacMan)
{
    PacMan->tx = 15;
    PacMan->ty = 15;
    PacMan->posx = SCREEN_W/2-PacMan->tx/2;
    PacMan->posy = SCREEN_H/2-PacMan->ty/2;
    PacMan->deplacement = 4;
    PacMan->vies = 5;
}

void mort(t_enemy *monenemy, t_PacMan *PacMan, int *compteur, BITMAP *dbbuffer)
{

    if(getpixel(dbbuffer,monenemy->dposx-5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx+5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+5) == makecol(255,255,255) ||getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-5) == makecol(255,255,255)  && *compteur == 0)
      PacMan->vies = 4;
else if(getpixel(dbbuffer, monenemy->dposx, monenemy->dposy)!= makecol(255,255,255) && PacMan->vies == 4)
    *compteur = 1;
else if(getpixel(dbbuffer,monenemy->dposx-5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx+5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+5) == makecol(255,255,255) ||getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-5) == makecol(255,255,255)  && *compteur == 1)
    PacMan->vies = 3;
else if(getpixel(dbbuffer, monenemy->dposx, monenemy->dposy)!= makecol(255,255,255) && PacMan->vies == 3)
    *compteur = 2;
else if(getpixel(dbbuffer,monenemy->dposx-5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx+5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+5) == makecol(255,255,255) ||getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-5) == makecol(255,255,255)  && *compteur == 2)
    PacMan->vies = 2;
else if(getpixel(dbbuffer, monenemy->dposx, monenemy->dposy)!= makecol(255,255,255) && PacMan->vies == 2)
    *compteur = 3;
else if(getpixel(dbbuffer,monenemy->dposx-5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx+5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+5) == makecol(255,255,255) ||getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-5) == makecol(255,255,255) && *compteur == 3)
    PacMan->vies = 1;
else if(getpixel(dbbuffer, monenemy->dposx, monenemy->dposy)!= makecol(255,255,255) && PacMan->vies == 1)
    *compteur = 4;
else if(getpixel(dbbuffer,monenemy->dposx-5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx+5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+5) == makecol(255,255,255) ||getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-5) == makecol(255,255,255)  && *compteur == 4)
    PacMan->vies = 0;

//    printf("%d  \n", compteur);

printf("%d \n", PacMan->vies);
}



