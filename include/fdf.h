/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:43:13 by aschenk           #+#    #+#             */
/*   Updated: 2024/04/22 20:00:59 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "settings.h" // Color Macros
# include "errors.h" // Error Message Macros

# include "libft.h" // libft
# include "mlx.h" // MiniLibX
# include <X11/keysym.h> // Macros for key symbols, e.g. XK_Escape
# include <X11/X.h> //Macros releated to the event names/masks, e.g. KeyPress

# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open, close, read, write
# include <stdio.h> // perror
# include <string.h> // strerror
# include <float.h> // FLT_MAX macro
# include <math.h> // sin(), cos()

//	++++++++++++++++
//	++ STRUCTURES ++
//	++++++++++++++++

// Data structure holding image info, incl. dimensions, pixel data, color, and
// endianess.
//	- void *img:	Pointer to image object. Used when manipulating image as a
//					whole, e.g. loading into memory or passing to redering ftcs.
//	- char *data:	Pointer to the start of image data -> raw pixel information.
//					Used in operations reading/modifying individual pixels, such
//					as setting the color.
//	- int bpp:		Number of bits used to represent each pixel, which
//					defines the color depth: 32 bits (4 bytes) -> TRGB
//	- int size_len:	Length of each line in the image in bytes,
//					indicating the number of bytes needed to store a single
//					row of pixels in the image.
//	- int endian:	Endianness refers to the byte order in which data types are
//					stored in memory (either big or little endian; left to right
//					and right to left, respectively). Used to determine how to
//					interpret image data ('img' and 'data' members).
typedef struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_len;
	int		endian;
}	t_img;

//	- int color_provided:	Flag if .fdf file provides colors (no: 0, yes: 1).
// close_window needed to set a flag
typedef struct s_fdf
{
	int		fd;
	char	*line;
	int		x_max;
	int		y_max;
	int		**z;
	int		**color;
	int		color_provided;
	void	*mlx;
	void	*win;
	t_img	img;
	float	x_proj_max;
	float	y_proj_max;
	float	x_proj_min;
	float	y_proj_min;
	float	scale;
	float	x_offset;
	float	y_offset;
	float	**x_proj;
	float	**y_proj;
}	t_fdf;


//	+++++++++++++
//	++ PROGRAM ++
//	+++++++++++++

// main.c

int		main(int argc, char **argv);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// map_x_y.c

void	get_x_and_y(t_fdf *fdf, char *file);

// map_z.c

void	get_z(t_fdf *fdf, char *file);

// map_color.c

void	get_color(t_fdf *fdf, char *file);

// map_projection.c

void	get_scale(t_fdf *fdf);
void	get_offset(t_fdf *fdf);

// mlx_render.c

void	render_image(t_fdf *fdf);

// mlx_events.c

int		handle_keypress(int keycode, t_fdf *fdf);
int		handle_x(t_fdf	*fdf);

// free.c

void	free_fdf(t_fdf **fdf_ptr);
void	free_str_arr(char ***array_ptr);

// utils.c

void	msg_and_exit(char *msg, t_fdf *fdf);
void	perror_and_exit(char *msg, t_fdf *fdf);

#endif
