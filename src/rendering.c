/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/10/01 14:15:45 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	render_chunk(t_world *world, t_data *data)
{
	static int	y_tile;
	static int	stride;
	static int	initial_stride;
	static int	aa_mode;
	static int	aa_y;
	static int	done;
	int			rows_done;
	int			rows_limit;
	int			x;
	int			xx;
	int			yy;
	int			skip;
	t_ray		r;
	t_rgb		col;

	if (data->reset)
	{
		y_tile = 0;
		stride = PIXELATE_START_STRIDE;
		initial_stride = stride;
		if (stride < 1)
			stride = 1;
		if (stride > data->cam->hsize)
			stride = data->cam->hsize;
		if (stride > data->cam->vsize)
			stride = data->cam->vsize;
		if (initial_stride > stride)
			initial_stride = stride;
		aa_mode = 0;
		aa_y = 0;
		done = 0;
		data->reset = false;
	}
	if (done)
		return (1);
	if (aa_mode == 1)
	{
		rows_done = 0;
		while (rows_done < CHUNK_SIZE && aa_y < data->cam->vsize)
		{
			x = 0;
			while (x < data->cam->hsize)
			{
				int		s;
				float	inv;
				float	rsum;
				float	gsum;
				float	bsum;

				s = 0;
				inv = 1.0f / (float)AA_SPP;
				rsum = 0.0f;
				gsum = 0.0f;
				bsum = 0.0f;
				while (s < AA_SPP)
				{
					float	jx;
					int		h; 
					float	jy;
					t_ray	rr;
					t_rgb	cc;

					jx = ((float)s + 0.5f) * inv;
					h = (s * 73 + 37) % AA_SPP;
					jy = ((float)h + 0.5f) * inv;
					rr = ray_for_pixel(data->cam,
							(float)x + jx, (float)aa_y + jy);
					cc = color_at(world, &rr, MAX_RECURSION);
					rsum += cc.r;
					gsum += cc.g;
					bsum += cc.b;
					s++;
				}
				col.r = rsum * inv;
				col.g = gsum * inv;
				col.b = bsum * inv;
				mlx_put_pixel(data->img, x, aa_y, color_to_hex(col));
				x++;
			}
			aa_y++;
			rows_done++;
		}
		if (aa_y >= data->cam->vsize)
		{
			aa_mode = 0;
			done = 1;
			printf("Render complete (with AA)\n");
		}
		return (1);
	}
	if (stride <= 1 && y_tile >= data->cam->vsize)
	{
		if (AA_SPP > 1 && aa_mode == 0)
		{
			aa_mode = 1;
			aa_y = 0;
			return (1);
		}
		done = 1;
		printf("Render complete\n");
		return (1);
	}
	if (stride == initial_stride)
		rows_limit = data->cam->vsize;
	else
	{
		rows_limit = data->cam->vsize / stride;
		if (rows_limit > CHUNK_SIZE)
			rows_limit = CHUNK_SIZE;
	}
	rows_done = 0;
	while (rows_done < rows_limit && y_tile < data->cam->vsize)
	{
		x = 0;
		while (x < data->cam->hsize)
		{
			skip = 0;
			if (stride < initial_stride)
			{
				if ((x % (2 * stride) == 0) && (y_tile % (2 * stride) == 0))
					skip = 1;
			}
			if (!skip)
			{
				r = ray_for_pixel(data->cam, (float)x, (float)y_tile);
				col = color_at(world, &r, MAX_RECURSION);
				{
					uint32_t	hex;

					hex = color_to_hex(col);
					yy = y_tile;
					while (yy < y_tile + stride && yy < data->cam->vsize)
					{
						xx = x;
						while (xx < x + stride && xx < data->cam->hsize)
						{
							mlx_put_pixel(data->img, xx, yy, hex);
							xx++;
						}
						yy++;
					}
				}
			}
			x += stride;
		}
		y_tile += stride;
		rows_done++;
	}
	if (y_tile >= data->cam->vsize)
	{
		if (stride > 1)
		{
			stride = stride / 2;
			if (stride < 1)
				stride = 1;
			y_tile = 0;
		}
	}
	return (1);
}

void	img_wipe(t_data *data, t_rgb color)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < data->mlx->height)
	{
		x = 0;
		while (x < data->mlx->width)
		{
			mlx_put_pixel(data->img, x, y, color_to_hex(color));
			x++;
		}
		y++;
	}
	return ;
}

void	render_with_parsing(void *param)
{
	render_chunk(((t_data *)param)->world, param);
}

void	render(void *param)
{
	static int		render_status;
	static t_world	*world;
	static t_camera	*cam;
	static t_data	*data;

	if (render_status == 0)
	{
		data = (t_data *)param;
		world = default_world_6();
		cam = camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 3);
		cam->transform = view_transform(point(-2, 2, -6),
				point(0, 1, 0), vector(0, 1, 0));
		data->reset = true;
		data->cam = cam;
		render_status = 1;
	}
	if (render_status == 1)
		render_status = render_chunk(world, data);
}
