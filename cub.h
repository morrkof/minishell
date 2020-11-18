/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:21:22 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/04 18:17:04 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include "bmp.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "libft/libft.h"

# define PI 3.14159265359
# define PI3 1.047197551
# define COLOR_YELLOW 0x00FFC300
# define COLOR_RASPBERRY 0x00C70039
# define COLOR_BORDEAU 0x00900C3F
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R_ARR 65363
# define KEY_L_ARR 65361
# define KEY_ESC 65307
# define SPD 0.1
# define TURN_SPD 0.05
# define RAYS 300

typedef	struct		s_tex
{
	char			*path;
	void			*img;
	int				*addr;
	int				w;
	int				h;
}					t_tex;

typedef	struct		s_wall
{
	float			hstart;
	float			hpart;
	float			wstart;
	float			wpart;
	float			marg;
	float			height;
	float			width;
	int				texw;
	int				texh;
	int				*texa;
	int				rayn;
}					t_wall;

typedef struct		s_ang
{
	float			ang;
	float			dist;
	float			rel_ang;
}					t_ang;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_ray
{
	int				number;
	float			len;
	float			angle;
	float			next_ang;
	float			start;
	float			part;
	t_tex			*texture;
}					t_ray;

typedef struct		s_spr {
	float			x;
	float			y;
	float			dist;
	float			width;
	float			rel_ang;
	float			tang;
	float			bang;
	float			angle;
	struct s_spr	*next;
}					t_spr;

typedef	struct		s_data {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				l_len;
	int				end;
	char			**map;
	int				map_width;
	int				map_height;
	float			px;
	float			py;
	float			pa;
	int				ceil_color;
	int				floor_color;
	t_tex			north;
	t_tex			south;
	t_tex			east;
	t_tex			west;
	t_tex			sprite;
	t_list			*map_list;
	t_spr			*fov_spr;
}					t_data;

typedef	struct		s_flags {
	int				width;
	int				height;
	int				resolution;
	int				ceil_color;
	int				floor_color;
	int				r_color;
	int				g_color;
	int				b_color;
	int				no_texture;
	int				so_texture;
	int				ea_texture;
	int				we_texture;
	int				sprite_texture;
	int				map;
	int				player;
}					t_flags;

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				ft_error(int error);
void				check_ext(char *line);
void				create_screenshot(t_data *data);
void				init_bmp_data(t_bmpfile *file, t_bmpinf *img, t_data *data);
int					refresh(t_data *data);
int					ft_keys_walk(int keycode, t_data *data);
void				move_player(t_data *data, float angle);
int					esc_key(int keycode, t_data *data);
int					ft_exit(void);
void				fill_parameters(int fd, t_data *data);
void				flags_init(t_flags *flags);
void				check_flags(t_flags *flags);
void				read_lines(t_data *data, int fd, t_flags *flags);
void				sort_line(char *line, t_data *data, t_flags *flags, int i);
void				fill_resolution(char *line, t_data *data, t_flags *flags);
int					fill_size(char *line, int my_size, int *flag);
int					fill_color(char *line, t_flags *flags, int *flag);
void				sort_color(char *line, t_flags *flags, t_color *col);
int					fill_color_part(char *line, int *flag);
void				rgb_init(t_flags *flags);
void				fill_file_path(char *line, t_tex *side, int *flag);
void				open_textures(t_data *data);
void				*get_xpm(t_data *data, t_tex *side);
int					*get_addr(void *img, t_data *data);
int					set_texture(t_data *data, int *a, t_ray *ray, char c);
void				fill_map(t_data *data);
void				validate_map(t_data *data);
void				check_cell(t_data *data, int x, int y);
void				check_player(t_data *data, t_flags *flags);
void				check_player_angle(t_data *data, int x, int y);
char				is_map_coordinates(t_data *data, float x, float y);
t_spr				*new_spr(float x, float y, float dist, float angle);
void				add_spr(t_spr **lst, t_spr *new);
int					get_sprite_count(t_spr *lst);
t_spr				*get_sprite_w_smaller_dist(t_spr *lst, float dist);
void				set_sprites(t_data *data);
void				clear_sprites(t_spr **lst);
void				draw_ray(t_data *data, t_ray ray);
void				draw_sprite(t_data *data, t_ray ray);
void				draw_walls_and_sprites(t_data *data);
void				draw_ceil_and_floor(t_data *data);
void				spr_init(t_wall *spr, t_data *data, t_ray ray, t_spr *spt);
int					spr_pix_put(t_data *data, t_wall spr, int ox, int oy);
void				wall_init(t_wall *wal, t_data *data, t_ray ray);
void				wall_pix_put(t_data *data, t_wall wal, int ox, int oy);
void				ray_init(t_ray *ray, t_data *data, float angle);
t_ray				cast_ray(t_data *data, float angle);
t_ray				check_horizontal_walls(t_data *data, float angle);
t_ray				check_vertical_walls(t_data *data, float angle);
void				ray_assign_h(t_data *data, t_ray *ray);
void				ray_assign_v(t_data *data, t_ray *ray);
float				calc_s_ang(t_data *data, float x, float y);
float				calc_s_dist(t_data *data, float x, float y);
char				check_angle(float angle, float left_side, float right_side);
float				diff_angle(float a1, float a2);
t_ang				fill_ang(t_data *data, float x, float y);
float				norm_ang(float angle);
int					get_max_str(t_list *temp);
void				draw_map(t_data *data);
void				draw_player(t_data *data);
void				my_square(t_data *data, float x, float y, int px);

#endif
