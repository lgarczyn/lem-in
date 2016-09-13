/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 19:20:59 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/13 19:21:00 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			display_ant(int ant, char *name, t_bool *isfirst)
{
	if (*isfirst)
		*isfirst = false;
	else
		ft_putchar_buf(' ');
	ft_putchar_buf('L');
	ft_putnbr_buf(ant);
	ft_putchar_buf('-');
	ft_putstr_buf(name);
}

void			display_paths(t_map *map, int time, t_bool *isfirst)
{
	int			i;
	int			s;
	int			ant;
	t_path		*path;

	path = map->paths;
	while (path)
	{
		i = time;
		s = MAX(0, i - path->wait + 1);
		ant = path->antid;
		while (i >= s)
		{
			if (i < path->len)
				display_ant(ant, map->rooms[path->steps[i]].name, isfirst);
			ant++;
			i--;
		}
		path = path->next;
	}
}

void			display_instant(t_map *map)
{
	int			i;
	t_bool		isfirst;
	char		buffer[1000];

	ft_buf(buffer, 1000, 1);
	i = 1;
	isfirst = true;
	while (i <= map->antcount)
	{
		display_ant(i, map->rooms[map->end].name, &isfirst);
		i++;
	}
	ft_putchar_buf('\n');
	ft_flush_buf();
}

void			display(t_map *map)
{
	t_bool		isfirst;
	int			i;
	char		buffer[1000];

	ft_buf(buffer, 1000, 1);
	i = 0;
	while (1)
	{
		isfirst = true;
		display_paths(map, i, &isfirst);
		if (isfirst == false)
			ft_putchar_buf('\n');
		else
			break ;
		i++;
	}
	ft_flush_buf();
}
