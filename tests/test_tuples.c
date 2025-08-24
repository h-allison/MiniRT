/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:10:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/24 17:05:08 by mmillhof         ###   ########.fr       */
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

	a.x = 0;
	a.y = 0;
	a.z = 1;
	a.w = 0;
	b.x = 1.1;
	b.y = 2.1;
	b.z = 3.1;
	b.w = 0;
	c.x = 1.10001;
	c.y = 2.09999;
	c.z = 3.1;
	c.w = 0;

	print_tuple("a", a);
	printf("\n");
	print_tuple("b", b);
	printf("\n");
	print_tuple("c", c);
	printf("\n");

	printf("a == c: %i\n", tisequal(a, b));
	printf("b == c: %i\n\n", tisequal(b, c));

	print_tuple("(a + b)", tadd(a, b));
	printf("\n");
	print_tuple("(a - b)", tsub(a, b));
	printf("\n");
	print_tuple("(negative c)", tneg(c));
	printf("\n");
	print_tuple("(b * 3.5)", tmult(b, 3.5));
	printf("\n");
	print_tuple("(b / 2)", tdiv(b, 2));
	printf("\n");
	printf("magnitude c: %f\n\n", tmag(c));
	print_tuple("(normalized c)", tdiv(c, tmag(c)));
}

static void	print_tuple(char *str, t_tuple a)
{
	printf("%s.x = %f\n", str, a.x);
	printf("%s.y = %f\n", str, a.y);
	printf("%s.z = %f\n", str, a.z);
	printf("%s.w = %f\n", str, a.w);
}
