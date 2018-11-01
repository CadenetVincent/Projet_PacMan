#include "prototypes.h"

t_map * choix_map(t_map * change_map)
{

    switch(change_map->choix)
    {

    case 0:

        if(change_map->border != 0)
        {
            change_map->actual_front = change_map->noborder_pac_man[0];
            change_map->actual_test = change_map->buffer_pc_nb[0];
        }
        else
        {
            change_map->actual_front = change_map->map_pac_man[0];
            change_map->actual_test = change_map->buffer_pc[0];
        }

        break;

    case 1:

        if(change_map->border != 0)
        {
            change_map->actual_front = change_map->noborder_pac_man[1];
            change_map->actual_test = change_map->buffer_pc_nb[1];
        }
        else
        {
            change_map->actual_front = change_map->map_pac_man[1];
            change_map->actual_test = change_map->buffer_pc[1];
        }

        break;

    case 2:

        if(change_map->border != 0)
        {
            change_map->actual_front = change_map->noborder_pac_man[2];
            change_map->actual_test = change_map->buffer_pc_nb[2];
        }
        else
        {
            change_map->actual_front = change_map->map_pac_man[2];
            change_map->actual_test = change_map->buffer_pc[2];
        }


        break;

    case 3:

        if(change_map->border != 0)
        {
            change_map->actual_front = change_map->noborder_pac_man[3];
            change_map->actual_test = change_map->buffer_pc_nb[3];
        }
        else
        {
            change_map->actual_front = change_map->map_pac_man[3];
            change_map->actual_test = change_map->buffer_pc[3];
        }

        break;
    }
    return change_map;
}

t_map * initialisermap()
{
    int i;
    char nomfichier[100];
    t_map *gestion_map;
    gestion_map = (t_map*) malloc(1 * sizeof(t_map));

    gestion_map->border= 0;
    gestion_map->choix= 0;

    gestion_map->actual_front=NULL;
    gestion_map->actual_test=NULL;

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/bufferpc_%d.bmp",i);
        gestion_map->buffer_pc[i]=load_bitmap(nomfichier,NULL);
        if (!gestion_map->buffer_pc[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/bufferpc_nb_%d.bmp",i);
        gestion_map->buffer_pc_nb[i]=load_bitmap(nomfichier,NULL);
        if (!gestion_map->buffer_pc_nb[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/map_pac_man_%d.bmp",i);
        gestion_map->map_pac_man[i]=load_bitmap(nomfichier,NULL);
        if (!gestion_map->map_pac_man[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/noborder_pac_man_%d.bmp",i);
        gestion_map->noborder_pac_man[i]=load_bitmap(nomfichier,NULL);
        if (!gestion_map->noborder_pac_man[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }


    return gestion_map;
}
