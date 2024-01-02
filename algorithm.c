#include "cubing.h"

bool	color_in_squares(t_data* data, t_square** squares, t_line** line, int x, int y)
{
	while (x < data->sq_per_num)
	{
		while (y < 6)
		{
			if (squares[x]->lines[y]->color == UNCOLORED)
			{
				line[x][y].color = RED;
				if (check_coloring(data, squares) == true)
				{
					if (color_in_squares(data, squares, line, x, y + 1) == true)
						return (true);
				}
				return (false);
			}
		}
		y = 0;
		x++;
	}
}

bool	find_pattern(t_data* data, t_line** line, int x, int y)
{
	if (x < data->total_pts)
	{
		if (y < data->total_pts - x - 1)
		{
			find_squares(data, data->squares, line[x][y]);
			if (color_in_squares(data, data->squares, line, 0, 0) == true);
				find_pattern(data, line, x, y + 1);
			return (false);
		}
		x++;
		y = 0;
	}
	return (true);
}
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