#include "lemin.h"

void			flatten_rooms(t_map *map)
{
	t_room		*final;
	t_room		*node;
	int			i;
	
	final = (t_room*)ft_salloc(sizeof(t_room) * map->roomcount);
	node = map->rooms;
	i = map->roomcount;
	while (node)
	{
		final[--i] = *node;
		node = node->next;
		free(final[i].next);
		final[i].next = NULL;
	}
	map->rooms = final;
}

#include <stdio.h>

void			count_links(t_map *map)
{
	t_link		*link;

	link = map->links;
	while(link)
	{
		map->rooms[link->a].linkcount++;
		map->rooms[link->b].linkcount++;
		link = link->next;
	}
}

void			alloc_links(t_map *map)
{
	int			i;

	i = 0;
	while(i < map->roomcount)
	{
		map->rooms[i].links = ft_salloc(map->rooms[i].linkcount * sizeof(int));
		map->rooms[i++].linkcount = 0;
	}
}

void			store_links(t_map *map)
{
	t_link		*link;
	t_link		*prev;
	t_room		*rooma;
	t_room		*roomb;
	
	link = map->links;
	while(link)
	{
		rooma = &(map->rooms[link->a]);
		roomb = &(map->rooms[link->b]);
		rooma->links[rooma->linkcount++] = roomb->id;
		roomb->links[roomb->linkcount++] = rooma->id;
		prev = link;
		link = link->next;
		free(prev);
	}
	map->links = NULL;
}

t_error			apply_links(t_map *map)
{
	flatten_rooms(map);
	count_links(map);
	alloc_links(map);
	store_links(map);
	return (e_success);
}