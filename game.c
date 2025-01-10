/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:45:33 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 18:36:43 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	handle_key(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		ft_printf("ESC pressed. Closing game...\n");
		close_game(game);
	}
	else if (keycode == LEFT || keycode == A)
		move_player(game, -1, 0);
	else if (keycode == UP || keycode == W)
		move_player(game, 0, -1);
	else if (keycode == RIGHT || keycode == D)
		move_player(game, 1, 0);
	else if (keycode == DOWN || keycode == S)
		move_player(game, 0, 1);
	else if (keycode == 65451) // '+' augmente la taille
	{
		game->window_width += 100;
		game->window_height += 100;
		ft_printf("Increasing window size to %dx%d\n", game->window_width, game->window_height);

		// Détruire l'ancienne fenêtre et recréer une nouvelle avec les dimensions mises à jour
		mlx_destroy_window(game->mlx, game->window);
		game->window = mlx_new_window(game->mlx, game->window_width, game->window_height, "So Long");
		if (!game->window)
		{
			ft_printf("ERROR: Failed to create resized window\n");
			close_game(game);
		}

		// Re-render la carte
		render_map(game);
	}
	else if (keycode == 65453) // '-' réduit la taille
	{
		if (game->window_width > 200 && game->window_height > 200)
		{
			game->window_width -= 100;
			game->window_height -= 100;
			ft_printf("Decreasing window size to %dx%d\n", game->window_width, game->window_height);

			// Détruire l'ancienne fenêtre et recréer une nouvelle avec les dimensions mises à jour
			mlx_destroy_window(game->mlx, game->window);
			game->window = mlx_new_window(game->mlx, game->window_width, game->window_height, "So Long");
			if (!game->window)
			{
				ft_printf("ERROR: Failed to create resized window\n");
				close_game(game);
			}

			// Re-render la carte
			render_map(game);
		}
	}
	return (0);
}

int	resize_window(t_game *game)
{
	int	screen_width;
	int	screen_height;

	if (!game || !game->mlx || !game->window)
		return (0);

	// Récupère la taille actuelle de l'écran
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);

	// Ajuste les dimensions de la fenêtre pour qu'elles respectent la taille de la carte
	game->window_width = (screen_width < game->map.width * 64) ? screen_width : game->map.width * 64;
	game->window_height = (screen_height < game->map.height * 64) ? screen_height : game->map.height * 64;

	// Redessine la carte avec les nouvelles dimensions
	render_map(game);
	ft_printf("Window resized to: %d x %d\n", game->window_width, game->window_height);
	return (0);
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
			ft_printf("Congratulations! You reached the exit in %d moves.\n",
				game->player_moves + 1);
			close_game(game);
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
