/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:52:00 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/18 17:54:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_error(char *msg, int ret)
{
	ft_putstr_fd("ERROR\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return(ret);
}

int		rt_error_e(char *element, char *msg, int ret)
{
	ft_putstr_fd("ERROR\n", 2);
	ft_putstr_fd(element, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return(ret);
}

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
