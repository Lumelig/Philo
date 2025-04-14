/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:21:58 by jpflegha          #+#    #+#             */
/*   Updated: 2025/04/14 20:00:26 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_and_exit(const char *error)
{
    printf(RED"%s\n"RST, error);
    exit(EXIT_FAILURE);
}