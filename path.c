/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 19:26:38 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/13 19:26:40 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				explore(t_map *map, t_room *room)
{
	t_room			*next;
	t_exploration	exp;
	int				i;

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
			continue ;
		if (next->explo.state == s_explored && next->explo.len == exp.len)
			if (next->explo.dist < exp.dist)
				continue ;
		next->explo = exp;
		if (next->type == t_none)
			explore(map, next);
	}
}

void				fill_path(t_map *map, int *path, int len, t_room *end)
{
	path[--len] = end->id;
	while (len > 0)
	{
		len--;
		path[len] = end->explo.id;
		end = &(map->rooms[end->explo.id]);
		end->explo.state = s_burned;
	}
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

t_path				*find_best_path(t_map *map)
{
	t_room			*end;
	t_path			*path;

	explore(map, &(map->rooms[map->start]));
	end = &(map->rooms[map->end]);
	if (end->explo.state != s_explored)
		return (NULL);
	path = ft_secalloc(sizeof(t_path));
	path->dist = end->explo.dist;
	path->len = end->explo.len;
	path->steps = ft_salloc(path->len * sizeof(int));
	fill_path(map, path->steps, path->len, &(map->rooms[map->end]));
	clean_map(map);
	return (path);
}

void				find_paths(t_map *map)
{
	t_path			*next_path;
	t_path			*paths;
	t_path			*node;

	paths = find_best_path(map);
	if (!paths)
		ERROR();
	if (paths->len == 1)
	{
		map->paths = paths;
		return ;
	}
	while (1)
	{
		next_path = find_best_path(map);
		if (next_path == NULL)
			break ;
		node = paths;
		while (node->next)
			node = node->next;
		node->next = next_path;
	}
	map->paths = paths;
}
