#include "malloc.h"

void	*generate_block(int type)
{
	ft_printf("gen block type : %d\n", type);
	int block_size;
	int i;
	void *map;
	t_block *block;
	void *tmp;

	block_size = sizeof(t_block) + (SIZE * (sizeof(t_area) + type));
	ft_printf("block size %d\n", block_size);
	map = mmap(0, block_size ,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map == NULL)
		ft_printf("Error with mmap\n");
	block = map;
	block->nb_used = 0;
	block->type = type;
	block->available = map + sizeof(t_block);
	block->next = NULL;

	i = sizeof(t_block);;
	tmp = map;
	tmp += sizeof(t_block);
	ft_printf("FIRST INCREMENT: %d\n", type + sizeof(t_area));
	while (i < block_size)
	{
		ft_printf("same multiple of area %p\n", tmp);

		(*((t_area*)tmp)).free = 0;
		(*((t_area*)tmp)).size = 0;
		(*((t_area*)tmp)).block = map;
		i += type + sizeof(t_area);
		tmp += type + sizeof(t_area);
	}
		ft_printf("Adress of block avail: %p\n", block->available);
	return map;
}



void	*get_correct_block(int type)
{
	static void *tiny;
	static void *small;
	t_block	*tmp;

	if (type == TINY && tiny == NULL)
	{
		tiny = generate_block(type);
		return tiny;
	}
	else if (type == SMALL && small == NULL)
	{
		small = generate_block(type);
		return small;
	}
	tmp = type == TINY ? tiny : small;
	if (tmp->nb_used < SIZE)
	{
		ft_printf("OK\n");
		return type == TINY ? tiny : small;
	}
	while (tmp->next != NULL)
	{
		if (tmp->nb_used <= SIZE)
		{
			return tmp;
		}
		tmp = tmp->next;

	}
	tmp->next = generate_block(TINY);
	return tmp->next;
}

void	*get_correct_area(size_t size, void *block)
{
	int i;
	int block_size;
	int type;
	t_block *b;
	t_area *area;
	void *tmp;
	type = (*((t_block*)block)).type;
	i = sizeof(t_block);
	block += sizeof(t_block);
	tmp = block;
	block_size = sizeof(t_block) + (SIZE * (sizeof(t_area) + type));
	ft_printf("SECOND INCREMENT: %d\n", type + sizeof(t_area));
	while (i < block_size)
	{
		area = tmp;
		ft_printf("trying to find one..\n");
		if (area->free == 0)
		{
			ft_printf("found one !!\n");
			area->free = 1;
			area->size = size;
			b = area->block;
			ft_printf("block adress im after : %p\n", b);
			b->nb_used += 1;
			ft_printf("herer?\n");
			return area;
		}
		i += type + sizeof(t_area);
		tmp += type + sizeof(t_area);
	}
	ft_printf("didnt found one...\n");
	return NULL;

}

void	*mallok(size_t size)
{
	void	*block;
	void	*area;
	int	type;
	if (size < SMALL)
	{
		type = SMALL;
		if (size < TINY)
			type = TINY;
		block = get_correct_block(type);

		area = get_correct_area(size, block);
		return (area + sizeof(t_area));
	}
	return NULL;


}

int main()
{
	char *str;
	char **tab;
	int i = 0;
	while (i < 5)
	{
		ft_printf("beginloop");
		str = (char *)mallok(5);
		str[0] = 'a';
		str[1] = 'a';
		str[2] = 'a';
		str[3] = 'a';
		str[4] = '\0';
		ft_printf("%d\n", i);
		ft_printf("%p\n", str);
		i++;
	}
	return 0;
}
