/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:39:36 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/17 23:13:41 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_taken_fork(int philo_nr, long start_ms)
{
	printf("%-5li %3i has taken a fork\n", (get_time() - start_ms), philo_nr);
}

void	print_is_eating(int philo_nr, long start_ms)
{
	printf("%-5li %3i is eating\n", (get_time() - start_ms), philo_nr);
}

void	print_is_sleeping(int philo_nr, long start_ms)
{
	printf("%-5li %3i is sleeping\n", (get_time() - start_ms), philo_nr);
}

void	print_is_thinking(int philo_nr, long start_ms)
{
	printf("%-5li %3i is thinking\n", (get_time() - start_ms), philo_nr);
}

void	print_died(int philo_nr, long start_ms)
{
	printf("%-5li %3i died\n", (get_time() - start_ms), philo_nr);
}
