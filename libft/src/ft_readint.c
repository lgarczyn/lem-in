/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 17:21:03 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/03 17:21:07 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool			ft_readint(int *target)
{
	t_uint	c;
	int		check;

	c = ft_getchar();
	if (c < '0' || c > '9')
		return (false);
	*target = c - '0';
	ft_readchar();
	while (ft_getchar() >= '0' && ft_getchar() <= '9')
	{
		check = *target * 10;
		if (check / 10 != *target)
		{
			*target = INT_MAX;
			return (true);
		}
		*target = check + ft_getchar() - '0';
		ft_readchar();
	}
	return (true);
}
