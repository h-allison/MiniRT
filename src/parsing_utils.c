/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:08 by hallison          #+#    #+#             */
/*   Updated: 2025/09/18 17:54:06 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
// Checks that char c is a digit or a '.'
// Used to check [0.0-1.0] type input before converting to float

bool	c_is_positive_float(int c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (true)
	else
		return (false);
}

// Checks that str is of a certain length
// Checks all chars in string according to helper function pointer

bool	str_check(char *str, int max_len, int min_len, bool (*)char_check(c))
{
	int	i;


	if (ft_strlen(str) > (max_len) || ft_strlen(str) < (min_len))
		return (false);
	i = 0;
	while (str[i])
	{
		if (!char_check(str[i]))
			return (false);
		i++;
	}
	return (true);
}
*/


// TODO integrate all whitespaces into tokenization
int	ft_is_whitespace(const char nptr)
{
	if (nptr == ' ' || nptr == '\t' || nptr == '\n'
		|| nptr == '\r' || nptr == '\v' || nptr == '\f')
		return (1);
	else
		return (0);
}

int	calculate_integral(const char *str, float *integral, int *i);
int	calculate_decimal(const char *str, float *decimal, int *i);
int	determine_sign(const char *str, int *sign, int *i);

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

	printf("str = %s\n", str);
	integral = 0;
	decimal = 0;
	i = 0;
	*f = 0;
	if (determine_sign(str, &i, &sign) != 0)
		return(-1);
	if (str[i] != '.')
	{
		if (calculate_integral(str, &integral, &i) != 0)
			return (-1);
	}
	if (str[i] == '.')
	{	
		i++;
		if (calculate_integral(str, &decimal, &i) != 0)
			return (-1);
	}
	*f = sign * (integral + decimal);
	return (0);
}

// calculate_integral(): helper function for rt_atof()
// Calculates value up to possible decimal point & modifies float pointer
// Returns -1 if non-numeric chars / format error encountered

int	calculate_integral(const char *str, float *integral, int *i)
{
	*integral = 0;
	if (str[*i] == '\0')
		return(-1);
	while (str[*i] && str[*i] != '.')
	{
		if (!(str[*i] >= '0' && str[*i] <= '9'))
			return(-1);
		*integral = (*integral * 10) + str[*i] - '0';
		(*i)++;
	}
	printf("integral = %f\n", *integral);
	return (0);
}

// calculate_decimal(): helper function for rt_atof()
// Calculates value after decimal point & modifies float pointer
// Returns -1 if non-numeric chars / format error encountered

int	calculate_decimal(const char *str, float *decimal, int *i)
{
	*decimal = 0;
	if (str[*i] == '\0')
		return(-1);
	while (str[*i])
	{
		if (!(str[*i] >= '0' && str[*i] <= '9'))
			return(-1);
		*decimal = (*decimal * 10) + str[*i] - '0';
		(*i)++;
	}
	*decimal = *decimal * 0.1;
	printf("decimal = %f\n", *decimal);
	return (0);
}

// determine_decimal(): helper function for rt_atof()
// Determines sign of float.
// Returns -1 if non-numeric chars / format error encountered

int	determine_sign(const char *str, int *sign, int *i)
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

