#include "ramsey.h"

int	dimensions;

static uint32_t	connect_dots(uint16_t num1, uint16_t num2)
{
	return (num1 << 8 | num2);
}

static void	init_points(t_point* points, t_line* lines)
{
	int		points_total;
	int		lines_total;

	points_total = pow(2, dimensions);
	lines_total = bino_coeff(points_total, 2);
	points = malloc(points_total * sizeof(t_point));
	lines = malloc(lines_total * sizeof(t_line));
	if (!points || !lines)
		exit(EXIT_FAILURE);
	for (int i = 1; i <= points_total; i++)
		points[i].num = i;
	
/* 	for (int i = 0; i < x; i++)
	{
		points[i].lines = malloc(2 * dimensions * sizeof(t_line *));
	} */
	return (points);
}

int main(int argc, char** argv)
{
	t_point*	dots;
	t_line*		lines;

	if (argc != 2)
		return (1);
	dimensions = atoi(argv[1]);
	dots = NULL;
	lines = NULL;
	init_points(dots, lines);
	printf("Size of pointstruct: %lu\n", malloc_size(dots));
}