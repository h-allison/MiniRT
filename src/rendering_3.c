/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:26:02 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 16:58:22 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	should_skip(t_data *data, int x, int y)
{
	int	ret;

	ret = 0;
	if (data->rs.stride < data->rs.initial_stride)
		if ((x % (2 * data->rs.stride) == 0)
			&& (y % (2 * data->rs.stride) == 0))
			ret = 1;
	return (ret);
}

int	compute_rows_limit(t_data *data)
{
	int	lim;

	lim = data->cam->vsize;
	if (data->rs.stride != data->rs.initial_stride)
	{
		lim = data->cam->vsize / data->rs.stride;
		if (lim > CHUNK_SIZE)
			lim = CHUNK_SIZE;
	}
	return (lim);
}

static uint32_t	pixel_hex(t_world *world, t_data *data, int x, int y)
{
	t_ray		r;
	t_rgb		c;
	uint32_t	h;

	r = ray_for_pixel(data->cam, (float)x, (float)y);
	c = color_at(world, &r, MAX_RECURSION);
	h = color_to_hex(c);
	return (h);
}

static void	draw_block_fast(t_data *data, int x, int y, uint32_t hex)
{
	int			yy;
	int			xx;
	uint32_t	*row;

	yy = y;
	while (yy < y + data->rs.stride && yy < data->cam->vsize)
	{
		row = (uint32_t *)data->img->pixels;
		row = row + (size_t)yy * (size_t)data->img->width;
		xx = x;
		while (xx < x + data->rs.stride && xx < data->cam->hsize)
		{
			row[xx] = hex;
			xx++;
		}
		yy++;
	}
}

int	render_pixelated_chunk(t_world *world, t_data *data, int rows_limit)
{
	int			rows_done;
	int			x;
	uint32_t	hex;

	rows_done = 0;
	while (rows_done < rows_limit && data->rs.y_tile < data->cam->vsize)
	{
		x = 0;
		while (x < data->cam->hsize)
		{
			if (!should_skip(data, x, data->rs.y_tile))
			{
				hex = pixel_hex(world, data, x, data->rs.y_tile);
				draw_block_fast(data, x, data->rs.y_tile, hex);
			}
			x += data->rs.stride;
		}
		data->rs.y_tile += data->rs.stride;
		rows_done++;
	}
	return (1);
}
