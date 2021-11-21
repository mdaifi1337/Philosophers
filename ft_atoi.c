/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:37:30 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/21 11:35:44 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int	ft_atoi(const char *str, int *error)
{
	unsigned int	res;

	res = 0;
	if (*str == '-' || *str <= '0' || *str >= '9')
	{
		(*error)++;
		return ((unsigned int)0);
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0') % 10;
		str++;
	}
	return (res);
}
