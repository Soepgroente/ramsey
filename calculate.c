#include "cubing.h"

int	check_two_digits(uint16_t a, uint16_t b)
{
	uint16_t x = a ^ b;
	int count = 0;

	for (int i = 0; i < 16; i++)
	{
		if ((x >> i) & 1)
			count++;
	}
	return (count);
}

int32_t	find_4th_point(uint16_t total, uint16_t a, uint16_t b, uint16_t c)
{
	uint16_t	d;

	if (a == c || b == c)
		return (-1);
	d = a ^ b ^ c;
	if (check_two_digits(c, d) != 1 || d > total)
		return (-1);
	return (d);
}

bool	check_single_square(t_square* square)
{
	int	count = 0;

	(void)square;
	for (int i = 0; i < 6; i++)
	{
		// if (square->lines[i] == UNCOLORED)
		// 	return (true);
		// if (square->lines[i] == RED)
			count++;
	}
	if (count == 0 || count == 6)
		return (false);
	else
		return (true);
}

/* bool	solve_square(t_line** square, int i, int permissions)
{
	while (i < 6)
	{
		if ((permissions << i & 1) == 1)
		{
			(*square)[i].color = RED;
			i++;
			if (solve_square(square, i, permissions) == true)
				return (true);
			(*square)[i].color = BLUE;
			if (solve_square(square, i, permissions) == true)
				return (true);
			return (false);
		}
		else
			i++;
	}
	if (check_single_square(*square) == false)
		return (false);
	return (true);
} */

/* static bool	find_config(t_data* data, t_line* line)
{
	(void)data;
	(void)line;
	return (true);
	// uint16_t	a = line->a;
	// uint16_t	b = line->b;
	// uint16_t	c;
	// int			d;
	// t_square*	squares;

	// squares = calloc(data->total_pts, sizeof(t_square));
	// c = 0;
	// while (c < data->total_pts)
	// {
	// 	d = find_4th_point(data, a, b, c);
	// 	if (d != -1 && (check_coloring(data, data->lines, a, b, c, d) == false))
	// 		return (false);
	// 	c++;
	// }
	// return (true);
} */

bool	find_pattern(t_data* data, t_line** line, int x, int y)
{
	static size_t iter = 0;

	iter++;
	if (iter == 1)
	{
		print_lines(line, data->total_pts, data->total_lines);
		iter = 0;
		data->m_iter++;
	}
	while (x < data->total_pts)
	{
		while (y < data->total_pts - x - 1)
		{
			find_squares(data, line[x][y]);
			y++;
		}
		x++;
		y = 0;
	}
	return (true);
			// if (line[x][y].color == UNCOLORED)
			// {	
	// 		line[x][y].color = RED;
	// 		if (find_config(data, &line[x][y]) == true)
	// 		{
	// 			if (find_pattern(data, line, x, y + 1) == true)
	// 				return (true);
	// 		}
	// 		line[x][y].color = BLUE;
	// 		if (find_config(data, &line[x][y]) == true)
	// 		{
	// 			if (find_pattern(data, line, x, y + 1) == true)
	// 				return (true);
	// 		}
	// 		line[x][y].color = UNCOLORED;
	// 		return (false);
	// 	}
	// 	x++;
	// 	y = 0;
	// }
	// return (printf("Iterations: %d million and %zu\n", data->m_iter, iter), true);
}