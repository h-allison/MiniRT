/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:20:06 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 13:35:57 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_px_fast(t_data *data, int x, int y, uint32_t hex)
{
	uint32_t	*pix32;
	int			w;
	size_t		idx;

	w = data->img->width;
	pix32 = (uint32_t *)data->img->pixels;
	idx = (size_t)y * (size_t)w + (size_t)x;
	pix32[idx] = hex;
}
