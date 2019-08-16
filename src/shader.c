/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:08:34 by emarin            #+#    #+#             */
/*   Updated: 2019/08/16 15:12:21 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <stdio.h>

const char	*file_to_string(char *filename)
{
	FILE	*fp;
	long	size;
	char	*buffer;

	if (!(fp = fopen(filename, "rb")))
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (NULL);
	}
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	if (!(buffer = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (fread(buffer, size, 1, fp) != 1)
	{
		fprintf(stderr, "file read failed\n");
		fclose(fp);
		return (NULL);
	}
	fclose(fp);
	buffer[size] = '\0';
	return (buffer);
}

int8_t		compile_shader(const char **src, unsigned int *shader, int type)
{
	int		success;
	char	info_log[512];

	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, src, NULL);
	free((char*)(*src));
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		if (type == GL_VERTEX_SHADER)
			fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n"\
			, info_log);
		else
			fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n"\
			, info_log);
		return (FALSE);
	}
	return (TRUE);
}

int8_t		link_shader(unsigned int *shader_program\
, unsigned int *fragment_shader, unsigned int *vertex_shader)
{
	int		success;
	char	info_log[512];

	*shader_program = glCreateProgram();
	glAttachShader(*shader_program, *vertex_shader);
	glAttachShader(*shader_program, *fragment_shader);
	glLinkProgram(*shader_program);
	glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
		fprintf(stderr, "ERROR::SHADER::LINKING_FAILED\n%s\n", info_log);
		return (FALSE);
	}
	glDetachShader(*shader_program, *vertex_shader);
	glDetachShader(*shader_program, *fragment_shader);
	glDeleteShader(*vertex_shader);
	glDeleteShader(*fragment_shader);
	return (TRUE);
}

int8_t		create_shader(unsigned int *shader_program)
{
	unsigned int	fragment_shader;
	unsigned int	vertex_shader;
	const char		*fragment_src;
	const char		*vertex_src;

	if (!(vertex_src = file_to_string("../src/shaders/test_vs.glsl")))
		return (FALSE);
	if (!compile_shader(&vertex_src, &vertex_shader, GL_VERTEX_SHADER))
		return (FALSE);
	if (!(fragment_src = file_to_string("../src/shaders/test_fs.glsl")))
		return (FALSE);
	if (!compile_shader(&fragment_src, &fragment_shader, GL_FRAGMENT_SHADER))
		return (FALSE);
	if (!link_shader(shader_program, &fragment_shader, &vertex_shader))
		return (FALSE);
	return (TRUE);
}
