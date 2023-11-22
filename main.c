#include "cubing.h"

int	dimensions;

static void	initialize_stuff(t_data* data)
{
	int i = 0;

	data->m_iter = 0;
	data->total_pts = pow(2, dimensions);
	data->total_lines = bino_coeff(data->total_pts, 2);
	data->squares = malloc((data->total_pts) * sizeof(t_square *));
	if (data->squares == NULL)
		exit(EXIT_FAILURE);
	for (i = 0; i < data->total_pts - 2; i++)
	{
		data->squares[i] = calloc(1, sizeof(t_square));
		if (data->squares[i] == NULL)
			exit(EXIT_FAILURE);
	}
	i = 0;
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

int main(int argc, char** argv)
{
	t_data	data;
	// clock_t	start;
	// clock_t	end;

	if (argc != 2)
		return (1);
	dimensions = atoi(argv[1]);
	if (dimensions < 2)
		return (2);
	initialize_stuff(&data);
	FILE* fp = fopen("squares.txt", "w+");
	fclose(fp);
	// start = clock();
	find_pattern(&data, data.lines, 0, 0);
	// end = clock();
	// print_lines(data.lines, data.total_pts, data.total_lines);
	// printf("Runtime: %lu seconds\n", (end - start) / CLOCKS_PER_SEC);
}