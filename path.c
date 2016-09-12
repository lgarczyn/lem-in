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
		{
			printf("%*cound: %s burned\n", exp.len * 2, 'f', next->name);
			continue ;
		}
		if (next->explo.state == s_explored && next->explo.len < exp.len)
		{
			printf("%*cound: %s explored\n", exp.len * 2, 'f', next->name);
			continue;
		}
		if (next->explo.state == s_explored && next->explo.len == exp.len)
			if (next->explo.dist < exp.dist)
			{
				printf("%*cound: %s explored\n", exp.len * 2, 'f', next->name);
				continue;
			}
		if (next->explo.state == s_explored)
			printf("%*cound: %s explored but replaced\n", exp.len * 2, 'f', next->name);
		else
			printf("%*cound: %s not explored\n", exp.len * 2, 'f', next->name);
		next->explo = exp;
		if (next->type == t_start)
			printf("%*cound: %s start\n", exp.len * 2, 'f', room->name);
		if (next->type == t_end)
			printf("%*cound: %s end\n", exp.len * 2, 'f', room->name);
		if (next->type == t_none)
			explore(map, next);
	}
	printf("%*c %s\n", room->explo.len * 2, '}', room->name);
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
	
	printf("finding best path:\n");
	printf("explo len start %i\n", map->rooms[map->start].explo.len);
	explore(map, &(map->rooms[map->start]));
	end = &(map->rooms[map->end]);
	if (end->explo.state != s_explored)
		return (NULL);
	path = ft_secalloc(sizeof(t_path));
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
		if (map->rooms[i].explo.state == s_explored)
			map->rooms[i].explo.state = s_clean;
		map->rooms[i].explo.len = 0;
		map->rooms[i].explo.dist = 0;
		map->rooms[i].explo.id = 0;
		i++;
	}
}

t_error				find_paths(t_map *map)
{
	t_path			*next_path;
	t_path			*paths;
	t_path			*node;
	
	printf("START\n");
	paths = find_best_path(map);
	printf("END\n");
	if (!paths)
		return (e_parsing);
	clean_map(map);
	while (1)
	{
		printf("START\n");
		next_path = find_best_path(map);
		printf("END\n");
		if (next_path == NULL)
			break ;
		node = paths;
		while (node->next)
			node = node->next;
		node->next = next_path;
		clean_map(map);
	}
	map->paths = paths;
	return (e_success);
}
