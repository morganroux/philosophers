/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:06:23 by mroux             #+#    #+#             */
/*   Updated: 2021/04/15 16:04:06 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo			*init_philos(t_global *gl)
{
	int				i;
	t_philo			*philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * gl->number_of_philos);
	while (i < gl->number_of_philos)
	{
		philos[i].philo_number = i + 1;
		philos[i].meals = 0;
		philos[i].eating = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i].eating, NULL);
		philos[i].forks[0] = &gl->forks[i % gl->number_of_philos];
		philos[i].forks[1] = &gl->forks[(i + 1) % gl->number_of_philos];
		philos[i].status = 1;
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(int argc, char *argv[])
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
		extract_number_of_philosophers(argc, argv));
	while (i < extract_number_of_philosophers(argc, argv))
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

int				init_gl(t_global *gl, int argc, char *argv[])
{
	pthread_mutex_init(&gl->mutex_print, NULL);
	gl->number_of_philos = extract_number_of_philosophers(argc, argv);
	gl->time_to_sleep = extract_time_to_sleep(argc, argv);
	gl->time_to_eat = extract_time_to_eat(argc, argv);
	gl->time_to_die = extract_time_to_die(argc, argv);
	gl->number_of_meals = extract_number_of_meals(argc, argv);
	return (0);
}

int				init(t_global *gl, int argc, char *argv[])
{
	if (init_gl(gl, argc, argv) == -1)
		return (-1);
	if ((gl->forks = init_forks(argc, argv)) == NULL)
		return (-1);
	if ((gl->philos = init_philos(gl)) == NULL)
		return (-1);
	return (0);
}
