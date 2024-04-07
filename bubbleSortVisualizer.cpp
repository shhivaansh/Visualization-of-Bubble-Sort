#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <unistd.h> // For sleep function, works on Unix-like systems
#include <graphics.h>

using namespace std;

// Initialize the size with the total numbers to sorted and the gap to be maintained in graph
vector<int> numbers;
int size = 200;
int gap = 6;

// Function for swapping the lines graphically
void swapLines(int i, int j, int x, int y)
{
    setcolor(GREEN);
    line(i, size, i, size - x);
    setcolor(BLACK);
    line(i, size, i, size - x);
    setcolor(WHITE);
    line(i, size, i, size - y);

    setcolor(GREEN);
    line(j, size, j, size - y);
    setcolor(BLACK);
    line(j, size, j, size - y);
    setcolor(WHITE);
    line(j, size, j, size - x);
}

// Bubble sort function
void bubbleSort()
{
    int temp, i, j;

    for (i = 1; i < size; i++)
    {
        for (j = 0; j < size - i; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;

                // As we swapped the last two numbers
                // just swap the lines with the values.
                // This is function call for swapping the lines
                swapLines(gap * j + 1, gap * (j + 1) + 1, numbers[j + 1], numbers[j]);
            }
        }
    }
}

int main()
{
    // auto detection of screen size
    int gd = DETECT, gm;
    int wid1;

    // Graph initialization
    initgraph(&gd, &gm, NULL);

    // setting up window size (gap*size) * (size)
    wid1 = initwindow(gap * size + 1, size + 1);
    setcurrentwindow(wid1);

    // Initializing the array
    for (int i = 1; i <= size; i++)
        numbers.push_back(i);

    // Find a seed and shuffle the array
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));

    // Initial plot of numbers in graph
    for (int i = 1; i <= gap * size; i += gap)
    {
        line(i, size, i, (size - numbers[i / gap]));
    }

    // Delay the code
    delay(200);

    // Call sort
    bubbleSort();

    // Output sorted numbers
    cout << "Sorted Array: ";
    for (int i = 0; i < size; i++)
    {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Wait for some time
    usleep(5000000); // sleep for 5 seconds

    // Close the graph
    closegraph();

    return 0;
}
