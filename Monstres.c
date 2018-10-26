#include "prototypes.h"


t_enemy * initialiserenemy()
{
    t_enemy *mmonstre;
    mmonstre=(t_enemy*) malloc(1 * sizeof(t_enemy));

    mmonstre->dposx= 0;
    mmonstre->dposy= 0;
    mmonstre->ddeplacement=2;
    mmonstre->ddirection = rand()%4;
    mmonstre->alive = 1;
    mmonstre->dtx=25;
    mmonstre->dty=25;
    mmonstre->resetdir=0;
    mmonstre->compteur_enemy = 0;


    return mmonstre;
}




