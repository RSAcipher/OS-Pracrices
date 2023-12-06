#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double mass;
} Point;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int findMinMassPoint(Point *points, int n) {
    int minIndex = 0;
    double minMass = points[0].mass;

    for (int i = 1; i < n; i++) {
        if (points[i].mass < minMass) {
            minMass = points[i].mass;
            minIndex = i;
        }
    }

    return minIndex;
}

void mergePoints(Point *points, int *n) {
    while (*n > 1) {
        int minIndex = findMinMassPoint(points, *n);

        double minDistance = INFINITY;
        int nearestIndex = -1;
        for (int i = 0; i < *n; i++) {
            if (i != minIndex) {
                double dist = distance(points[minIndex], points[i]);
                if (dist < minDistance) {
                    minDistance = dist;
                    nearestIndex = i;
                }
            }
        }

        points[nearestIndex].mass += points[minIndex].mass;

        for (int i = minIndex; i < *n - 1; i++) {
            points[i] = points[i + 1];
        }
        (*n)--;
    }
}

int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    Point *points = (Point *)malloc(n * sizeof(Point));

    for (int i = 0; i < n; i++) {
        printf("Enter coordinates (x y) and mass for point %d: ", i + 1);
        scanf("%lf %lf %lf", &points[i].x, &points[i].y, &points[i].mass);
    }
    mergePoints(points, &n);

    printf("The remaining point has coordinates (%.2f, %.2f) and mass %.2f\n",
           points[0].x, points[0].y, points[0].mass);

    free(points);
    return 0;
}
