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
# define _LEMIN_H

# include "libft.h"

#define ERROR()		error()

typedef enum		e_type
{
	t_none = 0,
	t_start = 1,
	t_end = 2,
}					t_type;

typedef enum		e_state
{
	s_clean = 0,
	s_explored = 1,
	s_burned = 2,
}					t_state;

typedef enum		e_error
{
	e_success = 0,
	e_logic = 1,
	e_parsing = 2,
	e_allocation = 3,
}					t_error;

typedef struct		s_name
{
	char			*name;
	struct s_name	*next;
}					t_name;

typedef struct		s_link
{
	int				a;
	int				b;
	struct s_link	*next;
}					t_link;

typedef struct		s_exploration
{
	t_state			state;
	int				len;
	int				id;
	float			dist;
}					t_exploration;

typedef struct		s_room
{
	int				id;
	t_p				pos;
	char			*name;
	t_type			type;
	t_state			state;
	t_exploration	explo;
	int				linkcount;
	int				*links;
	struct s_room	*next;
}					t_room;

typedef struct		s_path
{
	int				antid;
	int				wait;
	int				len;
	int				*steps;
	float			dist;
	struct s_path	*next;
}					t_path;

typedef struct		s_map
{
	int				antcount;
	int				roomcount;
	t_room			*rooms;
	t_link			*links;
	int				start;
	int				end;
	t_path			*paths;
}					t_map;

void				error(void);
int					xatoi(char *str);

t_map				get_map();
void				parse(t_map *map);
t_bool				check(t_map *map);
void				apply_links(t_map *map);
void				find_paths(t_map *map);
void				solve(t_map *map);
void				display_instant(t_map *map);
void				display(t_map *map);

#endif
