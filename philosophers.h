/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:26:40 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/21 13:00:07 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# define THINKING "is thinking"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define DIED "died"
# define TAKEN_A_FORK "has taken a fork"

typedef struct s_philos
{
	unsigned int	meal_count;
	useconds_t		last_meal;
	pthread_t		this_id;
	pthread_mutex_t	fork;
	pthread_mutex_t	this_lock;
}t_philos;

typedef struct s_data
{
	unsigned int	can_eat;
	unsigned int	nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	max_meals;
	t_philos		*philos;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	can_eat_lock;
}t_data;

typedef struct s_param
{
	int		id;
	t_data	*data;
}t_param;

int			dead(t_data *data);
int			ft_atoi(const char *str, int *error);
void		print_msg(t_data *data, int id, char *msg);
void		ft_think(t_data *data, int id);
void		ft_eat(t_data *data, int id);
void		ft_sleep(t_data *data, int id);
void		destroy_everything(t_data *data);
useconds_t	get_time(void);
t_data		*mutex_init_error(t_data *data);
t_data		*free_error(t_data *data);

#endif