/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:17:19 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/12 18:53:28 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


t_light	light = {
	.position = {-40.0, 50.0, 0.0},
	.intensity = 0.6,               
	.color = {10, 0, 255} 
};

int	main(void)
{
	t_vars		vars;
	t_sphere	sphere;

	sphere.center.x = 0;
	sphere.center.y = 0;
	sphere.center.z = -50;
	sphere.diameter = 20;
	sphere.color[0] = 255;
	sphere.color[1] = 0;
	sphere.color[2] = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT");
	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	render(&vars, sphere, light);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
