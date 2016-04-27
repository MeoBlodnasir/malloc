/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:13:20 by aduban            #+#    #+#             */
/*   Updated: 2016/04/26 20:45:11 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include "libft/libft.h"
# include <sys/mman.h>
# include <stdio.h>
//# define TINY (((getpagesize()) / SIZE) - sizeof(t_infos))
# define TINY 100
# define SMALL 1000
//# define SMALL (((getpagesize() * 4 ) / SIZE) - sizeof(t_infos))
# define SIZE 100
# define TINY_OFFSET (TINY + sizeof(t_area))
# define SMALL_OFFSET (SMALL + sizeof(t_area))

typedef struct s_large
{
	void	*previous;
	void	*next;
}		t_large;
typedef struct	s_area
{
	int		free;
	size_t		size;
	void		*block;
	t_large		large;
}		t_area;


typedef struct s_block
{
	int		type;
	int		nb_used;
	void		*available;
	void		*next;
}		t_block;


#endif
