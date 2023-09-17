#ifndef RAMSEY_H
#define RAMSEY_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <malloc/malloc.h>

#define UNCOLORED 0
#define RED 1
#define BLUE 2

extern int dimensions;

typedef struct s_point
{
	struct t_line	*lines;
	uint16_t		num;
}	t_point;

typedef struct s_line
{
	uint32_t	points;
	uint8_t		color;
	uint8_t		plane;
}	t_line;

uint64_t	factorial(uint32_t num);
uint64_t	bino_coeff(uint32_t x, uint32_t y);

#endif