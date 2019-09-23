/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 20:25:56 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 13:54:55 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "scop.h"

void	cam_init(t_camera *cam)
{
	cam->pos = vect3(0.0f, 0.0f, 3.0f);
	cam->front = vect3(0.0f, 0.0f, -1.0f);
	cam->up = vect3(0.0f, 1.0f, 0.0f);
	cam->yaw = -90.0f;
	cam->pitch = 0.0f;
}

void	cam_process_move(t_camera *cam, t_cam_mov_e mov, float dt_time)
{
	float	speed;

	speed = 2.0f * dt_time;
	if (mov == e_forward)
		cam->pos = v3_add(cam->pos, v3_scal_mul(cam->front, speed));
	if (mov == e_backward)
		cam->pos = v3_sub(cam->pos, v3_scal_mul(cam->front, speed));
	if (mov == e_left)
		cam->pos = v3_sub(cam->pos, \
		v3_scal_mul(v3_normalize(v3_cross(cam->front, cam->up)), speed));
	if (mov == e_right)
		cam->pos = v3_add(cam->pos, \
		v3_scal_mul(v3_normalize(v3_cross(cam->front, cam->up)), speed));
}

void	cam_process_mouse(t_camera *cam, float x_offset, float y_offset)
{
	float	sensitivity;
	t_vect3	front;

	sensitivity = 0.1;
	x_offset *= sensitivity;
	y_offset *= sensitivity;
	cam->yaw = cam->yaw + x_offset;
	cam->pitch += y_offset;
	if (cam->pitch > 89.0f)
		cam->pitch = 89.0f;
	if (cam->pitch < -89.0f)
		cam->pitch = -89.0f;
	front.x = cos(radians(cam->yaw)) * cos(radians(cam->pitch));
	front.y = sin(radians(cam->pitch));
	front.z = sin(radians(cam->yaw)) * cos(radians(cam->pitch));
	cam->front = v3_normalize(front);
}
