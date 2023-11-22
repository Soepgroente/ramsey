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

	for (int i = 0; i < 6; i++)
	{
		if (square->lines[i]->color == UNCOLORED)
			return (true);
		if (square->lines[i]->color == RED)
			count++;
	}
	if (count == 0 || count == 6)
		return (false);
	return (true);
}

bool	check_coloring(t_data* data, t_line line)
{
	t_square**	squares;
	uint16_t a = line.a;
	uint16_t b = line.b;
	int	i = 0;

	squares = allocate_squarray(data->sq_per_num);
	find_squares(data, squares, line);
	while (i < data->sq_per_num)
	{
		if (squares[i]->lines != NULL)
		{
			if (check_single_square(squares) == false)
				return (free_squarray(squares), false);
		}
		i++;
	}
	return (free_squarray(squares), true);
}
