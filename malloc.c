/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:54:42 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 17:18:10 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*mallok(size_t size)
{
	void	*block;
	void	*area;
	int		type;

	if (size < SMALL)
	{
		type = SMALL;
		if (size < TINY)
			type = TINY;
		block = get_correct_block(type);
		if (block == NULL)
			return (NULL);
		area = get_correct_area(size, block, type);
		if (area == NULL)
			return (NULL);
		return (area + sizeof(t_area));
	}
	else
	{
		return (handle_large(size));
	}
	return (NULL);
}
