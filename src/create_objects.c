/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:14:22 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/04 17:38:54 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	sphere()
{
	t_object	sphere;

	sphere.objtype = OBJ_SPHERE; 
	sphere.transform = create_id_matrix();
	sphere.m.color = color(0xFF, 0xFF, 0xFF);
	sphere.m.ambient = 0.1;
	sphere.m.diffuse = 0.9;
	sphere.m.specular = 0.9;
	sphere.m.shininess = 200;
	return (sphere);
}

t_light	point_light(t_tuple position, t_rgb intensity)
{
	t_light light;

	printf("intensity.r = %f\n", intensity.r);
	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_world	default_world()
{
	t_world		w;
	t_object	s1;
	t_object	s2;
	t_light		light;
	
	light = point_light(point(-10, 10, -10), color(255, 255, 255));
	s1 = sphere();
	
	s1.m.color = color(204, 255, 153);
	s1.m.diffuse = 0.7;
	s1.m.specular = 0.2;
	s2 = sphere();
	s2.transform = mmultfree(scaling(0.5, 0.5, 0.5), s2.transform); //set_scaling??
	w.s = malloc(3 * sizeof(t_object));
	w.s[0] = s1;
	w.s[1] = s2;
	w.s[2].transform = NULL;
	w.light = malloc(sizeof(t_light));
	if (!w.light)
			exit (1);
	w.light[0] = light;
	return (w);
}
