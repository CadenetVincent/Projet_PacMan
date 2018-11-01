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
int main()
{
    int pos_enemy[2][4]= {{255,497,255,497},{283,283,640,640}};
    int i = 0;

    t_enemy * monenemy[4];
    t_map * gestion_map;
    t_Diamant * Diamant[4];

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

    lancerAllegro();
    int a = 0;
    int compteur_death = 80;
    int compteur_score = 0;
    int stop = 0;
    int niveau = 0;
    //int border = 0;
    //int choix = 0;

    t_PacMan *bob;
    t_PacMan PacMan;
    bob = &PacMan;

    intialisationPacMan(bob);

    srand(time(NULL));

    map = create_bitmap(SCREEN_W,SCREEN_H);
    dbbuffer = create_bitmap(SCREEN_W,SCREEN_H);
    menu = load_bitmap("menu.bmp", NULL);
    menubuffer = load_bitmap("menubuffer.bmp", NULL);
    Diamants = load_bitmap("diamant.bmp",NULL);
    regles = load_bitmap("regles.bmp", NULL);
    bordure = load_bitmap("bordure.bmp", NULL);

    gestion_map = initialisermap();

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

/// NE PAS OUBLIER DE MODIFIER LES DIAMANTS POUR EN METTRE 5 !!!!!!
    while(!key[KEY_ESC])
    {
        blit(menubuffer, dbbuffer,0,0,0,0,SCREEN_W,SCREEN_H);

        blit(menu, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(255,0,0))
        {
            PacMan.vies = 5;

            PacMan.score = 0;
            stop = 0;
            for(i=0; i<4; i++)
            {
                Diamant[i] = initialiserDiamants();

            }
            PacMan.posx = SCREEN_W/2-PacMan.tx/2-10;
            PacMan.posy = SCREEN_H/2-PacMan.ty/2-10;


            while(PacMan.score != 4 && PacMan.vies != 0 && !key[KEY_S])
            {
                niveau = 0;
                gestion_map->choix = 0;
                gestion_map = choix_map(gestion_map);
                stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);

                //stretch_blit(test, map, 0,0,test->w,test->h,0,0,SCREEN_W,SCREEN_H);

                rectfill(dbbuffer, PacMan.posx,PacMan.posy, PacMan.posx+25, PacMan.posy+22, makecol(255,255,255));

                stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);


                perso_img = deplacementPacMan(dbbuffer, &PacMan, &a);

                if(PacMan.turn_img == 0)
                {
                    draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
                }
                else
                {
                    draw_sprite_h_flip(map,perso_img,PacMan.posx,PacMan.posy);
                }

                //masked_blit(perso_img, map, 0,0,PacMan.posx,PacMan.posy,perso_img->w,perso_img->h);
                //draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
//mort(&monenemy, &PacMan, &compteur,dbbuffer);

/// 47-40

                for(i=0; i<4; i++)
                {

                    monenemy[i]->compteur_enemy++;

                    if(monenemy[i]->compteur_enemy == 100)
                    {
                        monenemy[i]->resetdir=0;
                        monenemy[i]->compteur_enemy=0;
                        //mort(&monenemy[i], &PacMan, &compteur, dbbuffer);
                    }

                    // enemy = call_monster(dbbuffer,monenemy[i],&PacMan);
                    gestionDiamant(dbbuffer, Diamant[i], front, &stop);


                    masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);

                    suppressionDiamant(dbbuffer,Diamant[i],&PacMan);


                    if(Diamant[i]->boolean != 1)
                    {
                        masked_blit(Diamants, map,0,0, Diamant[i]->posx, Diamant[i]->posy, SCREEN_W,SCREEN_H);
                    }

                }

                blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
                score(&Diamant,&PacMan,&compteur_score, niveau);
                compteur_death++;
//compteur_score++;
//printf("%d \n\n", compteur_score);
                compteur_death = death(monenemy, &PacMan, compteur_death,dbbuffer);
//compteur_score = score(Diamant,&PacMan,compteur_score,dbbuffer);






 if(key[KEY_S])
            {
                sauvegarde1( &monenemy,&PacMan, gestion_map);
            }

                rest(20);
            }
            stop = 0;
            for(i=0; i<4; i++)
            {
                Diamant[i] = initialiserDiamants();

            }
            PacMan.posx = SCREEN_W/2-PacMan.tx/2;
            PacMan.posy = SCREEN_H/2-PacMan.ty/2;


            while(PacMan.score != 8 && PacMan.vies != 0 && !key[KEY_S])
            {
                niveau = 1;


                gestion_map->choix = 1;
                gestion_map = choix_map(gestion_map);

                stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);

                //stretch_blit(test, map, 0,0,test->w,test->h,0,0,SCREEN_W,SCREEN_H);

                rectfill(dbbuffer, PacMan.posx,PacMan.posy, PacMan.posx+25, PacMan.posy+22, makecol(255,255,255));

                stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);


                perso_img = deplacementPacMan(dbbuffer, &PacMan, &a);

                if(PacMan.turn_img == 0)
                {
                    draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
                }
                else
                {
                    draw_sprite_h_flip(map,perso_img,PacMan.posx,PacMan.posy);
                }

                //masked_blit(perso_img, map, 0,0,PacMan.posx,PacMan.posy,perso_img->w,perso_img->h);
                //draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
