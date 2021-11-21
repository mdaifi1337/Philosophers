/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shinigami.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 10:43:21 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/21 13:01:25 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*shinigami(void *arg)
{
	int		i;
	int		are_full;
	t_data	*data;

	data = (t_data *)arg;
	are_full = 0;
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].this_lock);
		if (get_time() - data->philos[i].last_meal >= data->time_to_die)
		{
			print_msg(data, i, DIED);
			pthread_mutex_unlock(&data->philos[i].this_lock);
			return ((void *)1);
		}
		if (data->max_meals != -1
			&& data->philos[i].meal_count >= data->max_meals)
				are_full++;
		pthread_mutex_unlock(&data->philos[i].this_lock);
	}
	are_full = (are_full == data->nbr_of_philos);
	return ((void *)(uintptr_t)are_full);
}

int	dead(t_data *data)
{
	pthread_t	death;
	void		*ret;

	pthread_create(&death, NULL, shinigami, (void *)data);
	pthread_join(death, (void *)&ret);
	return ((int)(uintptr_t)ret);
}