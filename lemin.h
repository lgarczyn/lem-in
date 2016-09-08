/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 16:42:46 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/08 16:42:47 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEMIN_H
# define _LEMIN_H_H

typedef struct		s_p
{
	int				x;
	int				y;
}					t_p;

typedef enum		e_type
{
	room = 0,
	start = 1,
	end = 2,
};

typedef enum		e_error
{
	success = 0,
	parsing = 1,
	allocation = 2,
};

typedef struct		s_room
{
	t_p				pos;
	t_type			type;
	int				count;
	struct s_room	*next;
	char			*name;
}					t_room;

typedef struct		s_path
{
	t_room			*a;
	t_room			*b;
	float			len;
	struct s_path	*next;
}					t_path;

typedef struct		s_map
{
	t_room			*rooms;
	t_path			*paths;	
};

t_room				*find_room(t_room *rooms, char *name);
t_error				parse_map(t_map *map);
#endif
