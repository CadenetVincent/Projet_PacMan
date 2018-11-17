#include "prototypes.h"

void consoleDeplacementPacMan(int *a, t_PacMan * PacMan, char  key)
{

     if (key == 'z' )
    {
        *a = 1;

    }
    else if (key == 's' )
    {
        *a = 2;
    }
    else if (key == 'd' )
    {
        *a = 3;
    }
    else if (key == 'q' )
    {
        *a = 4;
    }

    if ( *a == 1 )
    {
        PacMan->posx -= 1;
        if(PacMan->posx < 1)
        {
            PacMan->posx= 1;
        }


    }
    else if (*a == 2  )
    {
       PacMan->posx+= 1;
       if(PacMan->posx > 18)
        {
            PacMan->posx = 18;
        }
    }
    else if (*a == 3  )
    {
       PacMan->posy += 1;
       if(PacMan->posy > 48)
        {
            PacMan->posy = 48;
        }
    }
    else if (*a == 4 )
    {
        PacMan->posy -= 1;
        if(PacMan->posy< 1)
        {
            PacMan->posy = 1;
        }
    }
    //printf("%d ceci est x", *x);
//printf("%d xxxx " , (*x));
}


void intialisationPacManConsole(t_PacMan *PacMan)
{
    int i;
    char nomfichier[100];

    PacMan->tx = 15;
    PacMan->ty = 15;
    PacMan->posx = (rand() % 19) + 1;
    PacMan->posy = (rand() % 48) + 1;
    PacMan->deplacement = 7;
    PacMan->vies = 5;
    PacMan->turn_img = 0;
    PacMan->last_posx = 0;
    PacMan->last_posy = 0;
    PacMan->direction = 0;
    PacMan->last_direction = 0;

    //Traitement image sprites
    PacMan->compteur = 0;
    PacMan->temporiseur = 8;
    PacMan->image_actuelle = 0;

    //Image bottom
    /*for(i=0; i<2; i++)
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
*/

    PacMan->score = 0;

}
