/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:18:06 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/20 01:38:51 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_garcon	*generate_garcon(t_info *info)
{
	t_garcon	*garcon;

	garcon = ft_calloc(1, sizeof(t_garcon));
	if (!garcon)
		exit (254);
	garcon->info = info;
	garcon->table = generate_table(info);
	return (garcon);
}

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
	new->last_meal = info->start;
	new->info = info;
	new->right_fork = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(new->right_fork, NULL);
	assign_node(philo, new);
	return (new);
}

t_philo	*generate_table(t_info *info)
{
	t_philo	*table;
	int		i;

	table = NULL;
	if (info->nr_philo == 0)
		exit (0);
	pthread_mutex_init(info->status_mutex, NULL);
	i = 0;
	while (i < info->nr_philo)
		if (!add_to_table(&table, info, i++))
			error_exiting(table, 254);
	return (table);
}

void	launch_threads(t_garcon *garcon)
{
	t_philo	*tmp;

	if (pthread_create(&garcon->thread, NULL, (void *)garcon_routine,
			(void *)garcon) != 0)
		error_exiting(garcon->table, 254);
	tmp = garcon->table;
	if (pthread_create(&tmp->thread, NULL, (void *)routine, (void *)tmp) != 0)
		error_exiting(garcon->table, 254);
	pthread_detach(tmp->thread);
	tmp = tmp -> next;
	while (tmp != garcon->table)
	{
		if (pthread_create(&tmp->thread, NULL, (void *)routine,
				(void *)tmp) != 0)
			error_exiting(garcon->table, 254);
		pthread_detach(tmp->thread);
		tmp = tmp->next;
	}
}