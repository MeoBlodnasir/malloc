/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:54:42 by aduban            #+#    #+#             */
/*   Updated: 2016/12/05 12:39:02 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	ft_printf("malloc\n");
	void	*block;
	void	*area;
	int		type;

	if (size < SMALL)
	{
		ft_printf("small malloc\n");
		type = SMALL;
		if (size < TINY)
			type = TINY;
		block = get_correct_block(type);
		ft_printf("got correct block\n");
		if (block == NULL)
		{
			ft_printf("block is nill\n");
			return (NULL);
		}
		area = get_correct_area(size, block, type);
		ft_printf("got correct area\n");
		if (area == NULL)
		{
			printf("Area is nil\n");
			return (NULL);
		}
		printf("returning from malloc\n");
		return (area + sizeof(t_area));
	}
	else
	{
		ft_printf("large malloc\n");
		return (handle_large(size));
	}
	return (NULL);
}
