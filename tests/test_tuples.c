/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:10:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/24 21:04:05 by mmillhof         ###   ########.fr       */
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
	print_tuple("a", a);
	printf("\n");
	print_tuple("b", b);
	printf("\n\n");

	a = point(4.3, -4.2, 3.1);
	b = point(4.3, -4.19999, 3.10001);
	c = point(4.3, -4.1, 3.2);
	
	printf("is equal?\n");
	print_tuple("a", a);
	printf("\n");
	print_tuple("b", b);
	printf("\n");
	print_tuple("c", c);
	printf("\n");

	printf("a == b: %i\n", tisequal(a, b));
	printf("a == c: %i\n\n", tisequal(b, c));

	a = point(3, -2, 5);
	b = vector(-2, 3, 1);

	printf("add tuples\n");
	print_tuple("a", a);
	printf("\n");
	print_tuple("b", b);
	printf("\n");
	print_tuple("(a + b)", tadd(a, b));
	printf("\n\n");

	a = point(3, 2, 1);
	b = point(5, 6, 7);

	printf("subtract tuples\n");
	print_tuple("a", a);
	printf("\n");
	print_tuple("b", b);
	printf("\n");
	print_tuple("(a - b)", tsub(a, b));
	printf("\n\n");

	printf("negate tuples\n");
	print_tuple("(negative c)", tneg(c));
	printf("\n\n");

	printf("multiply tuples\n");
	print_tuple("(b * 3.5)", tmult(b, 3.5));
	printf("\n\n");

	printf("divide tuples\n");
	print_tuple("(b / 2)", tdiv(b, 2));
	printf("\n\n");

	printf("magnitude c: %f\n\n", tmag(c));

	print_tuple("(normalized c)", tdiv(c, tmag(c)));
}

static void	print_tuple(char *str, t_tuple a)
{
	printf("%s.x = %f\n", str, a.x);
	printf("%s.y = %f\n", str, a.y);
	printf("%s.z = %f\n", str, a.z);
	printf("%s.w = %f\n", str, a.w);
	if (a.w == 0)
		printf("is a vector\n");
	if (a.w == 1)
		printf("is a point\n");
}
