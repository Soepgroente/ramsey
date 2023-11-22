#include "cubing.h"

char	*ft_itoa(int n)
{
	char	*res;
	int	x = n; int	count = 0;

	res = calloc(8, sizeof(char));
	if (res == NULL)
		exit(EXIT_FAILURE);
	if (n == 0)
	{
		res[0] = '0';
		res[1] = ' ';
		return (res);
	}
	while (x > 0)
	{
		x /= 10;
		count++;
	}
	x = n;
	res[count] = ' ';
	while (x > 0)
	{
		count--;
		res[count] = x % 10 + '0';
		x /= 10;
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;

	if (!s1 || !s2)
		exit(EXIT_FAILURE);
	i = strlen(s1);
	s3 = calloc((i + strlen(s2) + 1), sizeof(char));
	if (!s3)
		exit(EXIT_FAILURE);
	strcpy(s3, s1);
	strcpy(&s3[i], s2);
	free(s1);
	free(s2);
	return (s3);
}

void	print_lines(t_line** lines, int total_pts, int total_lines)
{
	int i = 0; int line = 0;
	FILE*	file;

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
			fprintf(file, "A: %d	B: %d	", lines[i][x].a, lines[i][x].b);
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

void	print_square(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
	size_t	size;
	int		len;
	char*	square;
	char*	buffer;
	FILE*	file;

	order_points(&a, &b, &c, &d);
	// printf("Expect: %d %d %d %d\n", a, b, c, d);
	file = fopen("squares.txt", "r");
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	square = ft_strjoin(ft_itoa(a), ft_itoa(b));
	square = ft_strjoin(square, ft_itoa(c));
	square = ft_strjoin(square, ft_itoa(d));
	len = strlen(square);
	// square = realloc(square, len + 1);
	square[len - 1] = '\0';
	// len++;
	buffer = malloc((size + 1) * sizeof(char));
	buffer[size] = '\0';
	fread(buffer, size, sizeof(char), file);
	fclose(file);
	if (strstr(buffer, square) == NULL)
	{
		file = fopen("squares.txt", "a+");
		fprintf(file, "%d %d %d %d\n", a, b, c, d);
		fclose(file);
	}
	free(buffer);
	free(square);
}

void print_bits(size_t num, size_t size)
{
	size_t i;

	size *= 8;
	for (i = 1; i <= size; i++)
	{
		printf("%d", (num & (1 << (size - i))) ? 1 : 0);
    }
    printf("\n");
}
