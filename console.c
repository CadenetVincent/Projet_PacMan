#include "prototypes.h"

t_chen * init_chenille(int place)
{
    t_chen *chenille;
    chenille=(t_chen*) malloc(1 * sizeof(t_chen));

    chenille->coordX = 0;
    chenille->coordY = 0;
    chenille->ancienX = 0;
    chenille->ancienY = 0;
    chenille->position = place;
    chenille->Adir = 0;
    chenille->dir = 0;

    return chenille;
}


void consoleDeplacementPacMan(int *a, t_PacMan * PacMan, char  *key, int bord,int * tab[20][50], float x, t_chen * Chenille[30],int diff_score)
{
    for (int i = 0; i<diff_score; i++)
    {
    Chenille[i]->ancienX =Chenille[i]->coordX;
    Chenille[i]->ancienY =Chenille[i]->coordY;
    }

    PacMan->last_posx = PacMan->posx;
    PacMan->last_posy = PacMan->posy;
    PacMan->last_direction = PacMan->direction;

    if ( *key == 'z' &&tab[PacMan->posx-1][PacMan->posy] != 1)
    {
        *a = 1;
    }
    else if (*key == 's' && tab[PacMan->posx+1][PacMan->posy] != 1 )
    {
        *a = 2;
    }
    else if (*key == 'd'&& tab[PacMan->posx][PacMan->posy+1] != 1 )
    {
        *a = 3;
    }
    else if (*key == 'q'&& tab[PacMan->posx][PacMan->posy-1] != 1 )
    {
        *a = 4;
    }

    if ( *a == 1 && tab[PacMan->posx-1][PacMan->posy] != 1)
    {
        PacMan->posx -= x;
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
        PacMan->posx+= x;
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
                PacMan->posx = 18;
            }
        }

    }
    else if (*a == 3 && tab[PacMan->posx][PacMan->posy+1] != 1 )
    {
        PacMan->posy += x;
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
        PacMan->posy -= x;
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
void consoleDeplacementPacMan1(int *a, t_PacMan * PacMan, char  *key, int bord,int * tab[20][50], float x)
{

    if ( *key == 'z' &&tab[PacMan->posx-1][PacMan->posy] != 1)
    {
        *a = 1;
    }
    else if (*key == 's' && tab[PacMan->posx+1][PacMan->posy] != 1 )
    {
        *a = 2;
    }
    else if (*key == 'd'&& tab[PacMan->posx][PacMan->posy+1] != 1 )
    {
        *a = 3;
    }
    else if (*key == 'q'&& tab[PacMan->posx][PacMan->posy-1] != 1 )
    {
        *a = 4;
    }

    if ( *a == 1 && tab[PacMan->posx-1][PacMan->posy] != 1)
    {
        PacMan->posx -= x;
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
        PacMan->posx+= x;
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
                PacMan->posx = 18;
            }
        }

    }
    else if (*a == 3 && tab[PacMan->posx][PacMan->posy+1] != 1 )
    {
        PacMan->posy += x;
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
        PacMan->posy -= x;
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

void intialisationPacManConsole(t_PacMan *PacMan, int * tab[20][50])
{
    int compteur = 0;
    int i;
    char nomfichier[100];

    PacMan->tx = 15;
    PacMan->ty = 15;
    while(compteur != 1)
    {


        PacMan->posx = (rand() % 19) + 1;
        PacMan->posy = (rand() % 47) + 2;

        if(tab[PacMan->posx][PacMan->posy] != 1)
        {
            compteur++;
        }



    }

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
                Color(1,0);
                printf("%c", 220);
                *bord = 1;
            }
            else if(tab[0][j] == 2)
            {
                Color(8,0);
                printf("%c", 220);
                *bord = 0;
            }


        }
        printf("\n");
    }

}

void sauvegardeConsole(t_PacMan * PacMan)
{
    //printf("reussite\n");
    FILE * fichier = NULL;
    fichier = fopen("sauvegardes.txt", "w");

    if (fichier != NULL)
    {


        fprintf(fichier, "%d %d %d %d",PacMan->posx, PacMan->posy, PacMan->vies,PacMan->score );
        fclose(fichier);
    }
}

void recuperationConsole(t_PacMan * PacMan)
{
    FILE * fichier = NULL;
    fichier = fopen("sauvegardes.txt", "r");


    if (fichier != NULL)
    {

        fscanf(fichier, "%d %d %d %d ", &PacMan->posx, &PacMan->posy,&PacMan->vies, &PacMan->score);
        fclose(fichier);
    }
}

void gestionDiamantConsole(t_Diamant* Diamant, int * stop,int * tab[20][50])
{
    int compteur = 1;
    int compteur2 = 0;



    while(Diamant->posx == 0 || Diamant->posy == 0 || compteur == 1 && *stop != 5)
    {

        compteur2 = 0;
        Diamant->posx = (rand() % 19) + 1;
        Diamant->posy = (rand() % 47) + 2;

        if(tab[Diamant->posx][Diamant->posy] == 1)
        {
            compteur2++;
        }


        if(compteur2 == 0)
        {

            compteur = 0;
            (*stop)++;
            gotoligcol(Diamant->posx, Diamant->posy);
            Color(2,0);
            printf("D");
            Color(11,0);

        }
    }
}

void suppressionDiamantConsole( t_Diamant * Diamant, t_PacMan * PacMan)
{
    if(PacMan->posx == Diamant->posx && PacMan->posy == Diamant->posy)
    {
        Diamant->boolean = 1;
    }

}

void Color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}

