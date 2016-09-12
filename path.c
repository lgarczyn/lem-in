#include "lemin.h"

void				explore(t_map *map, t_room *room)
{
	t_room			*next;
	t_exploration	exp;
	int				i;

	printf("%*code %s {\n", room->explo.len * 2, 'n', room->name);
	i = -1;
	exp.len = room->explo.len + 1;
	exp.state = s_explored;
	exp.id = room->id;
	while (++i < room->linkcount)
	{
		next = &(map->rooms[room->links[i]]);
		exp.dist = room->explo.dist + ft_dist(room->pos, next->pos);
		if (next->explo.state == s_burned)
			continue ;
		if (next->explo.state == s_explored && next->explo.len < exp.len)
			continue;
		if (next->explo.state == s_explored && next->explo.len == exp.len)
			if (next->explo.dist < exp.dist)
				continue;
		next->explo = exp;
		if (next->type == t_none)
			explore(map, next);
		else
			printf("%*cound: %i\n", exp.len * 2, 'f', next->type);
	}
	printf("%*c\n", room->explo.len * 2, '}');
}

void				fill_path(t_map *map, int *path, int len, t_room *end)
{
	while (len > 1)
	{
		len--;
		path[len] = end->explo.id;
		end = &(map->rooms[end->explo.id]);
		end->explo.state = s_burned;
	}
}

t_path				*find_best_path(t_map *map)
{
	t_room			*end;
	t_path			*path;
	
	explore(map, &(map->rooms[map->start]));
	end = &(map->rooms[map->end]);
	if (end->explo.state != s_explored)
		return (NULL);
	path = ft_salloc(sizeof(t_path));
	path->dist = end->explo.dist;
	path->len = end->explo.len;
	path->steps = ft_salloc(path->len * sizeof(int));
	fill_path(map, path->steps, path->len, &(map->rooms[map->end]));
	return (path);
}

void				clean_map(t_map *map)
{
	int				i;
	
	i = 0;
	while (i < map->roomcount)
	{
		map->rooms[i++].explo.state = s_clean;
	}
}

t_error				find_paths(t_map *map)
{
	t_path			*best_path;
	t_path			*paths;
	t_path			*node;
	
	printf("START\n");
	paths = find_best_path(map);
	if (!paths)
		return (e_parsing);
	while ((best_path = find_best_path(map)))
	{
		printf("START\n");
		node = paths;
		while (node->next)
			node = node->next;
		node->next = best_path;
		clean_map(map);
	}
	map->paths = paths;
	return (e_success);
}
