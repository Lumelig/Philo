#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

# define RST "\033[0m"
# define RED "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"

#define DEBUG_MODE 0


typedef enum    e_opcode
{
        LOCK,
        UNLOCK,
        INIT,
        DESTROY,
        CREATE,
        JOIN,
        DETACH,
}       t_opcode;

typedef enum    e_time_code
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_time_code;

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIED,
}       t_philo_status;

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
    long        last_meal;
    t_fork      *first_fork;
    t_fork      *second_fork;
    pthread_t   thread_id;
    t_mtx       philo_mtx;
    t_table     *table;
    
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
    bool        thread_ready;
    long        threads_running_nbr;
    pthread_t   monitor;
    t_mtx       table_mtx;
    t_mtx       write_mtx;
    t_fork      *forks;
    t_philo     *philo;
    
};


void    error_and_exit(const char *error);
void    check_input(t_table *table, char **input);
void    *safe_malloc(size_t bytes);
void    safe_mtx(t_mtx  *mutex, t_opcode opcode);
void    safe_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void    my_usleep(long usec, t_table *table);
long    gettime(t_time_code time_code);
void    increase_long(t_mtx *mtx, long *value);


void    data_init(t_table *table);
void thinking(t_philo *philo, bool pre_sim);

bool    simulation_finish(t_table *table);
void    set_long(t_mtx *mtx, long *dest, long value);
long    get_long(t_mtx *mtx, long *value);
bool    get_bool(t_mtx *mtx, bool *value);
void set_bool(t_mtx *mtx, bool *dest, bool value);


void    wait_philo(t_table *table);

void    write_status(t_philo_status status, t_philo *philo, bool debug);
void de_sync_philo(t_philo *philo);
void start_procces(t_table *table);
void   *monitor_dinner(void *daye);
bool    all_threads_running(t_mtx *mtx, long *threads, long philos);
void    clean_all(t_table *tabel);