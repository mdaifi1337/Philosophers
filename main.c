/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 09:49:34 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/21 13:00:44 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	read_args(t_data *data, int argc, char *argv[])
{
	int	error;

	error = 0;
	data->nbr_of_philos = ft_atoi(argv[1], &error);
	data->time_to_die = ft_atoi(argv[2], &error);
	data->time_to_eat = ft_atoi(argv[3], &error);
	data->time_to_sleep = ft_atoi(argv[4], &error);
	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5], &error);
	return (error == 0);
}

t_data	*init(int argc, char *argv[])
{
	int		i;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data || !read_args(data, argc, argv))
		return (free_error(data));
	data->philos = (t_philos *)malloc(sizeof(t_philos) * data->nbr_of_philos);
	if (!data->philos)
		return (free_error(data));
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_init(&data->philos[i].fork, NULL);
		pthread_mutex_init(&data->philos[i].this_lock, NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->can_eat_lock, NULL);
	data->can_eat = data->nbr_of_philos - 1;
	return (data);
}

void	*run_simulation(void *arg)
{
	int		id;
	t_data	*data;

	id = ((t_param *)arg)->id;
	data = ((t_param *)arg)->data;
	while (1)
	{
		ft_think(data, id);
		ft_eat(data, id);
		ft_sleep(data, id);
	}
	free(arg);
	return (NULL);
}

int	philos(t_data *data)
{
	useconds_t	start;
	t_param		*param;
	int			i;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		return (0);
	i = -1;
	start = get_time();
	while (++i < data->nbr_of_philos)
	{
		param[i].id = i;
		param[i].data = data;
		data->philos[i].last_meal = start;
		pthread_create(&data->philos[i].this_id, NULL,
			run_simulation, (void *)&param[i]);
	}
	return (1);
}

int	running(t_data *data)
{
	int	i;
	int	are_full;

	are_full = 0;
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].this_lock);
		if (get_time() - data->philos[i].last_meal >= data->time_to_die)
		{
			print_msg(data, i, DIED);
			printf("current time : %u | last meal : %u\n", get_time(), data->philos[i].last_meal);
			pthread_mutex_unlock(&data->philos[i].this_lock);
			return (0);
		}
		if (data->max_meals != -1
			&& data->philos[i].meal_count >= data->max_meals)
			are_full++;
		pthread_mutex_unlock(&data->philos[i].this_lock);
	}
	are_full = (are_full == data->nbr_of_philos);
	return (are_full == 0);
}

int	main(int argc, char *argv[])
{
	t_data 	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments !\n");
		exit(1);
	}
	data = init(argc, argv);
	if (!data)
		exit(1);
	if (philos(data))
		while (!dead(data))
			;
	destroy_everything(data);
	return (0);
}