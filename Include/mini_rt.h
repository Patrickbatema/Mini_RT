/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:01 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/15 16:59:28 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "libft/libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//*-------------------- 📖 𝘿𝙀𝙁𝙄𝙉𝙄𝙏𝙄𝙊𝙉𝙎 📖 ---------------------*//

# define BLUE "\x1B[94m"
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"
# define RESET "\x1B[0m"

# define WIDTH 960
# define HEIGHT 680
# define MLX_ERROR 1

typedef struct s_scene_state
{
	int			ambient_light_found;
	int			camera_found;
}				t_scene_state;

typedef struct s_vector
{
	double x, y, z;
}				t_vector;

typedef struct s_ambient
{
	double		ratio;
	int			color[3];
}				t_ambient;

typedef struct s_camera
{
	t_vector	position;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef struct s_light
{
	t_vector	position;
	double		intensity;
	int			color[3];
}				t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		diameter;
	int			color[3];
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	int			color[3];
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	direction;
	double		diameter;
	double		height;
	int 		color[3];
}				t_cylinder;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

//*---------------------- ⚙️ 𝙎𝙏𝙍𝙐𝘾𝙏𝙎 ⚙️ -----------------------*//
typedef enum s_identifier_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}				t_identifier_type;

typedef struct s_scene_data
{
	t_ambient	ambient_light;
	t_camera	camera;
	t_light		light;
	t_list		*shapes;
	int			shape_count;
}				t_scene_data;
//*---------------------- ⚙️ 𝙎𝙏𝙍𝙐𝘾𝙏𝙎 ⚙️ -----------------------*//

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_camera	camera;
}				t_vars;

int				validate_scene(char *filename);
void			parse_scene(char *filename);
void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int				make_color(float percent, int flag, int r, int g);
t_vector		vector_add(t_vector a, t_vector b);
void			render_cylinder_basic(t_vars *vars, t_cylinder cylinder);
void			render_plane(t_vars *vars, t_plane plane);
float			intersect_ray_plane(t_ray ray, t_plane plane);
float	intersect_ray_sphere(t_ray ray, t_sphere sphere);

t_vector		vector_sub(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
t_vector		vector_scale(t_vector v, double s);
double			dot(t_vector a, t_vector b);
double			norm(t_vector v);
void			render(t_vars *vars, t_sphere sphere, t_light light);
void render_scene(t_vars *vars, t_sphere *sphere, t_plane *plane, t_light *light);

t_vector		normalize(t_vector v);
int				create_trgb(int t, int r, int g, int b);
void render_scene_with_sphere_and_plane(t_vars *vars, t_sphere sphere, t_plane plane, t_light light);
int adjust_color_by_light(int *color, double light_intensity);

//*----------------------- 👁️ 𝙋𝘼𝙍𝙎𝙀 👁️ -----------------------*//
// todo              ~~~  parse errors  ~~~                  *//
int				invalid_input(int ac, char **av);
void			error(char *str);

// todo              ~~~   data init    ~~~                  *//
void			*init_data(t_scene_data *scene_data, int ac, char **av);
int				get_identifier(char **line, t_identifier_type *type,
					t_scene_data *scene_data);

// todo              ~~~ value extract  ~~~                  *//
void			parse_coordinates(char *input, t_vector *vec);
int				parse_colors(char *input, int colors[3]);

// todo              ~~~     utils      ~~~                  *//
double			ft_atof(const char *str);
int				skip_spaces(char *str);
char			*strdup_upto_whitespace(const char *s);

// todo              ~~~   get shapes   ~~~                  *//
t_sphere		*get_sphere_data(char *line);
t_plane			*get_plane_data(char *line);
t_cylinder		*get_cylinder_data(char *line);

// todo              ~~~  add elements  ~~~                  *//
int				add_shape_data(t_identifier_type type, t_scene_data *scene_data,
					char *line);
int				add_capital_element(t_identifier_type type,
					t_scene_data *scene_data, char *line);

// todo              ~~~     print      ~~~                  *//
void			print_camera(const t_camera *camera);
void			print_identifier_type(t_identifier_type type);
void			print_sphere(const t_sphere *sphere);
void			print_ambient(const t_ambient *ambient);
void 			print_light(const t_light *light);
void			print_plane(const t_plane *plane);
void			print_cylinder(const t_cylinder *cylinder);

#endif
