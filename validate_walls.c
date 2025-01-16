/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:51:42 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/16 16:08:09 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	validate_horizontal_walls(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.grid[0][i])
	{
		if (game->map.grid[0][i] != WALL)
		{
			ft_printf("Error\nMap is not closed by walls at top\n");
			return (0);
		}
		else if (game->map.grid[game->map.height - 1][i] != WALL)
		{
			ft_printf("Error\nMap is not closed by walls at bottom\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	validate_vertical_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i][0] != WALL)
		{
			ft_printf("Error\nMap is not closed by walls at left\n");
			return (0);
		}
		else if (game->map.grid[i][game->map.width - 1] != WALL)
		{
			ft_printf("Error\nMap is not closed by walls at right\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_walls(t_game *game)
{
	if (!validate_horizontal_walls(game) || !validate_vertical_walls(game))
		return (0);
	return (1);
}
