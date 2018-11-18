#include "prototypes.h"

void load_map1(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan * PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[], int *fermeture, t_PacMan * Sub_Pac[20])
{
      int result_score = 0;
    int diff_score = 0;
    int score_diff = 0;
    BITMAP * Sub_map[20];
    BITMAP * coeur;
    coeur = load_bitmap("coeur.bmp", NULL);
    time_t temps = time(NULL);
    time_t start = time(NULL);
    int temps_restant = 0;
    int temps_final = 60;
    t_Sun * Monsun;
    int compteursun = 0;
    int imagesun =0;
    int temporiseursun = 10;

    start = time(NULL);

    Monsun = initialiserSun();

    while(PacMan->score != score_limit && PacMan->vies != 0 && *fermeture != 1)
    {
        temps_restant = (int)(time(NULL) - temps); //compt_time = (int)(time(NULL) - start);
        temps_final = 60 - temps_restant;


        gestion_map->choix = choise_map;

        gestion_map = choix_map(gestion_map);

        stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);


        rectfill(dbbuffer, PacMan->posx,PacMan->posy, PacMan->posx+22, PacMan->posy+20, makecol(255,255,255));

        stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);

        if(niveau == 3)
        {
            PacMan->deplacement = 10;
            score_diff = PacMan->score - 15;
        }

       start = gestionSun(map,dbbuffer,Monsun,PacMan,front,start);

       if(Monsun->posx - PacMan->posx <10 && Monsun->posx - PacMan->posx > -10 && Monsun->posy - PacMan->posy <10 && Monsun->posy - PacMan->posy >-10)
       {
           Monsun->boolean = 0;
           PacMan->get_Sun = 3;
       }


    if(compteursun >= temporiseursun)
    {
       imagesun++;
       compteursun=0;
    }
    if(imagesun >= 6)
    {
        imagesun = 0;
    }

    draw_sprite(map,Monsun->SOLEIL[imagesun],Monsun->posx,Monsun->posy);


        printf("Score diff : %d",score_diff);

        perso_img =  deplacementPacMan(dbbuffer, PacMan, &a, Sub_Pac, score_diff);

        if(PacMan->turn_img == 0)
        {
            draw_sprite(map,perso_img,PacMan->posx,PacMan->posy);
        }
        else
        {
            draw_sprite_h_flip(map,perso_img,PacMan->posx,PacMan->posy);
        }

        for(int i= 0; i< PacMan->vies; i++)
        {
            draw_sprite_h_flip(map,coeur,20 + 20*i,570);
        }

        textprintf(map, font, 3, 3, makecol(100, 255, 100), "%d",temps_final);
        textprintf(map, font, 140, 3, makecol(100, 255, 100), "Score : %d",PacMan->score);

        if(temps_final == 0)
        {
            PacMan->vies = 0;
        }

        if(score_diff > 0)
        {
            for (int i = 0; i<score_diff; i++)
            {
                if(i == 0)
                {
                    Sub_Pac[i]->posx = PacMan->last_posx;
                    Sub_Pac[i]->posy = PacMan->last_posy;
                }
                else
                {
                    if(PacMan->direction == 0)
                    {
                       Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                       Sub_Pac[i]->posy = Sub_Pac[i]->posy;
                    }else
                    {

                    Sub_Pac[i]->posx = Sub_Pac[i-1]->last_posx;
                    Sub_Pac[i]->posy = Sub_Pac[i-1]->last_posy;

                    }
                }

                if(PacMan->direction == 2)
                {
                    Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_up, 3);
                    //draw_sprite(map,Sub_map[i],Sub_Pac[i]->posx,Sub_Pac[i]->posy+20);

                }
                if(PacMan->direction == 4)
                {
                    Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
                    //draw_sprite(map,Sub_map[i],Sub_Pac[i]->posx,Sub_Pac[i]->posy+20);
                }
                if(PacMan->direction == 3)
                {
                    Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
                   // draw_sprite(map,Sub_map[i],Sub_Pac[i]->posx-20,Sub_Pac[i]->posy);
                }
                if(PacMan->direction == 1)
                {
                    Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_bot, 2);
                    //draw_sprite(map,Sub_map[i],Sub_Pac[i]->posx,Sub_Pac[i]->posy-20);
                    //draw_sprite(map,Sub_map[i],Sub_Pac[i]->posx+20,Sub_Pac[i]->posy);
                }
            draw_sprite(map,Sub_map[i],Sub_Pac[i]->posx,Sub_Pac[i]->posy);
            }
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

            enemy = call_monster(dbbuffer,monenemy[i],PacMan);


            masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);





        }
        for(i=0; i<5; i++)
        {
            gestionDiamant(dbbuffer, Diamant[i], front, &stop);
            suppressionDiamant(dbbuffer,Diamant[i],PacMan);
            if(Diamant[i]->boolean != 1)
            {
                masked_blit(Diamants, map,0,0, Diamant[i]->posx, Diamant[i]->posy, SCREEN_W,SCREEN_H);
            }


        }

        blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        score(Diamant,PacMan,compteur_score, niveau);


        compteur_death++;
        compteur_death = death(monenemy, PacMan, compteur_death,dbbuffer);

        if(key[KEY_S])
        {
            sauvegarde1( monenemy,PacMan, gestion_map);
            *fermeture = 1;
        }
        rest(20);
        //printf("vies : %d\n score : %d\n", PacMan->vies, PacMan->score);
    }
}


