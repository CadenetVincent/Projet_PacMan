#include "prototypes.h"

void sauvegarde1(t_enemy *monenemy[], t_PacMan * PacMan, t_map * gestion_map)
{
    //printf("reussite\n");
    FILE * fichier = NULL;
    fichier = fopen("sauvegardes.txt", "w");

    FILE * fichier1 = NULL;
    fichier1 = fopen("sauvegarde1.txt", "w");

    if (fichier != NULL)
    {


        fprintf(fichier, "%d %d %d %d %d %d",PacMan->posx, PacMan->posy, PacMan->vies,PacMan->score, gestion_map->choix, gestion_map->border );
        fclose(fichier);
    }
    if(fichier1 != NULL)
    {
        //printf("reussite1\n");
        for(int i = 0; i < 4; i++)
        {
            fprintf(fichier1, "%d %d\n ",monenemy[i]->dposx, monenemy[i]->dposy);
        }

        fclose(fichier1);
    }



}

void recuperation(t_enemy *enemy[], t_PacMan * PacMan, t_map * gestion_map, int choise_map)
{
    FILE * fichier = NULL;
    fichier = fopen("sauvegardes.txt", "r");

    FILE * fichier1 = NULL;
    fichier1 = fopen("sauvegarde1.txt", "r");

    if (fichier != NULL)
    {

        fscanf(fichier, "%d %d %d %d %d %d ", &PacMan->posx, &PacMan->posy,&PacMan->vies, &PacMan->score, &choise_map,&gestion_map->border);
        fclose(fichier);
        printf("%d\n", PacMan->score);
    }

    if(fichier1 != NULL)
    {
        for(int i = 0; i < 4 ; i++)
        {
            fscanf(fichier, "%d %d ", &enemy[i]->dposx, &enemy[i]->dposy);
        }
    }
}

