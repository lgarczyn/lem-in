/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 19:21:24 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/13 19:21:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				parse_comment(t_type *type, char *str)
{
	if (ft_strcmp(str, "##start") == 0)
		*type |= t_start;
	else if (ft_strcmp(str, "##end") == 0)
		*type |= t_end;
}

int					get_id(t_map *map, char *name, t_bool create)
{
	t_room			*room;

	room = map->rooms;
	while (room)
	{
		if (ft_strcmp(room->name, name) == 0)
			if (create)
				return (-1);
			else
				return (room->id);
		else
			room = room->next;
	}
	if (create)
		return (map->roomcount);
	else
		return (-1);
}

void				parse_room(t_map *map, t_type *type, char *str)
{
	t_room			*room;
	char			**split;

	split = ft_strsplit(str, ' ');
	room = ft_secalloc(sizeof(t_room));
	room->name = split[0];
	room->pos.x = xatoi(split[1]);
	room->pos.y = xatoi(split[2]);
	free(split[1]);
	free(split[2]);
	free(split);
	room->type = *type;
	*type = t_none;
	room->id = get_id(map, room->name, true);
	if (room->id == -1)
		ERROR();
	room->next = map->rooms;
	map->rooms = room;
	map->roomcount++;
}

void				parse_link(t_map *map, char *str)
{
	t_link			*link;
	char			**split;

	link = ft_secalloc(sizeof(t_link));
	split = ft_strsplit(str, '-');
	link->a = get_id(map, split[0], false);
	link->b = get_id(map, split[1], false);
	free(split[0]);
	free(split[1]);
	free(split);
	if (link->a == -1 || link->b == -1)
		ERROR();
	link->next = map->links;
	map->links = link;
}

void				parse(t_map *map)
{
	char			*str;
	t_type			type;
	int				test;

	if (ft_readtochar(&str, '\n') <= 0)
		ERROR();
	ft_putendl(str);
	map->antcount = xatoi(str);
	type = t_none;
	while ((test = ft_readtochar(&str, '\n')) > 0)
	{
		if (*str == '#')
			parse_comment(&type, str);
		else if (ft_countchar(str, ' ') == 2)
			parse_room(map, &type, str);
		else if (ft_countchar(str, '-') == 1)
			parse_link(map, str);
		else
			ERROR();
		ft_putendl(str);
		free(str);
	}
}
