#include "prototypes.h"

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

        if(getpixel(dbbuffer, Diamant->posx+30, Diamant->posy+30) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx+15, Diamant->posy+15) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx, Diamant->posy+30) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx, Diamant->posy+15) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx+30, Diamant->posy) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx, Diamant->posy) == makecol(255,0,0) || getpixel(dbbuffer, Diamant->posx+15, Diamant->posy) == makecol(255,0,0))
        {
            compteur2++;
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
    else if(niveau == 3)
    {
        *compteur = 14;
    }

    //printf("%d",PacMan->get_Sun);
    /*if(PacMan->get_Sun > 3)
    {
        *compteur = *compteur + PacMan->get_Sun;
    }*/

    for(int i = 0; i < 4; i++)
    {


        if(Diamant[i]->boolean == 1)
        {
            *compteur = *compteur + 1;


        }
    }

    PacMan->score = *compteur;
    //printf("%d\n\n", *compteur);

}

