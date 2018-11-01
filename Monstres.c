#include "prototypes.h"


t_enemy * initialiserenemy()
{
    t_enemy *mmonstre;
    mmonstre=(t_enemy*) malloc(1 * sizeof(t_enemy));

    mmonstre->dposx= 0;
    mmonstre->dposy= 0;
    mmonstre->ddeplacement=3;
    mmonstre->ddirection = rand()%4;
    mmonstre->alive = 1;
    mmonstre->dtx=25;
    mmonstre->dty=25;
    mmonstre->resetdir=0;
    mmonstre->compteur_enemy = 0;


    return mmonstre;
}

void follow_monster(t_enemy * monenemy, t_PacMan *PacMan, BITMAP*dbbuffer)
{
    if(abs(monenemy->dposx - PacMan->posx) > abs(monenemy->dposy - PacMan->posy))
    {
        //GO LEFT NORMALY
        // Go left !
        if(monenemy->dposx - PacMan->posx > 0)
        {
            if (getpixel(dbbuffer,monenemy->dposx-monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
            {
                monenemy->dposx = monenemy->dposx-monenemy->ddeplacement;
            }
            else
            {

                //Go down !
                if(monenemy->dposy - PacMan->posy < 0)
                {
                    if(getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+monenemy->dty+monenemy->ddeplacement) != makecol(255,00,00))
                    {
                        monenemy->dposy = monenemy->dposy+monenemy->ddeplacement;
                    }
                }
                //Go up !
                else
                {
                    if (getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-monenemy->ddeplacement ) != makecol(255,00,00))
                    {
                        monenemy->dposy = monenemy->dposy-monenemy->ddeplacement;
                    }
                }



            }


        }
        //GO RIGHT NORMALY
        //Go right !
        else
        {
            if (getpixel(dbbuffer,monenemy->dposx+monenemy->dtx+monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
            {
                monenemy->dposx = monenemy->dposx+monenemy->ddeplacement; // mouvement négatif en abscisses
            }
            else
            {

                //Go down !
                if(monenemy->dposy - PacMan->posy < 0)
                {
                    if(getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+monenemy->dty+monenemy->ddeplacement) != makecol(255,00,00))
                    {
                        monenemy->dposy = monenemy->dposy+monenemy->ddeplacement;
                    }
                }
                //Go up !
                else
                {
                    if (getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-monenemy->ddeplacement ) != makecol(255,00,00))
                    {
                        monenemy->dposy = monenemy->dposy-monenemy->ddeplacement;
                    }
                }

            }

        }
    }
    if(abs(monenemy->dposy - PacMan->posy) > abs(monenemy->dposx - PacMan->posx))
    {
        //GO DOWN NORMALY
        //Go down !
        if(monenemy->dposy - PacMan->posy < 0)
        {
            if(getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+monenemy->dty+monenemy->ddeplacement) != makecol(255,00,00))
            {
                monenemy->dposy = monenemy->dposy+monenemy->ddeplacement;
            }
            else
            {

                // Go left !
                if(monenemy->dposx - PacMan->posx > 0)
                {
                    if (getpixel(dbbuffer,monenemy->dposx-monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
                    {
                        monenemy->dposx = monenemy->dposx-monenemy->ddeplacement;
                    }
                    // Go right !
                }
                else
                {
                    if (getpixel(dbbuffer,monenemy->dposx+monenemy->dtx+monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
                    {
                        monenemy->dposx = monenemy->dposx+monenemy->ddeplacement; // mouvement négatif en abscisses
                    }
                }
            }
        }

        //GO UP NORMALY
        //Go up !
        else
        {
            if (getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-monenemy->ddeplacement ) != makecol(255,00,00))
            {
                monenemy->dposy = monenemy->dposy-monenemy->ddeplacement;
            }
            else
            {

                // Go left !
                if(monenemy->dposx - PacMan->posx > 0)
                {
                    if (getpixel(dbbuffer,monenemy->dposx-monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
                    {
                        monenemy->dposx = monenemy->dposx-monenemy->ddeplacement;
                    }
                    // Go right !
                }
                else
                {
                    if (getpixel(dbbuffer,monenemy->dposx+monenemy->dtx+monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
                    {
                        monenemy->dposx = monenemy->dposx+monenemy->ddeplacement; // mouvement négatif en abscisses
                    }
                }

            }

        }

    }
}


BITMAP * call_monster(BITMAP*dbbuffer,t_enemy * monenemy, t_PacMan *PacMan)
{
    BITMAP * enemy = load_bitmap("enemy.bmp",NULL);;

    if((monenemy->alive == 1))
    {
        if((monenemy->dposx - PacMan->posx > -150) && (monenemy->dposy - PacMan->posy > -150) && (monenemy->dposx - PacMan->posx < 150) && (monenemy->dposy - PacMan->posy < 150))
        {
            enemy = load_bitmap("enemy_follow.bmp",NULL);

            monenemy->ddeplacement = 4;

            follow_monster(monenemy, PacMan, dbbuffer);

        }
        else
        {
            monenemy->ddeplacement = 3;

            if(monenemy->ddirection == 0)
            {

                if(monenemy->resetdir !=1 && getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-monenemy->ddeplacement-5) != makecol(121,255,63))
                {
                    monenemy->ddirection= rand()%4;
                    monenemy->resetdir=1;

                }
                else if (getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-monenemy->ddeplacement ) != makecol(255,00,00))
                {
                    monenemy->dposy = monenemy->dposy-monenemy->ddeplacement;
                }
                else
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

                }
                else if(getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+monenemy->dty+monenemy->ddeplacement) != makecol(255,00,00))
                {

                    monenemy->dposy = monenemy->dposy+monenemy->ddeplacement;


                }
                else
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

                }
                else if (getpixel(dbbuffer,monenemy->dposx-monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
                {
                    monenemy->dposx = monenemy->dposx-monenemy->ddeplacement; // mouvement négatif en abscisses
                }
                else
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

                }
                else if (getpixel(dbbuffer,monenemy->dposx+monenemy->dtx+monenemy->ddeplacement,monenemy->dposy) != makecol(255,00,00))
                {
                    monenemy->dposx = monenemy->dposx+monenemy->ddeplacement; // mouvement négatif en abscisses
                }
                else
                {
                    monenemy->ddirection = 1;
                    monenemy->resetdir=0;
                }
            }
        }

    }

    /*if(getpixel(dbbuffer,monenemy->dposx-5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx+5,monenemy->dposy) == makecol(255,255,255) || getpixel(dbbuffer,monenemy->dposx,monenemy->dposy+5) == makecol(255,255,255) ||getpixel(dbbuffer,monenemy->dposx,monenemy->dposy-5) == makecol(255,255,255)  )
    {


    }
    /*printf("%d",monenemy->resetdir);*/

//mort(&monenemy, &PacMan, &compteur, dbbuffer);

    if (monenemy->dposx+monenemy->dtx<0)
        monenemy->dposx = SCREEN_W+monenemy->dposx+monenemy->dtx;
    if (monenemy->dposx>=SCREEN_W)
        monenemy->dposx = monenemy->dposx-SCREEN_W-monenemy->dtx;
    if (monenemy->dposy+monenemy->dty<0)
        monenemy->dposy = SCREEN_H+monenemy->dposy+monenemy->dty;
    if (monenemy->dposy>=SCREEN_H)
        monenemy->dposy = monenemy->dposy-SCREEN_H-monenemy->dty;

    return enemy;
}


BITMAP * deplacementPacMan(BITMAP *dbbuffer, t_PacMan *PacMan, int *a)
{
    BITMAP * sprite_pacman = load_bitmap("pacman_sprites/pacman_right_0.bmp",NULL);

    if (key[KEY_UP] && getpixel(dbbuffer,PacMan->posx,PacMan->posy-PacMan->deplacement -7 ) != makecol(255,0,0) && getpixel(dbbuffer,PacMan->posx+25,PacMan->posy-PacMan->deplacement - 7 ) != makecol(255,0,0) )
    {
        *a = 1;
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_up, 3);
    }
    if (key[KEY_DOWN] && getpixel(dbbuffer,PacMan->posx,PacMan->posy+PacMan->ty+PacMan->deplacement + 13 ) != makecol(255,00,00)&& getpixel(dbbuffer,PacMan->posx + 25,PacMan->posy+PacMan->ty+PacMan->deplacement+13 ) != makecol(255,00,00))
    {
        *a = 2;
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_right, 8);
    }
    if (key[KEY_LEFT] && getpixel(dbbuffer,PacMan->posx-PacMan->deplacement -20,PacMan->posy) != makecol(255,00,00)&& getpixel(dbbuffer,PacMan->posx-PacMan->deplacement - 20,PacMan->posy + 22) != makecol(255,00,00))
    {
        *a = 3;
        PacMan->turn_img = 1;
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_right, 8);
    }
    if (key[KEY_RIGHT] && getpixel(dbbuffer,PacMan->posx+PacMan->tx+PacMan->deplacement +25,PacMan->posy ) != makecol(255,00,00)&& getpixel(dbbuffer,PacMan->posx+PacMan->tx+PacMan->deplacement + 25,PacMan->posy + 22) != makecol(255,00,00))
    {
        *a = 4;
        PacMan->turn_img = 0;
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_bot, 2);
    }

    if ( *a == 1 && getpixel(dbbuffer,PacMan->posx,PacMan->posy-PacMan->deplacement ) != makecol(255,00,00))
    {
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_up, 3);
        PacMan->posy = PacMan->posy-PacMan->deplacement;// mouvement négatif en ordonnées
        //printf("%d \n", a);
    }
    else
    {
        PacMan->posy = PacMan->posy;
    }
    if (*a == 2 && getpixel(dbbuffer,PacMan->posx,PacMan->posy+PacMan->ty+PacMan->deplacement + 13 ) != makecol(255,0,0))
    {
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_right, 8);
        PacMan->posy = PacMan->posy+PacMan->deplacement;// mouvement positif en ordonnées
    }
    else
    {
        PacMan->posy = PacMan->posy;

    }
    if (*a == 3 && getpixel(dbbuffer,PacMan->posx-PacMan->deplacement,PacMan->posy) != makecol(255,00,00))
    {
        PacMan->turn_img = 1;
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_bot, 2);
        PacMan->posx = PacMan->posx-PacMan->deplacement; // mouvement négatif en abscisses
    }
    else
    {
        PacMan->posx = PacMan->posx;
    }
    if (*a == 4 && getpixel(dbbuffer,PacMan->posx+PacMan->tx+PacMan->deplacement + 25,PacMan->posy  ) != makecol(255,00,00))
    {
        PacMan->turn_img = 0;
        sprite_pacman = action_sprite_pacman(PacMan, PacMan->pacman_right, 8);
        PacMan->posx = PacMan->posx+PacMan->deplacement; // mouvement positif en abscisses
    }
    else
    {
        PacMan->posx = PacMan->posx;
    }

    // contrôle des bords
    if (PacMan->posx+PacMan->tx<0)
        PacMan->posx = SCREEN_W+PacMan->posx+PacMan->tx;
    if (PacMan->posx>=SCREEN_W)
        PacMan->posx = PacMan->posx-SCREEN_W-PacMan->tx;
    if (PacMan->posy+PacMan->ty<0)
        PacMan->posy = SCREEN_H+PacMan->posy+PacMan->ty;
    if (PacMan->posy>=SCREEN_H)
        PacMan->posy = PacMan->posy-SCREEN_H-PacMan->ty;

    return sprite_pacman;


    //printf("%d \n", PacMan->vies);
}

