#include "lemin.h"

void			display_ant(int ant, char *name, t_bool *isfirst)
{
	if (*isfirst)
		*isfirst = false;
	else
		ft_putchar(' ');
	ft_putchar_buf('L');
	ft_putnbr_buf(ant);
	ft_putchar_buf('-');
	ft_putstr_buf(name);
}

void			display_path(t_map *map, t_path *path, int time, t_bool *isfirst)
{
	int			i;
	int			s;
	int			ant;
	
	i = time;
	s = MAX(0, i - path->wait);
	ant = path->antid;
	while (i > s)
	{
		if (i < path->len)
			display_ant(ant, map->rooms[path->steps[i]].name, isfirst);
		ant++;
		i--;
	}
}

void			display_instant(t_map *map)
{
	int			i;
	t_bool		isfirst;
	
	i = 1;
	isfirst = true;
	while (i <= map->antcount)
	{
		display_ant(i, map->rooms[map->end].name, &isfirst);
		i++;
	}
	ft_putchar_buf('\n');
}

void			display(t_map *map)
{
	t_path		*paths;
	t_bool		isfirst;
	int			i;
	char		buffer[100000];

	ft_buf(buffer, 100000, 1);
	i = 0;
	while (1)
	{
		paths = map->paths;
		isfirst = true;
		while (paths)
		{
			display_path(map, paths, i, &isfirst);
			paths = paths->next;
		}
		ft_putchar_buf('\n');
		i++;
	}
}