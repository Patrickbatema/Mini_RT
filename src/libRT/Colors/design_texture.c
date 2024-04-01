/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:55:21 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 16:55:30 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_pattern *stripe_pattern(t_color a, t_color b)
{
    t_pattern *pattern = malloc(sizeof(t_pattern));
    if (!pattern)
        exit(EXIT_FAILURE);
    pattern->a = a;
    pattern->b = b;
    return pattern;
}

t_color stripe_at(t_pattern *pattern, t_tuple point)
{
    if (((int)floor(fabs(point.x * 10.0)) + (int)floor(fabs(point.y * 10.0))) % 2 == 0) {
        return pattern->a;
    } else {
        return pattern->b;
    }
}
