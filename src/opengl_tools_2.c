/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:17:33 by emarin            #+#    #+#             */
/*   Updated: 2019/09/24 18:12:52 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "tga.h"

void	fps_input(GLFWwindow *window, t_win_user *win_u, t_camera *cam)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam_process_move(cam, e_forward, win_u->dt_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam_process_move(cam, e_backward, win_u->dt_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam_process_move(cam, e_left, win_u->dt_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam_process_move(cam, e_right, win_u->dt_time);
}

void	update_win_title(GLFWwindow *window)
{
	t_win_user	*win_u;
	char		buff[128];

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	snprintf(buff, sizeof(buff), \
	"Scop		rotate: %s | texture_mode: %s | fps_mode: %s\n", \
	((win_u->settings.rotate_mode) ? "on" : "off"), \
	((win_u->settings.texture_mode) ? "texture" : "color"), \
	((win_u->settings.fps_mode) ? "on" : "off"));
	glfwSetWindowTitle(window, buff);
}

void	key_callback(GLFWwindow *window, int key, int scancode, int action)
{
	t_win_user	*win_u;

	(void)scancode;
	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
\
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		win_u->settings.texture_mode = !win_u->settings.texture_mode;
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		win_u->settings.rotate_mode = !win_u->settings.rotate_mode;
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		win_u->settings.fps_mode = !win_u->settings.fps_mode;
	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS)
		init_win_u(win_u, FALSE);
	update_win_title(window);
}
