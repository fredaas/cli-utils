#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

#define MODE_HEXIFY 1
#define MODE_HEXIFY_CONVERT 2
#define MODE_RADIX_CONVERT 3

int current_mode = -1;

/**
 * Checks if 'src' contains 'symbol'
 *
 * Returns 1 if true, 0 otherwise.
 */
int string_contains(char *src, char symbol)
{
    int i = 0;
    char c;
    while ((c = src[i++]) != '\0')
    {
        if (c == symbol)
            return 1;
    }
    return 0;
}

/**
 * Strips 'src' from any characters found in 'token'
 */
void string_strip(char *src, char *token)
{
    char string[256];
    strcpy(string, src);
    int size = strlen(string);
    if (!size)
        return;
    int j = size - 1;
    while (j >= 0 && string_contains(token, string[j]))
        j--;
    string[j + 1] = '\0';
    int i = 0;
    while (i < j && string_contains(token, string[i]))
        i++;
    strcpy(src, string + 1);
}


int hex2int(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A'  + 10;
    return -1;
}

char int2hex(int x)
{
    if (x >= 10 && x <= 15)
        return 'a' + x - 10;
    if (x >= 0 && x <= 9)
        return '0' + x;
    return '\0';
}

/* Check that 'value' has the correct decimal form, i.e. intenger and
   fractional part is separated by single '.' */
static inline void assert_decimal_form(char *value)
{
    int size = strlen(value);
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        printf("%c\n", value[i]);
        if (value[i] == '.')
        {
            if (count == 1)
            {
                fprintf(stderr, "[ERROR] Invaid decimal value\n");
                exit(1);
            }
            count++;
        }
    }
}

static inline void assert_radix_value(int radix)
{
    if (radix != 2 && radix != 16)
    {
        fprintf(stderr, "[ERROR] Invalid radix value\n");
        exit(1);
    }
}

static inline void assert_ascii_char(int c)
{
    if (c < 0 || c >= 256)
    {
        fprintf(stderr, "[ERROR] Invalid ASCII token\n");
        exit(1);
    }
}

static inline void assert_hex_char(char c)
{
    if (!(c >= '0' && c <= '9') ||
        !(c >= 'a' && c <= 'f') ||
        !(c >= 'A' && c <= 'F'))
    {
        fprintf(stderr, "[ERROR] Invalid HEX token\n");
        exit(1);
    }
}

uint32_t numbits(uint32_t b)
{
    uint32_t count = 0;
    while ((b >>= 1) > 0)
        count++;
    return count + 1;
}

/* Splits the string 'src' at 'token' and stores the result in 'dst'

   Note: Maximum fractional string length is 128.
 */
void strsplit(char values[][128], char *src, char *token)
{
    char string[256];
    /* Preserve 'src' pointer */
    strcpy(string, src);
    int i = 0;
    char *chunk = strtok(string, token);
    while (chunk != NULL)
    {
        strcpy(values[i++], chunk);
        chunk = strtok(NULL, token);
    }
    strcpy(values[i], "\0");
}

void print_hex2bin(char values[][128])
{
    for (int i = 0; i < 2; i++)
    {
        char *string = values[i];
        for (int j = 0; j < strlen(string); j++)
        {
            int x = hex2int(string[j]);
            int w = 4, n = 0;
            while (n++ < 4)
                printf("%d", (x >> (w - n)) & 1);
        }
        if (i == 0)
            printf(".");
        if (i == 1)
            printf("\n");
    }
}

int radix2int(char *value, int radix)
{
    assert_radix_value(radix);
    int x = 0; int n = strlen(value);
    switch (radix)
    {
    case 2:
        for (int i = 0; i < n; i++)
            x += (value[i] - '0') * pow(radix, n - i - 1);
        break;
    case 16:
        for (int i = 0; i < n; i++)
            x += hex2int(value[i]) * pow(radix, n - i - 1);
        break;
    }
    return x;
}

void print_bin2hex(char values[][128])
{
    for (int i = 0; i < 2; i++)
    {
        char *string = values[i];
        for (int j = 0; j < strlen(string); j += 4)
        {
            char chunk[5];
            strncpy(chunk, string + j, 4);
            chunk[4] = '\0';
            printf("%c", int2hex(radix2int(chunk, 2)));
        }
        if (i == 0)
            printf(".");
        if (i == 1)
            printf("\n");
    }
}

int main(int argc, char **argv)
{
    current_mode = atoi(argv[1]);

    char input_string[256];

    strcpy(input_string, argv[2]);

    assert_decimal_form(input_string);

    char values[2][128];
    strsplit(values, input_string, ".");

    for (int i = 0; i < 2; i++)
        printf("%s\n", values[i]);

    // print_hex2bin(values);
    print_bin2hex(values);

    // if (current_mode == MODE_RADIX_CONVERT)
    // {
    //     char value[256];
    //     strcpy(value, argv[2]);
    //     // string_strip(value, "\"");
    //     int radix0  = atoi(argv[3]);
    //     // int radix1  = atoi(argv[4]);

    //     uint32_t base = radix2base10(value, radix0);

    //     printf("%d\n", base);

    //     /* Convert to RADIX */
    // }

    // char value[256];
    // strcpy(value, argv[2]);
    // string_strip(value, "\"");

    // if (current_mode == MODE_HEXIFY)
    // {
    //     int i = 0; char c;
    //     while ((c = value[i++]) != '\0')
    //     {
    //         assert_ascii_char(c);
    //         int x = c >> 4;
    //         int y = c & 0xf;
    //         printf("%x%x", x, y);
    //     }
    //     printf("\n");
    // }

    // if (current_mode == MODE_HEXIFY_CONVERT)
    // {
    //     char *value = argv[2];
    //     int size = strlen(value);
    //     for (int i = 0; i < size; i += 2)
    //     {
    //         int x = hex2int(value[i]);
    //         int y = hex2int(value[i + 1]);
    //         int c = x << 4 | y;
    //         assert_hex_char(c);
    //         printf("%c", c);
    //     }
    //     printf("\n");
    // }

    return 0;
}
