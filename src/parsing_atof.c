/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:08 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 19:14:14 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	calculate_integral(const char *str, float *integral, int *i);
static int	calculate_decimal(const char *str, float *decimal, int *i);
static int	determine_sign(const char *str, int *sign, int *i);

// rt_atoff(): string-to-float function specific to miniRT
// Returns -1 if non-numeric chars / format error encountered
// Allows one leading "+" or "-"
// Returns 0 on success

int	rt_atof(const char	*str, float *f)
{
	int		i;
	int		sign;
	float	integral;
	float	decimal;

	integral = 0;
	decimal = 0;
	sign = 1;
	i = 0;
	if (determine_sign(str, &sign, &i) != 0)
		return (-1);
	if (str[i] != '.')
	{
		if (calculate_integral(str, &integral, &i) != 0)
			return (-1);
	}
	if (str[i] == '.')
	{
		i++;
		if (calculate_decimal(str, &decimal, &i) != 0)
			return (-1);
	}
	*f = sign * (integral + decimal);
	return (0);
}

// calculate_integral(): helper function for rt_atof()
// Calculates value up to possible decimal point & modifies float pointer
// Returns -1 if non-numeric chars / format error encountered

static int	calculate_integral(const char *str, float *integral, int *i)
{
	if (str[*i] == '\0')
		return (-1);
	while (str[*i] && str[*i] != '.')
	{
		if (!(str[*i] >= '0' && str[*i] <= '9'))
			return (-1);
		*integral = (*integral * 10) + str[*i] - '0';
		(*i)++;
	}
	return (0);
}

// calculate_decimal(): helper function for rt_atof()
// Calculates value after decimal point & modifies float pointer
// Returns -1 if non-numeric chars / format error encountered

static int	calculate_decimal(const char *str, float *decimal, int *i)
{
	float	places;
	float	digit;

	places = 0.1;
	if (str[*i] == '\0')
		return (-1);
	while (str[*i])
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

// determine_decimal(): helper function for rt_atof()
// Determines sign of float.
// Returns -1 if non-numeric chars / format error encountered

static int	determine_sign(const char *str, int *sign, int *i)
{
	*sign = 1;
	if (str[0] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	if (str[0] == '+')
		(*i)++;
	if (!((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.'))
		return (-1);
	return (0);
}
