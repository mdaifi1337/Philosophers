/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:19:05 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/21 12:47:44 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think(t_data *data, int id)
{
	int	can_eat;

	can_eat = 0;
	print_msg(data, id, THINKING);
	while (!can_eat)
	{
		pthread_mutex_lock(&data->can_eat_lock);
		if (data->can_eat > 0)
		{
			can_eat = 1;
			data->can_eat--;
		}
		pthread_mutex_unlock(&data->can_eat_lock);
	}
}

void	ft_sleep(t_data *data, int id)
{
	int			i;

	print_msg(data, id, SLEEPING);
	usleep(data->time_to_sleep * 1000);
}

void	ft_eat(t_data *data, int id)
{
	pthread_mutex_lock(&data->philos[id % data->nbr_of_philos].fork);
	print_msg(data, id, TAKEN_A_FORK);
	pthread_mutex_lock(&data->philos[(id + 1) % data->nbr_of_philos].fork);
	print_msg(data, id, TAKEN_A_FORK);
	pthread_mutex_lock(&data->philos[id].this_lock);
	data->philos[id].meal_count++;
	pthread_mutex_unlock(&data->philos[id].this_lock);
	print_msg(data, id, EATING);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->philos[id].this_lock);
	data->philos[id].last_meal = get_time();
	pthread_mutex_unlock(&data->philos[id].this_lock);
	pthread_mutex_lock(&data->can_eat_lock);
	data->can_eat++;
	pthread_mutex_unlock(&data->can_eat_lock);
	pthread_mutex_unlock(&data->philos[(id + 1) % data->nbr_of_philos].fork);
	pthread_mutex_unlock(&data->philos[id % data->nbr_of_philos].fork);
}
