/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:21:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/09 19:10:54 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'C' || c == 'P' || c == 'E')
		return (1);
	return (0);
}

static int	check_line_validity(char *line)
{
	int i;

	i = 0;
	while (line[i]  && line[i] != '\n')
	{
		if (!is_valid_char(line[i]))
		{
			ft_printf("Invalid character '%c' in line: %s\n", line[i], line);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	remove_newline(char *line)
{
	int len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	validate_map(t_game *game)
{
	int	i;
	int	j;

	game->map.player_count = 0;
	game->map.collect_count = 0;
	game->map.exit_count = 0;
	game->map.width = ft_strlen(game->map.grid[0]);
	i = 0;
	while (game->map.grid[i])
	{
		if ((int)ft_strlen(game->map.grid[i]) != game->map.width)
			return (ft_printf("ERROR: Map is not rectangular\n"), 0);
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_char(game->map.grid[i][j]))
				return (ft_printf("ERROR: Invalid character '%c' in map\n", game->map.grid[i][j]), 0);
			game->map.player_count += (game->map.grid[i][j] == 'P');
			game->map.collect_count += (game->map.grid[i][j] == 'C');
			game->map.exit_count += (game->map.grid[i][j] == 'E');
			j++;
		}
		i++;
	}
	if (game->map.player_count != 1 || game->map.collect_count < 1 || game->map.exit_count < 1)
		return (ft_printf("ERROR: Invalid map elements (P=%d, C=%d, E=%d)\n",
			game->map.player_count, game->map.collect_count, game->map.exit_count), 0);
	return (1);
}

char	**read_map(char *filename, t_game *game)
{
	int		fd;
	int		lines;
	char	*line;
	char	**map;

	// Compte le nombre de lignes
	lines = count_lines(filename);
	if (lines < 0)
		return (ft_printf("ERROR: Invalid map or cannot read the map\n"), NULL);
	ft_printf("Detected map has %d lines\n", lines);

	// Ouvre le fichier
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("ERROR: cannot open the map\n"), NULL);

	// Alloue la mémoire pour la carte
	map = malloc(sizeof(char *) * (lines + 1)); // +1 pour le NULL final
	if (!map)
		return (ft_printf("ERROR: Failed to allocate memory for map\n"), close(fd), NULL);

	game->map.height = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		ft_printf("Reading line: %s\n", line);

		// Vérifie la validité de la ligne
		if (!check_line_validity(line))
		{
			ft_printf("ERROR: Oops, invalid or no char in map\n");
			free(line);
			free_map(map, game->map.height);
			close(fd);
			return (NULL);
		}

		// Ajoute la ligne à la carte
		map[game->map.height++] = line;
		line = get_next_line(fd);
	}
	map[game->map.height] = NULL;
	close(fd);
	game->map.grid = map;
	return (map);
}
