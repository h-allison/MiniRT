/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:45:58 by hallison          #+#    #+#             */
/*   Updated: 2025/09/05 19:04:08 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_default_world(t_world *world);
void	print_matrix(float **m, int size);

int	main(void)
{
	t_world 		w;
	t_ray			r;
	t_intersection *xs;
	t_intersection	is;
	t_object		s;
	t_comps			comps;
	t_rgb			c;
	int				i;

	// Testing default_world()
	w = default_world();
	printf("Testing default_world()\n\n");
	printf("w.light.position = [%f, %f, %f, %f]\n",
			w.light->position.x, w.light->position.y, w.light->position.z, w.light->position.w);
	printf("w.light.intensity = [%f, %f, %f]\n",
			w.light->intensity.r, w.light->intensity.g, w.light->intensity.b);
	printf("pointer to s1 = %p\n", &w.s[0]);
	printf("pointer to s2 = %p\n", &w.s[1]);
	test_default_world(&w);
	free(w.light);
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.s);
	printf("\n");

	// Intersect a world with a ray
	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	xs = intersect_world(&w, &r);
	i = 0;
	while (xs[i].object)
	{
		printf("xs[%i].t = %f\n", i, xs[i].t);
		i++;
	}
	printf("xs count = %i\n", i);
	free(w.light);
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.s);

	// Precomputing the state of an intersection

	w = default_world();
	s = sphere();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	is = intersection(4, &s);
	comps = prepare_computations(&is, &r);
	printf("comps.t = %f\n", comps.t);
	printf("should be is.t: %f\n", is.t);

	printf("\n");

	printf("comps.object is %p\n", comps.object);
	printf("comps.object.objtype = %i\n", comps.object->objtype);
	printf("should be is.object %p\n", is.object);
	printf("is.object.objtype = %i\n", is.object->objtype);

	printf("\n");

	printf("comps.point (0, 0, -1, 1) = %f, %f, %f, %f\n", comps.point.x, comps.point.y, comps.point.z, comps.point.w);
	printf("comps.eyev (0, 0, -1, 0) = %f, %f, %f, %f\n", comps.eyev.x, comps.eyev.y, comps.eyev.z, comps.eyev.w);
	printf("comps.normalv (0, 0, -1, 0) = %f, %f, %f, %f\n", comps.normalv.x, comps.normalv.y, comps.normalv.z, comps.normalv.w);
	printf("comps.inside = %d\n", comps.inside);
	free_matrix(s.transform, 4);
	free(w.light);
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.s);
	printf("\n");
	
	s = sphere();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	is = intersection(4, &s);
	comps = prepare_computations(&is, &r);
	printf("comps.inside = %d\n", comps.inside);
	free_matrix(s.transform, 4);
	printf("\n");

	s = sphere();
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	is = intersection(1, &s);
	comps = prepare_computations(&is, &r);
	printf("comps.point (0, 0, 1, 1) = %f, %f, %f, %f\n", comps.point.x, comps.point.y, comps.point.z, comps.point.w);
	printf("comps.eyev (0, 0, -1, 0) = %f, %f, %f, %f\n", comps.eyev.x, comps.eyev.y, comps.eyev.z, comps.eyev.w);
	printf("comps.inside (should be true) = %d\n", comps.inside);
	printf("comps.normalv (0, 0, -1, 0) = %f, %f, %f, %f\n", comps.normalv.x, comps.normalv.y, comps.normalv.z, comps.normalv.w);
	free_matrix(s.transform, 4);
	printf("\n");

	// Shading an Intersection

	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = w.s[0];
	is = intersection(4, &s);
	comps = prepare_computations(&is, &r);
	c = shade_hit(&w, &comps);
	printf("c should be (0.38066, 0.47583, 0.2855): %f, %f, %f\n", c.r, c.g, c.b);
	free(w.light);
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.s);
	printf("\n");
	
	w = default_world();
	w.light[0] = point_light(point(0, 0.25, 0), color(255, 255, 255));
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	s = w.s[1];
	is = intersection(0.5, &s);
	comps = prepare_computations(&is, &r);
	printf("w.s[0].transform\n");
	print_matrix(w.s[0].transform, 4);
	printf("w.s[1].transform\n");
	print_matrix(w.s[1].transform, 4);
	c = shade_hit(&w, &comps);
	printf("c should be (0.90498, 0.90498, 0.90498): %f, %f, %f\n", c.r, c.g, c.b);
	free(w.light);
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.s);
	printf("\n");

	w = default_world();
	r = ray(point(0, 0, -5), vector(0, 1, 0));
	xs[0].object = NULL;
	c = color_at(&w, &r);
	printf("c should be (0, 0, 0): %f, %f, %f\n", c.r, c.g, c.b);
	free(w.light);
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.s);
	printf("\n");
	
	w = default_world();
	r = ray(point(0, 0, 0.75), vector(0, 0, -1));
	xs[0].object = NULL;
	w.s[0].m.ambient = 1;
	w.s[1].m.ambient = 1;
	c = color_at(&w, &r);
	printf("c inner: %f, %f, %f\n", w.s[0].m.color.r, w.s[0].m.color.g, w.s[0].m.color.b);
	printf("c (should match inner): %f, %f, %f\n", c.r, c.g, c.b);
	free(w.light);
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.s);
	free(xs);
	return (0);
}

void	print_matrix(float **m, int size)
{
	int	x;
	int	y;

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

void	test_default_world(t_world *w)
{
	printf("	t_world w contains light <-- point_light(point(-10, 10, 10), color(1, 1, 1))\n");
	printf("	checking w.light.position:\n");
	if (w->light->position.x == -10)
		printf("	✅ ");
	else
		printf("	❌ ");
	if (w->light->position.y == 10)
		printf("	✅ ");
	else
		printf("	❌ ");
	if (w->light->position.z == -10)
		printf("	✅ ");
	else
		printf("	❌ ");
	printf("\n");

	printf("	checking w.light.intensity:\n");
	if (w->light->intensity.r == 1)
		printf("	✅ ");
	else
		printf("	❌ ");
	if (w->light->intensity.g == 1)
		printf("	✅ ");
	else
		printf("	❌ ");
	if (w->light->intensity.b == 1)
		printf("	✅ ");
	else
		printf("	❌ ");
	printf("\n");

	printf("	t_world w contains s1 <-- sphere with\n");
	printf("	material.color (0.8, 1.0, 0.6)\n");
	printf("	%f, %f, %f\n", w->s[0].m.color.r, w->s[0].m.color.g, w->s[0].m.color.b);

	printf("\n");

	printf("	t_world w contains s1 <-- sphere with\n");
	printf("	material.diffuse (0.7)\n");
	printf("	%f\n", w->s[0].m.diffuse);
	printf("	material.specular (0.2)\n");
	printf("	%f\n", w->s[0].m.specular);

	printf("\n");
	printf("	t_world contains s2 <-- sphere with\n");
	printf("	material.diffuse (0.9)\n");
	printf("	%f\n", w->s[1].m.diffuse);
	printf("	material.specular (0.9)\n");
	printf("	%f\n", w->s[1].m.specular);
}
