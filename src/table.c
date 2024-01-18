/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:51:47 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/18 11:06:04 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_node(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if (!*philo)
	{
		*philo = new;
		new->next = *philo;
	}
	else
	{
		tmp = *philo;
		while (tmp->next != *philo)
			tmp = tmp->next;
		tmp->next = new;
		tmp->left_fork = new->right_fork;
		new->next = *philo;
		new->left_fork = (*philo)->right_fork;
	}
}

static t_philo	*add_to_table(t_philo **philo, t_info *info, int i)
{
	t_philo	*new;

	new = ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->nr = i + 1;
	new->last_meal_time = info->start_time;
	new->info = info;
	new->right_fork = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(new->right_fork, NULL);
	assign_node(philo, new);
	return (new);
}

void	generate_table(int nr_philo, t_info *info)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		i;

	philo = NULL;
	if (nr_philo == 0)
		exit (0);
	i = 0;
	while (i < nr_philo)
		if (!add_to_table(&philo, info, i++))
			free_table_exit(philo);
	pthread_mutex_init(info->is_dead_mutex, NULL);
	tmp = philo;
	if (pthread_create(&tmp->thread, NULL, (void *)routine, (void *)tmp) != 0)
		free_table_exit(philo);
	tmp = tmp -> next;
	while (tmp != philo)
	{
		if (pthread_create(&tmp->thread, NULL, (void *)routine,
				(void *)tmp) != 0)
			free_table_exit(philo);
		tmp = tmp->next;
	}
	pthread_exit(0);
}
