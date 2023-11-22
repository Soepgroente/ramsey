#include "cubing.h"

void	free_squarray(t_square** squares)
{
	int	i = 0;

	while (squares[i] != NULL)
	{
		free(squares[i]->lines);
		i++;
	}
	free(squares);
}