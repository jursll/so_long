/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:37:53 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/16 13:59:35 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == PLAYER)
			{
				game->player_pos.y = i;
				game->player_pos.x = j;
				ft_printf("Player position found at [%d][%d]\n", i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	ft_printf("Error\nNo player position (P) found in map\n");
	return (0);
}

int	validate_walls(t_game *game)
{
	int	i;

	// Vérifie la première et la dernière ligne
	i = 0;
	while (game->map.grid[0][i])
	{
		if (game->map.grid[0][i] != WALL || game->map.grid[game->map.height - 1][i] != WALL)
		{
			ft_printf("Error\nMap is not closed by walls at top/bottom\n");
			return (0);
		}
		i++;
	}

	// Vérifie les bords gauche et droit
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i][0] != WALL || game->map.grid[i][game->map.width - 1] != WALL)
		{
			ft_printf("Error\nMap is not closed by walls at left/right (line %d)\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	flood_fill(char **grid, int x, int y, t_game *game, int *reached_exit)
{
	if (x < 0 || y < 0 || x >= game->map.height || y >= game->map.width)
		return;
	if (grid[x][y] == WALL || grid[x][y] == 'F') // F pour "flooded"
		return;
	if (grid[x][y] == EXIT)
	{
		*reached_exit = 1; // Indique qu'on peut atteindre la sortie
		return; // On ne continue pas après l'exit
	}
	if (grid[x][y] == COLLECTIBLE)
		game->map.collect_count--; // Collectible atteint

	grid[x][y] = 'F'; // Marquer comme visité

	// Appel récursif pour les 4 directions
	flood_fill(grid, x + 1, y, game, reached_exit);
	flood_fill(grid, x - 1, y, game, reached_exit);
	flood_fill(grid, x, y + 1, game, reached_exit);
	flood_fill(grid, x, y - 1, game, reached_exit);
}

int	validate_path(t_game *game)
{
	char	**temp_grid;
	int		i;
	int		reached_exit;

	reached_exit = 0; // Reset du flag avant chaque validation

	// Allouer une copie de la carte
	temp_grid = allocate_map(game->map.height);
	if (!temp_grid)
		return (ft_printf("Error\nMemory allocation failed for flood fill\n"), 0);

	// Copie de la carte pour le flood fill
	i = 0;
	while (i < game->map.height)
	{
		temp_grid[i] = ft_strdup(game->map.grid[i]);
		if (!temp_grid[i])
			return (free_map(temp_grid, i), 0);
		i++;
	}

	// Lancement du flood fill
	flood_fill(temp_grid, game->player_pos.y, game->player_pos.x, game, &reached_exit);

	// Validation après le flood fill
	if (game->map.collect_count > 0)
	{
		ft_printf("Error\nNot all collectibles are reachable\n");
		free_map(temp_grid, game->map.height);
		return (0);
	}
	if (!reached_exit)
	{
		ft_printf("Error\nExit is not reachable\n");
		free_map(temp_grid, game->map.height);
		return (0);
	}
	free_map(temp_grid, game->map.height);
	return (1); // Tout est accessible
}
