#include "cubing.h"

int	greatest_common_divisor(int a, int b)
{
	while (b != 0)
	{
		a = a % b;
		b ^= a;
		a ^= b;
		b ^= a;
	}
	return (a);
}

int	smallest_prime_factor(int a, int b)
{
	int	x; int success = 0;

	if (a == 0 || b == 0)
	{
		puts("Dividing by zero, are you insane!?");
		return (0);
	}
	if (a < b)
	{
		b ^= a;
		a ^= b;
		b ^= a;
	}
	x = b;
	while (x > 1)
	{
		if (a % x == 0 && b % x == 0)
			success = x;
		x--;
	}
	return (success);
}

uint64_t	factorial(uint32_t num)
{
	uint64_t	res;

	res = 1;
	while (num > 1)
	{
		res *= num;
		num--;
	}
	return (res);
}

uint64_t	bino_coeff(uint32_t x, uint32_t y)
{
	uint64_t res = 1;
	uint32_t i = 1;
	uint32_t tmp = x - y;

	while (x > tmp)
	{
		res *= x;
		if (i <= y)
		{
			res /= i;
			i++;
		}
		x--;
	}
	return (res);
}
