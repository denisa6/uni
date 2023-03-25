#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
PROBLEM 1
a. Generate all the prime numbers smaller than a given natural number n.
b. Given a vector of numbers, find the longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number.
*/

void print_menu()
{
    // this function prints the options from the menu
    printf("Choose between these options:\n");
    printf("1. Generate all the prime numbers smaller than a given natural number n.\n");
    printf("2. Given a vector of numbers, find the longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number\n");
    printf("3. Exit\n");
}

typedef struct
{
    int array[101], lenght;
}Vector;

int closest_prime(int n) {
    // this function finds the closest prime number to n
    // param value = the number we base our search on
    // return the closest prime number
    if (is_prime(n) == 1)
        return n;
    int smaller, bigger;
    smaller = n--;
    bigger = n++;
    int found = 1;
    while (found) {
        if (is_prime(smaller) == 1)
            return smaller;
        else
            smaller--;
        if (is_prime(bigger) == 1)
            return bigger;
        else
            bigger++;
    }
}


// function a
Vector prime_smaller_than(int number) {
    // this function returns an array of prime numbers smaller than n
    // return: the vector containing the prime numbers required
    Vector v;
    v.lenght = 0;
    for (int i = 2; i < number; i++) {
        if (is_prime(i) == 1) {
            v.array[v.lenght] = i;
            v.lenght++;
        }
    }
    return v;
}


// function b
Vector read_normal_vector()
{
    // this function reads the elements of a vector, knowing the lenght of it.
    // return: the final vector
    Vector v;
    printf("give the lenght of the vector\n");
    scanf_s("%d", &v.lenght);
    printf("give values\n");
    for (int i = 0; i < v.lenght; i++)
        scanf_s("%d", &v.array[i]);
    return v;
}

int is_prime(int number)
{
    // this function verifies whether a number is prime or not
    // param value = the number to be checked
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

void longest_inc_subsequence_prime_sum(Vector v, int* start, int* lenght)
{
    // this function finds the start and the lenght of the longest sequence of cosecutive elements whose sum is a prime number
    // param values = v - the vector to be checked, start - the start of the req seq, lenght - the length of the req seq
    int current_start = 0, current_lenght = 0, final_start = 0, max_lenght = 0, sum;
    for (int i = 0; i < v.lenght - 1; i++)
    {
        sum = v.array[i] + v.array[i + 1];
        if (is_prime(sum) == 1 && v.array[i] < v.array[i + 1])
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
    // param values = v - the vector we want to print, start - the start of the seq, length - the legth of the seq
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
        scanf_s("%d", &option);
        if (option == 1) {
            int n;
            printf("Give value for n: ");
            scanf_s("%d", &n);
            Vector v = prime_smaller_than(n);
            printf("The prime numbers are: \n");
            print_sequence(v, 0, v.lenght);
            int closest = closest_prime(n);
            printf("Closest prime to n is: %d\n", closest);
        }
        else {
            if (option == 2) {
                Vector v2 = read_normal_vector();
                int start, lenght;
                longest_inc_subsequence_prime_sum(v2, &start, &lenght);
                printf("The longest inc subsequence is: ");
                print_sequence(v2, start, lenght);
            }
            else {
                if (option == 3) {
                    printf("you're finshed :))\n");
                    not_finished = 0;
                }
                else {
                    printf("wrong input");
                }
            }
        }
    }
    return 0;
}