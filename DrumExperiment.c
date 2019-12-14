#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
* Defines the maximum line length.
*/
#define MAX_LINE_SIZE 1024
/**
 * Defines the maximum line length.
 */
#define MAX_INPUT_SIZE 100
/**
 * Defines the delimeters used to separate the input.
 */
#define INPUT_DELIMS " \t\r\n"
/**
 * Defines the valid characters for rational number.
 */
#define RATIONAL_VALID_CHARS "0123456789."
/**
 * Defines the valid characters for natural number.
 */
#define NATURAL_VALID_CHARS "0123456789"
/**
 * Defines a function that calculate the parameter needed to convert a string to a double.
 */
#define DOUBLE_PARAMETER(x) (1.0/x)
/**
 * Defines a function that calculate the floor of the half of the given x.
 */
#define HALF_FLOOR(x) (floor(x/2.0))
/**
 * Defines a function that calculate the ceiling of the half of the given x.
 */
#define HALF_CEIL(x) (ceil(x/2.0))

/**
 * Defines the maximum double length.
 */
const int MAX_DOUBLE_LENGTH = 9;
/**
 * Defines an initializing value.
 */
const int INITIALIZE_VAL = 0;
/**
 * Defines a constant of no-values.
 */
const int NO_VALUES = 0;
/**
 * Defines the parameter to convert a string to an int.
 */
const int INT_PARAM = 1;
/**
 * Defines the increasing factor of the parameter (to convert a string to an int).
 */
const int INCREASING_FACTOR = 10;
/**
 * Defines a constant of one character.
 */
const int ONE_CHAR = 1;
/**
 * Defines a constant of first value index.
 */
const int FIRST_VAL = 0;
/**
 * Defines a constant of second value index.
 */
const int SECOND_VAL = 1;
/**
 * Defines a constant the modulu calculation.
 */
const int MOD_CONST = 2;
/**
 * Defines a failure constant.
 */
const int FAILURE = -1;
/**
 * Defines constant of the round calculation.
 */
const int ROUND_CONST = 1000;
/**
 * Defines the number of stars that will be printed for the maximum value.
 */
const int STARS_FOR_MAX = 20;
/**
 * Defines a constant that if the maximum will be bigger than it, the program won't print anything.
 */
const double EPSILON = 0.00000001;
/**
 * Defines a zero character.
 */
const char ZERO_CHAR = '0';
/**
 * Defines a dot character.
 */
const char DOT = '.';
/**
 * Defines a star character.
 */
const char STAR = '*';

/**
 * Converting a string to an int, assuming that the input string is legal.
 * @param str String to convert.
 * @param length the length of the given string.
 * @return The int that fit the given string.
 */
int stringToInt(const char *str, long length)
{
    int result = INITIALIZE_VAL;
    int parameter = INT_PARAM;
    for (long i = length - 1; i >= 0; i--)
    {
        int x = str[i] - ZERO_CHAR;
        result += x * parameter;
        parameter *= INCREASING_FACTOR;
    }
    return result;
}

/**
 * Converting a string to a double, assuming that the input string is legal.
 * @param str String to convert.
 * @param length the length of the given string (including the dot).
 * @return The double that fit the given string.
 */
double stringToDouble(const char *str, long length)
{
    double result = INITIALIZE_VAL;
    int dot_index = INITIALIZE_VAL;
    while (str[dot_index] != DOT && dot_index != length)
    {
        dot_index++;
    }
    result += stringToInt(str, dot_index);
    int parameter = INCREASING_FACTOR;
    for (long i = dot_index + 1; i < length; i++)
    {
        int x = str[i] - ZERO_CHAR;
        result += x * DOUBLE_PARAMETER(parameter);
        parameter *= INCREASING_FACTOR;
    }
    return result;
}

/**
 * Checks if the given string can be converted to a legal rational number - double.
 * @param str String to check.
 * @param length The length of the given string.
 * @return EXIT_FAILURE if the input is not legal, and EXIT_SUCCESS otherwise.
 */
