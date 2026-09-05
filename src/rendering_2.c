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
#include <pthread.h>

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
		tmp = color_at(world, &rr, data->rs.max_recursion);
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

typedef struct s_aa_task
{
	t_world	*world;
	t_data	*data;
	int		y_start;
	int		y_end;
}	t_aa_task;

static void	*render_aa_rows(void *arg)
{
	t_aa_task	*task;
	int		y;
	int		x;
	t_rgb		col;

	task = (t_aa_task *)arg;
	y = task->y_start;
	while (y < task->y_end && y < task->data->cam->vsize)
	{
		x = 0;
		while (x < task->data->cam->hsize)
		{
			col = aa_row_color(task->world, task->data, x, y);
			put_px_fast(task->data, x, y, color_to_hex(col));
			x++;
		}
		y++;
	}
	return (NULL);
}

static int	aa_thread_count(int rows)
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

static int	render_aa_chunk(t_world *world, t_data *data)
{
	int		rows_done;
	int		threads;
	int		i;
	int		start_idx;
	int		end_idx;
	int		y_start;
	int		y_end;
	pthread_t	ids[16];
	t_aa_task	tasks[16];

	rows_done = data->cam->vsize - data->rs.aa_y;
	if (rows_done > data->rs.chunk_size)
		rows_done = data->rs.chunk_size;
	if (rows_done <= 0)
		rows_done = 0;
	threads = aa_thread_count(rows_done);
	y_start = data->rs.aa_y;
	i = 0;
	while (i < threads)
	{
		start_idx = (rows_done * i) / threads;
		end_idx = (rows_done * (i + 1)) / threads;
		y_end = y_start + end_idx;
		tasks[i].world = world;
		tasks[i].data = data;
		tasks[i].y_start = y_start + start_idx;
		tasks[i].y_end = y_end;
		pthread_create(&ids[i], NULL, render_aa_rows, &tasks[i]);
		i++;
	}
	i = 0;
	while (i < threads)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
	data->rs.aa_y += rows_done;
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

static void	update_render_mode(t_data *data)
{
	int	was_moving;

	was_moving = data->rs.moving_active;
	data->rs.moving_active = (data->rs.moving_frames > 0);
	if (was_moving && !data->rs.moving_active)
		data->reset = true;
	if (data->rs.moving_frames > 0)
	{
		data->rs.chunk_size = MOVING_CHUNK_SIZE;
		data->rs.max_recursion = MOVING_MAX_RECURSION;
	}
	else
	{
		data->rs.chunk_size = STEADY_CHUNK_SIZE;
		data->rs.max_recursion = STEADY_MAX_RECURSION;
	}
}

int	render_chunk(t_world *world, t_data *data)
{
	int	rows_limit;

	update_render_mode(data);
	rs_reset_if_needed(data);
	if (data->rs.done)
		return (1);
	if (data->rs.aa_mode == 1)
		return (render_aa_chunk(world, data));
	rows_limit = compute_rows_limit(data);
	render_pixelated_chunk(world, data, rows_limit);
	advance_or_start_aa(data);
	if (data->rs.moving_frames > 0)
		data->rs.moving_frames--;
	return (1);
}
