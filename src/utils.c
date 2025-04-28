/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:21:58 by jpflegha          #+#    #+#             */
/*   Updated: 2025/04/28 14:58:37 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    my_usleep(long usec, t_table *table)
{
    long    start;
    long    elapsed;
    long    remain;

    start = gettime(MICROSECOND);
    while (gettime(MICROSECOND) - start < usec)
    {
        if (simulation_finish(table))
            break;
        elapsed = gettime(MICROSECOND);
        remain = usec - elapsed;
        if (remain > 1e3)
            usleep(remain / 2);
        else
        {
            while (gettime(MICROSECOND) - start < usec)
                ;
        }
        
        
    }
    
}

long    gettime(t_time_code time_code)
{
    struct timeval tv;
   
    if (gettimeofday(&tv, NULL))
        error_and_exit("Gettimeofday failed");
    if (SECOND == time_code)
        return(tv.tv_sec + (tv.tv_usec / 1000000));
    else if (MILLISECOND == time_code)
        return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    else if (MICROSECOND == time_code)
        return((tv.tv_sec * 1000000) + tv.tv_usec);
    else
        error_and_exit("Wrong input to gettime");
    return(0);
}       


void    error_and_exit(const char *error)
{
    printf(RED"%s\n"RST, error);
    exit(EXIT_FAILURE);
}