int checkRationalNum(const char *str, long length)
{
    int dot_count = INITIALIZE_VAL;
    if (length > MAX_DOUBLE_LENGTH ||
        (str[FIRST_VAL] == ZERO_CHAR && length > ONE_CHAR && str[SECOND_VAL] != DOT))
    {
        return EXIT_FAILURE;
    }
    for (long i = INITIALIZE_VAL; i < length; i++)
    {
        if (!strchr(RATIONAL_VALID_CHARS, str[i]))
        {
            return EXIT_FAILURE;
        }
        if (str[i] == DOT)
        {
            dot_count++;
            if (dot_count > ONE_CHAR || i == length - 1)
            {
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

/**
 * Checks if the given string can be converted to a legal natural number - int.
 * @param str String to check.
 * @param length The length of the given string.
 * @return EXIT_FAILURE if the input is not legal, and EXIT_SUCCESS otherwise.
 */
int checkNaturalNum(const char *str, long length)
{
    if (str[FIRST_VAL] == ZERO_CHAR && length > ONE_CHAR)
    {
        return EXIT_FAILURE;
    }
    for (long i = INITIALIZE_VAL; i < length; i++)
    {
        if (!strchr(NATURAL_VALID_CHARS, str[i]))
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * Get an array input from the user. If the input is legal, it will convert it to a double array.
 * @param input_arr An empty arr with the size of the maximum input the user allowed to put.
 * @return The length of the input array if it was legal, -1 otherwise.
 */
int readUserArrInput(double *input_arr)
{
    char line[MAX_LINE_SIZE];
    char *value = NULL;
    if (fgets(line, MAX_LINE_SIZE, stdin) == NULL)
    {
        return FAILURE;
    }
    value = strtok(line, INPUT_DELIMS);
    int i = INITIALIZE_VAL;
    while (value != NULL && i < MAX_INPUT_SIZE)
    {
        size_t length = strlen(value);
        if (checkRationalNum(value, length) == EXIT_FAILURE)
        {
            return FAILURE;
        }
        input_arr[i] = stringToDouble(value, length);
        value = strtok(NULL, INPUT_DELIMS);
        i++;
    }
    if (i == NO_VALUES || (value != NULL && i >= MAX_INPUT_SIZE))
    {
        return FAILURE;
    }
    return i;
}

/**
 * Get an input from the user. If the input is a legal natural number, it will convert it to an int.
 * @return The int the user put if it was legal, -1 otherwise.
 */
int readUserNumInput()
{
    char line[MAX_LINE_SIZE];
    char *value = NULL;
    if (fgets(line, MAX_LINE_SIZE, stdin) == NULL)
    {
        return FAILURE;
    }
    for (unsigned long i = INITIALIZE_VAL; i < strlen(line) - 1; i++)
    {
        if (strchr(INPUT_DELIMS, line[i]))
        {
            return FAILURE;
        }
    }
    value = strtok(line, INPUT_DELIMS);
    if (value == NULL)
    {
        return FAILURE;
    }
    size_t length = strlen(value);
    if (checkNaturalNum(value, length) == EXIT_FAILURE)
    {
        return FAILURE;
    }
    return stringToInt(value, length);
}

/**
 * Normalize the given array.
 * @param arr A pointer to the array.
 * @param length The length of the given array.
 */
void normalizeArr(double *arr, int length)
{
    double sum = INITIALIZE_VAL;
    for (int i = INITIALIZE_VAL; i < length; i++)
    {
        sum += arr[i];
    }
    for (int i = INITIALIZE_VAL; i < length; i++)
    {
        arr[i] /= sum;
    }
}

/**
 * Centralize the given array.
 * @param arr A pointer to the array.
 * @param length The length of the given array.
 */
void centralizeArr(double *arr, int length)
{
    int center = HALF_FLOOR(MAX_INPUT_SIZE);
    int half_length = HALF_FLOOR(length);
    int last_idx = center + half_length - 1;
    if (last_idx == length - 1)
    {
        return;
    }
    for (int i = length - 1; i >= 0; i--)
    {
        arr[last_idx] = arr[i];
        arr[i] = INITIALIZE_VAL;
        last_idx--;
    }
}

/**
 * @param t Int to parameterize.
 * @return The parameterization of t.
 */
int param(int t)
{
    int floor_center = HALF_FLOOR(MAX_INPUT_SIZE);
    return t + floor_center;
}

/**
 * Calculating the convolution between g and h, and put the result into the given conv_arr.
 * @param g_arr A pointer to g array.
 * @param h_arr A pointer to h array.
 * @param conv_arr A pointer to the result array.
 */
void singleConvolution(const double *g_arr, const double *h_arr, double *conv_arr)
{
    double sum;
    int g_idx, h_idx;
    int ceil_center = HALF_CEIL(MAX_INPUT_SIZE);
    int floor_center = HALF_FLOOR(MAX_INPUT_SIZE);
    for (int t = - ceil_center - 1; t < floor_center - 1; t++)
    {
        sum = INITIALIZE_VAL;
        for (int m = - ceil_center; m <= floor_center; m++)
        {
            g_idx = param(t - m);
            h_idx = param(m);
            if (FIRST_VAL <= g_idx && g_idx < MAX_INPUT_SIZE &&
                FIRST_VAL <= h_idx && h_idx < MAX_INPUT_SIZE)
            {
                sum += g_arr[g_idx] * h_arr[h_idx];
            }
        }
        conv_arr[param(t) + 1] = sum;
    }
    normalizeArr(conv_arr, MAX_INPUT_SIZE);
}

/**
 * Calculationg the convolution n times of g with h.
 * @param g_arr A pointer to g array.
 * @param h_arr A pointer to h array.
 * @param conv_arr A pointer to the result array.
 * @param n The times that left to do the convolution.
 * @param original_n The original times to do the convolution.
 * @return 0 if the result is in g_arr, 1 if the result will be in conv_arr.
 */
int convolution(double *g_arr, double *h_arr, double *conv_arr,  int n, int original_n)
{
    if (n == 0)
    {
        return original_n % MOD_CONST;
        // if it returns 0 - the result will be in g_arr, if it returns 1 - it will be in conv_arr.
    }
    singleConvolution(g_arr, h_arr, conv_arr);
    return convolution(conv_arr, h_arr, g_arr, n - 1, original_n);
}

/**
 * Round the values in the given array.
 * @param arr A pointer to the array.
 * @param length The length of the given array.
 */
void roundArr(double *arr, int length)
{
    for (int i = INITIALIZE_VAL; i < length; i++)
    {
        arr[i] = round(arr[i] * ROUND_CONST) / ROUND_CONST;
    }
}

/**
 * Finds the maximum value in the given array.
 * @param arr A pointer to the array.
 * @param length The length of the given array.
 * @return The maximum value.
 */
double findMax(const double *arr, int length)
{
    double max = INITIALIZE_VAL;
    for (int i = INITIALIZE_VAL; i < length; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

/**
 * Prints the histogram of the given array. For each value it will print it's value and the fitted
 * number of stars.
 * @param arr A pointer to the array.
 */
void histogram(double *arr)
{
    roundArr(arr, MAX_INPUT_SIZE);
    double max = findMax(arr, MAX_INPUT_SIZE);
    if (max > EPSILON)
    {
        for (int i = INITIALIZE_VAL; i < MAX_INPUT_SIZE; i++)
        {
            int numOfStars = floor((arr[i] / max) * STARS_FOR_MAX);
            printf("%0.3f: ", arr[i]);
            for (int j = INITIALIZE_VAL; j < numOfStars; j++, putchar(STAR));
            printf("\n");
        }
    }
}

/**
 * Prints error massage.
 * @return EXIT_FAILURE value.
 */
int error()
{
    fprintf(stderr, "ERROR\n");
    return EXIT_FAILURE;
}

/**
 * Runs the whole program.
 * @return 0 if the run was successful, EXIT_FAILURE otherwise.
 */
int main()
{
    double g_arr[MAX_INPUT_SIZE] = {INITIALIZE_VAL};
    int g_len = readUserArrInput(g_arr);
    if (g_len == FAILURE)
    {
        return error();
    }
    double h_arr[MAX_INPUT_SIZE] = {INITIALIZE_VAL};
    int h_len = readUserArrInput(h_arr);
    if (h_len == FAILURE || h_len > g_len)
    {
        return error();
    }
    int n = readUserNumInput();
    if (n == FAILURE)
    {
        return error();
    }
    normalizeArr(g_arr, g_len);
    centralizeArr(g_arr, g_len);
    normalizeArr(h_arr, h_len);
    centralizeArr(h_arr, h_len);
    double conv_arr[MAX_INPUT_SIZE] = {INITIALIZE_VAL};
    int res = convolution(g_arr, h_arr, conv_arr, n, n);
    if (res == 0)
    {
        histogram(g_arr);
    }
    else
    {
        histogram(conv_arr);
    }
    return 0;
}
