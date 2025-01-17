/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:37:53 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/17 16:51:26 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	handle_remaining_line(char *line)
{
	if (line)
	{
		free(line);
		ft_printf("Error\nMap format is invalid\n");
		return (0);
	}
	return (1);
}

int	check_lines_after_map(int fd, char *line)
{
	while (line)
	{
		if (line[0] != '\0' && line[0] != '\n')
		{
			free(line);
			ft_printf("Error\nMap format is invalid\n");
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

void	count_map_elements(t_game *game)
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
				game->map.player_count++;
			else if (game->map.grid[i][j] == COLLECTIBLE)
				game->map.collect_count++;
			else if (game->map.grid[i][j] == EXIT)
				game->map.exit_count++;
			j++;
		}
		i++;
	}
}

void	flood_fill(char **grid, int x, int y, t_flood_fill_args *args)
{
	if (x < 0 || y < 0)
		return ;
	if (x >= args->game->map.height || y >= args->game->map.width)
		return ;
	if (grid[x][y] == WALL || grid[x][y] == 'F')
		return ;
	if (grid[x][y] == EXIT)
	{
		*(args->reached_exit) = 1;
		return ;
	}
	if (grid[x][y] == COLLECTIBLE)
		args->game->map.collect_count--;
	grid[x][y] = 'F';
	flood_fill(grid, x + 1, y, args);
	flood_fill(grid, x - 1, y, args);
	flood_fill(grid, x, y + 1, args);
	flood_fill(grid, x, y - 1, args);
}
