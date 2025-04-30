# include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_FORK == status && !simulation_finish(philo->table))
        printf("%ld "RST" %d has taken The 1° fork"
               "\t\t\tn°"B"[ %d ] \n"RST, elapsed, philo->id,
               philo->first_fork->fork_id);
    else if (TAKE_SECOND_FORK == status && !simulation_finish(philo->table))
        printf("%ld "RST" %d has taken the 2° fork"
               "\t\t\tn° "B"[ %d ] \n"RST, elapsed, philo->id,
               philo->second_fork->fork_id);
    else if (EATING == status && !simulation_finish(philo->table))
        printf("%ld "C" %d is eating "
               "\t\t\t"Y" [ %ld ]\n"RST, elapsed, philo->id, philo->meals);
    else if (SLEEPING == status && !simulation_finish(philo->table))
        printf("%ld "RST" %d is sleeping \n", elapsed, philo->id);
    else if (THINKING == status && !simulation_finish(philo->table))
        printf("%ld "RST" %d is thinking \n", elapsed, philo->id);
    else if (DIED == status)
        printf(RED"\t\t %ld %d died \n"RST, elapsed, philo->id);
}

void    write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long elapsed;

    elapsed = gettime(MILLISECOND) - philo->table->start;
    safe_mtx(&philo->table->write_mtx, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
        && !simulation_finish(philo->table))
            printf(M"%-6ld  "C"Philo %d has taken a fork \n"RST, elapsed, philo->id);
        else if (EATING == status && !simulation_finish(philo->table))
            printf(M"%-6ld  "G"Philo %d is eating\n"RST, elapsed, philo->id);
        else if (SLEEPING == status && !simulation_finish(philo->table))
            printf(M"%-6ld  "B"Philo %d is slleping\n"RST, elapsed, philo->id);
        else if (THINKING == status && !simulation_finish(philo->table))
            printf(M"%-6ld  "Y"Philo %d is thinking\n"RST, elapsed, philo->id);
        else if (DIED == status)
            printf(M"%-6ld  "RED"Philo %d is died...\n"RST, elapsed, philo->id);
    }
    safe_mtx(&philo->table->write_mtx, UNLOCK);

}