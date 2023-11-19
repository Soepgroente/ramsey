#include "cubing.h"

static void	swap_single(int* x, int* y)
{
	int tmp;

	if (*x > *y)
	{
		tmp = *y;
		*y = *x;
		*x = tmp;
	}
}

static void	order_points(int* a, int* b, int* c, int* d)
{
	swap_single(a, b);
	swap_single(a, c);
	swap_single(a, d);
	swap_single(b, c);
	swap_single(b, d);
	swap_single(c, d);
}

int8_t	color_permission(t_line** square)
{
	int8_t	permission = 0;

	for (int i = 0; i < 6; i++)
	{
		if ((*square[i]).color == UNCOLORED)
			permission = permission | (1 << i);
	}
	return (permission);
}

bool	check_coloring(t_data* data, t_line** lines, int a, int b, int c, int d)
{
	int8_t	perm;

	order_points(&a, &b, &c, &d);
	data->square[0] = &lines[a][b];
	data->square[1] = &lines[a][c];
	data->square[2] = &lines[a][d];
	data->square[3] = &lines[b][c];
	data->square[4] = &lines[b][d];
	data->square[5] = &lines[c][d];
	perm = color_permission(data->square);
	if (solve_square(data->square, 0, perm) == true)
		return (true);
	return (false);
}

