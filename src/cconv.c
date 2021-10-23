#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/* Returns returns the 'n'-base logarithm of 'value'
 */
#define log(value, n) (log2(value) / log2(n))

int RADIX;

int MAX_U; /* Upper bound */
int MAX_L; /* Lower bound */

int U;    /* LHS of float. */
double L; /* RHS of float. */

enum {
    BINARY = 2,
    OCTAL  = 8,
    DEC    = 10,
    HEX    = 16,
};

static inline void fsplit(int *a, double *b, double value)
{
    double x, y;
    y = modf(value, &x);
    if (a != NULL)
        *a = x;
    if (b != NULL)
        *b = y;
}

static inline void print_values(int *values)
{
    for (int i = 0; i < MAX_U + MAX_L; i++)
    {
        int value = values[i];

        if (i == MAX_U)
            printf(".");

        if (RADIX == HEX)
        {
            if (value < 10)
                printf("%d", value);
            else
                printf("%c", 'F' - (15 - value));
        }
        else
        {
            printf("%d", value);
        }
    }

    printf("\n");
}

static inline void convert_values(int *values)
{
    for (int i = MAX_U - 1; i >= 0; i--)
    {
        values[i] = U % RADIX;
        U /= RADIX;
    }
    for (int i = MAX_U; i < MAX_U + MAX_L; i++)
    {
        L *= RADIX;
        fsplit(&U, &L, L);
        values[i] = U;
    }
}

int main(int argc, char **argv)
{
    argc--;

    if (argc < 2 || argc > 3)
    {
        printf("Usage:\n\n    cradix <value> <radix> [<decimal precision>]\n\n"
        );
        exit(1);
    }

    fsplit(&U, &L, atof(argv[1]));
    RADIX = atoi(argv[2]);
    MAX_U = (int)log(U, RADIX) + 1;

    if (argc == 3)
        MAX_L = atoi(argv[3]);

    int values[MAX_U + MAX_L];

    convert_values(values);
    print_values(values);

    return EXIT_SUCCESS;
}