//mort(&monenemy, &PacMan, &compteur,dbbuffer);

/// 47-40

                for(i=0; i<4; i++)
                {

                    monenemy[i]->compteur_enemy++;

                    if(monenemy[i]->compteur_enemy == 100)
                    {
                        monenemy[i]->resetdir=0;
                        monenemy[i]->compteur_enemy=0;
                        //mort(&monenemy[i], &PacMan, &compteur, dbbuffer);
                    }

                    // enemy = call_monster(dbbuffer,monenemy[i],&PacMan);
                    gestionDiamant(dbbuffer, Diamant[i], front, &stop);


                    masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);

                    suppressionDiamant(dbbuffer,Diamant[i],&PacMan);


                    if(Diamant[i]->boolean != 1)
                    {
                        masked_blit(Diamants, map,0,0, Diamant[i]->posx, Diamant[i]->posy, SCREEN_W,SCREEN_H);
                    }

                }

                blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
                score(&Diamant,&PacMan,&compteur_score, niveau);
                compteur_death++;
//compteur_score++;
//printf("%d \n\n", compteur_score);
                compteur_death = death(monenemy, &PacMan, compteur_death,dbbuffer);
//compteur_score = score(Diamant,&PacMan,compteur_score,dbbuffer);





 if(key[KEY_S])
            {
                sauvegarde1( &monenemy,&PacMan, gestion_map);
            }


                rest(20);



            }

            stop = 0;
            for(i=0; i<4; i++)
            {
                Diamant[i] = initialiserDiamants();

            }
            PacMan.posx = SCREEN_W/2-PacMan.tx/2;
            PacMan.posy = SCREEN_H/2-PacMan.ty/2;

            while(PacMan.score != 12 && PacMan.vies != 0 && !key[KEY_S])
            {
                niveau = 2;



                gestion_map->choix = 2;
                gestion_map = choix_map(gestion_map);

                stretch_blit(gestion_map->actual_test, dbbuffer,0,0,gestion_map->actual_test->w,gestion_map->actual_test->h,0,0,SCREEN_W,SCREEN_H);

                //stretch_blit(test, map, 0,0,test->w,test->h,0,0,SCREEN_W,SCREEN_H);

                rectfill(dbbuffer, PacMan.posx,PacMan.posy, PacMan.posx+25, PacMan.posy+22, makecol(255,255,255));

                stretch_blit(gestion_map->actual_front, map, 0,0,gestion_map->actual_front->w,gestion_map->actual_front->h,0,0,SCREEN_W,SCREEN_H);


                perso_img = deplacementPacMan(dbbuffer, &PacMan, &a);

                if(PacMan.turn_img == 0)
                {
                    draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
                }
                else
                {
                    draw_sprite_h_flip(map,perso_img,PacMan.posx,PacMan.posy);
                }

                //masked_blit(perso_img, map, 0,0,PacMan.posx,PacMan.posy,perso_img->w,perso_img->h);
                //draw_sprite(map,perso_img,PacMan.posx,PacMan.posy);
//mort(&monenemy, &PacMan, &compteur,dbbuffer);

/// 47-40

                for(i=0; i<4; i++)
                {

                    monenemy[i]->compteur_enemy++;

                    if(monenemy[i]->compteur_enemy == 100)
                    {
                        monenemy[i]->resetdir=0;
                        monenemy[i]->compteur_enemy=0;
                        //mort(&monenemy[i], &PacMan, &compteur, dbbuffer);
                    }

                    //enemy = call_monster(dbbuffer,monenemy[i],&PacMan);
                    gestionDiamant(dbbuffer, Diamant[i], front, &stop);


                    masked_blit(enemy, map, 0,0,monenemy[i]->dposx,monenemy[i]->dposy,enemy->w,enemy->h);

                    suppressionDiamant(dbbuffer,Diamant[i],&PacMan);


                    if(Diamant[i]->boolean != 1)
                    {
                        masked_blit(Diamants, map,0,0, Diamant[i]->posx, Diamant[i]->posy, SCREEN_W,SCREEN_H);
                    }

                }

                blit(map, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
                score(&Diamant,&PacMan,&compteur_score, niveau);
                compteur_death++;
//compteur_score++;
//printf("%d \n\n", compteur_score);
                compteur_death = death(monenemy, &PacMan, compteur_death,dbbuffer);
//compteur_score = score(Diamant,&PacMan,compteur_score,dbbuffer);




 if(key[KEY_S])
            {
                sauvegarde1( &monenemy,&PacMan, gestion_map);
            }



                rest(20);



            }

            if(key[KEY_S])
            {
                sauvegarde1( &monenemy,&PacMan, gestion_map);
            }

            /*blit(menubuffer, dbbuffer,0,0,0,0,SCREEN_W,SCREEN_H);

                    blit(dbbuffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H);*/

        }
        else if(mouse_b&1 == 1 && getpixel(dbbuffer, mouse_x,mouse_y) == makecol(76,255,0))
            printf("SP \n");
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

