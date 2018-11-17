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

void load_mapConsole(char  nom[30], int * tab[20][50], int  bord, int * Diamant,t_PacMan *PacMan, int * stop, char *key, int * a, int * compteur, int niveau, int *vit, int MAX, int MIN, t_enecons * monenecons[4], int dead_mons, time_t start, float acc)
{
    int compt_time = 0;
    int scorep;
    int stockage;
    float x = 1;
    float y = 1;
    int v = 1;
    int boolean = 0;
    chargementMap(nom, tab, &bord);
    for(int i = 0; i < 5 ; i++)
    {
        gestionDiamantConsole(Diamant[i], &stop, tab );
    }

    for(int i = 0; i<4; i++)
    {
        monenecons[i] = initEnCons();
    }

    PacMan->score = MIN;
    stockage = PacMan->score;

    while(PacMan->score < MAX && PacMan->score >= MIN && PacMan->vies != 0 && *key != 'n')
    {


        if(kbhit())
        {
            *key = getch();
        }

        gotoligcol(25,0);
        if(PacMan->score >= 5)
        {
             init_table_mons(monenecons,tab,dead_mons,PacMan);
        }




        gotoligcol(PacMan->posx,PacMan->posy);
        printf(" ");

        consoleDeplacementPacMan(a,PacMan, key,bord, tab,x);

        gotoligcol(PacMan->posx,PacMan->posy);
        Color(5,0);
        printf("X");
        Color(15,0);

        gotoligcol(26,0);
        printf("Vous avez %d nombres de vies !",PacMan->vies);

        compt_time = (int)(time(NULL) - start);
        compt_time = 120 - compt_time;
        if(compt_time <= 0)
        {
            PacMan->vies = 0;
        }
        gotoligcol(27,0);
        printf("Il vous reste %d secondes !",compt_time);

        gotoligcol(28,0);
        scorep = PacMan->score * 10;
        printf("Votre score est de : %d !",scorep);






        for(int i = 0; i < 5 ; i++)
        {
            suppressionDiamantConsole(Diamant[i], PacMan);

        }



        score(Diamant,PacMan,&compteur, niveau);

        if(PacMan->score > stockage)
        {
            x = x * acc;
            stockage = PacMan->score;
        }

        if(*key == 'c' )
        {
            sauvegardeConsole(PacMan);
            *key = 'n';
        }

        if(*key == 'p' && boolean == 0)
        {
            y = x;
            x = 0;
            boolean = 1;

            for(int i = 0; i < 4; i++)
            {
                monenecons[i]->dep = 0;
            }
        }

        if(*key == 'o' && boolean == 1)
        {
            x = y;
            boolean = 0;
            for(int i = 0; i < 4; i++)
            {
                monenecons[i]->dep = 4;
            }
        }


        Sleep(*vit);
    }

}

int affichageMenu()
{
    int choixMenu = 0;
    printf("*****************************************\n" );
    printf("*                                       *\n" );
    printf("*               PACMAN                  *\n" );
    printf("*                                       *\n" );
    printf("*****************************************\n" );
    printf("1. Jouer\n");
    printf("2. Charger la sauvegarde du jeu\n");
    printf("3. Instructions\n");
    printf("4. Vitesse de jeu\n");
    printf("5. Bordure \n");
    printf("6. Fermer le jeu\n");
    printf("\nVotre choix?\n");
    scanf("%d", &choixMenu);

    return choixMenu;
}



void boucle_totale(char  nom[30], int * tab[20][50], int  *bord, int * Diamant,t_PacMan *PacMan, int * stop, char key, int * a, int * compteur, int niveau, int *vit, int MAX, int MIN, t_enecons * monenecons[4], int dead_mons, time_t start, char * key1)
{
    float acc = 1.0;

    //DEBUT CHOIX MENU
    int choixMenu = 0;
    int variable = 0;
    //char key1 = 'm';

    choixMenu = affichageMenu();

    switch(choixMenu)
    {
    case 1:
        system("cls");

        while(key != 'n')
        {
            /*if(kbhit())
            {
                key = getch();
            }*/

            if(*bord == 1)
            {
                nom = "map1.txt";

            }
            else if(*bord == 0)
            {
                nom = "map1sb.txt";
            }

            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            *stop = 5;

            MAX = MAX + 5;
             MIN = MIN + 5;
            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,vit,MAX,MIN,monenecons,dead_mons,start,acc);

            system("cls");
            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            if(*bord == 1)
            {
                nom = "map2.txt";

            }
            else if(*bord == 0)
            {
                nom = "map2sb.txt";
            }

             MAX = MAX + 5;
             MIN = MIN + 5;
            *stop = 5;

            int niveau1 = 1;


            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc);
            system("cls");
            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            if(*bord == 1)
            {
                nom = "map3.txt";

            }
            else if(*bord == 0)
            {
                nom = "map3sb.txt";
            }
            MAX = MAX + 5;
            MIN = MIN + 5;
            *stop = 5;


            niveau1 = 2;
            acc = 1.1;
            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc);
            key = 'n';
        }
        key = 'm';
        system("cls");

        break;
    case 2:
