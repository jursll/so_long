/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:25:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 20:20:10 by julrusse         ###   ########.fr       */
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

// GAME OBJECTS KEYS
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define WALL '1'
# define FLOOR '0'

// GAME KEYWORDS
# define ESC 65307
# define W 119
# define UP 65362
# define A 97
# define LEFT 65361
# define S 115
# define DOWN 65364
# define D 100
# define RIGHT 65363
# define PLUS 65451
# define MINUS 65453

typedef struct	s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct	s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_count;
	int			collect_count;
	int			exit_count;
}				t_map;

typedef struct	s_game
{
	t_map		map;
	void		*mlx;
	void		*window;
	t_position	player_pos;
	int			player_moves;
	int			window_width;
	int			window_height;
	int			tile_size;
	void		*textures[5];
}				t_game;

//		utils.c (2)
char	**allocate_map(int height);
void	free_map(char **map, int lines);

//		read_map.c (4)
char	**read_map(char *filename, t_game *game);

//		validate_map.c (5)
int		validate_map(t_game *game);

//		validate_path.c (4)
int		find_player_position(t_game *game);
int		validate_walls(t_game *game);
int		validate_path(t_game *game);

//		render.c (4)
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y, int tile_size);
void	resize_and_render(t_game *game);
void	load_textures(t_game *game);

//		game.c (2)
int		handle_key(int keycode, t_game *game);
void	move_player(t_game *game, int dx, int dy);

//		main.c (4)
void	init_game(t_game *game);
int		close_game(t_game *game);
void	cleanup(t_game *game);

#endif
