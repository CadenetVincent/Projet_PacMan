#include "prototypes.h"

void load_map(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[], int *fermeture)
{

    while(PacMan.score != score_limit && PacMan.vies != 0 && *fermeture != 1)
    {
        gestion_map->choix = choise_map;

        gestion_map = choix_map(gestion_map);

        stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);


        rectfill(dbbuffer, PacMan.posx,PacMan.posy, PacMan.posx+22, PacMan.posy+20, makecol(255,255,255));

        stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);


        perso_img =  deplacementPacMan(dbbuffer, &PacMan, &a);
        if(PacMan.turn_img == 0)
        {
            draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
        }
        else
        {
            draw_sprite_h_flip(map,perso_img,PacMan.posx,PacMan.posy);
        }

        for(i=0; i<4; i++)
        {

            monenemy[i]->compteur_enemy++;

            if(monenemy[i]->compteur_enemy == 100)
            {
                monenemy[i]->resetdir=0;
                monenemy[i]->compteur_enemy=0;
                //mort(&monenemy[i], &PacMan, &compteur, dbbuffer);
            }

            enemy = call_monster(dbbuffer,monenemy[i],&PacMan);
            gestionDiamant(dbbuffer, Diamant[i], front, &stop);


            masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);

            suppressionDiamant(dbbuffer,Diamant[i],&PacMan);


            if(Diamant[i]->boolean != 1)
            {
                masked_blit(Diamants, map,0,0, Diamant[i]->posx, Diamant[i]->posy, SCREEN_W,SCREEN_H);
            }

        }

        blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        //printf("%d\n  %d\n ", Diamant[0]->boolean, PacMan->vies);

        score(Diamant,&PacMan,compteur_score, niveau);


        compteur_death++;
        compteur_death = death(monenemy, &PacMan, compteur_death,dbbuffer);

        if(key[KEY_S])
        {
            sauvegarde1( monenemy,&PacMan, gestion_map);
            *fermeture = 1;
        }
        rest(20);
        printf("%d", PacMan.vies);
    }
}


void load_map1(int i,int niveau, int choise_map, int score_limit, int score_max, int * a, int stop, int  compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[], int *fermeture)
{


    while(PacMan.score < score_limit && PacMan.score >= score_max && PacMan.vies != 0 && *fermeture != 1)
    {
        // printf("'(-è_");
        gestion_map->choix = choise_map;

        gestion_map = choix_map(gestion_map);

        stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);


        rectfill(dbbuffer, PacMan.posx,PacMan.posy, PacMan.posx+25, PacMan.posy+22, makecol(255,255,255));

        stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);


        perso_img =  deplacementPacMan(dbbuffer, &PacMan, &a);
        if(PacMan.turn_img == 0)
        {
            draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
        }
        else
        {
            draw_sprite_h_flip(map,perso_img,PacMan.posx,PacMan.posy);
        }

        for(i=0; i<4; i++)
        {

            monenemy[i]->compteur_enemy++;

            if(monenemy[i]->compteur_enemy == 100)
            {
                monenemy[i]->resetdir=0;
                monenemy[i]->compteur_enemy=0;
                //mort(&monenemy[i], &PacMan, &compteur, dbbuffer);
            }

            enemy = call_monster(dbbuffer,monenemy[i],&PacMan);
            gestionDiamant(dbbuffer, Diamant[i], front, &stop);


            masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);

            suppressionDiamant(dbbuffer,Diamant[i],&PacMan);


            if(Diamant[i]->boolean != 1)
            {
                masked_blit(Diamants, map,0,0, Diamant[i]->posx, Diamant[i]->posy, SCREEN_W,SCREEN_H);
            }

        }

        blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        //printf("%d\n  %d\n ", Diamant[0]->boolean, PacMan->vies);

        score(Diamant,&PacMan,&compteur_score, niveau);


        compteur_death++;
        compteur_death = death(monenemy, &PacMan, compteur_death,dbbuffer);

        if(key[KEY_S])
        {
            sauvegarde1( monenemy,&PacMan, gestion_map);
            *fermeture = 1;
        }
        rest(20);
    }
}

void load_mapConsole(char  nom[30], int * tab[20][50], int  bord, int * Diamant,t_PacMan *PacMan, int * stop, char key, int * a, int * compteur, int niveau, int vit, int MAX, int MIN, t_enecons * monenecons[4], int dead_mons)
{

    chargementMap(nom, tab, &bord);
    for(int i = 0; i < 5 ;i++)
    {
        gestionDiamantConsole(Diamant[i], &stop, tab );
    }

    for(int i = 0; i<4; i++)
    {
        monenecons[i] = initEnCons();
    }

PacMan->score = MIN;
    while(PacMan->score < MAX && PacMan->score >= MIN && PacMan->vies != 0 && key != 'p')
    {


if(kbhit())
        {
            key = getch();
        }

        gotoligcol(25,0);


        init_table_mons(monenecons,tab,dead_mons,PacMan);
        //collision_perso_mons_cons(PacMan, monenecons);

        gotoligcol(PacMan->posx,PacMan->posy);
        printf(" ");

        consoleDeplacementPacMan(a,PacMan, key,bord, tab);

        gotoligcol(PacMan->posx,PacMan->posy);
        Color(5,0);
        printf("X");
       Color(15,0);

    //printf("%d", PacMan->score);



 for(int i = 0; i < 5 ;i++)
    {
        suppressionDiamantConsole(Diamant[i], PacMan);

    }



    score(Diamant,PacMan,&compteur, niveau);

    Sleep(vit);
    }

}

void boucle_totale(char  nom[30], int * tab[20][50], int  bord, int * Diamant,t_PacMan *PacMan, int * stop, char key, int * a, int * compteur, int niveau, int vit, int MAX, int MIN, t_enecons * monenecons[4], int dead_mons)
{
    for(int i = 0 ; i < 5; i++)
    {
        Diamant[i] = initialiserDiamants();
    }

    load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,key,a,&compteur,niveau,vit,MAX,MIN,monenecons,dead_mons);

    system("cls");
for(int i = 0 ; i < 5; i++)
    {
        Diamant[i] = initialiserDiamants();
    }

    char nom1[30] = "map2.txt";
    int max = 10;
    int min = 5;
    *stop = 5;

    int niveau1 = 1;


load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,key,a,&compteur,niveau1,vit,max,min,monenecons,dead_mons);

}
