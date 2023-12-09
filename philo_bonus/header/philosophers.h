/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:15:10 by psalame           #+#    #+#             */
/*   Updated: 2023/12/09 15:13:26 by psalame          ###   ########.fr       */
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
# include <stdlib.h>
# include <signal.h>
# define SEMA_FORKS "philo_forks"
# define SEMA_PRINT "philo_print"

typedef enum e_state
{
	thinking,
	eating,
	sleeping
}	t_state;

typedef struct s_philosoph
{
	t_state	state;
	long	state_date;
	long	last_meal_date;
	int		number_meal;
	int		id;
}			t_philosoph;

typedef struct s_simulation_data
{
	int		nb_philosophers;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	int		nb_meal;
}			t_simulation_data;

typedef struct s_children_pids
{
	int	*pids;
	int	current_pid;
	int	checker_pthread
}		t_children_pids;


// utils
// todo ceck if all used
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);
long	get_program_time(void);

// Error managment
void	exit_error(void);

// multi-process managment
int		*init_philosophers(t_simulation_data data);
void	wait_process_finish(void); // todo lock print semaphore is do it



#endif