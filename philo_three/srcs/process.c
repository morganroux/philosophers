/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 22:31:02 by mroux             #+#    #+#             */
/*   Updated: 2021/03/30 23:01:34 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

typedef struct 		s_args_checker
{
	int				*status;
	sem_t			*sem_status;
	long long		time_to_die;
	t_philo			*philo;
}					t_args_checker;

void			*checker(void *arg)
{
	t_thread_args	*p_args;
	struct timeval	now;
	long long		time;
	long long		ttd;

	p_args = (t_thread_args *)arg;
	ttd = p_args->gl->time_to_die;
	gettimeofday(&p_args->philo->last_lunch, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		time = timeval_to_ms(&now) - timeval_to_ms(&p_args->philo->last_lunch);
		if (time >= ttd)
		{
			//printf("==aie %lld - %lld\n", time, ttd);
			//sem_wait(p_args->sem_status);
			p_args->philo->status = -1;
			return NULL;
		}
		ft_usleep(50);
	}
}

void			launch_checker(t_thread_args *p_args, pthread_t *checker_id)
{
	pthread_create(checker_id, NULL, &checker, p_args);
	pthread_detach(*checker_id);
}

void			*philo_thread(void *arg)
{
	t_thread_args	*p_args;
	struct timeval	tp;
	pthread_t		checker_id;

	p_args = (t_thread_args *)arg;
	gettimeofday(&tp, NULL);
	launch_checker(p_args, &checker_id);
	while (p_args->philo->status == 1)
	{
		if (p_args->philo->status == 1)
			take_forks(p_args->philo, p_args->gl, 0);
		if (p_args->philo->status == 1)
			take_forks(p_args->philo, p_args->gl, 1);
		if (p_args->philo->status == 1)
			eat(p_args->philo, p_args->gl);
		if (p_args->philo->status == 1)
			do_sleep(p_args->philo, p_args->gl);
		if (p_args->philo->status == 1)
			think(p_args->philo, p_args->gl);
	}
	printf("==out %d\n", p_args->philo->philo_number);
	sem_close(p_args->philo->forks);
	sem_unlink("philo_forks");
	sem_close(p_args->gl->mutex_print);
	sem_unlink("philo_print");
	return (NULL);
}
