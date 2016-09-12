/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skiptochar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 17:20:49 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/03 17:20:50 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool			ft_skiptochar(t_byte c)
{
	t_uint		r;

	while ((r = ft_readchar()) != (t_uint)c)
	{
		if (R_END(r))
			return (false);
	}
	return (true);
}
