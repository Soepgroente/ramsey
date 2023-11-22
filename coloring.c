#include "cubing.h"

static void	swap_single(uint16_t* x, uint16_t* y)
{
	if (*x > *y)
	{
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}

void	order_points(uint16_t* a, uint16_t* b, uint16_t* c, uint16_t* d)
{
	swap_single(a, b);
	swap_single(a, c);
	swap_single(a, d);
	swap_single(b, c);
	swap_single(b, d);
	swap_single(c, d);
}

// int8_t	color_permission(t_line** square)
// {
// 	int8_t	permission = 0;

// 	for (int i = 0; i < 6; i++)
// 	{
// 		if ((*square[i]).color == UNCOLORED)
// 			permission = permission | (1 << i);
// 	}
// 	return (permission);
// }

bool	check_coloring(t_square* square, t_line** lines, uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
	(void)square;
	(void)lines;
	order_points(&a, &b, &c, &d);
	return (false);
}

