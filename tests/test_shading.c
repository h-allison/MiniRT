/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/05 16:20:58 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_matrix(float **m, int size);

int main (void)
{
	t_object	s;
	t_light		l;
	t_tuple		n;
	t_tuple		p;
	t_tuple		v;
	t_tuple		r;
	float		**m;
	t_largs 	largs;
	t_rgb		result;

	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere();
	n = normal_at(&s, point(1, 0, 0));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere();
	n = normal_at(&s, point(0, 1, 0));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere();
	n = normal_at(&s, point(0, 0, 1));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");

	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere();
	n = normal_at(&s, point(sqrtf(3)/3, sqrtf(3)/3, sqrtf(3)/3));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	p = position(ray(point(0, 0, 0), n), -1);
	printf("pos(t = -1): %f, %f, %f, %f\n", p.x, p.y, p.z, p.w);
	free_matrix(s.transform, 4);
	printf("\n");
	printf("\n");
	
	//

	printf("n = normal_at(s, points(0, 1, 0) (at a translated sphere)\n");
	s = sphere();
	set_transform(&s, translation(0, 1, 0));
	n = normal_at(&s, point(0, 1.70711, -0.70711));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");

	printf("n = normal_at(s, points(0, 1, 0) (at a translated sphere)\n");
	s = sphere();
	m = mmultfree(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
	set_transform(&s, m);
	n = normal_at(&s, point(0, sqrtf(2)/2, -sqrtf(2)/2));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");
	
	//

	printf("r = reflect(v(1, -1, 0), n(0, 1, 0))\n");
	v = vector(1, -1, 0);
	n = vector(0, 1, 0);
	r = reflect(v, n);	
	printf("n: %f, %f, %f, %f\n", r.x, r.y, r.z, r.w);
	printf("\n");
	
	printf("r = reflect(v(0, -1, 0), n(sqrtf(2)/2, sqrtf(2)/2, 0))\n");
	v = vector(0, -1, 0);
	n = vector(sqrtf(2)/2, sqrtf(2)/2, 0);
	r = reflect(v, n);	
	printf("n: %f, %f, %f, %f\n", r.x, r.y, r.z, r.w);
	printf("\n");
	printf("\n");

	l = point_light(point(0, 0, 0), color(0xFF, 0xFF, 0xFF));
	printf("light > position: %f, %f, %f, %f\n",
		l.position.x, l.position.y, l.position.z, l.position.w);
	printf("light > color: %f, %f, %f\n",
		l.intensity.r, l.intensity.g, l.intensity.b);
	printf("\n");

	printf("eye between light and surface\n");
	s = sphere();
	largs.material = s.m;
	largs.point = point(0, 0, 0);
	largs.eyev = vector(0, 0, -1);
	largs.normalv = vector(0, 0, -1);
	largs.light = point_light(point(0, 0, -10), color(0xFF, 0xFF, 0xFF));
	result = lighting(&largs);
	printf("color(%f, %f, %f)\n", result.r, result.g, result.b);
	printf("\n");
	
	printf("eye between light and surface, eye offset 45deg\n");
	s = sphere();
	largs.material = s.m;
	largs.point = point(0, 0, 0);
	largs.eyev = vector(0, sqrtf(2)/2, -sqrt(2)/2);
	largs.normalv = vector(0, 0, -1);
	largs.light = point_light(point(0, 0, -10), color(0xFF, 0xFF, 0xFF));
	result = lighting(&largs);
	printf("color(%f, %f, %f)\n", result.r, result.g, result.b);
	printf("\n");
	
	printf("eye opposite surface, light offset 45deg\n");
	s = sphere();
	largs.material = s.m;
	largs.point = point(0, 0, 0);
	largs.eyev = vector(0, 0, -1);
	largs.normalv = vector(0, 0, -1);
	largs.light = point_light(point(0, 10, -10), color(0xFF, 0xFF, 0xFF));
	result = lighting(&largs);
	printf("color(%f, %f, %f)\n", result.r, result.g, result.b);
	printf("\n");
	
	printf("eye in path of reflection vector\n");
	s = sphere();
	largs.material = s.m;
	largs.point = point(0, 0, 0);
	largs.eyev = vector(0, -sqrtf(2)/2, -sqrt(2)/2);
	largs.normalv = vector(0, 0, -1);
	largs.light = point_light(point(0, 10, -10), color(0xFF, 0xFF, 0xFF));
	result = lighting(&largs);
	printf("color(%f, %f, %f)\n", result.r, result.g, result.b);
	printf("\n");
	
	printf("light behind the surface\n");
	s = sphere();
	largs.material = s.m;
	largs.point = point(0, 0, 0);
	largs.eyev = vector(0, 0, -1);
	largs.normalv = vector(0, 0, -1);
	largs.light = point_light(point(0, 0, 10), color(0xFF, 0xFF, 0xFF));
	result = lighting(&largs);
	printf("color(%f, %f, %f)\n", result.r, result.g, result.b);
	printf("\n");
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
