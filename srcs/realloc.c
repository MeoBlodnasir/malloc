/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:54:30 by aduban            #+#    #+#             */
/*   Updated: 2016/12/01 17:52:09 by aduban           ###   ########.fr       */
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

	ft_printf("realloc\n");
	if (ptr && !check_free2(ptr))
		return (NULL);
	ret = malloc(size);
	if (ret == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		area = ret - sizeof(t_area);
		ft_memcpy(ret, ptr, area->size);
		free(ptr);
	}
	return (ret);
}
