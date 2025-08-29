#include "minirt.h"

void    print_matrix(float **m, int size);
void    fill_matrix(float **m, int size, float steps);
static void print_tuple(char *str, t_tuple a); 

int	main(void)
{
	t_tuple point;
	float  **transform;
	t_tuple	target;

	point = create_point(-3, 4, 5);
	transform = translation(5, -3, 2);
	target = tmatrixmult(transform, point);
	printf("Translation matrix:\n");
	print_matrix(transform, 4);
	free_matrix(transform, 4);
	print_tuple("Source: ", point);
	print_tuple("Target: ", target);
	printf("\n");

	//

	float **inv;

	point = create_point(-3, 4, 5);
	transform = translation(5, -3, 2);
	inv = minvert(transform, 4);
	target = tmatrixmult(inv, point);
	free_matrix(transform, 4);
	print_tuple("source: ", point);
	print_tuple("target: ", target);

	// testing with vector

	t_tuple vector;

	printf("\n Now with a vector...\n");
    vector = create_vector(-3, 4, 5);
    transform = translation(5, -3, 2); 
    target = tmatrixmult(transform, vector);
    print_tuple("Source: ", vector);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");

	// scaling

	printf("\nSCALING a point\n");
    point = create_point(-4, 6, 8);
    transform = scaling(2, 3, 4); 
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");

	printf("\nSCALING a vector\n");
    vector = create_vector(-4, 6, 8);
    transform = scaling(2, 3, 4); 
    target = tmatrixmult(transform, vector);
    print_tuple("Source: ", vector);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");
	
	printf("\nSCALING point with inverse\n");
    vector = create_vector(-4, 6, 8);
    transform = scaling(2, 3, 4); 
	inv = minvert(transform, 4);
    target = tmatrixmult(inv, vector);
    printf("\ntransform:\n");
	print_matrix(transform, 4);
    printf("\ninverted transform:\n");
	print_matrix(inv, 4);
    print_tuple("\nSource: ", vector);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
	free_matrix(inv, 4);
    printf("\n");

	printf("\nREFLECTING a point\n");
    point = create_point(2, 3, 4);
    transform = scaling(-1, 1, 1); 
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");

	// rotating

	printf("\nROTATING a point around x, half quarter\n");
    point = create_point(0, 1, 0);
    transform = rotation_x(M_PI / 4); 
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");
	
	printf("ROTATING a point around x, full quarter\n");
    point = create_point(0, 1, 0);
    transform = rotation_x(M_PI / 2); 
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");
	
	printf("ROTATING a point around x, half quarter, opposite dir (inv)\n");
    point = create_point(0, 1, 0);
    transform = rotation_x(M_PI / 4); 
	inv = minvert(transform, 4);
    target = tmatrixmult(inv, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
	free_matrix(inv, 4);
    printf("\n");
	
	printf("\nROTATING a point around y, half quarter\n");
    point = create_point(0, 0, 1);
    transform = rotation_y(M_PI / 4); 
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");
	
	printf("\nROTATING a point around z, full quarter\n");
    point = create_point(0, 1, 0);
    transform = rotation_z(M_PI / 2); 
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
    printf("\n");
	
	printf("\nSHEARING x in proportion to z\n");
    point = create_point(2, 3, 4);
	static float	s[6];
	s[1] = 1;
    transform = shearing(s);
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
	s[1] = 0;
    printf("\n");
	
	printf("SHEARING y in proportion to x\n");
    point = create_point(2, 3, 4);
	s[2] = 1;
    transform = shearing(s);
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
	s[2] = 0;
    printf("\n");
	
	printf("SHEARING y in proportion to z\n");
    point = create_point(2, 3, 4);
	s[3] = 1;
    transform = shearing(s);
    target = tmatrixmult(transform, point);
    print_tuple("Source: ", point);
    print_tuple("Target: ", target);
	free_matrix(transform, 4);
	s[3] = 0;
    printf("\n");

	float	**ta;
	float	**tb;
	float	**tc;

	printf("CHAINING TRANSFORMS\n");
    point = create_point(1, 0, 1);
    ta = rotation_x(M_PI / 2);
	tb = scaling(5, 5, 5);
	tc = translation(10, 5, 7);
    print_tuple("Source: ", point);
	point = tmatrixmult(ta, point);
    print_tuple("Target: ", point);
	point = tmatrixmult(tb, point);
    print_tuple("Target: ", point);
	point = tmatrixmult(tc, point);
    print_tuple("Target: ", point);
	free_matrix(ta, 4);
	free_matrix(tb, 4);
	free_matrix(tc, 4);
    printf("\n");
	
	printf("COMBINING TRANSFORMS\n");
    point = create_point(1, 0, 1);
    ta = rotation_x(M_PI / 2);
	tb = scaling(5, 5, 5);
	tc = translation(10, 5, 7);
	transform = matrixmult(tc, tb);
	transform = matrixmult(transform, ta);
	point = tmatrixmult(transform, point);
    print_tuple("Target: ", point);
	free_matrix(ta, 4);
	free_matrix(tb, 4);
	free_matrix(tc, 4);
	free_matrix(transform, 4);
    printf("\n");	
}

void    fill_matrix(float **m, int size, float steps)
{
    int     i;
    int     j;
    float   fill;

    i = 0;
    fill = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            m[i][j++] = fill;
            fill += steps;
        }
        i++;
    }
}

void    print_matrix(float **m, int size)
{
    int x;
    int y;

    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
            printf("%f ", m[y][x++]);
        printf("\n");
        y++;
    }
}

static void print_tuple(char *str, t_tuple a)
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
