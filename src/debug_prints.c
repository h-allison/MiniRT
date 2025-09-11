
#include "minirt.h"

void	print_tuple(char *str, t_tuple a)
{
	printf("%s x = %f ", str, a.x);
	printf("y = %f ", a.y);
	printf("z = %f ", a.z);
	printf("w = %f", a.w);
	if (a.w == 0)
		printf("  > is a vector\n");
	else if (a.w == 1)
		printf("  > is a point\n");
	else
		printf("\n");
}

void	print_vector(char *str, t_tuple a)
{
	if (a.w == 1)
		printf("ERROR. Not a vector\n");
	else
	{
		printf("%s x = %f ", str, a.x);
		printf("y = %f ", a.y);
		printf("z = %f ", a.z);
		printf("w = %f", a.w);
	}
}
