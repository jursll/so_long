/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:45:33 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/17 16:50:26 by julrusse         ###   ########.fr       */
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
	int	collectibles;

	y = 0;
	collectibles = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (grid[y][x] == COLLECTIBLE)
				collectibles++;
			x++;
		}
		y++;
	}
	return (collectibles);
}

static void	handle_exit(t_game *game)
{
	game->map.collect_count = count_collectibles(game->map.grid,
			game->map.height, game->map.width);
	if (game->map.collect_count > 0)
	{
		ft_printf("You cannot exit yet! %d fish left to collect\n",
			game->map.collect_count);
	}
	else
	{
		ft_printf("You win! %d moves\n", game->player_moves + 1);
		close_game(game);
	}
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_pos.x + dx;
	new_y = game->player_pos.y + dy;
	if (game->map.grid[new_y][new_x] != WALL)
	{
		if (game->map.grid[new_y][new_x] == EXIT)
		{
			handle_exit(game);
			return ;
		}
		if (game->map.grid[new_y][new_x] == COLLECTIBLE)
			game->map.collect_count--;
		game->map.grid[game->player_pos.y][game->player_pos.x] = FLOOR;
		game->player_pos.x = new_x;
		game->player_pos.y = new_y;
		game->map.grid[new_y][new_x] = PLAYER;
		game->player_moves++;
		ft_printf("Total moves: %d\n", game->player_moves);
		render_map(game);
	}
}
