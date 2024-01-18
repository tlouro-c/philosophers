/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:37:24 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/18 11:05:59 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_mutex_t	is_dead_mutex;
	t_info			*info;

	if (argc < 5)
		not_enough_arguments();
	info = ft_calloc(1, sizeof(t_info));
	info->start_time = get_time();
	info->nr_philo = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	info->is_dead = 0;
	info->is_dead_mutex = &is_dead_mutex;
	if (argv[5])
		info->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = LONG_MAX;
	generate_table(info->nr_philo, info);
}
