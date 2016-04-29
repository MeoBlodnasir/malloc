/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:03:22 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 17:14:34 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free_block(t_block *block)
{
	t_block	*prev;
	t_block	*next;
	int		ret;

	prev = block->previous;
	next = block->next;
	if (prev != NULL)
		prev->next = next;
	else
	{
		if (next != NULL)
		{
			set_tiny(next);
		}
		else
			set_tiny(NULL);
	}
	if (next != NULL)
		next->previous = prev;
	ret = munmap(block, block->size);
	if (ret != 0)
	{
		perror("");
		ft_printf("munmap error\n");
	}
}

void	handle_small(t_area *area)
{
	t_block	*block;

	area->free = 0;
	area->size = 0;
	block = area->block;
	block->nb_used -= 1;
	if (block->nb_used <= 0)
		free_block(block);
}

void	free(void *ptr)
{
	t_area	*area;
	int		ret;
	t_area	*prev;
	t_area	*next;

	if (ptr == NULL)
		return ;
	area = ptr - sizeof(t_area);
	if (area->size < SMALL)
		return (handle_small(area));
	prev = area->large.previous;
	next = area->large.next;
	if (prev != NULL)
		prev->large.next = next;
	else if (next != NULL)
		set_large(next);
	if (next != NULL)
		next->large.previous = prev;
	ret = munmap(ptr - sizeof(t_area), area->size + sizeof(t_area));
	if (ret != 0)
	{
		ft_printf("munmap failed\n");
	}
	return ;
}
