#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_x("x: ");
    int y = get_y("y: ");
    int z = x + y;
    printf("%i\n", z);
}