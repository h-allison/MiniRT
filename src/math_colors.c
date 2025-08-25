/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:47:05 by hallison          #+#    #+#             */
/*   Updated: 2025/08/26 00:16:27 by matthias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Add 2 colors */

t_rgb	cadd(t_rgb c1, t_rgb c2)
{
	t_rgb	sum;

	sum.r = c1.r + c2.r;
	sum.g = c1.g + c2.g;
	sum.b = c1.b + c2.b;
	return (sum);
}

/* Subtract color from color */

t_rgb	csub(t_rgb c1, t_rgb c2)
{
	t_rgb	diff;

	diff.r = c1.r - c2.r;
	diff.g = c1.g - c2.g;
	diff.b = c1.b - c2.b;
	return (diff);
}

/* Multiply color by scalar */

t_rgb	cscale(t_rgb c1, float s)
{
	t_rgb	product;

	product.r = c1.r * s;
	product.g = c1.g * s;
	product.b = c1.b * s;
	return (product);
}

/* Multipy color by color*/
// aka Hadamard product or Schur product
// blends 2 colors together

t_rgb	cmult(t_rgb c1, t_rgb c2)
{
	t_rgb	product;

	product.r = c1.r * c2.r;
	product.g = c1.g * c2.g;
	product.b = c1.b * c2.b;
	return (product);
}

/* Convert t_rgb color to int / hex */

int	color_to_hex(t_rgb color)
{
	int	hex_color;

	hex_color = (int)(color.r * 255);
	hex_color = hex_color << 8;
	hex_color = hex_color + (int)(color.g * 255);
	hex_color = hex_color << 8;
	hex_color = hex_color + (int)(color.b * 255);
	hex_color = hex_color << 8;
	hex_color = hex_color + 0xFF;
	return (hex_color);
}
