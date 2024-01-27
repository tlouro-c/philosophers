/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:37:24 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/27 10:25:01 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_garcon	*garcon;
	t_info		*info;
	t_mutex		status_mutex;

	if (argc < 5)
		return (not_enough_arguments(), 1);
	info = ft_calloc(1, sizeof(t_info));
	info->nr_philo = ft_atol(argv[1]);
	info->life_time = ft_atol(argv[2]);
	info->eat_time = ft_atol(argv[3]);
	info->sleep_time = ft_atol(argv[4]);
	info->status_mutex = &status_mutex;
	if (argv[5])
		info->nr_meals = ft_atol(argv[5]);
	else
		info->nr_meals = LONG_MAX;
	garcon = generate_garcon(info);
	launch_threads(garcon);
	free_table(garcon->table);
	free(garcon);
	free(info);
	return (0);
}
