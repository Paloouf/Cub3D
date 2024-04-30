/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:11:49 by ltressen          #+#    #+#             */
/*   Updated: 2023/10/12 14:47:01 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
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
}	t_mnmp;

typedef struct s_key
{
	int	forward;
	int	back;
	int	r_left;
	int	r_right;
	int	s_left;
	int	s_right;
	int	open;
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

typedef struct s_spr
{
	char	type;
	double	x;
	double	y;
	double	spritex;
	double	spritey;
	double	dist;
	double	invert;
	double	transx;
	double	transy;
	int		spr_screenx;
	int		spr_hgt;
	int		spr_wth;
	int		draw_starty;
	int		draw_endy;
	int		draw_startx;
	int		draw_endx;
	int		tex_x;
	int		tex_y;
	int		transf;
	int		tex;
}	t_spr;

typedef struct s_cam
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	d_distx;
	double	d_disty;
	double	s_distx;
	double	s_disty;
	int		hit;
	double	step;
	int		stepx;
	int		stepy;
	double	w_dist;
	double	w_x;
	char	w_num;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		mapx;
	int		mapy;
	int		side;
	double	line_hgt;
	int		draw_start;
	int		draw_end;
}	t_cam;

typedef struct s_img
{
	void	*image;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	int		img_w;
	int		img_h;
	void	*img;
	int		*addr;
	int		color;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**map;
	char	**mapcpy;
	int		hgt;
	int		phangle;
	int		pvangle;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	posx;
	double	posy;
	int		tono;
	int		*spr_order;
	int		valid;
	int		gameover;
	int		gamewin;
	int		game;
	int		menu;
	double	speed;
	int		error_code;
	int		flag_fl;
	int		flag_cl;
	t_img	img;
	t_floor	fl;
	t_ceil	cl;
	t_key	key;
	t_cam	*cam;
	t_tex	*tex;
	t_spr	*spr;
}	t_cub;

void	minimap(t_cub *cub);
int		key_events(int key, t_cub *cub);
int		close_cross(t_cub *cub);
void	render_walls(t_cub *cub, int color, float i, float j);
void	render_background(t_cub *cub, int color);
int		rgba_to_int(int r, int g, int b, float a);
void	pxl_to_img(t_cub *cub, int x, int y, unsigned int color);
void	parse(char *argv, t_cub *cub, int file, int error);
void	parse_suite(char *argv, t_cub *cub, int file, int error);
int		parse_info(t_cub *cub, char *line, int i);
int		init_game(t_cub *data);
void	camera(t_cub *cub, int x);
int		ft_atoi_du_pauvre(char *str, int i);
int		key_release(int key, t_cub *cub);
int		ft_color_f(t_cub *cub, int i, int x);
int		ft_color_c(t_cub *cub, int i, int x);
int		mouse_events(int x, int y, t_cub *cub);
void	move(t_cub *cub);
void	sprite(t_cub *cub);
void	jump(t_cub *cub);
void	check_sprite(t_cub *cub);
void	ft_door(t_cub *cub);
void	game_over(t_cub *cub);
void	game_win(t_cub *cub);
void	menu(t_cub *cub);
int		mouse_keys(int key, int x, int y, t_cub *cub);
void	init_all(t_cub *cub, int flag);
int		ft_error(char *str);
void	free_all(t_cub *cub);
int		check(t_cub *cub);
int		check_door(t_cub *cub, int i, int j);
void	parse_reset(t_cub *cub);
void	draw_north(t_cub *cub, int i, int j);
void	draw_west(t_cub *cub, int i, int j);
void	draw_south(t_cub *cub, int i, int j);
void	draw_east(t_cub *cub, int i, int j);
int		ft_floor(t_cub *cub, char *line);
int		ft_ceiling(t_cub *cub, char *line);
void	flood_fill(t_cub *cub, int x, int y);
int		fill_tex(t_cub *cub, int barrel, int i);
void	ft_sort_sprite(t_cub *cub);
void	add_barrel(t_cub *cub, int i, char *line);
void	get_img_addr(t_cub *cub);
void	draw_wall(t_cub *cub, int x, int i);
void	math_draw(t_cub *cub, int x);
void	dda(t_cub *cub, int x);
void	math_two(t_cub *cub, int x);
void	math_one(t_cub *cub, int x);
int		check_player(t_cub *cub);

#endif
