/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 13:14:00 by emarin            #+#    #+#             */
/*   Updated: 2019/08/14 16:05:28 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scop.h"

float	radians(float degree_angle)
{
	return (degree_angle * M_PI / 180.0f);
}

float	degrees(float radian_angle)
{
	return (radian_angle * 180.0f / M_PI);
}
