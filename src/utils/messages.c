/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:39:36 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/20 14:22:59 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *msg)
{
	if (!alive(philo))
		return ;
	printf("%-5li %3li %s\n", (get_time() - philo->info->start), philo->nr,
		msg);
}

void	print_death(t_philo *philo)
{
	printf("%-5li %3li died\n", (get_time() - philo->info->start), philo->nr);
}

void	not_enough_arguments(void)
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 121);
	exit(255);
}

void	error_exiting(t_philo *table, int error_code)
{
	free_table(table);
	write(2, "Error, exiting...\n", 19);
	exit(error_code);
}
