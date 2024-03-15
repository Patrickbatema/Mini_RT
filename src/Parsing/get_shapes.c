/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:18:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/15 17:16:31 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_coordinates(t_vector vec)
{
	if (vec.x < -1 || vec.x > 1)
		return (1);
	else if (vec.y < -1 || vec.y > 1)
		return (2);
	else if (vec.z < -1 || vec.z > 1)
		return (3);
	return (0);
}

t_sphere	*get_sphere_data(char *line)
{
	t_sphere	*sphere;
	char		*value;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	get_next_value(&value, &line);
	parse_coordinates(value, &(sphere->center));
	free(value);
	get_next_value(&value, &line);
	sphere->diameter = ft_atof(value);
	free(value);
	get_next_value(&value, &line);
	if (parse_colors(value, sphere->color) != 0)
	{
		free(value);
		free(sphere);
		return (error("RGB Colors for Sphere are incorrect"), NULL);
	}
	free(value);
	return (sphere);
}

t_plane	*get_plane_data(char *line)
{
	t_plane	*plane;
	char	*value;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	get_next_value(&value, &line);
	parse_coordinates(value, &(plane->point));
	free(value);
	get_next_value(&value, &line);
	parse_coordinates(value, &(plane->normal));
	free(value);
	if (check_coordinates(plane->normal) != 0)
		return (free(plane), error("Plane vector value incorrect"), NULL);
	get_next_value(&value, &line);
	if (parse_colors(value, plane->color) != 0)
	{
		free(value);
		free(plane);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	return (plane);
}

t_cylinder	*get_cylinder_data(char *line)
{
	t_cylinder	*cylinder;
	char		*value;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	get_next_value(&value, &line);
	parse_coordinates(value, &(cylinder->center));
	free(value);
	get_next_value(&value, &line);
	parse_coordinates(value, &(cylinder->direction));
	free(value);
	if (check_coordinates(cylinder->direction) != 0)
		return (free(cylinder), error("Cylinder vector value incorrect"), NULL);
	get_next_value(&value, &line);
	cylinder->diameter = ft_atof(value);
	free(value);
	get_next_value(&value, &line);
	cylinder->height = ft_atof(value);
	free(value);
	get_next_value(&value, &line);
	if (parse_colors(value, cylinder->color) != 0)
	{
		free(value);
		free(cylinder);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	return (cylinder);
}
