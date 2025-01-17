/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:25:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/17 16:42:03 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define WALL '1'
# define FLOOR '0'

# define ESC 65307
# define W 119
# define UP 65362
# define A 97
# define LEFT 65361
# define S 115
# define DOWN 65364
# define D 100
# define RIGHT 65363

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_count;
	int			collect_count;
	int			exit_count;
}				t_map;

typedef struct s_game
{
	t_map		map;
	void		*mlx;
	void		*window;
	t_position	player_pos;
	int			player_moves;
	int			window_width;
	int			window_height;
	int			tile_size;
	int			shortest_path;
	void		*textures[5];
}				t_game;

typedef struct s_flood_fill_args
{
	int			*reached_exit;
	t_game		*game;
}				t_flood_fill_args;

//		utils.c (2)
char	**allocate_map(int height);
void	free_map(char **map, int lines);

//		read_map.c (5)
int		fill_map(int fd, char **map, int *height);
char	**read_map(char *filename, t_game *game);

//		validate_map.c (5)
int		validate_map(t_game *game);

//		validate_utils.c (4)
int		handle_remaining_line(char *line);
int		check_lines_after_map(int fd, char *line);
void	count_map_elements(t_game *game);
void	flood_fill(char **grid, int x, int y, t_flood_fill_args *args);

//		validate_path.c (3)
int		validate_path(t_game *game);

//		validate_walls.c (3)
int		validate_walls(t_game *game);

//		render.c (3)
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y, int tile_size);
void	load_textures(t_game *game);

//		game.c (4)
int		find_player_position(t_game *game);
int		handle_key(int keycode, t_game *game);
void	move_player(t_game *game, int dx, int dy);

//		main.c (4)
void	init_game(t_game *game);
int		close_game(t_game *game);
void	cleanup(t_game *game);

#endif
