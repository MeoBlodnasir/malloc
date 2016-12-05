/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:54:30 by aduban            #+#    #+#             */
/*   Updated: 2016/12/05 17:31:54 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		check_free2(void *ptr)
{
	t_area *area;

	area = ptr - sizeof(t_area);
	if (area->magic == 0xdeadbeef)
		return (1);
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;
	t_area	*area;
	/*

	   ft_printf("realloc\n");
	   if (ptr == NULL)
	   return malloc(size);
	   if (!check_free2(ptr))
	   return NULL;
	   ret = malloc(size);
	   ft_printf("il est revenu\n");
	   if (ret == NULL)
	   return NULL;
	   ft_printf("before area assign\n");
	   area = ret - sizeof(t_area);
	   ft_printf("before memcpy\n");
	   ft_memcpy(ret, ptr, area->size);
	   ft_printf("before free\n");
	   free(ptr);
	   ft_printf("Salut coco\n");
	   return ret;
	   */
	ft_printf("realloc\n");
	if (ptr && !check_free2(ptr))
		return (NULL);
	ret = malloc(size);
	ft_printf("il est revenu\n");
	if (ret == NULL)
	{
		printf("REALLOC FAILED\n");
		return (NULL);
	}
	if (ptr != NULL)
	{
		ft_printf("before area assign\n");
		area = ret - sizeof(t_area);
		ft_printf("before memcpy\n");
		ft_printf("before size %zd\n", area->size);
		ft_printf("%p, %p, %zd\n", ret, ptr, area->size);
		ft_memcpy(ret, ptr, area->size - sizeof(t_area));
		ft_printf("before free\n");
		free(ptr);
	}
	return (ret);
}
