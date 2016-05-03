/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:13:20 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 16:29:24 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include "libft/libft.h"
# include <sys/mman.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/resource.h>
# define TINY (((getpagesize()*4) - sizeof(t_block)) / SIZE) - sizeof(t_area)
# define SMALL (((getpagesize()*100) - sizeof(t_block)) / SIZE) - sizeof(t_area)
# define SIZE 100
# define TINY_OFFSET (TINY + sizeof(t_area))
# define SMALL_OFFSET (SMALL + sizeof(t_area))

typedef struct	s_large
{
	void		*previous;
	void		*next;
}				t_large;

typedef struct	s_area
{
	int			free;
	size_t		size;
	void		*block;
	t_large		large;
}				t_area;

typedef struct	s_block
{
	int			type;
	int			size;
	int			nb_used;
	void		*available;
	void		*previous;
	void		*next;
}				t_block;

void			free(void *ptr);
void			*get_correct_block(int type);
void			set_tiny(void *ptr);
void			*get_tiny(void);
void			*get_small(void);
void			*get_large(void);
void			set_tiny(void *ptr);
void			set_small(void *ptr);
void			set_large(void *ptr);
void			set_large(void *ptr);
void			*mallok(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem();
void			*handle_large(size_t size);
void			*get_correct_area(size_t size, void *block, int type);
int			add_and_check(unsigned long long l);
#endif
