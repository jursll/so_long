/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:35:22 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/17 16:41:24 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_lines(const char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0')
			lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && (line[0] == '\0' || line[0] == '\n'))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	fill_map(int fd, char **map, int *height)
{
	int		y;
	char	*line;

	y = 0;
	line = skip_empty_lines(fd);
	while (line && y < *height)
	{
		if (line[0] == '\0' || line[0] == '\n')
		{
			if (!check_lines_after_map(fd, line))
				return (0);
			line = NULL;
			break ;
		}
		remove_newline(line);
		map[y++] = line;
		line = get_next_line(fd);
	}
	if (!handle_remaining_line(line))
		return (0);
	*height = y;
	map[y] = NULL;
	return (1);
}

char	**read_map(char *filename, t_game *game)
{
	int	fd;

	game->map.height = count_lines(filename);
	if (game->map.height <= 0)
		return (ft_printf("Error\nInvalid or empty map file\n"), NULL);
	game->map.grid = allocate_map(game->map.height);
	if (!game->map.grid)
		return (ft_printf("Error\nMemory allocation failed for map\n"), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCannot open map file\n");
		return (free_map(game->map.grid, 0), NULL);
	}
	if (!fill_map(fd, game->map.grid, &game->map.height))
		return (free_map(game->map.grid, game->map.height), close(fd), NULL);
	close(fd);
	return (game->map.grid);
}
