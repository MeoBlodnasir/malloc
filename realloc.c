/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:32:06 by aduban            #+#    #+#             */
/*   Updated: 2016/04/26 20:54:07 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *reallok(void *ptr, size_t size)
{
	void *ret;
	ret = mallok(size);
	ret = ft_memcpy(ret, ptr, (*((t_infos*)(ret - sizeof(t_infos)))).size);
	freek(ptr);
	return ret;
}