system("cls");
    recuperationConsole(PacMan);
    printf("%d", PacMan->score);
    int compteur = 0;
      while(key != 'n')
        {

        if(PacMan->score <5 && PacMan->score >= 0)
        {
            while(key != 'n')
            {
                if(*bord == 1)
            {
                nom = "map1.txt";

            }
            else if(*bord == 0)
            {
                nom = "map1sb.txt";
            }

            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            *stop = 5;

            MAX =  5;
            MIN = 0 ;
            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,vit,MAX,MIN,monenecons,dead_mons,start,acc);

            compteur ++;


            system("cls");
            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            if(*bord == 1)
            {
                nom = "map2.txt";

            }
            else if(*bord == 0)
            {
                nom = "map2sb.txt";
            }

             MAX = MAX + 5;
             MIN = MIN + 5;
            *stop = 5;

            int niveau1 = 1;


            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc);
            compteur ++;
            system("cls");
            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            if(*bord == 1)
            {
                nom = "map3.txt";

            }
            else if(*bord == 0)
            {
                nom = "map3sb.txt";
            }
            MAX = MAX + 5;
            MIN = MIN + 5;
            *stop = 5;


            niveau1 = 2;
            acc = 1.1;
            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc);
            compteur ++;
            key = 'n';
            }


        }
        else  if(PacMan->score <10 && PacMan->score >= 5)
        {
            while(key != 'n')
            {

            MAX = 5;
            MIN = 0;


            system("cls");
            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            if(*bord == 1)
            {
                nom = "map2.txt";

            }
            else if(*bord == 0)
            {
                nom = "map2sb.txt";
            }

             MAX = MAX + 5;
             MIN = MIN + 5;
            *stop = 5;

            int niveau1 = 1;


            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc);
            compteur ++;
            system("cls");
            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            if(*bord == 1)
            {
                nom = "map3.txt";

            }
            else if(*bord == 0)
            {
                nom = "map3sb.txt";
            }
            MAX = MAX + 5;
            MIN = MIN + 5;
            *stop = 5;


            niveau1 = 2;
            acc = 1.1;
            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc);
            compteur ++;
            key = 'n';
            }
        }
         else  if(PacMan->score < 15 && PacMan->score >= 10)
         {
             while(key != 'n')
            {

            MAX = 10;
            MIN = 5;



            system("cls");
            for(int i = 0 ; i < 5; i++)
            {
                Diamant[i] = initialiserDiamants();
            }
            if(*bord == 1)
            {
                nom = "map3.txt";

            }
            else if(*bord == 0)
            {
                nom = "map3sb.txt";
            }
            MAX = MAX + 5;
            MIN = MIN + 5;
            *stop = 5;


            int niveau1 = 2;
            acc = 1.1;
            load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc);
            compteur ++;
            key = 'n';
            }
         }



        }
        system("cls");
        break;
    case 3:

        break;
    case 4:
        printf("choisisser la vitesse de jeu 1) 2) ou 3)\n");
        scanf("%d", &variable);

        if(variable == 1)
        {
            *vit = 100;
        }
        else if(variable == 2)
        {
            *vit = 110;
        }
        else if(variable == 3)
        {
            *vit = 120;
        }
system("cls");
        break;
    case 5:
        printf("choisisser avec bordure 1) ou sans bordure 2)\n");
        scanf("%d", &variable);

        if(variable == 1)
        {
            *bord = 1;
        }
        else if (variable == 2)
        {
            *bord = 0;
        }
        system("cls");
        break;
    case 6:
        *key1 = 'b';

        break;
    default:
        choixMenu = affichageMenu();
        break;
    }

    system("PAUSE");
    //FIN CHOIX MENU


}

void Console()
{
     srand(time(NULL));
    int x = 10,y = 25;
    time_t start = time(NULL);

    char key = 'a';
    char key1 = 'a';
    int compteurc = 0;
    int a = (rand() % 4) +1;
    float vit = 100;
    char nom[30] = "map3.txt";
    int bord = 1;
    int  stop = 5;
    int niveau = 0;
    int  compteur = 0;
    int dead_mons = 0;
    int MAX = 0;
    int MIN = -5;


    t_PacMan PacMan;
    t_PacMan * pt_PacMan;
    pt_PacMan = &PacMan;

    t_enecons * monenecons[4];
    t_Diamant * Diamant[5];

    PacMan.posx = 10;
    PacMan.posy = 25;
    PacMan.vies = 5;
    int *tab[20][50];

    intialisationPacManConsole(&PacMan,tab);




//load_mapConsole(nom,tab,bord, Diamant,&PacMan,&stop,key,&a,&compteur,niveau,vit,MAX,MIN);
while(key1 != 'b')
{
   boucle_totale(nom,tab,&bord, Diamant,&PacMan,&stop,key,&a,&compteur,niveau,&vit,MAX,MIN,monenecons,dead_mons,start, &key1);

}
}
