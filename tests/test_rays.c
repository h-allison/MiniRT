/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/31 18:38:44 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main (void)
{
	t_tuple			target;
	t_ray			r;
	t_sphere		s;
	t_intersection	i;
	t_intersection	*xs;

	printf("r = ray(origin, direction)\n");
	r = ray(point(1, 2, 3), vector(4, 5, 6));
	printf("r.origin: %f, %f, %f, %f\n", r.origin.x, r.origin.y, r.origin.z, r.origin.w);
	printf("r.direction: %f, %f, %f, %f\n", r.direction.x, r.direction.y, r.direction.z, r.direction.w);
	printf("\n");

	//

	printf("r = ray(pGoint(2, 3, 4), vector(1, 0, 0))\n");
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
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
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
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
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
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
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
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
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
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
		free(xs);
	}
	else
		printf("no intersect\n");
	printf("\n");

	printf("i = intersection(type, object, t)\n");
	i.t = 3.5;
//	i.type = OBJ_SPHERE;
	s = sphere(point(1, 4, 3), 1, color(0, 0, 0));
	i.object = &s;

//	if (i.type == OBJ_SPHERE)
//		s = *(t_sphere *)i.object;
	printf("i.t: %f\n", i.t);
	printf("i.object: %f, %f\n", s.origin.x, s.origin.y);
	printf("\n");

	t_intersection *inter;

	printf("hit: sphere(0, 0, 0), i1(1, s), i2(2, s)\n");
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersections(intersection(1, &s), intersection(2, &s));
	inter = hit(xs);
	if (!inter)
		printf("i: nothing\n");
	else
		printf("i: %f\n", inter->t);
	free(xs);
	free(inter);
	printf("\n");
	
	printf("hit: sphere(0, 0, 0), i1(-1, s), i2(1, s)\n");
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersections(intersection(-1, &s), intersection(1, &s));
	inter = hit(xs);
	if (!inter)
		printf("i: nothing\n");
	else
		printf("i: %f\n", inter->t);
	free(xs);
	free(inter);
	printf("\n");
	
	printf("hit: sphere(0, 0, 0), i1(-2, s), i2(-1, s)\n");
	s = sphere(point(0, 0, 0), 1, color(0, 0, 0));
	xs = intersections(intersection(-2, &s), intersection(-1, &s));
	inter = hit(xs);
	if (!inter)
		printf("i: nothing\n");
	else
		printf("i: %f\n", inter->t);
	free(xs);
	free(inter);
	printf("\n");
	return (0);
}
