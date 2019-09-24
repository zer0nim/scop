/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_tools_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:17:33 by emarin            #+#    #+#             */
/*   Updated: 2019/09/24 16:57:15 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "tga.h"

void	process_input(GLFWwindow *window)
{
	t_win_user	*win_u;
	t_camera	*cam;
	float		crnt_frame;

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	cam = &(win_u->cam);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
	crnt_frame = glfwGetTime();
	win_u->dt_time = crnt_frame - win_u->last_frame;
	win_u->last_frame = crnt_frame;
\
	if (win_u->settings.fps_mode)
		fps_input(window, win_u, cam);
}

void	mouse_cb(GLFWwindow *window, double x_pos, double y_pos)
{
	static float	last_x = SCREEN_W / 2.0;
	static float	last_y = SCREEN_H / 2.0;
	static int8_t	first_mouse = TRUE;
	t_camera		*cam;

	cam = &(((t_win_user *)glfwGetWindowUserPointer(window))->cam);
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = FALSE;
	}
	cam_process_mouse(cam, x_pos - last_x, last_y - y_pos);
	last_x = x_pos;
	last_y = y_pos;
}

void	frambuff_resize_cb(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

int8_t	init_window(GLFWwindow **window, const char *name)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Could not start glfw3\n");
		return (FALSE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*window = glfwCreateWindow(SCREEN_W, SCREEN_H, name, NULL, NULL);
	if (!(*window))
	{
		fprintf(stderr, "Fail to create glfw3 window\n");
		glfwTerminate();
		return (FALSE);
	}
	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, frambuff_resize_cb);
	glfwSetCursorPosCallback(*window, mouse_cb);
	glfwSetKeyCallback(*window, (void(*)(GLFWwindow *, int, int, int, int))\
	(size_t)&key_callback);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	return (TRUE);
}

int8_t	load_texture(const char *filename, unsigned int *texture)
{
	t_texture_info	*tga_tex;

	if (!(tga_tex = read_tga_file(filename)))
		return (FALSE);
	glGenTextures(1, &tga_tex->id);
	glBindTexture(GL_TEXTURE_2D, tga_tex->id);
	*texture = tga_tex->id;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, tga_tex->format, tga_tex->w
	, tga_tex->h, 0, tga_tex->format, GL_UNSIGNED_BYTE, tga_tex->texels);
	glGenerateMipmap(GL_TEXTURE_2D);
	free(tga_tex->texels);
	free(tga_tex);
	return (TRUE);
}
