/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:33:24 by mroux             #+#    #+#             */
/*   Updated: 2021/03/18 10:58:17 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct		s_args
{
	int				philo_number;
	struct timeval	last_lunch;
	int				meals;
	unsigned long 	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	started_at;
	sem_t			*forks;
	int				status;
}					t_args;

typedef struct		s_philo
{
	pthread_t		thread_id;
	void			*ret;
	t_args			args;
}					t_philo;

typedef struct		s_checker_args
{
	int				max_meals;
	t_args			*args;
}					t_checker_args;

/*
*	Init
*/

sem_t				*init_forks(int argc, char *argv[]);
t_philo				*init_philos(int argc, char *argv[], sem_t *forks);

/*
*	Actions
*/

int					check_status(t_args *p_args);
void				take_forks(t_args *p_args);
void				eat(t_args *p_args);
void				do_sleep(t_args *p_args);
void				think(t_args *p_args);

/*
*	Utils
*/

void				ft_usleep(unsigned long n);
int					ft_atoul(char const *str);

/*
*	Time
*/

unsigned long		timeval_to_ms(struct timeval *tp);
unsigned long		get_diff_in_ms(struct timeval *tp1, struct timeval *tp2);
unsigned long		get_relative_time_in_ms(unsigned long ref);

/*
*	Parsing
*/

int					check_vars(int argc, char *argv[]);
int					extract_number_of_philosophers(int argc, char *argv[]);
unsigned long		extract_time_to_die(int argc, char *argv[]);
unsigned long		extract_time_to_eat(int argc, char *argv[]);
unsigned long		extract_time_to_sleep(int argc, char *argv[]);
unsigned long		extract_number_of_meals(int argc, char *argv[]);

#endif