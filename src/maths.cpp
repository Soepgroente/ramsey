#include "ramsey.hpp"

i64	factorial(ui16 num)
{
	i64	res = 1;

	if (num == 0)
		return (0);
	while (num > 0)
	{
		if (num * res > INT64_MAX)
			return (-1);
		res *= num;
		num--;
	}
	return (res);
}

i64	binomial_coefficient(ui16 x, ui16 y)
{
	i64 res = 1;
	ui16 tmp = x - y;

	if (y > x)
		return (-1);
	if (y == 1)
		return (x);
	if (y == 0)
		return (1);
	while (x > tmp)
	{
		res *= x;
		x--;
		while (y > 1 && res % y == 0)
		{
			res /= y;
			y--;
		}
	}
	return (res);
}
