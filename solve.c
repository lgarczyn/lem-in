/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 19:20:23 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/13 19:20:24 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			attribute(t_path *paths)
{
	int			ant;

	ant = 1;
	while (paths)
	{
		paths->antid = ant;
		ant += paths->wait;
		paths = paths->next;
	}
}

void			solve(t_map *map)
{
	int			i;
	t_path		*best_path;
	t_path		*node;

	i = 0;
	while (i++ < map->antcount)
	{
		best_path = map->paths;
		node = best_path->next;
		while (node)
		{
			if (node->len + node->wait < best_path->len + best_path->wait)
				best_path = node;
			node = node->next;
		}
		best_path->wait++;
	}
	attribute(map->paths);
}
