#include "lemin.h"

t_error			check(t_map *map, t_bool *ignore)
{
	t_room		*room;
	int			i;
	
	i = 0;
	while (i < map->roomcount)
	{
		room = &(map->rooms[i]);
		if (i != room->id)
			ft_putendl("ERROR ids");
		if (room->type & t_start)
			map->start = i;
		if (room->type & t_end)
			map->end = i;
		i++;
	}
	if (map->start == -1 || map->end == -1)
		return (e_parsing);
	if (map->start == map->end)
		*ignore = true;
	return (e_success);
}