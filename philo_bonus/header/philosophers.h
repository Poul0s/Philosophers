/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:15:10 by psalame           #+#    #+#             */
/*   Updated: 2023/12/11 13:50:46 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# define SEMA_FORKS "philo_forks"
# define SEMA_PRINT "philo_print"
# define SEMA_DIED "philo_died"
# define SEMA_EATEN "philo_eaten"

typedef struct s_simulation_data
{
	int		nb_philosophers;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	int		nb_meal;
}			t_simulation_data;

typedef enum e_state
{
	thinking,
	eating,
	sleeping
}	t_state;

typedef struct s_philosoph
{
	t_state				state;
	long				state_date;
	long				last_meal_date;
	int					number_meal;
	short				number_forks;
	int					id;
	t_simulation_data	simulation_data;
}						t_philosoph;

typedef struct s_sema_watcher
{
	int			*pids;
	sem_t		*sem;
	pthread_t	thread;
}			t_sema_watcher;

// utils
int		ft_atoi(const char *nptr);
long	get_program_time(void);

// Error managment
void	exit_error(void);

// philosophers life
char	check_dead(t_philosoph *philosoph);
void	check_end(t_philosoph *philosoph);
void	check_eat(t_philosoph *philosoph);
void	check_sleep(t_philosoph *philosoph);
void	check_think(t_philosoph *philosoph);
void	print_state(t_philosoph *philosoph, long time);
void	print_fork_taken(t_philosoph *philosoph, long time);
void	start_philosopher_process(t_philosoph philosoph);

// multi-process managment
int		*init_philosophers(t_simulation_data data);
void	wait_process_finish(void);
void	wait_available_forks(t_philosoph *philosoph);
void	put_forks_back(t_philosoph *philosoph);
void	start_simulation(t_simulation_data data);
void	kill_philosophers(int *pids);

#endif