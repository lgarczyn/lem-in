/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 15:01:21 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/12 15:01:24 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

float	ft_dist(t_p a, t_p b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (sqrtf(a.x * a.x + a.y * a.y));
}
