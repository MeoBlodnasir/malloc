/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_apply_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:41:32 by aduban            #+#    #+#             */
/*   Updated: 2016/12/01 15:41:33 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uint8_t			flag_apply_main(t_buffer *dst, t_flags *flag)
{
	flag_apply_field_precision(dst, flag);
	flag_apply_field_zero(dst, flag);
	if (flag->diez)
		flag_apply_diez(dst, flag->type);
	flag_apply_plus(dst, flag);
	flag_apply_field_space(dst, flag);
	flag_apply_space(dst, flag);
	return (1);
}
