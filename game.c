/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:45:33 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/16 15:45:56 by julrusse         ###   ########.fr       */
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
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	else if (keycode == LEFT || keycode == A)
		move_player(game, -1, 0);
	else if (keycode == UP || keycode == W)
		move_player(game, 0, -1);
	else if (keycode == RIGHT || keycode == D)
		move_player(game, 1, 0);
	else if (keycode == DOWN || keycode == S)
		move_player(game, 0, 1);
	return (0);
}

static int	count_collectibles(char **grid, int height, int width)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (grid[y][x] == COLLECTIBLE)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_pos.x + dx;
	new_y = game->player_pos.y + dy;

	// Vérifie si le déplacement est valide (pas de mur)
	if (game->map.grid[new_y][new_x] != WALL)
	{
		if (game->map.grid[new_y][new_x] == EXIT)
		{
			game->map.collect_count = count_collectibles(game->map.grid, game->map.height, game->map.width);
			if (game->map.collect_count > 0)
			{
				ft_printf("Game Over! You reached the exit in %d moves but didn't collect all the collectibles.\n",
					game->player_moves + 1);
			}
			else
			{
				ft_printf("Congratulations! You reached the exit in %d moves.\n",
					game->player_moves + 1);
			}
			close_game(game); // Ferme le jeu
		}

		// Met à jour la carte pour déplacer le joueur
		if (game->map.grid[new_y][new_x] == COLLECTIBLE)
			game->map.collect_count--;

		game->map.grid[game->player_pos.y][game->player_pos.x] = FLOOR; // Ancienne position
		game->player_pos.x = new_x;
		game->player_pos.y = new_y;
		game->map.grid[new_y][new_x] = PLAYER; // Nouvelle position

		// Incrémente les mouvements
		game->player_moves++;
		ft_printf("Player moved to [%d][%d]. Total moves: %d\n",
			new_y, new_x, game->player_moves);

		// Re-render la carte
		render_map(game);
	}
	else
	{
		ft_printf("Blocked by wall at [%d][%d]\n", new_y, new_x);
	}
}
