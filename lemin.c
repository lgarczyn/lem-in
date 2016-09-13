/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 16:42:37 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/08 16:42:38 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		setup_map(t_map *map)
{
	ft_bzero(map, sizeof(t_map));
	map->start = -1;
	map->end = -1;
}

int			main(void)
{
	t_map	map;

	setup_map(&map);
	parse(&map);
	apply_links(&map);
	if (check(&map))
		return (0);
	find_paths(&map);
	solve(&map);
	if (map.paths->len <= 1)
		display_instant(&map);
	else
		display(&map);
	return (0);
}
