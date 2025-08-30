/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/30 22:59:53 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main (void)
{
	t_ray		r;
	t_tuple		target;
	t_sphere	s;
	float		*xs;

	printf("r = ray(origin, direction)\n");
	r = ray(point(1, 2, 3), vector(4, 5, 6));
	printf("r.origin: %f, %f, %f, %f\n", r.origin.x, r.origin.y, r.origin.z, r.origin.w);
	printf("r.direction: %f, %f, %f, %f\n", r.direction.x, r.direction.y, r.direction.z, r.direction.w);
	printf("\n");

	//

	printf("r = ray(point(2, 3, 4), vector(1, 0, 0))\n");
	r = ray(point(2, 3, 4), vector(1, 0, 0));
	target = position(r, 0);
	printf("position (r, 0): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	target = position(r, 1);
	printf("position (r, 1): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	target = position(r, -1);
	printf("position (r, -1): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	target = position(r, 2.5);
	printf("position (r, 2.5): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	printf("\n");
	
	//
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 0, -5), v(0, 0, 1))\n");
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0]);
		printf("intersect 1: %f\n", xs[1]);
		free(xs);
	}
	else
		printf("no intersect\n");
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 1, -5), v(0, 0, 1))\n");
	r = ray(point(0, 1, -5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0]);
		printf("intersect 1: %f\n", xs[1]);
		free(xs);
	}
	else
		printf("no intersect\n");
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 2, -5), v(0, 0, 1))\n");
	r = ray(point(0, 2, -5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0]);
		printf("intersect 1: %f\n", xs[1]);
		free(xs);
	}
	else
		printf("no intersect\n");
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 0, 0), v(0, 0, 1))\n");
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0]);
		printf("intersect 1: %f\n", xs[1]);
		free(xs);
	}
	else
		printf("no intersect\n");
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 0, 5), v(0, 0, 1))\n");
	r = ray(point(0, 0, 5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0]);
		printf("intersect 1: %f\n", xs[1]);
		free(xs);
	}
	else
		printf("no intersect\n");
	printf("\n");
	return (0);
}
