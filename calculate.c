#include "cubing.h"

static int	find_4th_point(t_data* data, int a, int b, int c)
{
	int	d;

	if (a == b || b == c || a == c)
		return (-1);
	d = a ^ b ^ c;
	if (d > data->total_pts)
		return (-1);
	return (d);
}

bool	check_single_square(uint8_t* square)
{
	int	count = 0;

	for (int i = 0; i < 6; i++)
	{
		if (square[i] == UNCOLORED)
			return (true);
		if (square[i] == RED)
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

static bool	find_config(t_data* data, t_line* line)
{
	int a = line->point_a;
	int b = line->point_b;
	int	c;
	int d;

	c = 0;
	while (c < data->total_pts)
	{
		d = find_4th_point(data, a, b, c);
		if (d != -1 && (check_coloring(data, data->lines, a, b, c, d) == false))
			return (false);
		c++;
	}
	return (true);
}

bool	find_pattern(t_data* data, t_line** lines, int x, int y)
{
	static size_t iter = 0;

	iter++;
	if (iter == 1000000)
	{
		print_lines(lines, data->total_pts, data->total_lines);
		iter = 0;
		data->m_iter++;
	}
	while (x < data->total_pts)
	{
		if (y < data->total_pts - x - 1)
		{
			// if (lines[x][y].color == UNCOLORED)
			// {	
			lines[x][y].color = RED;
			if (find_config(data, &lines[x][y]) == true)
			{
				if (find_pattern(data, lines, x, y + 1) == true)
					return (true);
			}
			lines[x][y].color = BLUE;
			if (find_config(data, &lines[x][y]) == true)
			{
				if (find_pattern(data, lines, x, y + 1) == true)
					return (true);
			}
			lines[x][y].color = UNCOLORED;
			return (false);
		}
		x++;
		y = 0;
	}
	return (printf("Iterations: %d million and %zu\n", data->m_iter, iter), true);
}