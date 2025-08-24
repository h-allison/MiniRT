/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:52:00 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/24 23:37:56 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_early_exit(int error)
{
	if (error == ERROR_WRONG_ARGS)
		ft_putstr_fd("ERROR: Usage: <*.rt>\n", 2);
	else if (error == ERROR_FILENAME)
		ft_putstr_fd("ERROR: Usage: <*.rt>\n", 2);
	else if (error == ERROR_OPEN)
	{
		perror("ERROR");
		exit(errno);
	}
	exit(1);
}
