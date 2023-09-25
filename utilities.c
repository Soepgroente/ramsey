#include "cubing.h"

void	print_lines(t_line* lines, int total_lines)
{
	int i = 0;
	FILE	*file;

	file = fopen("result.txt", "w");
	if (file == NULL)
	{
		puts("Error opening file");
		exit(1);
	}
	while (i < total_lines)
	{
		fprintf(file, "Line[%d]:	", i + 1);
		fprintf(file, "A: %d	B: %d	", lines[i].point_a, lines[i].point_b);
		if (lines[i].color == RED)
			fprintf(file, "RED\n");
		else if (lines[i].color == BLUE)
			fprintf(file, "BLUE\n");
		else
			fprintf(file, "UNCOLORED\n");
		i++;
	}
}