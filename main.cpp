#include <iostream>
#include <random>
#include <ctime>
#include "sorts.hpp"
using namespace std;

void init_random(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = random() % 10;
    }
    
}

int main()
{
    // Seeding random number generator
    srand(time(NULL));

    // Stuff
}