void load_map(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan * PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[], int *fermeture)
{
    BITMAP * coeur;
    coeur = load_bitmap("coeur.bmp", NULL);
    time_t temps = time(NULL);
    int temps_restant = 0;
    int temps_final = 0;

    while(PacMan->score != score_limit && PacMan->vies != 0 && *fermeture != 1)
    {
        temps_restant = (int)(time(NULL) - temps); //compt_time = (int)(time(NULL) - start);
        temps_final = 60 - temps_restant;

        gestion_map->choix = choise_map;

        gestion_map = choix_map(gestion_map);

        stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);


        rectfill(dbbuffer, PacMan->posx,PacMan->posy, PacMan->posx+22, PacMan->posy+20, makecol(255,255,255));

        stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);


        perso_img =  deplacementPacMan1(dbbuffer, PacMan, &a);
        if(PacMan->turn_img == 0)
        {
            draw_sprite(map,perso_img,PacMan->posx,PacMan->posy);
        }
        else
        {
            draw_sprite_h_flip(map,perso_img,PacMan->posx,PacMan->posy);
        }


        for(int i= 0; i< PacMan->vies; i++)
        {
            draw_sprite_h_flip(map,coeur,20 + 20*i,570);
        }

        textprintf(map, font, 3, 3, makecol(100, 255, 100), "%d",temps_final);
        textprintf(map, font, 140, 3, makecol(100, 255, 100), "Score : %d",PacMan->score);

        for(i=0; i<4; i++)
        {

            monenemy[i]->compteur_enemy++;

            if(monenemy[i]->compteur_enemy == 100)
            {
                monenemy[i]->resetdir=0;
                monenemy[i]->compteur_enemy=0;
                //mort(&monenemy[i], &PacMan, &compteur, dbbuffer);
            }

            enemy = call_monster(dbbuffer,monenemy[i],PacMan);


            masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);





        }
        for(i=0; i<5; i++)
        {
            gestionDiamant(dbbuffer, Diamant[i], front, &stop);
            suppressionDiamant(dbbuffer,Diamant[i],PacMan);
            if(Diamant[i]->boolean != 1)
            {
                masked_blit(Diamants, map,0,0, Diamant[i]->posx, Diamant[i]->posy, SCREEN_W,SCREEN_H);
            }


        }

        blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        score(Diamant,PacMan,compteur_score, niveau);


        compteur_death++;
        compteur_death = death(monenemy, PacMan, compteur_death,dbbuffer);

        if(key[KEY_S])
        {
            sauvegarde1( monenemy,PacMan, gestion_map);
            *fermeture = 1;
        }
        rest(20);
        //printf("vies : %d\n score : %d\n", PacMan->vies, PacMan->score);
    }
}

    void load_mapConsole(char  nom[30], int * tab[20][50], int  bord, int * Diamant,t_PacMan *PacMan, int * stop, char *key, int * a, int * compteur, int niveau, int vit, int MAX, int MIN, t_enecons * monenecons[4], int dead_mons, time_t start, float acc, t_chen * Chenille[30])
 {
        int compt_time = 0;
        int scorep;
        int stockage;
        int result_score = 0;
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

            //IMPORTANT
            //pour afficher ou non la chenille on utilise result_score

            result_score = PacMan->score - 15;

            consoleDeplacementPacMan(a,PacMan, key,bord, tab,x, Chenille, result_score);

            gotoligcol(PacMan->posx,PacMan->posy);
            Color(5,0);
            printf("X");
            Color(15,0);

            if(Chenille[0]->coordX > 0 && Chenille[0]->coordY >0)
            {
                for(int i = 0; i<result_score; i++)
                {
                    gotoligcol(Chenille[i]->coordX,Chenille[i]->coordY);
                    printf(" ");
                }
            }

            if(result_score > 0)
            {
                for (int i = 0; i<result_score; i++)
                {
                    if(i == 0)
                    {
                        Chenille[i]->coordX = PacMan->last_posx;
                        Chenille[i]->coordY = PacMan->last_posy;
                    }
                    else
                    {

                        Chenille[i]->coordX = Chenille[i-1]->ancienX;
                        Chenille[i]->coordY = Chenille[i-1]->ancienY;
                    }

                }
            }

            if(Chenille[0]->coordX != 0 && Chenille[0]->coordY !=0)
            {
                for(int i = 0; i<result_score; i++)
                {
                    gotoligcol(Chenille[i]->coordX,Chenille[i]->coordY);
                    printf("A");

                }
            }

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


            Sleep(vit);
        }

    }

    void load_mapConsole1(char  nom[30], int * tab[20][50], int  bord, int * Diamant,t_PacMan *PacMan, int * stop, char *key, int * a, int * compteur, int niveau, int vit, int MAX, int MIN, t_enecons * monenecons[4], int dead_mons, time_t start, float acc)
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

            consoleDeplacementPacMan1(a,PacMan, key,bord, tab,x);

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


            Sleep(vit);
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



    void boucle_totale(char  nom[30], int * tab[20][50], int  *bord, int * Diamant,t_PacMan *PacMan, int * stop, char key, int * a, int * compteur, int niveau, int *vit, int MAX, int MIN, t_enecons * monenecons[4], int dead_mons, time_t start, char * key1, t_chen * Chenille[30])
    {
        float acc = 1.0;

        //DEBUT CHOIX MENU
        int choixMenu = 0;
        int variable = 0;
        //char key1 = 'm';

        *vit = 100;
        choixMenu = affichageMenu();

        switch(choixMenu)
        {
        case 1:
            system("cls");

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


                MAX = MAX + 5;

                MIN = MIN + 5;
                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);

                //   MIN = MIN + 5;
                //        load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);


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


                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,*vit,MAX,MIN,monenecons,dead_mons,start,acc);
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
                acc = 1;
                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,*vit,MAX,MIN,monenecons,dead_mons,start,acc);
                system("cls");
                for(int i = 0 ; i < 5; i++)
                {
                    Diamant[i] = initialiserDiamants();
                }
                if(*bord == 1)
                {
                    nom = "map4.txt";

                }
                else if(*bord == 0)
                {
                    nom = "map4sb.txt";
                }
                MAX = MAX + 5;
                MIN = MIN + 5;
                *stop = 5;
                niveau1 = 3;
                acc = 1;
                load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,*vit,MAX,MIN,monenecons,dead_mons,start,acc,Chenille);




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


            if(PacMan->score <5 && PacMan->score >= 0)
            { key = 'r';

                while(key != 'n')
                {
                    PacMan->posx = 10;
                PacMan->posy = 25;
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
                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);

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


                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);
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
                    acc = 1;
                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);

                    MAX = 20;
                    MIN = 15;

                    system("cls");
                    for(int i = 0 ; i < 5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    if(*bord == 1)
                    {
                        nom = "map4.txt";

                    }
                    else if(*bord == 0)
                    {
                        nom = "map4sb.txt";
                    }
                   // MAX = MAX + 5;
                   // MIN = MIN + 5;
                    *stop = 5;


                     niveau1 = 3;
                    acc = 1;
                load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,*vit,MAX,MIN,monenecons,dead_mons,start,acc,Chenille);

                    key = 'n';
                }


            }
            else  if(PacMan->score <10 && PacMan->score >= 5)
            { key = 'r';
                while(key != 'n')
                {
PacMan->posx = 10;
                PacMan->posy = 25;
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


                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);
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
                    acc = 1;
                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);
                    compteur ++;

                    MAX = 20;
                    MIN = 15;

                    system("cls");
                    for(int i = 0 ; i < 5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    if(*bord == 1)
                    {
                        nom = "map4.txt";

                    }
                    else if(*bord == 0)
                    {
                        nom = "map4sb.txt";
                    }
                   // MAX = MAX + 5;
                   // MIN = MIN + 5;
                    *stop = 5;


                     niveau1 = 3;
                    acc = 1;
                load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,*vit,MAX,MIN,monenecons,dead_mons,start,acc,Chenille);

                    key = 'n';
                }
            }
            /*<<<<<<< HEAD

                         MAX = MAX + 5;
                         MIN = MIN + 5;
                        *stop = 5;

                        int niveau1 = 1;


                        load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc,Chenille);
                        compteur ++;
                        system("cls");
                        for(int i = 0 ; i < 5; i++)
            =======*/
            else  if(PacMan->score < 15 && PacMan->score >= 10)
            { key = 'r';
                while(key != 'n')
                {
PacMan->posx = 10;
                PacMan->posy = 25;
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
                    acc = 1;
                load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau,*vit,MAX,MIN,monenecons,dead_mons,start,acc);





                   /* if(*bord == 1)
                    {
                        nom = "map4.txt";

                    }
                    else if(*bord == 0)
                    {
                        nom = "map4sb.txt";
                    }
                    MAX = MAX + 5;
                    MIN = MIN + 5;
                    *stop = 5;


                    niveau1 = 2;
                    acc = 1;
                    load_mapConsole1(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,vit,MAX,MIN,monenecons,dead_mons,start,acc,Chenille);
                    compteur ++;*/
                    MAX = 20;
                    MIN = 15;

                    system("cls");
                    for(int i = 0 ; i < 5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    if(*bord == 1)
                    {
                        nom = "map4.txt";

                    }
                    else if(*bord == 0)
                    {
                        nom = "map4sb.txt";
                    }
                   // MAX = MAX + 5;
                   // MIN = MIN + 5;
                    *stop = 5;


                     niveau1 = 3;
                    acc = 1;
                load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,*vit,MAX,MIN,monenecons,dead_mons,start,acc,Chenille);

                    key = 'n';
                }



            }

            else  if(PacMan->score < 20 && PacMan->score >= 15)
            {
                key = 'r';
                while(key != 'n')
                {


 PacMan->posx = 10;
                PacMan->posy = 25;
MAX = 20;
                    MIN = 15;

                    system("cls");
                    for(int i = 0 ; i < 5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    if(*bord == 1)
                    {
                        nom = "map4.txt";

                    }
                    else if(*bord == 0)
                    {
                        nom = "map4sb.txt";
                    }
                   // MAX = MAX + 5;
                   // MIN = MIN + 5;
                    *stop = 5;


                    int niveau1 = 3;
                    acc = 1;
                load_mapConsole(nom,tab,bord, Diamant,PacMan,&stop,&key,a,&compteur,niveau1,*vit,MAX,MIN,monenecons,dead_mons,start,acc,Chenille);

                    key = 'n';
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

        t_map * Chenille[30];

        char soundtrack[100]= "starwars.wav";
        int volume=128;
        int voice;
        SAMPLE*sound;

        allegro_init();
        install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
        install_timer();

        set_color_depth(desktop_color_depth());
        if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) != 0)
        {
            printf("Error initialising sound: %s\n", allegro_error);
        }
        printf("test");

        //voice_set_playmode(voice,PLAYMODE_LOOP);

        //START MAIN
        sound=load_wav(soundtrack);
        if (!sound)
        {
            printf("Erreur de chargement de %s\n", sound);
            return 1;
        }
        //START GAME
        voice=allocate_voice(sound);
        voice_set_volume(voice,volume);
        voice_set_priority(voice,255);
        voice_start(voice);
        release_voice(voice);


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

        for(int i=0; i<30; i++)
        {
            Chenille[i] = init_chenille(i);
        }




//load_mapConsole(nom,tab,bord, Diamant,&PacMan,&stop,key,&a,&compteur,niveau,vit,MAX,MIN);
        while(key1 != 'b')
        {
            //BOUCLER LA MUSIQUE
            if(voice_check(voice==NULL))
            {
                voice_set_position(voice,0);
                voice_start(voice);
                release_voice(voice);
            }

            boucle_totale(nom,tab,&bord, Diamant,&PacMan,&stop,key,&a,&compteur,niveau,&vit,MAX,MIN,monenecons,dead_mons,start, &key1,Chenille);

        }
        destroy_sample(sound);
    }


    void Allegro()
    {


        int pos_enemy[2][4]= {{255,497,255,497},{283,283,640,640}};
        int i = 0;

        t_enemy * monenemy[4];
        t_map * gestion_map;
        t_Diamant * Diamant[4];
        t_PacMan * Sub_Pac[20];
        t_Sun * Sun;

        BITMAP * Sub_map[20];
        BITMAP *test;
        BITMAP *map;
        BITMAP *perso_img;
        BITMAP * enemy;
        BITMAP * front;
        BITMAP * dbbuffer;
        BITMAP * menu;
        BITMAP * menubuffer;
        BITMAP * mapbuffer[2];
        BITMAP * Diamants;
        BITMAP * regles;
        BITMAP * bordure;
        BITMAP * vitesse;

        time_t start = time(NULL);

        lancerAllegro();
        int a = 0;
        int compteur_death = 80;
        int compteur_score = 0;
        int stop = 0;
        int niveau = 0;
        int diff_final_score=0;
        int position_sub=0;
        int fermeture = 0;
        int choise_map = 0;
        int score_limit = 4;
        int score_max = 0;

        t_PacMan *bob;
        t_PacMan PacMan;
        bob = &PacMan;
        intialisationPacMan(bob);


        for(i=0; i<20; i++)
        {
            Sub_Pac[i] = intialisationSubPacMan();
            Sub_map[i] = load_bitmap("pacman_sprites/pacman_right_0.bmp",NULL);
        }

        srand(time(NULL));

        map = create_bitmap(SCREEN_W,SCREEN_H);
        dbbuffer = create_bitmap(SCREEN_W,SCREEN_H);
        menu = load_bitmap("menu.bmp", NULL);
        menubuffer = load_bitmap("menubuffer.bmp", NULL);
        Diamants = load_bitmap("diamant.bmp",NULL);
        regles = load_bitmap("regles.bmp", NULL);
        bordure = load_bitmap("bordure.bmp", NULL);
        vitesse = load_bitmap("vitesse.bmp", NULL);



        gestion_map = initialisermap();
        Sun = initialiserSun();

        //Choisir sa map avec ou sans bordure
        gestion_map->choix=0;
        gestion_map->border=0;

        gestion_map = choix_map(gestion_map);

        for(i=0; i<4; i++)
        {
            monenemy[i] = initialiserenemy();
            monenemy[i]->dposx= pos_enemy[0][i];
            monenemy[i]->dposy= pos_enemy[1][i];
            //Diamant[i] = initialiserDiamants();

        }

        PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
        PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;

        /// NE PAS OUBLIER DE MODIFIER LES DIAMANTS POUR EN METTRE 5 !!!!!!
        while(!key[KEY_ESC])
        {


            blit(menubuffer, dbbuffer,0,0,0,0,SCREEN_W,SCREEN_H);

            blit(menu, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

            if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(255,0,0))
            {
                fermeture = 0;
                PacMan.vies = 5;
                PacMan.score = 0;
                while(PacMan.vies > 0 && fermeture != 1 && PacMan.score != 20)
                {

                PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;
                    stop = 0;
                    niveau = 0;
                    score_limit = 5;
                    choise_map = 0;

                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }



                    load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);

                    printf("vies1 : %d\n score1 : %d\n", PacMan.vies, PacMan.score);

                    stop = 0;
                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();

                    }
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;


                    niveau = 1;
                    choise_map = 1;

                    printf("%d\n", PacMan.vies);
                    score_limit = 10;
                    load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);                            //, Sub_Pacvoid load_map(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[]);

                    stop = 0;
                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();

                    }
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;

                    niveau = 2;
                    choise_map = 2;
                    score_limit = 15;

                    load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);


                    stop = 0;
                    niveau = 3;
                    score_limit = 20;
                    choise_map = 3;

                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;
                    load_map1( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture, Sub_Pac);
