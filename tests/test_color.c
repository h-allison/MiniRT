/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:10:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/25 14:31:35 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"

static void	print_color(char *str, t_rgb c);

int	main(void)
{
	t_rgb	c1;
	t_rgb c2;
	t_rgb c3;

/* Create colors */

	c1 = color(255, 0, 0); // red
	c2 = color(0, 255, 0); // green
	c3 = color(0, 0, 255); // blue

	printf("create colors\n");
	print_color("c1: ", c1);
	print_color("c2: ", c2);
	print_color("c3: ", c3);
	printf("\n");
	printf("\n");

/* Add, subtract, scale, multiply colors */

	c1 = color(230, 171, 191);
	c2 = color(179, 26, 64);
	float s = 2;

	print_color("c1: ", c1);
	print_color("c2: ", c2);
	print_color("added: ", cadd(&c1, &c2));
	print_color("subtracted: ", csub(&c1, &c2));
	print_color("scaled: ", cscale(&c1, s));
	print_color("multiply: ", cmult(&c1, &c2));
	printf("\n");
}

static void	print_color(char *str, t_rgb c)
{
	printf("%s r = %f ", str, c.r);
	printf("g = %f ", c.g);
	printf("b = %f ", c.b);
	printf("\n");
}
