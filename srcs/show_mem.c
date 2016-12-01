/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:55:01 by aduban            #+#    #+#             */
/*   Updated: 2016/12/01 17:29:23 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_infos(t_area *area)
{
	(void)area;
	ft_printf("%p - %p : %d octets\n", (void *)area +
			sizeof(t_area), (void *)area + sizeof(t_area) +
			area->size, (int)area->size);
}

void	show_tiny(void *ptr, char *str)
{
	t_block	*block;
	t_area	*area;
	void	*tmp;
	int		i;

	(void)str;
	ft_printf("%s : %p\n", str, ptr);
	block = ptr;
	i = 0;
	tmp = ptr + sizeof(t_block);
	while (1)
	{
		while (i < block->size)
		{
			area = tmp;
			if (area->free == 1)
				print_infos(area);
			tmp += block->type + sizeof(t_area);
			i += block->type + sizeof(t_area);
		}
		block = block->next;
		if (block == NULL)
			break ;
		area = (void *)block + sizeof(t_block);
	}
}

void	show_large(void *ptr)
{
	t_area *area;

	ft_printf("LARGE : %p\n", ptr);
	area = ptr;
	while (1)
	{
		if (area->free == 1)
		{
			ft_printf("%p - %p : %d octets\n", (void *)area + sizeof(t_area),
					(void *)area + sizeof(t_area) + area->size,
					(int)area->size);
		}
		area = area->large.next;
		if (area == NULL)
			break ;
	}
}

void	show_alloc_mem(void)
{
	if (get_tiny() != NULL)
		show_tiny(get_tiny(), "TINY");
	if (get_small() != NULL)
		show_tiny(get_small(), "SMALL");
	if (get_large() != NULL)
		show_large(get_large());
}
