#include "malloc.h"


void	show_tiny(void *ptr, char *str)
{
	ft_printf("%s : %p\n",str,  ptr);
	t_block *block;
	t_area *area;
	void *tmp;
	block = ptr;
	int i;
	i = 0;
	tmp = ptr + sizeof(t_block);
	while (1)
	{
		while (i < block->size)
		{
			area = tmp;
			if (area->free == 1)
			{
				ft_printf("%p - %p : %d octets\n", (void *)area + sizeof(t_area),
						(void * )area + sizeof(t_area) + area->size,
						area->size);
			}
			tmp += block->type + sizeof(t_area);
			i += block->type + sizeof(t_area);
		}
		block = block->next;
		if (block == NULL)
			break ;	
		area = (void *)block  + sizeof(t_block);
	}
}

void	show_large(void *ptr)
{
	ft_printf("LARGE : %p\n",  ptr);
	t_area *area;
	area = ptr; 
	while (1)
	{
		if (area->free == 1)
		{
			ft_printf("%p - %p : %d octets\n", (void *)area + sizeof(t_area),
					(void * )area + sizeof(t_area) + area->size,
					area->size);
		}
		area = area->large.next;
		if (area == NULL)
			break ;
	}
}

void	show_alloc_mem()
{

	if (get_tiny() != NULL)
		show_tiny(get_tiny(), "TINY");
	if (get_small() != NULL)
		show_tiny(get_small(), "SMALL");
	if (get_large() != NULL)
		show_large(get_large());
}
