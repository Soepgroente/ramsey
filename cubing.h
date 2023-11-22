#ifndef CUBING_H
#define CUBING_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <malloc/malloc.h>
# include <string.h>
# include <time.h>

extern int dimensions;

typedef enum s_color
{
	RED,
	BLUE,
	UNCOLORED
}	t_coloring;

typedef struct s_line	t_line;
typedef struct s_square	t_square;

struct s_square
{
	// uint64_t	abcd;
	t_line*		lines[6];
	// uint16_t	a;
	// uint16_t	b;
	// uint16_t	c;
	// uint16_t	d;
};

struct s_line
{
	uint16_t	a;
	uint16_t	b;
	uint8_t		color;
};

typedef struct s_data
{
	t_line**	lines;
	t_square**	squares;
	int*		points;
	int			total_pts;
	int			total_lines;
	int			sq_per_num;
	int			m_iter;
}	t_data;

/*	Initialize	*/

t_square**	allocate_squarray(int size);
void		initialize_stuff(t_data* data);

/*	Maths	*/

uint64_t	factorial(uint32_t num);
uint64_t	bino_coeff(uint32_t x, uint32_t y);
int			greatest_common_divisor(int a, int b);
int			smallest_prime_factor(int a, int b);

/*	Utilities	*/

void		print_lines(t_line** lines, int total_pts, int total_lines);
void		print_square(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
void 		print_bits(size_t num, size_t size);

/*	Solving	*/

bool		find_pattern(t_data* data, t_line** line, int x, int y);
int32_t		find_4th_point(uint16_t total, uint16_t a, uint16_t b, uint16_t c);
// bool		solve_square(t_line** square, int i, int permissions);
bool		check_single_square(t_square* square);
void		find_squares(t_data* data, t_square** squares, t_line line);

/*	Coloring	*/

// int8_t		color_permission(t_line** square);
bool		check_coloring(t_square* square, t_line** lines, uint16_t a, uint16_t b, uint16_t c, uint16_t d);
void		order_points(uint16_t* a, uint16_t* b, uint16_t* c, uint16_t* d);

#endif