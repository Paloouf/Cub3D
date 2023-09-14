/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:49 by ltressen          #+#    #+#             */
/*   Updated: 2023/09/14 16:01:29 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define HEIGHT 1080
# define WIDTH 1920

typedef struct s_mnmp
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
} t_mnmp;

typedef struct s_key
{
	int	forward;
	int	back;
	int	r_left;
	int	r_right;
	int	s_left;
	int	s_right;
	int	crouch;
	int	jump;	
	int	shoot;
	int	aim;
	int	fov;
}	t_key;

typedef struct s_floor
{
	int	r_f;
	int	g_f;
	int	b_f;
}	t_floor;

typedef struct s_ceil
{
	int	r_c;
	int	g_c;
	int	b_c;
}	t_ceil;

typedef struct s_cam
{
	double	cameraX;
	double	raydirX;
	double	raydirY;
	double	d_distX;
	double	d_distY;
	double	s_distX;
	double	s_distY;
	int	hit;
	int	stepX;
	int	stepY;
	double	w_dist;
	int	mapX;
	int	mapY;
	int	side;
	double	line_height;
	int	draw_start;
	int	draw_end;
}	t_cam;

typedef struct s_img
{
	void	*image;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**map;
	int	hgt;
	int	phangle;
	int	pvangle;
	int	crouch;
	int	jump;
	int	fjump;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	posX;
	double	posY;
	t_img	img;
	t_floor	fl;
	t_ceil	cl;
	t_key	key;
	t_cam   *cam;
}	t_cub;

void	minimap(t_cub *cub);
int	key_events(int key, t_cub *cub);
int	close_cross(t_cub *cub);
void	render_walls(t_cub *cub, int color, float i, float j);
void	render_background(t_cub *cub, int color);
int	rgba_to_int(int r, int g, int b, float a);
void	pxl_to_img(t_cub *cub, int x, int y, unsigned int color);
int	parse(char *argv, t_cub *cub);
int	parse_info(t_cub *cub, char *line);
int	init_game(t_cub *data);
void	camera(t_cub *cub, int x);
int	ft_atoi_du_pauvre(char *str, int i);
int	key_release(int key, t_cub *cub);
int	ft_color_f(t_cub *cub, int i, int x);
int	ft_color_c(t_cub *cub, int i);
int	mouse_events(int key, t_cub *cub);
void	move (t_cub *cub);
void	jump(t_cub *cub);	
#endif
