//#include <stdio.h>
//#include <stdlib.h>
//#include <allegro.h>
#include "prototypes.h"

//Test push


/// NE PAS OUBLIER DE MODIFIER LES DIAMANTS POUR EN METTRE 5 !!!!!!
void lancerAllegro()
{
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}
/// NE PAS OUBLIER DE MODIFIER LES DIAMANTS POUR EN METTRE 5 !!!!!!

///Keep the same function for each map




int main()
{
    srand(time(NULL));
    int x = 10,y = 25;

    char key = 'a';
    int compteurc = 0;
    int a = (rand() % 4) +1;
    int vit = 60;
    char nom[30] = "map2.txt";
    int bord = 3;

    int * stop;
    int niveau = 0;
    int  compteur = 0;

    int dead_mons = 0;


    t_PacMan PacMan;
    t_enecons * monenecons[4];
    t_Diamant * Diamant[5];

    PacMan.posx = 10;
    PacMan.posy = 25;
    int *tab[20][50];


    intialisationPacManConsole(&PacMan);

    chargementMap(nom, tab, &bord);
    for(int i = 0; i < 5 ;i++)
    {
    Diamant[i] = initialiserDiamants();
    gestionDiamantConsole(Diamant[i], &stop, tab );
    }



    for(int i = 0; i<4; i++)
    {
    monenecons[i] = initEnCons(tab);
    }




    while(key != 'p')
    {

        if(kbhit())
        {
            key = getch();
        }


        Sleep(vit);

        // UNE SEULE FONCTION D'APPEl
        init_table_mons(monenecons,tab,dead_mons,PacMan);

        gotoligcol(PacMan.posx,PacMan.posy);
        printf(" ");

        consoleDeplacementPacMan(&a,&PacMan, key,bord, tab);

        gotoligcol(PacMan.posx,PacMan.posy);
        printf("X");
        gotoligcol(200,400);



        for(int i = 0; i < 5 ;i++)
    {
        suppressionDiamantConsole(Diamant[i], &PacMan);



    }



    score(Diamant,&PacMan,&compteur, niveau);
    }


printf("%d" ,PacMan.score);





    /*int pos_enemy[2][4]= {{255,497,255,497},{283,283,640,640}};
    int i = 0;

    t_enemy * monenemy[4];
    t_map * gestion_map;
    t_Diamant * Diamant[4];
    t_PacMan * Sub_Pac[20];
    t_Sun * Sun;
    // t_PacMan **PacMan1;

    //    PacMan1 = &PacMan;

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
    //int border = 0;
    //int choix = 0;



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

    PacMan.posx = SCREEN_W/2-PacMan.tx/2-10;
    PacMan.posy =  SCREEN_H/2-PacMan.ty/2-10;

    /// NE PAS OUBLIER DE MODIFIER LES DIAMANTS POUR EN METTRE 5 !!!!!!
    while(!key[KEY_ESC])
    {

        blit(menubuffer, dbbuffer,0,0,0,0,SCREEN_W,SCREEN_H);

        blit(menu, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(255,0,0))
        {
            fermeture = 0;
            PacMan.vies = 5;

            while(PacMan.vies > 0 && fermeture != 1)
            {



                PacMan.score = 0;
                stop = 0;
                niveau = 0;
                score_limit = 4;
                choise_map = 0;

                for(i=0; i<4; i++)
                {
                    Diamant[i] = initialiserDiamants();
                }



                load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, PacMan, monenemy, gestion_map, &Diamant,&fermeture);


                printf("%d\n", PacMan.vies);

                stop = 0;
                for(i=0; i<4; i++)
                {
                    Diamant[i] = initialiserDiamants();

                }
                PacMan.posx = SCREEN_W/2-PacMan.tx/2;
                PacMan.posy = SCREEN_H/2-PacMan.ty/2;
                //fermeture = 0;



                //score != 8, niveau 1, choix_map 1,

                niveau = 1;
                choise_map = 1;

                printf("%d\n", PacMan.vies);
                score_limit = 8;
                load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, PacMan, monenemy, gestion_map, &Diamant,&fermeture);                            //void load_map(int i,int niveau, int choise_map, int score_limit, int * a, int stop, int * compteur_score, int compteur_death, BITMAP * Diamants, BITMAP * front, BITMAP * enemy, BITMAP * dbbuffer, BITMAP * map, BITMAP * perso_img, t_PacMan  PacMan, t_enemy *monenemy[], t_map * gestion_map, t_Diamant * Diamant[]);

                stop = 0;
                for(i=0; i<4; i++)
                {
                    Diamant[i] = initialiserDiamants();

                }
                PacMan.posx = SCREEN_W/2-PacMan.tx/2;
                PacMan.posy = SCREEN_H/2-PacMan.ty/2;
                //fermeture = 0;
                niveau = 2;
                choise_map = 2;
                score_limit = 12;

                load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, PacMan, monenemy, gestion_map, &Diamant,&fermeture);

                //fermeture = 0;
                stop = 0;
                for(i=0; i<4; i++)
                {
                    Diamant[i] = initialiserDiamants();

                }
                PacMan.posx = SCREEN_W/2-PacMan.tx/2;
                PacMan.posy = SCREEN_H/2-PacMan.ty/2;

                start = time(NULL);
                PacMan.get_Sun=0;
                while(PacMan.score <= 40 && PacMan.vies != 0 && fermeture != 1)

                {

                    niveau = 3;
                    gestion_map->choix = 3;
                    gestion_map = choix_map(gestion_map);

                    stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);

                    rectfill(dbbuffer, PacMan.posx,PacMan.posy, PacMan.posx+25, PacMan.posy+22, makecol(255,255,255));

                    stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);


                    perso_img = deplacementPacMan(dbbuffer, &PacMan, &a);

                    start = gestionSun(map,dbbuffer,Sun,&PacMan,front,start);



                    if( abs(Sun->posx-PacMan.posx)<20 && abs(Sun->posy-PacMan.posy)<20 )
                    {
                        Sun->posx=0;
                        Sun->posy=0;
                        Sun->boolean=0;
                        PacMan.get_Sun = PacMan.get_Sun +4;
                        start = time(NULL);
                    }

                    if(Sun->boolean == 1)
                    {
                        printf("o");
                        Sun->actuel_map = action_sprite_pacman(&PacMan, Sun->SOLEIL, 6);
                        printf("i");
                        draw_sprite(map,Sun->actuel_map,Sun->posx,Sun->posy);
                    }

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

                    score(&Diamant,&PacMan,&compteur_score, niveau);

                    diff_final_score = PacMan.score - 14;

                    if(diff_final_score > 0)
                    {

                        for(i=0; i<diff_final_score; i++)
                        {
                            position_sub = 30;

                            if(Sub_Pac[i]->posx == 0 && Sub_Pac[i]->posy == 0)
                            {

                                if(i == 0)
                                {
                                    Sub_Pac[i]->direction = PacMan.direction;
                                    if(PacMan.direction == 2)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_up, 3);
                                        Sub_Pac[i]->posx = PacMan.posx;
                                        Sub_Pac[i]->posy = PacMan.posy-position_sub;
                                    }
                                    if(PacMan.direction == 4)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
                                        Sub_Pac[i]->posx = PacMan.posx-position_sub;
                                        Sub_Pac[i]->posy = PacMan.posy;

                                    }
                                    if(PacMan.direction == 3)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
                                        Sub_Pac[i]->posx = PacMan.posx+position_sub;
                                        Sub_Pac[i]->posy = PacMan.posy;

                                    }
                                    if(PacMan.direction == 1)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_bot, 2);
                                        Sub_Pac[i]->posx = PacMan.posx;
                                        Sub_Pac[i]->posy = PacMan.posy+position_sub;
                                    }

                                }
                                else
                                {

                                    Sub_Pac[i]->direction = Sub_Pac[i-1]->direction;
                                    if(Sub_Pac[i-1]->direction == 2)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_up, 3);
                                        Sub_Pac[i]->posx = Sub_Pac[i-1]->posx;
                                        Sub_Pac[i]->posy = Sub_Pac[i-1]->posy-position_sub;
                                    }
                                    if(Sub_Pac[i-1]->direction == 4)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
                                        Sub_Pac[i]->posx = Sub_Pac[i-1]->posx-position_sub;
                                        Sub_Pac[i]->posy = Sub_Pac[i-1]->posy;

                                    }
                                    if(Sub_Pac[i-1]->direction == 3)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
                                        Sub_Pac[i]->posx = Sub_Pac[i-1]->posx+position_sub;
                                        Sub_Pac[i]->posy = Sub_Pac[i-1]->posy;

                                    }
                                    if(Sub_Pac[i-1]->direction == 1)
                                    {
                                        Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_bot, 2);
                                        Sub_Pac[i]->posx = Sub_Pac[i-1]->posx;
                                        Sub_Pac[i]->posy = Sub_Pac[i-1]->posy+position_sub;
                                    }
                                }

                            }
                            else
                            {
                                if(i==0)
                                {
                                    if(PacMan.posy-Sub_Pac[i]->posy-position_sub>0)
                                    {
                                        //UP
                                        /*if(getpixel(dbbuffer,Sub_Pac[i]->posx,Sub_Pac[i]->posy-Sub_Pac[i]->deplacement -7 ) != makecol(255,0,0) && getpixel(dbbuffer,Sub_Pac[i]->posx+25,Sub_Pac[i]->posy-Sub_Pac[i]->deplacement - 7 ) != makecol(255,0,0))
                                        {
                                            if(PacMan.posx-Sub_Pac[i]->posx+position_sub<0)
                                            {
                                                Sub_Pac[i]->posx = Sub_Pac[i]->posx+Sub_Pac[i]->deplacement;
                                                Sub_Pac[i]->posy = Sub_Pac[i]->posy;
                                            }
                                            else
                                            {
                                                Sub_Pac[i]->posx = Sub_Pac[i]->posx-Sub_Pac[i]->deplacement;
                                                Sub_Pac[i]->posy = Sub_Pac[i]->posy;
                                            }
                                        }
                                        else
                                        {*/
    /* Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_up, 3);
     Sub_Pac[i]->posx = PacMan.posx;
     Sub_Pac[i]->posy = Sub_Pac[i]->posy+Sub_Pac[i]->deplacement;
     /*}*/
    /*  }
      else if(PacMan.posx-Sub_Pac[i]->posx-position_sub>0)
      {
          /*if(getpixel(dbbuffer,Sub_Pac[i]->posx+Sub_Pac[i]->tx+Sub_Pac[i]->deplacement +25,Sub_Pac[i]->posy ) != makecol(255,00,00)&& getpixel(dbbuffer,Sub_Pac[i]->posx+Sub_Pac[i]->tx+Sub_Pac[i]->deplacement + 25,Sub_Pac[i]->posy + 22) != makecol(255,00,00))
          {
              if(PacMan.posy-Sub_Pac[i]->posy-position_sub>0)
              {
                  Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                  Sub_Pac[i]->posy = Sub_Pac[i]->posy+Sub_Pac[i]->deplacement;
              }
              else
              {
                  Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                  Sub_Pac[i]->posy = Sub_Pac[i]->posy-Sub_Pac[i]->deplacement;
              }
          }
          else
          {*/
    /*  Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
      Sub_Pac[i]->posx = Sub_Pac[i]->posx+Sub_Pac[i]->deplacement;
      Sub_Pac[i]->posy = PacMan.posy;

      /* }*/
    /* }
     else if(PacMan.posx-Sub_Pac[i]->posx+position_sub<0)
     {
         /*if(getpixel(dbbuffer,Sub_Pac[i]->posx-Sub_Pac[i]->deplacement -20,Sub_Pac[i]->posy) != makecol(255,00,00)&& getpixel(dbbuffer,Sub_Pac[i]->posx-Sub_Pac[i]->deplacement - 20,Sub_Pac[i]->posy + 22) != makecol(255,00,00))
         {
             if(PacMan.posy-Sub_Pac[i]->posy-position_sub>0)
             {
                 Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                 Sub_Pac[i]->posy = Sub_Pac[i]->posy+Sub_Pac[i]->deplacement;
             }
             else
             {
                 Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                 Sub_Pac[i]->posy = Sub_Pac[i]->posy-Sub_Pac[i]->deplacement;
             }
         }
         else
         {*/
    /*     Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
         Sub_Pac[i]->posx = Sub_Pac[i]->posx-Sub_Pac[i]->deplacement;
         Sub_Pac[i]->posy = PacMan.posy;
         /*}*/
    /*   }
       else if(PacMan.posy-Sub_Pac[i]->posy+position_sub<0)
       {
           /*
              if(getpixel(dbbuffer,Sub_Pac[i]->posx,Sub_Pac[i]->posy+Sub_Pac[i]->ty+Sub_Pac[i]->deplacement + 7 ) != makecol(255,00,00)&& getpixel(dbbuffer,Sub_Pac[i]->posx + 25,Sub_Pac[i]->posy+Sub_Pac[i]->ty+Sub_Pac[i]->deplacement+7 ) != makecol(255,00,00))
              {
                  if(PacMan.posx-Sub_Pac[i]->posx+position_sub<0)
                  {
                      Sub_Pac[i]->posx = Sub_Pac[i]->posx+Sub_Pac[i]->deplacement;
                      Sub_Pac[i]->posy = Sub_Pac[i]->posy;
                  }
                  else
                  {
                      Sub_Pac[i]->posx = Sub_Pac[i]->posx-Sub_Pac[i]->deplacement;
                      Sub_Pac[i]->posy = Sub_Pac[i]->posy;
                  }
              }
              else
              {*/
    /*      Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_bot, 2);
          Sub_Pac[i]->posx = PacMan.posx;
          Sub_Pac[i]->posy = Sub_Pac[i]->posy-Sub_Pac[i]->deplacement;
          /* }*/
    /*  }
      else
      {
          Sub_Pac[i]->posx = Sub_Pac[i]->posx;
          Sub_Pac[i]->posy = Sub_Pac[i]->posy;
      }
    }
    else
    {

      if(Sub_Pac[i-1]->posy-Sub_Pac[i]->posy-position_sub>0)
      {
          /*
          if(getpixel(dbbuffer,Sub_Pac[i]->posx,Sub_Pac[i]->posy-Sub_Pac[i]->deplacement -7 ) != makecol(255,0,0) && getpixel(dbbuffer,Sub_Pac[i]->posx+25,Sub_Pac[i]->posy-Sub_Pac[i]->deplacement - 7 ) != makecol(255,0,0))
          {
              if(Sub_Pac[i-1]->posx-Sub_Pac[i]->posx+position_sub<0)
              {
                  Sub_Pac[i]->posx = Sub_Pac[i]->posx+Sub_Pac[i]->deplacement;
                  Sub_Pac[i]->posy = Sub_Pac[i]->posy;
              }
              else
              {
                  Sub_Pac[i]->posx = Sub_Pac[i]->posx-Sub_Pac[i]->deplacement;
                  Sub_Pac[i]->posy = Sub_Pac[i]->posy;
              }
          }
          else
          {
          */
    /*  Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_up, 3);
      Sub_Pac[i]->posx = Sub_Pac[i-1]->posx;
      Sub_Pac[i]->posy = Sub_Pac[i]->posy+Sub_Pac[i]->deplacement;
      /*
      }*/
    /*  }
      else if(Sub_Pac[i-1]->posx-Sub_Pac[i]->posx-position_sub>0)
      {
          /*
             if(getpixel(dbbuffer,Sub_Pac[i]->posx+Sub_Pac[i]->tx+Sub_Pac[i]->deplacement +25,Sub_Pac[i]->posy ) != makecol(255,00,00)&& getpixel(dbbuffer,Sub_Pac[i]->posx+Sub_Pac[i]->tx+Sub_Pac[i]->deplacement + 25,Sub_Pac[i]->posy + 22) != makecol(255,00,00))
             {
                 if(Sub_Pac[i-1]->posy-Sub_Pac[i]->posy-position_sub>0)
                 {
                     Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                     Sub_Pac[i]->posy = Sub_Pac[i]->posy+Sub_Pac[i]->deplacement;
                 }
                 else
                 {
                     Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                     Sub_Pac[i]->posy = Sub_Pac[i]->posy-Sub_Pac[i]->deplacement;
                 }
             }
             else
             {*/
    /*     Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
         Sub_Pac[i]->posx = Sub_Pac[i]->posx+Sub_Pac[i]->deplacement;
         Sub_Pac[i]->posy = Sub_Pac[i-1]->posy;
         /*}*/
    /* }
     else if(Sub_Pac[i-1]->posx-Sub_Pac[i]->posx+position_sub<0)
     {
         /*if(getpixel(dbbuffer,Sub_Pac[i]->posx-Sub_Pac[i]->deplacement -20,Sub_Pac[i]->posy) != makecol(255,00,00)&& getpixel(dbbuffer,Sub_Pac[i]->posx-Sub_Pac[i]->deplacement - 20,Sub_Pac[i]->posy + 22) != makecol(255,00,00))
         {
             if(Sub_Pac[i-1]->posy-Sub_Pac[i]->posy-position_sub>0)
             {
                 Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                 Sub_Pac[i]->posy = Sub_Pac[i]->posy+Sub_Pac[i]->deplacement;
             }
             else
             {
                 Sub_Pac[i]->posx = Sub_Pac[i]->posx;
                 Sub_Pac[i]->posy = Sub_Pac[i]->posy-Sub_Pac[i]->deplacement;
             }
         }
         else
         {*/
    /*   Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_right, 8);
       Sub_Pac[i]->posx = Sub_Pac[i]->posx-Sub_Pac[i]->deplacement;
       Sub_Pac[i]->posy = Sub_Pac[i-1]->posy;
       /*}*/
    /*   }
       else if(Sub_Pac[i-1]->posy-Sub_Pac[i]->posy+position_sub<0)
       {
           /*if(getpixel(dbbuffer,Sub_Pac[i]->posx,Sub_Pac[i]->posy+Sub_Pac[i]->ty+Sub_Pac[i]->deplacement + 7 ) != makecol(255,00,00)&& getpixel(dbbuffer,Sub_Pac[i]->posx + 25,Sub_Pac[i]->posy+Sub_Pac[i]->ty+Sub_Pac[i]->deplacement+7 ) != makecol(255,00,00))
           {
               if(Sub_Pac[i-1]->posx-Sub_Pac[i]->posx+position_sub<0)
               {
                   Sub_Pac[i]->posx = Sub_Pac[i]->posx+Sub_Pac[i]->deplacement;
                   Sub_Pac[i]->posy = Sub_Pac[i]->posy;
               }
               else
               {
                   Sub_Pac[i]->posx = Sub_Pac[i]->posx-Sub_Pac[i]->deplacement;
                   Sub_Pac[i]->posy = Sub_Pac[i]->posy;
               }
           }
           else
           {*/
    /*    Sub_map[i] = action_sprite_pacman(Sub_Pac[i], Sub_Pac[i]->pacman_bot, 2);
        Sub_Pac[i]->posx = Sub_Pac[i-1]->posx;
        Sub_Pac[i]->posy = Sub_Pac[i]->posy-Sub_Pac[i]->deplacement;
        /*}*/
    /*     }
         else
         {
             /*
             if(Sub_Pac[i-1]->posy == Sub_Pac[i]->posy && PacMan.direction == 4)
             {
             Sub_Pac[i]->posx = Sub_Pac[i-1]->posx+position_sub;
             Sub_Pac[i]->posy = Sub_Pac[i-1]->posy;
             }else if(Sub_Pac[i-1]->posy == Sub_Pac[i]->posy && PacMan.direction == 3)
             {
             Sub_Pac[i]->posx = Sub_Pac[i-1]->posx-position_sub;
             Sub_Pac[i]->posy = Sub_Pac[i-1]->posy;
             }else if(Sub_Pac[i-1]->posx == Sub_Pac[i]->posx && PacMan.direction == 2)
             {
             Sub_Pac[i]->posx = Sub_Pac[i-1]->posx;
             Sub_Pac[i]->posy = Sub_Pac[i-1]->posy+position_sub;
             }else if(Sub_Pac[i-1]->posx == Sub_Pac[i]->posx && PacMan.direction == 1)
             {
             Sub_Pac[i]->posx = Sub_Pac[i-1]->posx;
             Sub_Pac[i]->posy = Sub_Pac[i-1]->posy-position_sub;
             }*/
    /*     }

     }




    }


    if(Sub_Pac[i]->turn_img == 0)
    {
     draw_sprite(map,Sub_map[i],Sub_Pac[i]->posx,Sub_Pac[i]->posy);
    }
    else
    {
     draw_sprite_h_flip(map,Sub_map[i],Sub_Pac[i]->posx,Sub_Pac[i]->posy);
    }

    }

    }

    blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

    compteur_death++;
    compteur_death = death(monenemy, &PacMan, compteur_death,dbbuffer);

    if(key[KEY_S])
    {
    sauvegarde1( &monenemy,&PacMan, gestion_map);
    fermeture = 1;
    }

    rest(20);

    }
    }



    }
    else if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(76,255,0))
    {
    recuperation(&monenemy,&PacMan, gestion_map, choise_map);

    stop = 0;
    fermeture = 0;
    PacMan.vies = 5;


    while(PacMan.vies != 0 && fermeture != 1)
    {
    for(i=0; i<4; i++)
    {
    Diamant[i] = initialiserDiamants();
    }
    PacMan.posx = SCREEN_W/2-PacMan.tx/2;
    PacMan.posy = SCREEN_H/2-PacMan.ty/2;

    if(PacMan.score < 4 )
    {
    score_limit = 4;
    score_max = 0;
    niveau = 0;
    choise_map = 0;
    }

    if (PacMan.score < 8 && PacMan.score >= 4)
    {
    score_limit = 8;
    score_max = 4;
    niveau = 1;
    choise_map = 1;
    }

    if(PacMan.score <12 && PacMan.score >= 0)
    {
    score_limit = 12;
    score_max = 8;
    niveau = 2;
    choise_map = 2;
    }

    //PacMan.score = 0;
    load_map1( i, niveau,  choise_map,  score_limit, score_max,  &a,  stop,  compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, PacMan, monenemy, gestion_map, &Diamant, &fermeture);
    PacMan.score = PacMan.score + 4;
    printf("%d\n", PacMan.score);



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
    printf("VIT \n");
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
    exit(0);

    /// NE PAS OUBLIER DE MODIFIER LES DIAMANTS POUR EN METTRE 5 !!!!!!




    }
    */
    return 0;
}
END_OF_MAIN();

