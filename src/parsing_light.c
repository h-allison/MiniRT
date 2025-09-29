/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:51:51 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 16:04:57 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light_brightness(char *token, t_light *light)
{
	float	brightness;

	brightness = 0;
	if (rt_atof(token, &brightness) != 0)
		return (rt_error("L: brightness: invalid input", -1));
	if (brightness < 0 || brightness > 1)
		return (rt_error("L: brightness: must be in range [0.0, 1.0]", -1));
//	printf("Light brightness = %f\n", brightness);
	light->intensity.r = brightness;
	light->intensity.g = brightness;
	light->intensity.b = brightness;
//	printf("Light brightnes t_rgb = %f, %f, %f\n\n", light->intensity.r,
//		light->intensity.g, light->intensity.b);
	return (0);
}

int	parse_light_position(char *token, t_light *light)
{
	if (rt_atof_tuple(token, &light->position) != 0)
		return (rt_error("L: light position: invalid input", -1));
//	printf("Light position = %f, %f, %f, %f\n", light->position.x,
//		light->position.y, light->position.z, light->position.w);
	return (0);
}

static void	alloc_init_lights(t_world *world)
{
	int	i;

	world->light = (t_light **)ft_calloc((world->checklist->count_light + 2), sizeof(t_light *));
	if (!world->light)
		exit(1);
	i = 0;
	while (i < world->checklist->count_light)
	{
		world->light[i] = point_light(point(0, 0, 0), color(0, 0, 0));
		world->light[i]->last = false;
		i++;
	}
	world->light[i] = point_light(point(0, 0, 0), color(0, 0, 0));
	world->light[i]->last = true;
}

static int	mandatory_tokens_found(char **tokens)
{
	if (!tokens[1])
		return (rt_error("L: light position: missing values", -1));
	if (!tokens[2])
		return (rt_error("L: light brightness: missing values", -1));
	if (BONUS == false && tokens[3])
		return (rt_error("L: Extraneous args. Bonus not enabled", -1));
	return (0);
}

int	parse_light(char **tokens, t_world *world)
{
	static int	li;
	int			i;
	int			(*func[4])(char *tokens, t_light *light);

	func[0] = parse_light_position;
	func[1] = parse_light_brightness;
	func[2] = NULL;
	if (li == 0)
		alloc_init_lights(world);
	if (mandatory_tokens_found(tokens) != 0)
		return (-1);
	i = 0;
	while (func[i])
	{
		if (func[i](tokens[i + 1], world->light[li]) != 0)
			return (-1);
		i++;
	}
	if (BONUS == true && tokens[3])
	{
		if (parse_light_bonus(tokens, world->light[li]) != 0)
			return (-1);
	}
	li++;
	return (0);
}
