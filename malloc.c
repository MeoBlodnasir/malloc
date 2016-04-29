#include "malloc.h"


void	fill_area(void *tmp, int block_size, void *map, int type)
{
	int i;
	i = sizeof(t_block);;
	tmp += sizeof(t_block);
	while (i < block_size)
	{
		(*((t_area*)tmp)).free = 0;
		(*((t_area*)tmp)).size = 0;
		(*((t_area*)tmp)).block = map;
		i += type + sizeof(t_area);
		tmp += type + sizeof(t_area);
	}

}

void	*generate_block(int type, void *previous, void *next)
{
	int block_size;
	int i;
	void *map;
	t_block *block;
	void *tmp;

	block_size = sizeof(t_block) + (SIZE * (sizeof(t_area) + type));
	map = mmap(0, block_size ,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map == NULL)
	{
		ft_printf("Error with mmap\n");
		return (NULL);
	}
	block = map;
	block->nb_used = 0;
	block->size = block_size;
	block->type = type;
	block->available = map + sizeof(t_block);
	block->next = next;
	block->previous = previous;
	i = sizeof(t_block);
	tmp = map;
	fill_area(tmp, block_size, map, type);
	return map;
}


static void *tiny;

void	*get_tiny()
{
	return tiny;
}

void	set_tiny(void *ptr)
{
	tiny = ptr;

}
static void *small;
void	*get_small()
{
	return small;
}

void	set_small(void *ptr)
{
	small = ptr;

}


void	*get_correct_block(int type)
{
	t_block	*tmp;

	if (type == TINY && tiny == NULL)
	{
		tiny = generate_block(type, NULL, NULL);
		return tiny;
	}
	else if (type == SMALL && small == NULL)
	{
		small = generate_block(type, NULL, NULL);
		return small;
	}
	tmp = type == TINY ? tiny : small;
	if (tmp->nb_used < SIZE)
	{
		return type == TINY ? tiny : small;
	}
	while (tmp->next != NULL)
	{
		if (tmp->nb_used < SIZE)
		{
			return tmp;
		}
		tmp = tmp->next;

	}
	tmp->next = generate_block(type, tmp, NULL);
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
	while (i < block_size)
	{
		area = tmp;
		if (area->free == 0)
		{
			area->free = 1;
			area->size = size;
			b = area->block;
			b->nb_used += 1;
			return area;
		}
		i += type + sizeof(t_area);
		tmp += type + sizeof(t_area);
	}
	return NULL;

}


void	*generate_large_area(size_t size, void *prev, void *next)
{
	void *map;
	t_area *area;
	map = mmap(0, size + sizeof(t_area) ,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map == NULL)
		return (NULL);
	area = map;
	area->free = 1;
	area->large.previous = prev;
	area->large.next = next;
	area->size = size;
	return map;

}

	static void *large;

void	*get_large()
{
	return large;
}

void	set_large(void	*ptr)
{
	large = ptr;
}

void	*handle_large(size_t size)
{
	void *new;
	t_area *area;

	if (large == NULL)
	{
		large = generate_large_area(size, NULL, NULL);
		if (large == NULL)
			return (NULL);
		set_large(large);
		return (large + sizeof(t_area));
	}

	area = large;
	while (area->large.next != NULL)
	{
		area = area->large.next;
	}
	new = generate_large_area(size, area, NULL);
	area->large.next = new;
	return (new + sizeof(t_area));
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
		if (block == NULL)
			return (NULL);
		area = get_correct_area(size, block);
		if (area == NULL)
			return (NULL);
		return (area + sizeof(t_area));
	}
	else
	{
		return handle_large(size);
	}
	return NULL;
}
/*
   int main()
   {
	   char *str;
	   int i = 0;
	   char **tab;
	   tab = (char **)malloc(sizeof(char *) * 150);
	   while (i < 150)
	   {
		   str = (char *)mallok(5);
		   tab[i] = str;
		   i++;
	   }
	   show_alloc_mem();
	   i = 0;
	   while (i < 150)
	   {
		   ft_printf("index = %d\n", i);
		   freek(tab[i]);
			   i++;
		if (i % 10 == 0)
		{

	   show_alloc_mem();
		}
	   }

   }*/
int main(int argc, char **argv)
{
	if (argc == 2)
	{
		size_t	test_array[] = { 6, 20, 42 };
		size_t	test_array_size = sizeof(test_array) / sizeof(test_array[0]);

		size_t	count;
		size_t	i, j;

		count = atoi(argv[1]);

		char	*tmp[count];

		for (i = 0; i < test_array_size; i ++)
		{
			printf("testing %zu malloc() of size %zu\n", count, test_array[i]);

			for (j = 0; j < count; j ++)
			{
				tmp[j] = (char *)mallok(test_array[i]);
				if (!tmp[j])
				{
					count = j - 1;
					break ;
				}
			}

			for (j = 0; j < count; j ++)
			{
				freek(tmp[j]);
				ft_printf("index : %d\n", j);
			}

			printf("SUCCESS\n");
		}
	}
	else
	{
#define STR						"hello world!"
#define STR_SIZE		 sizeof("hello world!") - 1

		size_t	size_max = 4096;
		printf("Testing realloc() from %zu to %zu\n", STR_SIZE, size_max);

		size_t	size;
		char	*str;

		str = mallok(STR_SIZE + 1);
		if (!str)
		{
			fprintf(stderr, "mallok() failed size %zu\n", size);
			return (1);
		}
		memcpy(str, STR, STR_SIZE);
		str[STR_SIZE] = 0;

		size = STR_SIZE;

		while (size < size_max)
		{
			str = reallok(str, size + STR_SIZE + 1);
			if (!str)
			{
				fprintf(stderr, "mallok() failed size %zu\n", size);
				return (1);
			}
			memcpy(str + size, STR, STR_SIZE);
			size += STR_SIZE;
			str[size] = 0;

			//			fprintf(stderr, "str %p %s\n", (void *)str, str);
	//		ft_printf("size %d, max size %d, STR_SIZE %d\n", size, size_max, STR_SIZE);
		}

			freek(str);

		printf("SUCCESS\n");
	}

	return (0);
}
