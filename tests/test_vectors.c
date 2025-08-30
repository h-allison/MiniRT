/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:10:28 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/30 17:22:59 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct	s_proj
{
	t_tuple position;
	t_tuple velocity;
} t_proj;

typedef struct	s_env
{
	t_tuple	gravity;
	t_tuple	wind;
} t_env;

int	main(void)
{
	t_proj	ball;
	t_env	env;

	ball.position = point(0, 1, 0);
	ball.velocity = tnorm(vector(2, 2, 0));
	env.gravity = vector(0, -0.1, 0);
	env.wind = vector(-0.04, 0, 0);

	while (ball.position.y > 0)
	{
		printf("height: %f\n", ball.position.y);
		ball.position = tadd(ball.position, ball.velocity);
		ball.velocity = tadd(ball.velocity, tadd(env.gravity, env.wind));
	}
	printf("height: 0.000000\n\n");
	printf("the ball went %f units\n", ball.position.x);
	return (0);
}
