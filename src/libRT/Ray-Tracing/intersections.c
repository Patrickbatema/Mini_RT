/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/02 11:14:43 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersection	intersection(double t, t_sphere *object);
t_intersection	*hit(t_intersections *xs);

t_intersection intersection(double t, t_sphere *object)
{
    t_intersection i;
    i.t = t;
    i.object.sphere = object;
    return i;
}


t_intersection *hit(t_intersections *intersections)
{
    int i = 0;
    t_intersection *hit = NULL;
    while (i < intersections->count)
    {
        if (intersections->intersections[i].t >= 0)
        {
            if (hit == NULL || intersections->intersections[i].t < hit->t)
                hit = &(intersections->intersections[i]);
        }
        i++;
    }
    return (hit);
}
