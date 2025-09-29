/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atof_tuple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:08 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 19:15:34 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	calculate_integral(const char *str, float *integral, int *i);
static int	calculate_decimal(const char *str, float *decimal, int *i);
static int	determine_sign(const char *str, int *sign, int *i);
static int	calculate_coord(const char	*str, float *f, int *i);

// rt_atof_tuple(): string-to-tuple function specific to miniRT
// For use with input formatted "-41.0,50.0,0.0"
// Returns -1 if non-numeric chars / format error encountered
// Allows one leading "+" or "-"

int	rt_atof_tuple(const char *str, t_tuple *t)
{
	int		i;

	i = 0;
	if (calculate_coord(str, &t->x, &i) != 0)
		return (-1);
	if (str[i] != ',')
		return (-1);
	i++;
	if (calculate_coord(str, &t->y, &i) != 0)
		return (-1);
	if (str[i] != ',')
		return (-1);
	i++;
	if (calculate_coord(str, &t->z, &i) != 0)
		return (-1);
	if (str[i] != '\0')
		return (-1);
	return (0);
}

int	calculate_coord(const char	*str, float *f, int *i)
{
	int		sign;
	float	integral;
	float	decimal;

	integral = 0;
	decimal = 0;
	sign = 1;
	if (determine_sign(str, &sign, i) != 0)
		return (-1);
	if (str[*i] != '.')
	{
		if (calculate_integral(str, &integral, i) != 0)
			return (-1);
	}
	if (str[*i] == '.')
	{
		(*i)++;
		if (calculate_decimal(str, &decimal, i) != 0)
			return (-1);
	}
	*f = sign * (integral + decimal);
	return (0);
}

static int	calculate_integral(const char *str, float *integral, int *i)
{
	if (str[*i] == '\0')
		return (-1);
	while (str[*i] && str[*i] != '.' && str[*i] != ',')
	{
		if (!(str[*i] >= '0' && str[*i] <= '9'))
			return (-1);
		*integral = (*integral * 10) + str[*i] - '0';
		(*i)++;
	}
	return (0);
}

static int	calculate_decimal(const char *str, float *decimal, int *i)
{
	float	places;
	float	digit;

	places = 0.1;
	if (str[*i] == '\0')
		return (-1);
	while (str[*i] && str[*i] != ',')
	{
		digit = 0;
		if (!(str[*i] >= '0' && str[*i] <= '9'))
			return (-1);
		digit = str[*i] - '0';
		digit = digit * places;
		places = places / 10;
		*decimal = *decimal + digit;
		(*i)++;
	}
	return (0);
}

static int	determine_sign(const char *str, int *sign, int *i)
{
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	if (str[*i] == '+')
		(*i)++;
	if (!((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.'))
		return (-1);
	return (0);
}
