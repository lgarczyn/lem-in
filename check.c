/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 19:14:34 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/13 19:14:38 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		error(void)
{
	ft_putstr_fd("ERROR\n", 2);
	exit(1);
}

t_bool			check(t_map *map)
{
	t_room		*room;
	int			i;

	i = 0;
	while (i < map->roomcount)
	{
		room = &(map->rooms[i]);
		if (room->type & t_start && map->start != -1)
			ERROR();
		if (room->type & t_start)
			map->start = i;
		if (room->type & t_end && map->end != -1)
			ERROR();
		if (room->type & t_end)
			map->end = i;
		i++;
	}
	if (map->start == -1 || map->end == -1)
		ERROR();
	if (map->start == map->end)
		return (true);
	return (false);
}

int				xatoi(char *str)
{
	int			i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		ERROR();
	return (ft_atoi(str));
}
