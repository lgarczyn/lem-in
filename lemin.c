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

//REMOVE
#include <stdio.h>

int			error(int pos)
{
	ft_putstr_fd("ERROR\n", 2);
	ft_putnbr_fd(pos, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

t_room		*get_room(t_room *room, int pos)
{
	int		i;

	if (room->next)
	{
		i = 0;
		while (i < pos)
		{
			room = room->next;
			i++;
		}
		return (room);
	}
	else
	{
		return (&(room[pos]));
	}
}

void		display_rooms(t_room *rooms, int roomcount)
{
	int		i;
	int		j;
	t_room	*room;

	i = 0;
	while (i < roomcount)
	{
		room = get_room(rooms, i);
		printf("	room: %s\n", room->name);
		printf("		id: %i\n", room->id);
		printf("		pos: %i %i\n", room->pos.x, room->pos.y);
		printf("		type: %i\n", room->type);
		printf("		state: %i\n", room->explo.state);
		printf("		prev:\n");
		printf("			id: %i\n", room->explo.id);
		printf("			len: %i\n", room->explo.len);
		printf("			dist: %f\n", room->explo.dist);
		printf("		links: %i\n\t\t\t", room->linkcount);
		j = 0;
		while (j < room->linkcount)
		{
			printf(" %i:%s", room->links[j], get_room(rooms, room->links[j])->name);
			j++;
		}
		printf("\n");
		i++;
	}
}

void		display_paths(t_path *paths)
{
	int		i;
	int		j;

	i = 0;
	while (paths)
	{
		printf("	path: %i\n", i);
		printf("		wait: %i\n", paths->wait);;
		printf("		turns: %i\n", paths->len);;
		printf("		length: %f\n", paths->dist);;
		printf("		indices:");
		j = 0;
		while (j < paths->len)
		{
			printf(" %i", paths->steps[j]);
			j++;
		}
		i++;
	}
}

void		display_map(t_map *map, int pos)
{
	t_link	*link;

	printf("---------\n");
	printf("displaying map %i\n", pos);
	printf("	antcount %i\n", map->antcount);
	printf("	roomcount %i\n", map->roomcount);
	printf("	start %i\n", map->start);
	printf("	end %i\n", map->end);
	if (map->links)
	{
		printf("	links:\n\t\t");
		link = map->links;
		while (link)
		{
			printf(" (%i,%i)", link->a, link->b);
			if ((link->a >= 0 && link->a < map->roomcount) && (link->b >= 0 && link->b < map->roomcount))
				printf("{%s,%s}", get_room(map->rooms, link->a)->name, get_room(map->rooms, link->b)->name);
			else
				printf("{ERROR}");
			link = link->next;
		}
		printf("\n");
	}
	display_rooms(map->rooms, map->roomcount);
	display_paths(map->paths);
	printf("---------\n");
}

int			main(void)
{
	t_map	map;
	t_bool	ignore;

	ft_bzero(&map, sizeof(t_map));
	map.start = -1;
	map.end = -1;
	if (parse(&map))
		return (error(1));
	display_map(&map, 1);
	if (apply_links(&map))
		return (error(2));
	display_map(&map, 2);
	ignore = false;
	if (check(&map, &ignore))
		return (error(3));
	display_map(&map, 3);
	if (ignore)
		return (0);
	if (find_paths(&map))
		return (error(4));
	display_map(&map, 4);
	solve(&map);
	display_map(&map, 5);
	if (map.paths->len == 1)
		display_instant(&map);
	else
		display(&map);
	return (0);
}
