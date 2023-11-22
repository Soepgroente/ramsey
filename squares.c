#include "cubing.h"

void	find_lines(t_line** lines, t_square* square, uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
	square->lines[0] = &lines[a][b - a - 1];
	square->lines[1] = &lines[a][c - a - 1];
	square->lines[2] = &lines[a][d - a - 1];
	square->lines[3] = &lines[b][c - b - 1];
	square->lines[4] = &lines[b][d - b - 1];
	square->lines[5] = &lines[c][d - c - 1];
}

/* void	insert_squalues(t_square* square, uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
	square->a = a;
	square->b = b;
	square->c = c;
	square->d = d;
} */

void	find_squares(t_data* data, t_square** squares, t_line line)
{
	uint16_t 	a = line.a;
	uint16_t	b = line.b;
	uint16_t	c = 0;
	int32_t		d = 0;
	int	i = 0; int j = 0;
	
	while (c < data->total_pts)
	{
		d = find_4th_point(data->total_pts, a, b, c);
		if (d != -1)
		{
			// insert_squalues(squares[c], a, b, c, d);
			find_lines(data->lines, squares[c], a, b, c, d);
			// print_square(a, b, c, (uint16_t)d);
		}
		c++;
	}
}
