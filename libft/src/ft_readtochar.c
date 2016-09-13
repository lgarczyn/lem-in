/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readtochar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 15:17:33 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/09 15:17:35 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static int		get_return(int pos, t_uint cc, char **dst)
{
	if (R_ERROR(cc))
	{
		*dst = NULL;
		return (-1);
	}
	if (R_EOF(cc) && pos == 0)
	{
		*dst = NULL;
		return (-1);
	}
	return (pos);
}

int				ft_readtochar(char **dst, t_byte c)
{
	char		*str;
	t_uint		size;
	t_uint		pos;
	t_uint		cc;

	size = 64;
	str = malloc(size);
	pos = 0;
	while ((cc = ft_readchar()) != (t_uint)c)
	{
		if (R_END(cc))
			break;
		if (pos >= size)
		{
			str = ft_realloc(str, size, size * 2);
			size *= 2;
		}
		str[pos++] = cc;
	}
	*dst = (char*)malloc(pos + 1);
	ft_memmove(*dst, str, pos);
	(*dst)[pos] = '\0';
	free(str);
	return (get_return(pos, cc, dst));
}

