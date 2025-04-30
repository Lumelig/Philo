/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:17:53 by jpflegha          #+#    #+#             */
/*   Updated: 2025/04/30 13:48:42 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/
int main(int ac, char **argv)
{
    t_table table;
    
    if(5 == ac || 6 == ac)
    {
        check_input(&table, argv);
        data_init(&table);
        start_procces(&table);
        clean_all(&table);
    }
    else
    {
        error_and_exit("parameters are !!!:"G" \n1. number_of_philosophers\n2. time_to_die\n3. time_to_eat\n"
            "4. time_to_sleep\n"B"5. (optional argument)number_of_times_each_philosopher_must_eat");
    }
    return (0);
}