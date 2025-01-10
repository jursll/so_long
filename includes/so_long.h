/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:25:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 18:27:34 by julrusse         ###   ########.fr       */
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
# define ZOOM 65451
# define DEZOOM 65453

typedef struct	s_position
{
	int			x; // Coordonnée colonne (horizontal)
	int			y; // Coordonnée ligne (vertical)
}				t_position;

typedef struct	s_map
{
	char		**grid;   // La grille de la carte
	int			width;    // Largeur de la carte
	int			height;   // Hauteur de la carte
	int			player_count;   // Nombre de 'P'
	int			collect_count;  // Nombre de 'C'
	int			exit_count;     // Nombre de 'E'
}				t_map;

typedef struct	s_game
{
	t_map		map;       // La structure contenant la carte
	void		*mlx;      // MiniLibX context (future utilisation)
	void		*window;   // Fenêtre MiniLibX (future utilisation)
	t_position	player_pos;   // Structure contenant les coordonnées du joueur
	int			player_moves; // Compteur de mouvements du joueur
	int			window_width;  // Largeur actuelle de la fenêtre
	int			window_height; // Hauteur actuelle de la fenêtre
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

//		render.c (3)
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y, int tile_size);
void	load_textures(t_game *game);

//		game.c (3)
int		handle_key(int keycode, t_game *game);
int		resize_window(t_game *game);
void	move_player(t_game *game, int dx, int dy);

//		main.c (4)
void	init_game(t_game *game);
int		close_game(t_game *game);
void	cleanup(t_game *game);

#endif
