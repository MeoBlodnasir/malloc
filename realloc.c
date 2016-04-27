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
		ft_printf("char copied: %c\n", src2[i]);
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
	ft_printf("before danger, size is %d\n", (*((t_infos*)(ret - sizeof(t_infos)))).size);
	if ((*((t_infos*)(ret - sizeof(t_infos)))).size < TINY)
	{	
		ft_printf("tiny\n");
	ret = n_memcpy(ret, ptr, TINY);

	}
	else if ((*((t_infos*)(ret - sizeof(t_infos)))).size < SMALL)
	{	
		ft_printf("small\n");
	ret = n_memcpy(ret, ptr, SMALL);
	}
	else
	{
		ft_printf("large\n");
	ret = n_memcpy(ret, ptr, (*((t_infos*)(ret - sizeof(t_infos)))).size);
	}

	freek(ptr);
	return ret;
}

