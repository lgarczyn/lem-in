/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_salloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 14:14:02 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/09/12 14:15:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			*ft_salloc(size_t len)
{
	void		*alloc;

	alloc = malloc(len);
	if (!alloc)
	{
		ft_perror(NULL);
		exit(1);
	}
	return (alloc);
}
