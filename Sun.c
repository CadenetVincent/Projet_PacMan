#include "prototypes.h"

t_Sun * initialiserSun()
{
    int i = 0;
    char nomfichier[100];
    t_Sun *Sun;
    Sun = (t_Sun*) malloc(1 * sizeof(t_Sun));
    Sun->actuel_map = NULL;

    Sun->boolean=0;
    Sun->posx=0;
    Sun->posy=0;

    for(i=0; i<6; i++)
    {
        sprintf(nomfichier,"pacman_sprites/SOLEIL%d.bmp",i);
        Sun->SOLEIL[i]=load_bitmap(nomfichier,NULL);
        if (!Sun->SOLEIL[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }


    return Sun;
}

time_t gestionSun(BITMAP* map,BITMAP * dbbuffer, t_Sun* Sun, t_PacMan* PacMan, BITMAP*front, time_t start)
{
    int compteur = 0;

    if(PacMan->score >= 15)
    {
        compteur = (int)(time(NULL) - start);
    }
    printf("start : %d \n",start);
    printf("compteur : %d \n",compteur);

    if(compteur > 5 && compteur < 15 && Sun->boolean == 0)
    {

        while((Sun->posx == 0) || (Sun->posy == 0))
        {
            Sun->posx = (rand() % (760 - 20 + 1)) + 20;
            Sun->posy = (rand() % (560 - 20 + 1)) + 20;

            if(getpixel(dbbuffer, Sun->posx+30, Sun->posy+30) == makecol(255,0,0) || getpixel(dbbuffer, Sun->posx+15, Sun->posy+15) == makecol(255,0,0) || getpixel(dbbuffer, Sun->posx, Sun->posy+30) == makecol(255,0,0) || getpixel(dbbuffer, Sun->posx, Sun->posy+15) == makecol(255,0,0) || getpixel(dbbuffer, Sun->posx+30, Sun->posy) == makecol(255,0,0) || getpixel(dbbuffer, Sun->posx, Sun->posy) == makecol(255,0,0) || getpixel(dbbuffer, Sun->posx+15, Sun->posy) == makecol(255,0,0))
            {
                Sun->posx = 0;
                Sun->posy = 0;
            }
        }

        Sun->boolean = 1;
        printf("L");
    }


    if((compteur > 20))
    {
        start = time(NULL);
        compteur = 0;
        Sun->boolean = 0;
        Sun->posx=0;
        Sun->posy=0;
    }


    return start;

}



