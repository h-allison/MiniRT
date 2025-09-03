/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:14:22 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/03 18:40:05 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	sphere()
{
	t_sphere	sphere;

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

	light.position = position;
	light.intensity = intensity;
	return (light);
}
