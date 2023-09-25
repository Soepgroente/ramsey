#ifndef CUBING_H
#define CUBING_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <malloc/malloc.h>

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
	t_line*		lines;
	t_line		tmp[6];
	int*		points;
	int			total_pts;
	int			total_lines;
}	t_data;

uint64_t	factorial(uint32_t num);
uint64_t	bino_coeff(uint32_t x, uint32_t y);
void		print_lines(t_line* lines, int total_lines);

#endif