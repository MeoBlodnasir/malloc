/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:54:30 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 17:17:11 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*ret;
	t_area	*area;

	ret = malloc(size);
	if (ptr != NULL)
	{
		area = ret - sizeof(t_area);
		ft_memcpy(ret, ptr, area->size);
		free(ptr);
	}
	return (ret);
}