PacMan.score = 20;

                }



            }
            else if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(76,255,0))
            {

                recuperation(&monenemy,&PacMan, gestion_map, choise_map);

                stop = 0;
                fermeture = 0;
                PacMan.vies = 5;


                if(PacMan.score < 5 && PacMan.score >= 0)
                {
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;

                    //boucle_totale(nom,tab,&bord, Diamant,&PacMan,&stop,key,&a,&compteur,niveau,&vit,MAX,MIN,monenecons,dead_mons,start, &key1, Chenille);

                    score_limit = 5;
                    while(PacMan.vies > 0 && fermeture != 1 && PacMan.score != 15)
                    {

                        stop = 0;
                        niveau = 0;
                        score_limit = 5;
                        choise_map = 0;

                        for(i=0; i<5; i++)
                        {
                            Diamant[i] = initialiserDiamants();
                        }




                        load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);

                        printf("vies1 : %d\n score1 : %d\n", PacMan.vies, PacMan.score);

                        stop = 0;
                        for(i=0; i<5; i++)
                        {
                            Diamant[i] = initialiserDiamants();

                        }
                        PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                        PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;

                        niveau = 1;
                        choise_map = 1;

                        printf("%d\n", PacMan.vies);
                        score_limit = 10;
                        load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);                            //void load_map(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[]);

                        stop = 0;
                        for(i=0; i<5; i++)
                        {
                            Diamant[i] = initialiserDiamants();

                        }
                        PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                        PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;

                        niveau = 2;
                        choise_map = 2;
                        score_limit = 15;

                        load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);

 stop = 0;

                    niveau = 3;
                    score_limit = 20;
                    choise_map = 3;

                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;
                    load_map1( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture, Sub_Pac);
