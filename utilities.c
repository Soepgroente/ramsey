#include "cubing.h"

void	print_lines(t_line** lines, int total_pts, int total_lines)
{
	int i = 0; int line = 0;
	FILE	*file;

	file = fopen("result.txt", "w");
	if (file == NULL)
	{
		puts("Error opening file");
		exit(1);
	}
	while (line < total_lines)
	{
		for (int x = 0; x < total_pts - i - 1; x++)
		{
			fprintf(file, "Line[%d]:	", line);
			fprintf(file, "A: %d	B: %d	", lines[i][x].point_a, lines[i][x].point_b);
			if (lines[i][x].color == RED)
			{
				// fprintf(file, "\033[1;31m");
				fprintf(file, "RED\n");
				// fprintf(file, "\033[0m");
			}
			else if (lines[i][x].color == BLUE)
			{
				// fprintf(file, "\033[034m");
				fprintf(file, "BLUE\n");
				// fprintf(file, "\033[0m");
			}
			else
				fprintf(file, "UNCOLORED\n");
			line++;
		}
		i++;
	}
	fclose(file);
}

void print_bits(size_t num, size_t size)
{
	size_t i;

	size *= 8;
	for (i = 0; i < size; i++)
	{
		printf("%d", (num & (1 << i)) ? 1 : 0);
    }
    printf("\n");
}