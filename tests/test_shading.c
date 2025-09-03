/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/03 13:20:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_matrix(float **m, int size);

int main (void)
{
	t_sphere	s;
	t_tuple		n;
	t_tuple		p;
	float		**m;

	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	n = normal_at(s, point(1, 0, 0));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	n = normal_at(s, point(0, 1, 0));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");
	
	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	n = normal_at(s, point(0, 0, 1));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");

	printf("n = normal_at(s, points(1, 0, 0)\n");
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	n = normal_at(s, point(sqrtf(3)/3, sqrtf(3)/3, sqrtf(3)/3));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	p = position(ray(s.origin, n), -1);
	printf("pos(t = -1): %f, %f, %f, %f\n", p.x, p.y, p.z, p.w);
	free_matrix(s.transform, 4);
	printf("\n");
	printf("\n");
	
	//

	printf("n = normal_at(s, points(0, 1, 0) (at a translated sphere)\n");
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	set_transform(&s, translation(0, 1, 0));
	n = normal_at(s, point(0, 1.70711, -0.70711));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
	printf("\n");

	printf("n = normal_at(s, points(0, 1, 0) (at a translated sphere)\n");
	s = sphere(point(0, 0, 0), color(0, 0, 0));
	m = mmultfree(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
	set_transform(&s, m);
	n = normal_at(s, point(0, sqrtf(2)/2, -sqrtf(2)/2));
	printf("n: %f, %f, %f, %f\n", n.x, n.y, n.z, n.w);
	free_matrix(s.transform, 4);
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
