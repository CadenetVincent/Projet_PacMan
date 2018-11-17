#include "prototypes.h"

void consoleDeplacementPacMan(int *a, t_PacMan * PacMan, char  key, int bord,int * tab[20][50])
{
//gotoligcol(PacMan->posx,PacManposy);
//printf("%d", tab[PacMan->posx-1][PacMan->posy]);
     if (key == 'z' && tab[PacMan->posx-1][PacMan->posy] != 1 )
    {
        *a = 1;

    }
    else if (key == 's' && tab[PacMan->posx+1][PacMan->posy] != 1 )
    {
        *a = 2;
    }
    else if (key == 'd'&& tab[PacMan->posx][PacMan->posy+1] != 1 )
    {
        *a = 3;
    }
    else if (key == 'q'&& tab[PacMan->posx][PacMan->posy-1] != 1 )
    {
        *a = 4;
    }

    if ( *a == 1 && tab[PacMan->posx-1][PacMan->posy] != 1)
    {
        PacMan->posx -= 1;
        if(bord == 1)
        {
            if(PacMan->posx < 1)
        {
            PacMan->posx= 1;
        }
        }
        else if( bord == 0)
        {
            if(PacMan->posx < 1)
        {
            PacMan->posx= 18;
        }
        }



    }
    else if (*a == 2 && tab[PacMan->posx + 1][PacMan->posy] != 1 )
    {
       PacMan->posx+= 1;
       if(bord == 1)
       {
           if(PacMan->posx > 18)
        {
            PacMan->posx = 18;
        }
       }
       else if(bord == 0)
       {
            if(PacMan->posx > 18)
        {
            PacMan->posx = 1;
        }
       }

    }
    else if (*a == 3 && tab[PacMan->posx][PacMan->posy+1] != 1 )
    {
       PacMan->posy += 1;
       if(bord == 1)
       {
           if(PacMan->posy > 48)
        {
            PacMan->posy = 48;
        }
       }
       else if(bord == 0)
       {
            if(PacMan->posy > 48)
        {
            PacMan->posy = 1;
        }
       }

    }
    else if (*a == 4 && tab[PacMan->posx][PacMan->posy-1] != 1 )
    {
        PacMan->posy -= 1;
        if(bord == 1)
        {
            if(PacMan->posy< 1)
        {
            PacMan->posy = 1;
        }
        }
        else if (bord == 0)
        {
             if(PacMan->posy< 1)
        {
            PacMan->posy = 48;
        }
        }

    }
    //printf("%d ceci est x", *x);
//printf("%d xxxx " , (*x));
}

void gotoligcol( int lig, int col )
{
//ressources
COORD mycoord;

mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void intialisationPacManConsole(t_PacMan *PacMan)
{
    int i;
    char nomfichier[100];

    PacMan->tx = 15;
    PacMan->ty = 15;
    PacMan->posx = (rand() % 19) + 1;
    PacMan->posy = (rand() % 47) + 2;
    PacMan->deplacement = 7;
    PacMan->vies = 5;
    PacMan->turn_img = 0;
    PacMan->last_posx = 0;
    PacMan->last_posy = 0;
    PacMan->direction = 0;
    PacMan->last_direction = 0;

    PacMan->score = 0;

}


void chargementMap(char nom[], int * tab[20][50], int * bord)
{
     FILE * fichier = NULL;
    fichier = fopen(nom, "r");
     if(fichier != NULL)
    {

        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 50; j ++)
            {
                 fscanf(fichier,"%d", &tab[i][j]);

            }
        }
    }
    else
    {
        printf("impossible d'ouvrir le fichier \n");
    }

     for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 50; j ++)
            {
                if(tab[i][j] == 0)
                {
                    printf(" ");
                }
                else if(tab[0][j] == 1)
                {
                    printf("-");
                    *bord = 1;
                }
                else if(tab[0][j] == 2)
                {
                    printf("|");
                    *bord = 0;
                }


            }
            printf("\n");
        }

}
