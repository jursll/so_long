/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:25:04 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/09 18:57:02 by julrusse         ###   ########.fr       */
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
# define EMPTY '0'

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
# define RESTART 114

typedef struct	s_map
{
	char	**grid;   // La grille de la carte
	int		width;    // Largeur de la carte
	int		height;   // Hauteur de la carte
	int		player_count;   // Nombre de 'P'
	int		collect_count;  // Nombre de 'C'
	int		exit_count;     // Nombre de 'E'
}				t_map;

typedef struct	s_game
{
	t_map	map;       // La structure contenant la carte
	void	*mlx;      // MiniLibX context (future utilisation)
	void	*window;   // Fenêtre MiniLibX (future utilisation)
	void	*textures[5];
}				t_game;

char	**read_map(char *filename, t_game *game);
int		validate_map(t_game *game);
void	free_map(char **map, int lines);
void	render_map(t_game *game);
void	load_textures(t_game *game);
int		count_lines(const char *filename);

#endif
