#include "cubing.h"

int	dimensions;

static void	initialize_stuff(t_data* data)
{
	int		i = 0; 
	int		j = 0;

	data->total_pts = pow(2, dimensions);
	data->total_lines = bino_coeff(data->total_pts, 2);
	data->points = malloc(data->total_pts * sizeof(int));
	data->lines = malloc(data->total_lines * sizeof(t_line));
	if (data->points == NULL || data->lines == NULL)
		exit(EXIT_FAILURE);
	for (int i = 1; i <= data->total_pts; i++)
		data->points[i - 1] = i;
	while (j < data->total_lines)
	{
		for (int x = i + 1; x < data->total_pts; x++)
		{
			data->lines[j].point_a = i + 1;
			data->lines[j].point_b = x + 1;
			data->lines[j].color = UNCOLORED;
			// data->lines[j].plane = 1;
			j++;
		}
		i++;
	}
}

int main(int argc, char** argv)
{
	t_data	data;

	if (argc != 2)
		return (1);
	dimensions = atoi(argv[1]);
	initialize_stuff(&data);
	print_lines(data.lines, data.total_lines);
}