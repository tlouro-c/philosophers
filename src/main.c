/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:37:24 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/30 15:50:21 by tlouro-c         ###   ########.fr       */
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
	if ((info->nr_philo > 200 && printf("Error: too many philosophers\n"))
		|| info->life_time > INT_MAX
		|| info->eat_time > INT_MAX || info->sleep_time > INT_MAX)
		return (free(info), 1);
	info->status_mutex = &status_mutex;
	info->nr_meals = LONG_MAX;
	if (argv[5])
		info->nr_meals = ft_atol(argv[5]);
	garcon = generate_garcon(info);
	if (!garcon)
		return (1);
	launch_threads(garcon);
	clean_exit(garcon);
	return (0);
}
