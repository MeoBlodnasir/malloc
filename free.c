#include "malloc.h"

void	free_block(t_block *block)
{
	t_block *prev;
	t_block *next;
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
	}
	if (next != NULL)
		next->previous = prev;
	int ret;
	ret = munmap(block, block->size); 
	if (ret != 0)
	{
		perror("");
		ft_printf("munmap error\n");
	}
}

void	freek(void *ptr)
{
	t_area *area;
	t_block *block;
	area = ptr - sizeof(t_area);
	if (area->size < SMALL)
	{
		area->free = 0;
		area->size = 0;
		block = area->block;
		block->nb_used -= 1;
		if (block->nb_used <= 0)
			free_block(block);
		return ;
	}
	t_area *prev;
	t_area *next;
	prev = area->large.previous;
	next = area->large.next;
	if (prev != NULL)
		prev->large.next = next;
	else
	{
		if (next != NULL)
		{
			set_large(next);
		}
	}
	if (next != NULL)
		next->large.previous = prev;
	int ret;
	ret = munmap(ptr - sizeof(t_area), area->size + sizeof(t_area));
	if (ret != 0)
	{
		ft_printf("munmap failed\n");
	}
	return ;
}
