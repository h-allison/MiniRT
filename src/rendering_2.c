/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:26:02 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 13:35:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	aa_row_color(t_world *world, t_data *data, int x, int y)
{
	int		s;
	float	inv;
	t_rgb	sum;
	t_rgb	tmp;
	t_ray	rr;

	s = 0;
	inv = 1.0f / (float)AA_SPP;
	sum.r = 0.0f;
	sum.g = 0.0f;
	sum.b = 0.0f;
	while (s < AA_SPP)
	{
		rr = ray_for_pixel(data->cam, (float)x + (((float)s + 0.5f) * inv),
				(float)y + (((float)((s * 73 + 37) % AA_SPP) + 0.5f) * inv));
		tmp = color_at(world, &rr, MAX_RECURSION);
		sum.r += tmp.r;
		sum.g += tmp.g;
		sum.b += tmp.b;
		s++;
	}
	tmp.r = sum.r * inv;
	tmp.g = sum.g * inv;
	tmp.b = sum.b * inv;
	return (tmp);
}

static int	render_aa_chunk(t_world *world, t_data *data)
{
	int		rows_done;
	int		x;
	t_rgb	col;

	rows_done = 0;
	while (rows_done < CHUNK_SIZE && data->rs.aa_y < data->cam->vsize)
	{
		x = 0;
		while (x < data->cam->hsize)
		{
			col = aa_row_color(world, data, x, data->rs.aa_y);
			put_px_fast(data, x, data->rs.aa_y, color_to_hex(col));
			x++;
		}
		data->rs.aa_y++;
		rows_done++;
	}
	if (data->rs.aa_y >= data->cam->vsize)
	{
		data->rs.aa_mode = 0;
		data->rs.done = 1;
		printf("Render complete (with AA)\n");
	}
	return (1);
}

static void	advance_or_start_aa(t_data *data)
{
	if (data->rs.y_tile < data->cam->vsize)
		return ;
	if (data->rs.stride > 1)
	{
		data->rs.stride = data->rs.stride / 2;
		if (data->rs.stride < 1)
			data->rs.stride = 1;
		data->rs.y_tile = 0;
		return ;
	}
	if (AA_SPP > 1 && data->rs.aa_mode == 0)
	{
		data->rs.aa_mode = 1;
		data->rs.aa_y = 0;
		return ;
	}
	data->rs.done = 1;
	printf("Render complete\n");
}

static void	rs_reset_if_needed(t_data *data)
{
	int	s;

	if (!data->reset)
		return ;
	s = PIXELATE_START_STRIDE;
	data->rs.y_tile = 0;
	data->rs.stride = s;
	data->rs.initial_stride = s;
	if (data->rs.stride < 1)
		data->rs.stride = 1;
	if (data->rs.stride > data->cam->hsize)
		data->rs.stride = data->cam->hsize;
	if (data->rs.stride > data->cam->vsize)
		data->rs.stride = data->cam->vsize;
	if (data->rs.initial_stride > data->rs.stride)
		data->rs.initial_stride = data->rs.stride;
	data->rs.aa_mode = 0;
	data->rs.aa_y = 0;
	data->rs.done = 0;
	data->reset = false;
}

int	render_chunk(t_world *world, t_data *data)
{
	int	rows_limit;

	rs_reset_if_needed(data);
	if (data->rs.done)
		return (1);
	if (data->rs.aa_mode == 1)
		return (render_aa_chunk(world, data));
	rows_limit = compute_rows_limit(data);
	render_pixelated_chunk(world, data, rows_limit);
	advance_or_start_aa(data);
	return (1);
}
