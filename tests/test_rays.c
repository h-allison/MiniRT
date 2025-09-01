/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/01 18:13:36 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_matrix(float **m, int size);

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

	printf("r = ray(point(2, 3, 4), vector(1, 2, 0))\n");
	r = ray(point(2, 3, 4), vector(1, 2, 0));
	target = position(r, 0);
	printf("position (r, t = 0): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	target = position(r, 1);
	printf("position (r, t = 1): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	target = position(r, -1);
	printf("position (r, t = -1): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	target = position(r, 2.5);
	printf("position (r, t = 2.5): point(%f, %f, %f, %f)\n", target.x, target.y, target.z, target.w);
	printf("\n");
	
	//
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 0, -5), v(0, 0, 1))\n");
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
	}
	else
		printf("no intersect\n");
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 1, -5), v(0, 0, 1))\n");
	r = ray(point(0, 1, -5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	xs[0].object = NULL;
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
	}
	else
		printf("no intersect\n");
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 2, -5), v(0, 0, 1))\n");
	r = ray(point(0, 2, -5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	xs[0].object = NULL;
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
	}
	else
		printf("no intersect\n");
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 0, 0), v(0, 0, 1))\n");
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	s = sphere(point(0, 0, 0),  color(0, 0, 0));
	xs[0].object = NULL;
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
	}
	else
		printf("no intersect\n");
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("intersect(sphere(0, 0, 0), ray(p(0, 0, 5), v(0, 0, 1))\n");
	r = ray(point(0, 0, 5), vector(0, 0, 1));
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	xs[0].object = NULL;
	xs = intersect(s, r);
	if (xs)
	{
		printf("intersect 0: %f\n", xs[0].t);
		printf("intersect 1: %f\n", xs[1].t);
	}
	else
		printf("no intersect\n");
	free_matrix(s.transform, 4);
	printf("\n");

	printf("i = intersection(type, object, t)\n");
	i.t = 3.5;
//	i.type = OBJ_SPHERE;
	s = sphere(point(1, 4, 3), color(0, 0, 0));
	i.object = &s;
//	if (i.type == OBJ_SPHERE)
//		s = *(t_sphere *)i.object;
	printf("i.t: %f\n", i.t);
	printf("i.object: %f, %f\n", s.origin.x, s.origin.y);
	free_matrix(s.transform, 4);
	printf("\n");

	t_intersection *inter;

	printf("hit: sphere(0, 0, 0), i1(1, s), i2(2, s)\n");
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	xs[0].object = NULL;
	xs = intersections(intersection(1, &s), intersection(2, &s));
	inter = hit(xs);
	if (!inter)
		printf("i: nothing\n");
	else
		printf("i: %f\n", inter->t);
	free(inter);
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("hit: sphere(0, 0, 0), i1(-1, s), i2(1, s)\n");
	s = sphere(point(0, 0, 0),  color(0, 0, 0));
	xs[0].object = NULL;
	xs = intersections(intersection(-1, &s), intersection(1, &s));
	inter = hit(xs);
	if (!inter)
		printf("i: nothing\n");
	else
		printf("i: %f\n", inter->t);
	free(inter);
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("hit: sphere(0, 0, 0), i1(-2, s), i2(-1, s)\n");
	s = sphere(point(0, 0, 0),  color(0, 0, 0));
	xs[0].object = NULL;
	xs = intersections(intersection(-2, &s), intersection(-1, &s));
	inter = hit(xs);
	if (!inter)
		printf("i: nothing\n");
	else
		printf("i: %f\n", inter->t);
	free(inter);
	free_matrix(s.transform, 4);
	printf("\n");

	t_ray	*r2;
	float	**m;
	printf("transform: ray(point(1, 2, 3), vector(0, 1, 0)), mtr(3, 4, 5))\n");
	r = ray(point(1, 2, 3), vector(0, 1, 0));
	m = translation(3, 4, 5);
	r2 = transform(r, m);
	printf("r2->origin = %f, %f, %f, %f\n", r2->origin.x, r2->origin.y, r2->origin.z, r2->origin.w);
	printf("r2->direction = %f, %f, %f, %f\n", r2->direction.x, r2->direction.y, r2->direction.z, r2->direction.w);
	printf("\n");
	free_matrix(m, 4);
	free(r2);
	
	printf("transform: ray(point(1, 2, 3), vector(0, 1, 0)), msc(2, 3, 4))\n");
	r = ray(point(1, 2, 3), vector(0, 1, 0));
	m = scaling(2, 3, 4);
	r2 = transform(r, m);
	printf("r2->origin = %f, %f, %f, %f\n", r2->origin.x, r2->origin.y, r2->origin.z, r2->origin.w);
	printf("r2->direction = %f, %f, %f, %f\n", r2->direction.x, r2->direction.y, r2->direction.z, r2->direction.w);

	free_matrix(m, 4);
	free (r2);

	printf("\n");
	
	// set transform sphere
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	print_matrix(s.transform, 4);
	printf("\n");

	// changing a sphere's transformation
	m = translation(2, 3, 4);
	set_transform(&s, m);
	print_matrix(m, 4);
	printf("\n");
	print_matrix(s.transform, 4);
	free_matrix(s.transform, 4);
	free_matrix(m, 4);
	
	printf("\n");
    printf("Intersecting a scaled sphere with a ray\n");
    // intersecting a scaled sphere with a ray
    r = ray(point(0, 0, -5), vector(0, 0, 1));
    s = sphere(point(0, 0, 0), color(0, 0, 0));
	m = scaling(2, 2, 2);
	set_transform(&s, m);
	print_matrix(s.transform, 4);
	xs[0].object = NULL;
    xs = intersect(s, r); 
    // Should we include "count" in xs?
    printf("xs[0].t = %f\n", xs[0].t);
    printf("xs[1].t = %f\n", xs[1].t);
	free_matrix(m, 4);
	free_matrix(s.transform, 4);
   	free(xs);
	return (0);
}

void    print_matrix(float **m, int size)
{
    int x;
    int y;

    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
            printf("%f ", m[y][x++]);
        printf("\n");
        y++;
    }
}
