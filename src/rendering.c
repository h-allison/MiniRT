/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/06 00:16:13 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(void *param)
{
	static bool		render_done;
	t_data			*data;
	t_object		s;
	t_ray			r;
	t_rgb			col;
	t_tuple			ray_origin;
	t_tuple			pos;
	t_largs			largs;
	float			wall_z;
	float			wall_size;
	float			half;
	float			pixel_size;
	float			world_x;
	float			world_y;
	int				x;
	int				y;
	t_intersection	*ht;
	t_intersection	*xs;

	data = (t_data *)param;
	if (!render_done)
	{
		s = sphere();
		s.m.color = color(0x1F, 0xCE, 0xCB);
		s.m.diffuse = 0.9;
		s.m.specular = 0.9;
		s.m.shininess = 200;
		float	shear[6] = {.5, 0, 0, 0, 0, 0};
		s.transform = mmultfree(shearing(shear), s.transform);
		s.transform = mmultfree(rotation_y(M_PI / 6), s.transform);
		largs.light = point_light(point(5, 10, -10), color(255, 255, 255));
		ray_origin = point(0, 0, -10);
		wall_z = 10;
		wall_size = 7;
		half = wall_size / 2;
		pixel_size = wall_size / WIN_WIDTH;
		y = 0;
		while (y < WIN_HEIGHT)
		{
			world_y = half - pixel_size * y;
			x = 0; 
			while (x < WIN_WIDTH)
			{
				world_x = -half + pixel_size * x;
				pos = point(world_x, world_y, wall_z);
				r = ray(ray_origin, tnorm(tsub(pos, ray_origin)));
				xs = intersect(&s, r);
				ht = hit(xs);
				if (ht)
				{
					largs.point = position(r, ht->t);
					largs.normalv = normal_at(ht->object, largs.point);
					largs.eyev = tneg(r.direction);
					largs.material = ht->object->m;
					col = lighting(&largs);
					mlx_put_pixel(data->img, x, y, color_to_hex(col));
					free(ht);
				}
				xs[0].object = NULL;
				x++;
			}
			y++;
		}
	}
	if (!render_done)
	{
		free_matrix(s.transform, 4);
		free(xs);
		printf("render done!\n");
		canvas_export_ppm(data);
		render_done = true;
	}
}
