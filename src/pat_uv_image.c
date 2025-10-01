/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_uv_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:58:07 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 09:38:20 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*uv_image(t_canvas *canvas)
{
	t_pattern	*uv_image;

	uv_image = malloc(sizeof(*uv_image));
	uv_image->canvas = canvas;
	uv_image->transform = create_id_matrix();
	uv_image->invtrans = minvert(uv_image->transform, 4);
	uv_image->pattern_at = uv_image_at;
	uv_image->uv_pattern = NULL;
	uv_image->status = true;
	return (uv_image);
}

static t_rgb	pixel_at(t_canvas *canvas, int x, int y)
{
	return (canvas->img[y][x]);
}

t_rgb	uv_image_at(t_pattern *uv_image, t_tuple uv)
{
	float	x;
	float	y;

	uv.y = 1 - uv.y;
	x = uv.x * (uv_image->canvas->width - 1);
	y = uv.y * (uv_image->canvas->height -1);
	return (pixel_at(uv_image->canvas, (int)round(x), (int)round(y)));
}
