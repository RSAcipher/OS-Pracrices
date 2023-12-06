#include <stdio.h>
#include <math.h>

int main() {
    double array[] = {1.5, -2.3, 4.0, -5.1, 3.3};
    int n = sizeof(array) / sizeof(array[0]);

    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    double average = sum / n;

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] > average) {
            count++;
        }
    }
    int firstNegativeIndex = -1;
    for (int i = 0; i < n; i++) {
        if (array[i] < 0) {
            firstNegativeIndex = i;
            break;
        }
    }
    double absSum = 0.0;
    if (firstNegativeIndex != -1) {
        for (int i = firstNegativeIndex + 1; i < n; i++) {
            absSum += fabs(array[i]);
        }
    }
    printf("Number of elements greater than the average: %d\n", count);
    printf("Sum of absolute values after the first negative element: %.2f\n", absSum);

    return 0;
}

