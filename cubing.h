#ifndef CUBING_H
#define CUBING_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <malloc/malloc.h>
# include <time.h>

extern int dimensions;

typedef enum s_color
{
	RED,
	BLUE,
	UNCOLORED
}	coloring;

typedef struct s_line
{
	uint16_t	point_a;
	uint16_t	point_b;
	uint8_t		color;
}	t_line;

typedef struct s_data
{
	t_line**	lines;
	uint8_t*	square;
	int*		points;
	int			total_pts;
	int			total_lines;
	int			m_iter;
}	t_data;

/*	Maths	*/

uint64_t	factorial(uint32_t num);
uint64_t	bino_coeff(uint32_t x, uint32_t y);

/*	Utilities	*/
void		print_lines(t_line** lines, int total_pts, int total_lines);
void 		print_bits(size_t num, size_t size);

/*	Solving	*/

bool		find_pattern(t_data* data, t_line** line, int x, int y);
bool		solve_square(t_line** square, int i, int permissions);
bool		check_single_square(uint8_t* square);

/*	Coloring	*/

int8_t		color_permission(t_line** square);
bool		check_coloring(t_data* data, t_line** lines, int a, int b, int c, int d);

#endif