#include "cubing.h"

int	dimensions;

int main(int argc, char** argv)
{
	t_data	data;
	clock_t	start;
	clock_t	end;

	if (argc != 2)
		return (1);
	dimensions = atoi(argv[1]);
	if (dimensions < 2)
		return (2);
	initialize_stuff(&data);
	// FILE* fp = fopen("squares.txt", "w+");
	// fclose(fp);
	start = clock();
	find_pattern(&data, data.lines, 0, 0);
	end = clock();
	// print_lines(data.lines, data.total_pts, data.total_lines);
	printf("Runtime: %.2ld seconds\n", (long double)(end - start) / CLOCKS_PER_SEC);
}