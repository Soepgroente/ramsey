#include "cubing.h"

int	greatest_common_divisor(int a, int b)
{
	// while(b ^= a ^= b ^= a %= b)
	// 	;
    while (a != 0 && b != 0)
	{
		printf("a: %d, b: %d\n", a, b);
		b = b ^ a;
		a = a ^ b;
		b = b ^ a;
		b = a % b;
	}
    return (a); 
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
