/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/26 15:27:01 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	fisequal(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}