BITMAP* action_sprite_pacman(t_PacMan*PacMan, BITMAP*mabitmap[], int taille_max)
{

    PacMan->compteur++;

    if(PacMan->compteur >= PacMan->temporiseur)
    {
        PacMan->image_actuelle++;
        PacMan->compteur=0;
    }
    if(PacMan->image_actuelle >= taille_max)
    {
        PacMan->image_actuelle = 0;
    }

    return mabitmap[PacMan->image_actuelle];

}


void intialisationPacMan(t_PacMan *PacMan)
{
    int i;
    char nomfichier[100];
    PacMan->tx = 15;
    PacMan->ty = 15;
    PacMan->posx = SCREEN_W/2-PacMan->tx/2;
    PacMan->posy = SCREEN_H/2-PacMan->ty/2;
    PacMan->deplacement = 7;
    PacMan->vies = 5;
    PacMan->turn_img = 0;

    //Traitement image sprites
    PacMan->compteur = 0;
    PacMan->temporiseur = 8;
    PacMan->image_actuelle = 0;

    //Image bottom
    for(i=0; i<2; i++)
    {
        sprintf(nomfichier,"pacman_sprites/pacman_bot_%d.bmp",i);
        PacMan->pacman_bot[i]=load_bitmap(nomfichier,NULL);
        if (!PacMan->pacman_bot[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    //Image right
    for(i=0; i<8; i++)
    {
        sprintf(nomfichier,"pacman_sprites/pacman_right_%d.bmp",i);
        PacMan->pacman_right[i]=load_bitmap(nomfichier,NULL);
        if (!PacMan->pacman_right[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    //Image up
    for(i=0; i<3; i++)
    {
        sprintf(nomfichier,"pacman_sprites/pacman_up_%d.bmp",i);
        PacMan->pacman_up[i]=load_bitmap(nomfichier,NULL);
        if (!PacMan->pacman_up[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }


    PacMan->score = 0;

}

int death(t_enemy *monenemy[], t_PacMan *PacMan, int compteur, BITMAP *dbbuffer)
{

    int i;

    for(i=0; i<4; i++)
    {
        if((compteur>=100) && ( monenemy[i]->dposx - PacMan->posx < 15 ) && ( monenemy[i]->dposx - PacMan->posx > -15 ) && ( monenemy[i]->dposy - PacMan->posy <15 ) && ( monenemy[i]->dposy - PacMan->posy > -15 ))
        {
            PacMan->vies = PacMan->vies-1;
            return 0;
        }

    }

    return compteur;


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

//printf("%d \n", PacMan->vies);
}

t_Diamant * initialiserDiamants()
{
    t_Diamant *Diamant;
    Diamant=(t_Diamant*) malloc(1 * sizeof(t_Diamant));

    Diamant->posx = 0;
    Diamant->posy = 0;
    Diamant->boolean = 0;

    return Diamant;
}

void gestionDiamant(BITMAP * dbbuffer, t_Diamant* Diamant,BITMAP * front, int * stop)
{
    int compteur = 1;
    int compteur2 = 0;



    while(Diamant->posx == 0 || Diamant->posy == 0 || compteur == 1 && *stop != 4)
    {

        compteur2 = 0;
        Diamant->posx = (rand() % (760 - 20 + 1)) + 20;
        Diamant->posy = (rand() % (560 - 20 + 1)) + 20;

        printf("%d\n", Diamant->posx);
        printf("%d\n", Diamant->posy);



        if(getpixel(dbbuffer, Diamant->posx+30, Diamant->posy+30) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx+15, Diamant->posy+15) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx, Diamant->posy+30) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx, Diamant->posy+15) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx+30, Diamant->posy) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx, Diamant->posy) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx+15, Diamant->posy) == makecol(255,0,0))
        {
            compteur2++;
            printf("ERTYU\n");
        }



        if(compteur2 == 0)
        {
            compteur = 0;
            (*stop)++;
            //printf("423456787654\n");
        }
        /*else
        {
            compteur = 1;
        }*/


    }

    //printf("%d \n", *stop);



}

void suppressionDiamant(BITMAP * dbbuffer, t_Diamant * Diamant, t_PacMan * PacMan)
{
    if(getpixel(dbbuffer, Diamant->posx + 15, Diamant->posy) == makecol(255,255,255) ||getpixel(dbbuffer, Diamant->posx + 15, Diamant->posy+30) == makecol(255,255,255)||getpixel(dbbuffer, Diamant->posx, Diamant->posy+15) == makecol(255,255,255)||getpixel(dbbuffer, Diamant->posx + 15, Diamant->posy+30  ) == makecol(255,255,255))
    {
        Diamant->boolean = 1;
        //PacMan->score = PacMan->score + 1;
        printf("%d\n", PacMan->score);

    }




}

void score(t_Diamant *Diamant[], t_PacMan *PacMan, int * compteur, int niveau)
{
    if(niveau == 0)
    {
        *compteur = 0;
    }
    else if(niveau == 1)
    {
        *compteur = 4;
    }
    else if(niveau == 2)
    {
        *compteur = 8;
    }
    for(int i = 0; i < 4; i++)
    {
        if(Diamant[i]->boolean == 1)
        {
            *compteur = *compteur + 1;
        }
    }

    PacMan->score = *compteur;

    printf("%d zsdfghgfdsdfgh \n\n", PacMan->score);

}


