#include "cubing.h"

static void	find_other_point(t_data* data, t_line* line)
{
	
}

static bool	check_config(t_data* data, t_line* line)
{
	int i = 1;
	int	a;
	int	b;
	int	c;
	int	d;

	while (i <= dimensions)
	{

	}
}

bool	find_pattern(t_data* data, t_line* line)
{
	static int i = 0;

	while (i < data->total_lines)
	{
		for (int x = RED; x <= BLUE; x++)
		{
			if (line[i].color == UNCOLORED)
			{
				line[i].color = x;
				i++;
				if (check_config() == true)
				{
					find_pattern(data, line);
				}
			}
		}
	}
}