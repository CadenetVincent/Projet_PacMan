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

 Console();

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

            while(PacMan.vies > 0 && fermeture != 1 && PacMan.score != 12)
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

                niveau = 2;
                choise_map = 2;
                score_limit = 12;

                load_map( i, niveau,  choise_map,  score_limit,  &a,  stop,  &compteur_score,  compteur_death, Diamants, front,  enemy,  dbbuffer,  map,  perso_img, PacMan, monenemy, gestion_map, &Diamant,&fermeture);


                stop = 0;
                for(i=0; i<4; i++)
                {
                    Diamant[i] = initialiserDiamants();

                }
                PacMan.posx = SCREEN_W/2-PacMan.tx/2;
                PacMan.posy = SCREEN_H/2-PacMan.ty/2;

                start = time(NULL);
                PacMan.get_Sun=0;

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

    return 0;
}
END_OF_MAIN();

