#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
PROBLEM 6
a. Read a sequence of natural numbers (sequence ended by 0) and determine the number of 0 digits of the product
   of the read numbers.
b. Given a vector of numbers, find the longest contiguous subsequence such that the sum of any two consecutive elements
   is a prime number.
*/

void print_menu()
{
    // this function prints the options from the menu
    printf("Choose between these options:\n");
    printf("1. Read a sequence of natural numbers (sequence ended by 0) and determine the number of 0 digits of the product of the read numbers.\n");
    printf("2. Given a vector of numbers, find the longest contiguous subsequence such that the sum of any two consecutive elements is a prime number.\n");
    printf("3. Exit\n");
}

typedef struct
{
    int array[101], lenght;
}Vector;

// function a

Vector read_until_zero()
{
    // this function reads the elements of the vector until we encounter a 0 (not included in the vector).
    // return: the final vector we aquired
    int value;
    Vector v;
    v.lenght = 0;
    printf("give values\n");
    scanf("%d", &value);
    while (value)
    {
        v.array[v.lenght] = value;
        v.lenght++;
        scanf("%d", &value);
    }
    return v;
}

int return_product(Vector v)
{
    // this function computes the product of the elements of a vector
    // return: the product we computed
    int product = 1;
    for (int i = 0; i < v.lenght; i++)
        product = product * v.array[i];
    return product;
}

int return_nr_of_0_digits(int value)
{
    // this function computes the number of 0 digits of a value
    // return: the nr of 0 digits
    int counter = 0;
    while (value)
    {
        if (value % 10 == 0)
            counter++;
        value = value / 10;
    }
    return counter;
}

// function b

Vector read_normal_vector()
{
    // this function reads the elements of a vector, knowing the lenght of it.
    // return: the final vector
    Vector v;
    printf("give the lenght of the vector\n");
    scanf("%d", &v.lenght);
    printf("give values\n");
    for (int i = 0; i < v.lenght; i++)
        scanf("%d", &v.array[i]);
    return v;
}

int is_prime(int number)
{
    // this function verifies whether a number is prime or not
    // return: 1 if the number is prime, 0 otherwise
    int i = 2;
    while (i <= number / 2)
    {
        if (number % i == 0)
            return 0;
        i++;
    }
    return 1;
}

void longest_subsequence_prime_sum(Vector v, int* start, int* lenght)
{
    // this function finds the start and the lenght of the longest sequence of cosecutive elements whose sum is a prime number
    int current_start = 0, current_lenght = 0, final_start = 0, max_lenght = 0, sum;
    for (int i = 0; i < v.lenght - 1; i++)
    {
        sum = v.array[i] + v.array[i + 1];
        if (is_prime(sum) == 1)
            current_lenght++;
        else
        {
            if (current_lenght > max_lenght)
            {
                max_lenght = current_lenght;
                final_start = current_start;
            }
            current_lenght = 0;
            current_start = i + 1;
        }
    }
    if (current_lenght > max_lenght)
    {
        max_lenght = current_lenght;
        final_start = current_start;
    }
    *start = final_start;
    *lenght = max_lenght + 1;
}

void print_sequence(Vector v, int start, int lenght)
{
    // this function prints a subsequence of a vector knowing the start and lenght of it
    int i = start;
    for (int j = 1; j <= lenght; j++)
    {
        printf("%d ", v.array[i]);
        i++;
    }
    printf("\n");
}

int main()
{
    int option, not_finished = 1;
    while (not_finished == 1)
    {
        print_menu();
        printf("\nGive option\n>");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            int nr_of_0_digits, product;
            Vector v = read_until_zero();
            product = return_product(v);
            nr_of_0_digits = return_nr_of_0_digits(product);
            printf("The number of 0 digits of the product: %d\n", nr_of_0_digits);
            break;
        case 2:
            Vector v2 = read_normal_vector();
            int start, lenght;
            longest_subsequence_prime_sum(v2, &start, &lenght);
            printf("The longest subsequence is: ");
            print_sequence(v2, start, lenght);
            break;
        case 3:
            printf("you're finshed :))\n");
            not_finished = 0;
            break;
        default:
            printf("wrong input");
            break;
        }
    }
    return 0;
}