/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:05:09 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/16 16:07:47 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static char	**create_temp_grid(t_game *game)
{
	char	**temp_grid;
	int		i;

	temp_grid = allocate_map(game->map.height);
	if (!temp_grid)
	{
		ft_printf("Error\nMemory allocation failed for flood fill\n");
		return (NULL);
	}
	i = 0;
	while (i < game->map.height)
	{
		temp_grid[i] = ft_strdup(game->map.grid[i]);
		if (!temp_grid[i])
		{
			free_map(temp_grid, i);
			ft_printf("Error\nMemory allocation failed for grid copy\n");
			return (NULL);
		}
		i++;
	}
	return (temp_grid);
}

static int	validate_flood_fill(t_game *game, char **temp_grid,
	t_flood_fill_args *args)
{
	flood_fill(temp_grid, game->player_pos.y, game->player_pos.x, args);
	if (game->map.collect_count > 0)
	{
		ft_printf("Error\nNot all collectibles are reachable\n");
		free_map(temp_grid, game->map.height);
		return (0);
	}
	if (!*(args->reached_exit))
	{
		ft_printf("Error\nExit is not reachable\n");
		free_map(temp_grid, game->map.height);
		return (0);
	}
	return (1);
}

int	validate_path(t_game *game)
{
	char				**temp_grid;
	int					reached_exit;
	t_flood_fill_args	args;

	reached_exit = 0;
	args.reached_exit = &reached_exit;
	args.game = game;
	temp_grid = create_temp_grid(game);
	if (!temp_grid)
		return (0);
	if (!validate_flood_fill(game, temp_grid, &args))
		return (0);
	free_map(temp_grid, game->map.height);
	return (1);
}
