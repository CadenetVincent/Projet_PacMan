#include "prototypes.h"

BITMAP * choix_map(t_map * changemap)
{
    BITMAP * map_choise[2]=NULL;
    switch(changemap->choix)
    {

    case 0:

        if(changemap->border == 0)
        {
            map_choise[0] = changemap->noborder_pac_man[0];
            map_choise[1] = changemap->buffer_pc_nb[0];
        }
        else
        {
            map_choise[0] = changemap->map_pac_man[0];
            map_choise[1] = changemap->buffer_pc[0];
        }

        break;

    case 1:

        if(changemap->border == 0)
        {
            map_choise[0] = changemap->noborder_pac_man[1];
            map_choise[1] = changemap->buffer_pc_nb[1];
        }
        else
        {
            map_choise[0] = changemap->map_pac_man[1];
            map_choise[1] = changemap->buffer_pc[1];
        }

        break;

    case 2:

        if(changemap->border == 0)
        {
            map_choise[0] = changemap->noborder_pac_man[2];
            map_choise[1] = changemap->buffer_pc_nb[2];
        }
        else
        {
            map_choise[0] = changemap->map_pac_man[2];
            map_choise[1] = changemap->buffer_pc[2];
        }


        break;

    case 3:

        if(changemap->border == 0)
        {
            map_choise[0] = changemap->noborder_pac_man[3];
            map_choise[1] = changemap->buffer_pc_nb[3];
        }
        else
        {
            map_choise[0] = changemap->map_pac_man[3];
            map_choise[1] = changemap->buffer_pc[3];
        }

        break;
    }
    return map_choise;
}

t_map * initialisermap()
{
    char nomfichier[100];
    t_map *gestionmap;
    gestionmap=(t_map*) malloc(1 * sizeof(t_map));

    gestionmap->border=0;
    gestionmap->choix=0;

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/bufferpc_%d.bmp",i);
        gestionmap->buffer_pc[i]=load_bitmap(nomfichier,NULL);
        if (!gestionmap->buffer_pc[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/bufferpc_nb_%d.bmp",i);
        gestionmap->buffer_pc_nb[i]=load_bitmap(nomfichier,NULL);
        if (!gestionmap->buffer_pc_nb[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/map_pac_man_%d.bmp",i);
        gestionmap->map_pac_man[i]=load_bitmap(nomfichier,NULL);
        if (!gestionmap->map_pac_man[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }

    for(i=0; i<4; i++)
    {
        sprintf(nomfichier,"pacmap/noborder_pac_man_%d.bmp",i);
        gestionmap->noborder_pac_man[i]=load_bitmap(nomfichier,NULL);
        if (!gestionmap->noborder_pac_man[i])
        {
            allegro_message("PRB d'ouverture = %s",nomfichier);
        }
    }


    return gestionmap;
}