PacMan.score = 20;

                    }
                }

                else if(PacMan.score < 10 && PacMan.score >= 5)
                {
                    score_limit = 5;
                    while(PacMan.vies > 0 && fermeture != 1 && PacMan.score != 15)
                    {
                        stop = 0;
                        for(i=0; i<5; i++)
                        {
                            Diamant[i] = initialiserDiamants();

                        }
                        PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                        PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;


                        niveau = 1;
                        choise_map = 1;

                        printf("%d\n", PacMan.vies);
                        score_limit = score_limit + 5;
                        load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);                            //void load_map(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[]);

                        stop = 0;
                        for(i=0; i<5; i++)
                        {
                            Diamant[i] = initialiserDiamants();

                        }
                        PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                        PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;

                        niveau = 2;
                        choise_map = 2;
                        score_limit = score_limit + 5;

                        load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);
 stop = 0;
                    niveau = 3;
                    score_limit = 20;
                    choise_map = 3;

                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;
                    load_map1( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture, Sub_Pac);
PacMan.score = 20;

                    }
                }
                else if(PacMan.score < 15 && PacMan.score >= 10)
                {
                    score_limit = 10;
                    while(PacMan.vies > 0 && fermeture != 1 && PacMan.score != 15)
                    {
                        stop = 0;
                        for(i=0; i<5; i++)
                        {
                            Diamant[i] = initialiserDiamants();

                        }
                        PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                        PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;

                        niveau = 2;
                        choise_map = 2;
                        score_limit = score_limit + 5;

                        load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture);
 stop = 0;
                    niveau = 3;
                    score_limit = 20;
                    choise_map = 3;

                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;
                    load_map1( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture, Sub_Pac);
PacMan.score = 20;

                    }
             }
                    else if(PacMan.score < 20 && PacMan.score >= 15)
                    {
                        while(PacMan.vies > 0 && fermeture != 1 && PacMan.score != 20)
                        {
                             stop = 0;
                    niveau = 3;
                    score_limit = 20;
                    choise_map = 3;

                    for(i=0; i<5; i++)
                    {
                        Diamant[i] = initialiserDiamants();
                    }
                    PacMan.posx = SCREEN_W/2-PacMan.tx/2-8;
                    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-8;
                    load_map1( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, &PacMan, monenemy, gestion_map, &Diamant,&fermeture, &Sub_Pac);
PacMan.score = 20;
                        }

                    }


                }


            else if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(0,38,255))
            {
                while(!key[KEY_SPACE])
                {
                    blit(regles, screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
            }
            else if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(255,0,110))
                while(!key[KEY_1] && !key[KEY_2]  &&!key[KEY_3] )
                {
                    blit(vitesse, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
                }
            else if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(0,127,14))
            {
                blit(bordure, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
                int boolean = 0;
                while(boolean != 1)
                {
                    if(key[KEY_B])
                    {
                        boolean = 1;
                        gestion_map->border = 1;
                    }

                    if(key[KEY_SPACE])
                    {
                        boolean = 1;
                        gestion_map->border = 0;
                    }

                }

            }
            else if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(128,128,128))
            {
                key[KEY_ESC] = 1;
            }

            /// NE PAS OUBLIER DE MODIFIER LES DIAMANTS POUR EN METTRE 5 !!!!!!




        }

    }

    void Menu1()
    {
        char key2;
        int choix;

        while(key2 != 'k')
        {
            if(kbhit())
            {
                key2 = getch();
            }

            printf("voulez vous jouer en : \n 1) console \n 2) allegro\n 3) sortir\n");
            scanf("%d", &choix);
            if(choix == 1)
            {
                system("cls");
                Console();
            }
            else if(choix == 2)
            {
                system("cls");
                Allegro();
            }
            else if(choix == 3)
            {
                system("cls");
               exit(0);
            }



        }
    }
