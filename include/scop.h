/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:28:11 by emarin            #+#    #+#             */
/*   Updated: 2019/08/09 15:57:06 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "define.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>

char	create_shader(unsigned int *shader_program);

#endif
