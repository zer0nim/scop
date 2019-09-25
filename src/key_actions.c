/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:37:41 by emarin            #+#    #+#             */
/*   Updated: 2019/09/25 17:42:40 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	wireframe_mode(t_win_user *win_u)
{
	win_u->settings.wireframe_mode = !win_u->settings.wireframe_mode;
	if (win_u->settings.wireframe_mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void	fps_mode(GLFWwindow *window, t_win_user *win_u)
{
	cam_init(&(win_u->cam));
	win_u->settings.fps_mode = !win_u->settings.fps_mode;
	glfwSetInputMode(window, GLFW_CURSOR, ((win_u->settings.fps_mode) \
	? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));
}
