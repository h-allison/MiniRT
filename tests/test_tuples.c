/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:10:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/25 11:36:00 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"

static void	print_tuple(char *str, t_tuple a);

int	main(void)
{
	t_tuple	a;
	t_tuple b;
	t_tuple c;

	a = point(4.3, -4.2, 3.1);
	b = vector(4.3, -4.2, 3.1);

	printf("create tuples\n");
	print_tuple("a: ", a);
	print_tuple("b: ", b);
	printf("\n");

	a = point(4.3, -4.2, 3.1);
	b = point(4.3, -4.19999, 3.10001);
	c = vector(4.3, -4.1, 3.2);
	
	printf("is equal?\n");
	print_tuple("a: ", a);
	print_tuple("b: ", b);
	print_tuple("c: ", c);
	printf("\n");

	printf("a == b: %i\n", tisequal(a, b));
	printf("a == c: %i\n\n", tisequal(b, c));

	a = point(3, -2, 5);
	b = vector(-2, 3, 1);

	printf("add tuples\n");
	print_tuple("a: ", a);
	print_tuple("b: ", b);
	print_tuple("a + b: ", tadd(a, b));
	printf("\n");

	a = point(3, 2, 1);
	b = point(5, 6, 7);

	printf("subtract tuples\n");
	print_tuple("a: ", a);
	print_tuple("b: ", b);
	print_tuple("a - b: ", tsub(a, b));
	printf("\n");

	printf("negate tuples\n");
	print_tuple("negative c: ", tneg(c));
	printf("\n");

	printf("multiply tuples\n");
	print_tuple("b * 3.5: ", tmult(b, 3.5));
	printf("\n");

	printf("divide tuples\n");
	print_tuple("b / 2: ", tdiv(b, 2));
	printf("\n");

	a = vector(0, 1, 0);
	b = vector(-1, -2, -3);
	print_tuple("a: ", a);
	printf("magnitude a: %f\n\n", tmag(a));
	print_tuple("b: ", b);
	printf("magnitude b: %f\n", tmag(b));
	print_tuple("normalized b :", tnorm(b));
	printf("\n");
	
	a = vector(1, 2, 3);
	b = vector(2, 3, 4);
	print_tuple("a: ", a);
	print_tuple("b: ", b);
	printf("dot product a, b: %f\n", dot(a, b));
	print_tuple("cross product a, b: ", cross(a, b));
	print_tuple("cross product b, a: ", cross(b, a));
	printf("\n");
}

static void	print_tuple(char *str, t_tuple a)
{
	printf("%s x = %f ", str, a.x);
	printf("y = %f ", a.y);
	printf("z = %f ", a.z);
	printf("w = %f", a.w);
	if (a.w == 0)
		printf("  > is a vector\n");
	else if (a.w == 1)
		printf("  > is a point\n");
	else
		printf("\n");
}
