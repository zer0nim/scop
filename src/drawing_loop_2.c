/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_loop_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/09/24 17:50:23 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	texture_mix(t_data_3d *data_3d, GLFWwindow *window)
{
	t_win_user	*win_u;
	float		speed;

	speed = 0.8f;
	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	if (!win_u->settings.texture_mode && win_u->mix_val > 0.0f)
	{
		win_u->mix_val -= speed * win_u->dt_time;
		win_u->mix_val = (win_u->mix_val < 0.0f) ? 0.0f : win_u->mix_val;
	}
	else if (win_u->settings.texture_mode && win_u->mix_val < 1.0f)
	{
		win_u->mix_val += speed * win_u->dt_time;
		win_u->mix_val = (win_u->mix_val > 1.0f) ? 1.0f : win_u->mix_val;
	}
	set_float_sh(data_3d->shad_obj, "mix_val", win_u->mix_val);
}

void	rotate_model(t_win_user *win_u)
{
	float	speed;

	speed = -20.0f;
	win_u->transform.angle += speed * win_u->dt_time;
	if (win_u->transform.angle > 360.0f || win_u->transform.angle < 360.0f)
		win_u->transform.angle = fmod(win_u->transform.angle, 360.0f);
}
