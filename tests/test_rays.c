/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/30 20:43:53 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main (void)
{
	t_ray	r;
	t_tuple	target;

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
	return (0);
}
