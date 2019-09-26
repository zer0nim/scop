/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/09/26 12:16:10 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	torch_lighting_uniform(t_data_3d *data_3d, t_win_user *win_u)
{
	set_vec3_sh(data_3d->shad_obj, "spotLight.position", win_u->cam.pos);
	set_vec3_sh(data_3d->shad_obj, "spotLight.direction", win_u->cam.front);
	set_float_sh(data_3d->shad_obj, "spotLight.cutOff", cos(radians(12.5f)));
	set_float_sh(data_3d->shad_obj, "spotLight.outerCutOff", \
	cos(radians(15.0f)));
	set_float_sh(data_3d->shad_obj, "spotLight.constant", 1.0f);
	set_float_sh(data_3d->shad_obj, "spotLight.linear", 0.045f);
	set_float_sh(data_3d->shad_obj, "spotLight.quadratic", 0.0075f);
	set_vec3_sh(data_3d->shad_obj, "spotLight.ambient", \
	vect3(0.05f, 0.05f, 0.05f));
	set_vec3_sh(data_3d->shad_obj, "spotLight.diffuse", \
	vect3(0.8f, 0.8f, 0.8f));
	set_vec3_sh(data_3d->shad_obj, "spotLight.specular", \
	vect3(1.0f, 1.0f, 1.0f));
}

void	static_lighting_point_light(t_data_3d *data_3d, t_light *lights)
{
	char	buff[128];
	int		i;

	i = -1;
	while (++i < NB_POINT_LIGHT)
	{
		snprintf(buff, sizeof(buff), "pointLights[%d].position", i);
		set_vec3_sh(data_3d->shad_obj, buff, lights[i].pos);
		snprintf(buff, sizeof(buff), "pointLights[%d].constant", i);
		set_float_sh(data_3d->shad_obj, buff, 1.0f);
		snprintf(buff, sizeof(buff), "pointLights[%d].linear", i);
		set_float_sh(data_3d->shad_obj, buff, 0.045f);
		snprintf(buff, sizeof(buff), "pointLights[%d].quadratic", i);
		set_float_sh(data_3d->shad_obj, buff, 0.0075f);
		snprintf(buff, sizeof(buff), "pointLights[%d].ambient", i);
		set_vec3_sh(data_3d->shad_obj, buff, vect3(0.03, 0.03, 0.03));
		snprintf(buff, sizeof(buff), "pointLights[%d].diffuse", i);
		set_vec3_sh(data_3d->shad_obj, buff, lights[i].color);
		snprintf(buff, sizeof(buff), "pointLights[%d].specular", i);
		set_vec3_sh(data_3d->shad_obj, buff, vect3(1.0f, 1.0f, 1.0f));
	}
}

void	static_lighting_uniform(t_data_3d *data_3d, t_light *lights)
{
	glUseProgram(data_3d->shad_obj);
\
	set_vec3_sh(data_3d->shad_obj, "dirLight.direction", \
	vect3(-0.2f, -0.8f, -0.6f));
	set_vec3_sh(data_3d->shad_obj, "dirLight.ambient", vect3(0.15, 0.15, 0.15));
	set_vec3_sh(data_3d->shad_obj, "dirLight.diffuse", \
	vect3(0.99f, 0.98f, 0.94f));
	set_vec3_sh(data_3d->shad_obj, "dirLight.specular", \
	vect3(1.0f, 1.0f, 1.0f));
\
	set_int_sh(data_3d->shad_obj, "nbPointLight", NB_POINT_LIGHT);
\
	static_lighting_point_light(data_3d, lights);
}

void	static_lighting(t_data_3d *data_3d, t_light *lights)
{
	int		i;
	float	angle;
	float	r;

	r = 2.0f;
	i = -1;
	while (++i < NB_POINT_LIGHT)
	{
		angle = i * (360 / NB_POINT_LIGHT);
		lights[i].pos = vect3(r * cos(radians(angle)), 0.5f, r * \
		sin(radians(angle)));
	}
	lights[0].color = vect3(0.0f, 0.0f, 0.7f);
	lights[1].color = vect3(0.7f, 0.0f, 0.0f);
	lights[2].color = vect3(0.0f, 0.7f, 0.0f);
\
	static_lighting_uniform(data_3d, lights);
}
