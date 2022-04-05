#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    printf("Hello, world!\n");
    int x = get_x("x: ");
    int y = get_y("y: ");
    int z = x + y;
    printf("%i\n", z);

    if ( x > y )
    {
        printf("x is greater than y.\n");
    }
    else if ( x < y)
    {
        printf("x is smaller than y.\n");
    }
    else
    {
        printf("x is equal to y.\n");
    }
}


