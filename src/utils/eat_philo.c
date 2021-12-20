#include "philo.h"


int	check_if_everyone_has_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->all_meals_eaten);
	if (philo->root->everyone_has_eaten == 1)
	{
		pthread_mutex_unlock(&philo->root->all_meals_eaten);
		return (1);
	}
	pthread_mutex_unlock(&philo->root->all_meals_eaten);
	return (0);
}

int a_philo_has_eaten_his_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->has_eaten);
	if (philo->root->number_of_times_each_philosopher_must_eat
		&& philo->has_eaten == philo->root->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(&philo->root->has_eaten);
		return (1);
	}
	pthread_mutex_unlock(&philo->root->has_eaten);
	return (0);
}

void	philo_is_eating_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->root->is_eating);
	pthread_mutex_lock(&philo->root->has_eaten);
	philo->is_eating = 1; // mettre un lock 
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->root->has_eaten);
	pthread_mutex_unlock(&philo->root->is_eating);
}

void	print_philo_is_eating(t_philo *philo, int current_time)
{
	pthread_mutex_lock(&philo->root->death);
	if (philo->root->dead_philo == 1)
		pthread_mutex_unlock(&philo->root->death);
	else
	{
		pthread_mutex_unlock(&philo->root->death);
		pthread_mutex_lock(&philo->root->blabla);
		ft_putnbr_fd(current_time, 1);
		ft_putstr_fd(" ms philo ", 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putstr_fd(" has taken a fork ", 1);
		ft_putnbr_fd(philo->fork_right_hand, 1);
		write(1, "\n", 1);
		ft_putnbr_fd(current_time, 1);
		ft_putstr_fd(" ms philo ", 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putstr_fd(" has taken a fork ", 1);
		ft_putnbr_fd(philo->fork_left_hand, 1);
		write(1, "\n", 1);
		ft_putnbr_fd(current_time, 1);
		ft_putstr_fd(" ms philo ", 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putstr_fd(" is eating\n", 1);
		pthread_mutex_unlock(&philo->root->blabla);
	}
}

int	philo_is_eating(t_philo *philo)
{
	
	int current_time;
	pthread_mutex_lock(&philo->root->fork[philo->fork_left_hand]);
	pthread_mutex_lock(&philo->root->fork[philo->fork_right_hand]);
	current_time = get_current_time(philo);
	print_philo_is_eating(philo, current_time);
	philo_is_eating_mutex(philo);
	usleep(philo->root->time_to_eat);
	pthread_mutex_lock(&philo->root->is_eating);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->root->is_eating);
	pthread_mutex_lock(&philo->root->last_meal);
	current_time = get_current_time(philo);
	philo->last_meal = current_time;
	pthread_mutex_unlock(&philo->root->last_meal);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_right_hand]);
	pthread_mutex_unlock(&philo->root->fork[philo->fork_left_hand]);
	return (0);
}