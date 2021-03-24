/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:57:18 by mroux             #+#    #+#             */
/*   Updated: 2021/03/24 21:16:37 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		log_lunch(t_philo *philo)
{
	gettimeofday(&philo->last_lunch,  NULL);
}

void		take_forks(t_philo *philo, t_global *gl, int fork)
{
	pthread_mutex_lock(philo->forks[fork]);
	pthread_mutex_lock(&gl->mutex_print);
	printf("%lu: %d has taken a fork.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	pthread_mutex_unlock(&gl->mutex_print);
}

void		release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}

void		eat(t_philo *philo, t_global *gl)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	// printf("%d: last lunch: %lu\n", p_args->philo_number, timeval_to_ms(&now) - timeval_to_ms(&p_args->last_lunch));
	pthread_mutex_lock(&gl->mutex_print);
	printf("%lu: %d is eating.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	pthread_mutex_unlock(&gl->mutex_print);
	log_lunch(philo);
	ft_usleep(gl->time_to_eat * 1000);
	philo->meals++;
	release_forks(philo);
}

void		do_sleep(t_philo *philo, t_global *gl)
{
	pthread_mutex_lock(&gl->mutex_print);
	printf("%lu: %d is sleeping.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	pthread_mutex_unlock(&gl->mutex_print);
	ft_usleep(gl->time_to_sleep * 1000);
	// printf("%lu: %d is waking up.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
}

void		think(t_philo *philo, t_global *gl)
{
	pthread_mutex_lock(&gl->mutex_print);
	printf("%lu: %d is thinking.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	pthread_mutex_unlock(&gl->mutex_print);
}
