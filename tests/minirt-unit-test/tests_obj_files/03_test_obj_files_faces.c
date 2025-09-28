/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_obj_files_faces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/28 20:03:59 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_files_tests.h"

int	test_obj_files_faces(void)
{
	t_parser	*parser;

	parser = parse_obj_file("tests_obj_files/03_faces.obj");
	if (!parser || !fisequal(parser->vertices[1].x, -1)
		|| !fisequal(parser->vertices[1].x, -1)
		|| !fisequal(parser->vertices[1].y, 1)
		|| !fisequal(parser->vertices[1].z, 0)
		|| !fisequal(parser->vertices[1].w, 1)
		|| !fisequal(parser->vertices[2].x, -1)
		|| !fisequal(parser->vertices[2].y, 0.5)
		|| !fisequal(parser->vertices[2].z, 0)
		|| !fisequal(parser->vertices[2].w, 1)
		|| !fisequal(parser->vertices[3].x, 1)
		|| !fisequal(parser->vertices[3].y, 0)
		|| !fisequal(parser->vertices[3].z, 0)
		|| !fisequal(parser->vertices[3].w, 1)
		|| !fisequal(parser->vertices[4].x, 1)
		|| !fisequal(parser->vertices[4].y, 1)
		|| !fisequal(parser->vertices[4].z, 0)
		|| !fisequal(parser->vertices[4].w, 1))
	{
		free(parser);
		return (-1);
	}
	free(parser);
	return (0);
}
