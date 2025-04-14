#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

# define RST "\033[0m"
# define RED "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;


typedef struct s_fork
{
    t_mtx   fork;
    int     fork_id;
}t_fork;


typedef struct s_philo
{
    int         id;
    long        meals;
    bool        full;
    long        last_neal;
    t_fork      left_fork;
    t_fork      right_fork;
    pthread_t   thread_id;
    
}t_philo;

struct s_table
{
    long        philosophers;
    long        time_to_die;
    long        time_to_sleep;
    long        time_to_eat;
    long        meals_limit;
    long        start;
    long        ende;
    bool        ende_program;
    t_fork      *forks;
    t_philo     *philos;
    
};

//utils and errors
void    error_and_exit(const char *error);
void    check_input(t_table *table, char **input);
static const char   *correct_input(const char *str);
static long ft_atol(const char *str);