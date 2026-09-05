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
#include <pthread.h>

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
		if (lim > data->rs.chunk_size)
			lim = data->rs.chunk_size;
	}
	return (lim);
}

static uint32_t	pixel_hex(t_world *world, t_data *data, int x, int y)
{
	t_ray		r;
	t_rgb		c;
	uint32_t	h;

	r = ray_for_pixel(data->cam, (float)x, (float)y);
	c = color_at(world, &r, data->rs.max_recursion);
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

typedef struct s_tile_task
{
	t_world	*world;
	t_data	*data;
	int		y_start;
	int		y_end;
	int		stride;
}	t_tile_task;

static void	*render_tile_rows(void *arg)
{
	t_tile_task	*task;
	int		y;
	int		x;
	uint32_t	hex;

	task = (t_tile_task *)arg;
	y = task->y_start;
	while (y < task->y_end && y < task->data->cam->vsize)
	{
		x = 0;
		while (x < task->data->cam->hsize)
		{
			if (!should_skip(task->data, x, y))
			{
				hex = pixel_hex(task->world, task->data, x, y);
				draw_block_fast(task->data, x, y, hex);
			}
			x += task->stride;
		}
		y += task->stride;
	}
	return (NULL);
}

static int	tile_thread_count(int rows)
{
	long	count;

	count = sysconf(_SC_NPROCESSORS_ONLN);
	if (count < 1)
		count = 1;
	if (count > 16)
		count = 16;
	if (rows < count)
		count = rows;
	return ((int)count);
}

int	render_pixelated_chunk(t_world *world, t_data *data, int rows_limit)
{
	int			rows_done;
	int			threads;
	int			i;
	int			start_idx;
	int			end_idx;
	int			y_start;
	int			y_end;
	int			stride;
	int			max_rows;
	pthread_t	ids[16];
	t_tile_task	tasks[16];

	rows_done = rows_limit;
	stride = data->rs.stride;
	max_rows = (data->cam->vsize - data->rs.y_tile + stride - 1) / stride;
	if (rows_done > max_rows)
		rows_done = max_rows;
	if (rows_done <= 0 || data->rs.y_tile >= data->cam->vsize)
		return (1);
	threads = tile_thread_count(rows_done);
	y_start = data->rs.y_tile;
	i = 0;
	while (i < threads)
	{
		start_idx = (rows_done * i) / threads;
		end_idx = (rows_done * (i + 1)) / threads;
		y_end = y_start + end_idx * stride;
		tasks[i].world = world;
		tasks[i].data = data;
		tasks[i].y_start = y_start + start_idx * stride;
		tasks[i].y_end = y_end;
		tasks[i].stride = stride;
		pthread_create(&ids[i], NULL, render_tile_rows, &tasks[i]);
		i++;
	}
	i = 0;
	while (i < threads)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
	data->rs.y_tile += rows_done * stride;
	return (1);
}
