/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 16:19:51 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/12/17 16:19:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			*ft_realloc(void *ptr, size_t size, size_t newsize)
{
	void		*mem;

	if (!ptr)
		return (ft_memalloc(newsize));
	mem = ft_memalloc(newsize);
	ft_memmove(mem, ptr, size);
	free(ptr);
	return (mem);
}
