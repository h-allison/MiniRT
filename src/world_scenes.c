/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:12:31 by hallison          #+#    #+#             */
/*   Updated: 2025/09/16 18:38:03 by hallison         ###   ########.fr       */
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
	t_shape	middle;
	t_shape	right;
	t_shape	left;
	t_shape	behind;
	
	floor = plane();
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(200, 200, 200);
	floor.m.diffuse = 0.7;
	floor.m.ambient = 0.01;
	floor.m.specular = 0.1;
	floor.m.reflective = .1;
	floor.m.pattern = checkers_pattern(color(0, 0, 0), floor.m.color);

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-2, 0.33, 0), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(255, 128, 128);
	left.m.diffuse = 0.7;
	left.m.specular = 0.5;

	middle = sphere();
	middle.transform = mmultfree(translation(-0.2, 1, 1), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(0, 0, 0);
	middle.m.diffuse = 0.1;
	middle.m.specular = 0.2;
	middle.m.reflective = 1;
	middle.m.refractive_index = 1.05;
	middle.m.transparency = 0.2;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(1.5, 0.5, -1), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(140, 100, 255);
	right.m.diffuse = 0.7;
	right.m.specular = 0.4;
	right.m.pattern = ring_pattern(color(20, 80, 60), right.m.color);
	right.m.pattern.transform = mmultfree(scaling(0.1, 0.2, 0.2), right.m.pattern.transform);
	right.m.pattern.invtrans = minvert(right.m.pattern.transform, 4);
	
	behind = sphere();
	behind.transform = mmultfree(scaling(0.75, 0.75, 0.75), behind.transform);
	behind.transform = mmultfree(translation(1, 0.75, 4), behind.transform);
	behind.invtrans = minvert(behind.transform, 4);
	behind.m.color = color(255, 200, 255);
	behind.m.diffuse = 0.8;
	behind.m.specular = 0.5;
//	behind.m.pattern = ring_pattern(color(20, 80, 60), behind.m.color);
//	behind.m.pattern.transform = mmultfree(scaling(0.1, 0.2, 0.2), behind.m.pattern.transform);
	w.light = malloc(1 * sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(255, 255, 240));

	w.s = malloc(8 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = middle;
	w.s[2] = right;
	w.s[3] = left;
	w.s[4] = behind;
	w.s[5].transform = NULL;
	return (w);
}
