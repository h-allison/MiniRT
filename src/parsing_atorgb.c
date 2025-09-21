/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atrgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:08 by hallison          #+#    #+#             */
/*   Updated: 2025/09/18 17:54:06 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	calculate_channel(const char *str, float *channel, char c, int *i);

// rt_atorgb(): string to t_rgb function specific to miniRT
// RGB must be in the format [255,255,255]
// Returns -1 if non-numeric chars / format error encountered
// Disallows "-", "+", and "."
// Returns 0 on success
// Caller is responsible for checking that values are <= 255 ! 

int	rt_atorgb(const char *str, t_rgb *rgb)
{
	int		i;

	i = 0;
	if (calculate_channel(str, &rgb->r, 'r', &i) != 0)
			return (-1);
	if (calculate_channel(str, &rgb->g, 'g', &i) != 0)
			return (-1);
	if (calculate_channel(str, &rgb->b, 'b', &i) != 0)
			return (-1);
	return (0);
}

// calculate_channel(): helper function for rt_atof()
// Calculates r, g, or b value & modifies float pointer
// Returns -1 if invald chars encountered
// Returns -1 if missing comma after r, g,
// Returns -1 if b contains extraneous comma

int	calculate_channel(const char *str, float *channel, char c, int *i)
{
	if (str[*i] == '\0')
		return(-1);
	while (str[*i] && str[*i] != ',')
	{
		if (!(str[*i] >= '0' && str[*i] <= '9'))
			return(-1);
		*channel = (*channel * 10) + str[*i] - '0';
		(*i)++;
	}
	if (c == 'r' || c == 'g')
	{
		if (str[*i] != ',')
			return (-1);
		(*i)++;
	}
	if (c == 'b')
	{
		if (str[*i] != '\0')
			return (-1);
	}
	return (0);
}

