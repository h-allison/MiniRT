/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:12:31 by hallison          #+#    #+#             */
/*   Updated: 2025/09/17 14:47:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

t_material	m_red_glass(void)
{
	t_material	m;

	m.color = color(0xFF, 0xFF, 0xFF);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	m.reflective = 0.0;
	m.transparency = 0.0;
	m.refractive_index = 1.0;
	m.pattern = pattern();
	return(m);
}

t_shape	new_glass_sphere(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_sphere;
	s.local_intersect = local_intersect_sphere;
	s.m = material();
	s.m.transparency = 0.9;
	s.m.refractive_index = 1.5;
	return (s);
}

t_world	default_world_6(void)
{
	t_world	w;
	t_shape	floor;
	t_shape	big;
	t_shape	middle;
	t_shape	right;
	t_shape	left;
	t_shape cub;
	
	floor = plane();
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(200, 200, 200);
	floor.m.diffuse = 0.7;
	floor.m.ambient = 0.01;
	floor.m.specular = 0.2;
	floor.m.reflective = .2;
	floor.m.pattern = ring_pattern(color(80, 80, 80), floor.m.color);

	big = sphere();
	big.transform = mmultfree(translation(.5, 1, 4), big.transform);
	big.invtrans = minvert(big.transform, 4);
	big.m.color = color(140, 130, 100);
	big.m.diffuse = .6;
	big.m.ambient = .2;
	big.m.specular = 0.5;
	big.m.pattern = stripe_pattern(color(80, 80, 80), big.m.color);
	big.m.pattern.transform = mmultfree(scaling(0.4, 0.4, 0.6), big.m.pattern.transform);
	big.m.pattern.invtrans = minvert(big.m.pattern.transform, 4);

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-2, 0.33, 2), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(128, 120, 70);
	left.m.diffuse = 0.4;
	left.m.specular = 0.1;
	left.m.ambient = 0.1;
	left.m.reflective = 0.7;
	left.m.transparency = 0;

	middle = sphere();
	middle.transform = mmultfree(translation(-0.2, 1, -2), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(10, 20, 15);
	middle.m.diffuse = 1;
	middle.m.specular = 1;
	middle.m.shininess = 300;
	middle.m.ambient = 0.1;
	middle.m.reflective = 2;
	middle.m.transparency = 0.9;
	middle.m.refractive_index = 1.5;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(4, 0.5, 2.5), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(140, 100, 255);
	right.m.diffuse = 0.7;
	right.m.specular = 0.4;
	right.m.pattern = ring_pattern(color(20, 80, 60), right.m.color);
	right.m.pattern.transform = mmultfree(scaling(0.1, 0.2, 0.2), right.m.pattern.transform);
	right.m.pattern.invtrans = minvert(right.m.pattern.transform, 4);
	
	cub = cube();
	cub.transform = mmultfree(rotation_y(30 * DEG2RAD), cub.transform);
	cub.transform = mmultfree(scaling(0.2, 0.2, 0.2), cub.transform);
	cub.transform = mmultfree(translation(-1.8, 0.2, -1), cub.transform);
	cub.invtrans = minvert(cub.transform, 4);
	cub.m.color = color(40, 70, 100);
	cub.m.diffuse = .6;
	cub.m.ambient = .3;
	cub.m.specular = 0.6;
	cub.m.reflective = 0.4;

	w.light = malloc(1 * sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(255, 255, 240));

	w.s = malloc(8 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = big;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	w.s[5] = cub;
	w.s[6].transform = NULL;
	return (w);
}

t_world	default_world_cyl(void)
{
	t_world	w;
	t_shape	floor;
	t_shape	big;
	t_shape	middle;
	t_shape	right;
	t_shape	left;
	t_shape cub;
	
	floor = plane();
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(200, 200, 200);
	floor.m.diffuse = 0.7;
	floor.m.ambient = 0.01;
	floor.m.specular = 0.2;
	floor.m.reflective = .2;
	floor.m.pattern = ring_pattern(color(80, 80, 80), floor.m.color);

	big = sphere();
	big.transform = mmultfree(translation(.5, 1, 4), big.transform);
	big.invtrans = minvert(big.transform, 4);
	big.m.color = color(140, 130, 100);
	big.m.diffuse = .6;
	big.m.ambient = .2;
	big.m.specular = 0.5;
	big.m.pattern = stripe_pattern(color(80, 80, 80), big.m.color);
	big.m.pattern.transform = mmultfree(scaling(0.4, 0.4, 0.6), big.m.pattern.transform);
	big.m.pattern.invtrans = minvert(big.m.pattern.transform, 4);

	left = cylinder();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-2, 0.33, 2), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(128, 120, 70);
	left.m.diffuse = 0.4;
	left.m.specular = 0.1;
	left.m.ambient = 0.1;
	left.m.reflective = 0.7;
	left.m.transparency = 0;
	left.minimum = 0;
	left.maximum = 1;
	middle = sphere();
	middle.transform = mmultfree(translation(-0.2, 1, -2), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(10, 20, 15);
	middle.m.diffuse = 1;
	middle.m.specular = 1;
	middle.m.shininess = 300;
	middle.m.ambient = 0.1;
	middle.m.reflective = 2;
	middle.m.transparency = 0.9;
	middle.m.refractive_index = 1.5;

	right = cylinder();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(4, 0.5, 2.5), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(140, 100, 255);
	right.m.diffuse = 0.7;
	right.m.specular = 0.4;
	right.m.pattern = ring_pattern(color(20, 80, 60), right.m.color);
	right.m.pattern.transform = mmultfree(scaling(0.1, 0.2, 0.2), right.m.pattern.transform);
	right.m.pattern.invtrans = minvert(right.m.pattern.transform, 4);
	
	cub = cube();
	cub.transform = mmultfree(rotation_y(30 * DEG2RAD), cub.transform);
	cub.transform = mmultfree(scaling(0.2, 0.2, 0.2), cub.transform);
	cub.transform = mmultfree(translation(-1.8, 0.2, -1), cub.transform);
	cub.invtrans = minvert(cub.transform, 4);
	cub.m.color = color(40, 70, 100);
	cub.m.diffuse = .6;
	cub.m.ambient = .3;
	cub.m.specular = 0.6;
	cub.m.reflective = 0.4;

	w.light = malloc(1 * sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(255, 255, 240));

	w.s = malloc(8 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = big;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	w.s[5] = cub;
	w.s[6].transform = NULL;
	return (w);
}
