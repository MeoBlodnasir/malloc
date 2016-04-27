/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:32:06 by aduban            #+#    #+#             */
/*   Updated: 2016/04/27 14:03:24 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


void *n_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst2;
	const char	*src2;
	int			i;

	dst2 = dst;
	src2 = src;
	i = 0;
	while (n)
	{
		dst2[i] = src2[i];
		i++;
		n--;
	}
	return (dst);
}

void *reallok(void *ptr, size_t size)
{
	void *ret;
	ret = mallok(size);
	if (ret == NULL)
	{
		ft_printf("ret is dead baby\n");
	}
	if ((*((t_infos*)(ret - sizeof(t_infos)))).size < TINY)
	{	
		ret = n_memcpy(ret, ptr, 5);

	}
	else if ((*((t_infos*)(ret - sizeof(t_infos)))).size < SMALL)
	{	
		ret = n_memcpy(ret, ptr, SMALL);
	}
	else
	{
		ret = n_memcpy(ret, ptr, (*((t_infos*)(ret - sizeof(t_infos)))).size);
	}
	freek(ptr);
	return ret;
}

