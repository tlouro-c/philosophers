/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:52:21 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/20 01:33:03 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *s)
{
	long	n;
	int		i;
	int		negative;

	if (s == NULL)
		return (0);
	n = 0;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	negative = s[i] == '-';
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
		n = n * 10 + (s[i++] - '0');
	if (negative)
		return (n * -1);
	return (n);
}

void	*ft_calloc(int quantity, int size)
{
	void	*p;

	p = malloc(quantity * size);
	if (!p)
		return (NULL);
	memset(p, 0, size * quantity);
	return (p);
}

long	get_time(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	free_table(t_philo *table)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = table -> next;
	pthread_mutex_destroy(tmp->info->status_mutex);
	while (tmp != table)
	{
		next = tmp->next;
		pthread_mutex_destroy(tmp->right_fork);
		free(tmp->right_fork);
		free(tmp);
		tmp = next;
	}
	pthread_mutex_destroy(table->right_fork);
	free(table->right_fork);
	free(table);
}

int	alive(t_philo *philo)
{
	pthread_mutex_lock(philo->info->status_mutex);
	if (philo->info->death)
	{
		pthread_mutex_unlock(philo->info->status_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->info->status_mutex);
	return (1);
}
