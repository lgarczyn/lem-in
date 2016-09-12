#include "lemin.h"

t_error				parse_comment(t_type *type, char *str)
{
	if (ft_strcmp(str, "##start") == 0)
		*type |= t_start;
	else if (ft_strcmp(str, "##end") == 0)
		*type |= t_end;
	return (e_success);
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

t_error				parse_room(t_map *map, t_type *type, char *str)
{
	t_room			*room;
	char			**split;

	split = ft_strsplit(str, ' ');
	room = ft_secalloc(sizeof(t_room));
	room->name = split[0];
	room->pos.x = ft_atoi(split[1]);
	room->pos.y = ft_atoi(split[2]);
	free(split[1]);
	free(split[2]);
	free(split);
	room->type = *type;
	*type = t_none;
	room->id = get_id(map, room->name, true);
	if (room->id == -1)
		return (e_parsing);
	room->next = map->rooms;
	map->rooms = room;
	map->roomcount++;
	return (e_success);
}

t_error				parse_link(t_map *map, char *str)
{
	t_link			*link;
	char			**split;
	
	link = ft_secalloc(sizeof(t_link));
	split = ft_strsplit(str, '-');
	link->a = get_id(map, split[0], false);
	link->b = get_id(map, split[1], false);
	printf("got id %i for name %s\n", link->a, split[0]);
	printf("got id %i for name %s\n", link->b, split[1]);
	free(split[0]);
	free(split[1]);
	free(split);
	if (link->a == -1 || link->b == -1)
		return (e_parsing);
	link->next = map->links;
	map->links = link;
	return (e_success);
}

//if (map->paths->len == 0) check
//make sure that rtc null is stored if return = 0
//make sure that rtc returns 1 if just \n
//make sure map is init wit start and end at -1
//make sure that rooms are linked;
//replace char by t_byte ?

t_error				parse(t_map *map)
{
	char			*str;
	t_error			err;
	t_type			type;

	int test;
	
	err = e_success;
	//if (ft_readtochar('\n', &str) > 0)
	//	if ()
	map->antcount = 100;
	type = t_none;
	while ((test = ft_readtochar(&str, '\n')) > 0)
	{
		// ft_putchar('{');
		// ft_putstr(str);
		// ft_putchar('}');
		// ft_putnbr(test);
		// ft_putchar(':');
		if (*str == '#')
			err = parse_comment(&type, str);
		else if (ft_countchar(str, ' ') == 2)
			err = parse_room(map, &type, str);
		else if (ft_countchar(str, '-') == 1)
			err = parse_link(map, str);
		else
			err = e_parsing;
		//ft_putnbr(err);
		//ft_putchar('\n');
		if (err)
			return (err);
		ft_putendl(str);
		free(str);
	}
	return (e_success);
}