/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:13 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/05 16:17:35 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	shade_hit(t_world *w, t_comps *comps)
{
	t_largs	largs;

	largs.material = comps->object->m;
	largs.light = w->light[0];
	largs.point = comps->point;
	largs.eyev = comps->eyev;
	largs.normalv = comps->normalv;
	return (lighting(&largs));
}
