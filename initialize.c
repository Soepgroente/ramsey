#include "cubing.h"

t_square**	allocate_squarray(int size)
{
	t_square**	squares;

	squares = calloc(size, sizeof(t_square *));
	if (squares == NULL)
		exit(EXIT_FAILURE);
	for (int i = 0; i < size; i++)
	{
		squares[i] = calloc(1, sizeof(t_square));
		if (squares[i] == NULL)
			exit(EXIT_FAILURE);
	}
}

void	initialize_stuff(t_data* data)
{
	int i = 0;

	data->m_iter = 0;
	data->total_pts = pow(2, dimensions);
	data->total_lines = bino_coeff(data->total_pts, 2);
	data->sq_per_num = data->total_pts / 2 - 1;
	data->squares = allocate_squarray(data->sq_per_num);
	data->lines = calloc((data->total_pts - 1), sizeof(t_line *));
	if (data->lines == NULL)
		exit(EXIT_FAILURE);
	while (i < data->total_pts - 1)
	{
		data->lines[i] = calloc((data->total_pts - i - 1), sizeof(t_line));
		if (data->lines[i] == NULL)
			exit(EXIT_FAILURE);
		for (int x = 0; x < data->total_pts - i - 1; x++)
		{
			data->lines[i][x].a = i;
			data->lines[i][x].b = i + x + 1;
			data->lines[i][x].color = UNCOLORED;
		}
		i++;
	}
}