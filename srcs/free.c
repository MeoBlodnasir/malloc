/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:03:22 by aduban            #+#    #+#             */
/*   Updated: 2016/12/01 17:52:26 by aduban           ###   ########.fr       */
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
		write(1, "munmap error\n", ft_strlen("munmap error\n"));
	}
}

void	handle_small(t_area *area)
{
	t_block	*block;

	area->free = 0;
	area->size = 0;
	area->magic = 0;
	block = area->block;
	block->nb_used -= 1;
	if (block->nb_used <= 0)
		free_block(block);
}

int		check_free(void *ptr)
{
	t_area *area;

	area = ptr - sizeof(t_area);
	if (area->magic == 0xdeadbeef)
		return (1);
	return (0);
}

void	free(void *ptr)
{
	t_area	*area;
	int		ret;
	t_area	*prev;
	t_area	*next;

	ft_printf("free\n");
	if (ptr == NULL || (ptr && !check_free(ptr)))
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
		write(1, "munmap failed\n", ft_strlen("munmap failed\n"));
	}
	return ;
}
