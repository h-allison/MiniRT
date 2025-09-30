/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_p.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:19:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 16:02:13 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRTP_H
# define MINIRTP_H

# include "libft.h"
# include "minirt.h"
# include <stdbool.h>

#define	BONUS true

typedef struct	s_checklist
{
	bool	a_parsed;
	bool	c_parsed;
	bool	l_parsed;
	int		count_light;
	int		count_sphere;
	int		count_cyl;
	int		count_cube;
	int		count_plane;
	int		count_cone;
	int		count_shape;
}	t_checklist;

#endif
