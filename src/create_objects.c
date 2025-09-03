/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:14:22 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/03 15:27:08 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	sphere(t_tuple origin, t_rgb color)
{
	t_sphere	sphere;

	sphere.origin = origin;
	sphere.transform = create_id_matrix();
	sphere.color = color;
	sphere.material.color = color;
	sphere.material.ambient = 0.1;
	sphere.material.diffuse = 0.9;
	sphere.material.specular = 0.9;
	sphere.material.shininess = 200;
	return (sphere);
}

t_light	point_light(t_tuple position, t_rgb intensity)
{
	t_light light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}
