/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 17:19:16 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/03 17:20:29 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#define READ_BUFFER 1024

t_uint				ft_getchar_int(t_bool move)
{
	static t_byte	buffer[READ_BUFFER];
	static int		pos;
	static int		len;
	t_byte			c;

	if (pos >= len)
	{
		pos = 0;
		len = read(0, buffer, READ_BUFFER);
		if (len == 0)
			return (READ_EOF);
		if (len < 0)
			return (READ_ERROR);
	}
	c = buffer[pos];
	if (move)
		pos++;
	return (c);
}
