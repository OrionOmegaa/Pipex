/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdescamp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:35:06 by hdescamp          #+#    #+#             */
/*   Updated: 2024/11/19 14:39:11 by hdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_u(unsigned int num, size_t *count)
{
	char	*str;

	str = ft_aux_pf(num, "0123456789");
	ft_printf_s(str, count);
	free(str);
}
