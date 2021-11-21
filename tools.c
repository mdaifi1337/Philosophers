/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 09:57:51 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/21 13:00:22 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*free_error(t_data *data)
{
	destroy_everything(data);
	return (NULL);
}

useconds_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_msg(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%u %d %s\n", data->philos[id].last_meal, id + 1, msg);
	pthread_mutex_unlock(&data->print_lock);
}

void	destroy_everything(t_data *data)
{
	int	i;

	if (data)
	{
		pthread_mutex_destroy(&data->can_eat_lock);
		pthread_mutex_destroy(&data->print_lock);
		if (data->philos)
		{
			i = -1;
			while (++i < data->nbr_of_philos)
			{
				pthread_mutex_destroy(&data->philos[i].fork);
				pthread_mutex_destroy(&data->philos[i].this_lock);
			}
			free(data->philos);
		}
		free(data);
	}
}
