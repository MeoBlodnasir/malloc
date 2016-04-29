/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:54:30 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 16:32:35 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*reallok(void *ptr, size_t size)
{
	void	*ret;
	t_area	*area;

	ret = malloc(size);
	area = ret - sizeof(t_area);
	ft_memcpy(ret, ptr, area->size);
	free(ptr);
	return (ret);
}
