#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Defining the struct as point containig two float values x and y
    typedef struct{
            float x, y ;
            } point ;
    point origin = {0,0};                //Defining origin
// Remember to add the malloc

float distance(point P1 , point p2);

int main()
{
    int n;                  // The number of points
    printf("Give the number of points you want to give: ");
    scanf("%d",&n);


    point Point[n];    //Defining the array of data type point in an array Point of n elements.

    printf("Give the values of points, first the x coordinate follwed by the y coordinate :");

    for(int i=0; i<n; i++)
          {  scanf("%f%f", &Point[i].x , &Point[i].y);
          }

   // printf("The distance between the two points P2 and P3 is: %f", distance(Point[1],Point[2]));
    float distance_square[n];
    for(int i=0; i<n; i++){
        distance_square[i] = distance(Point[i],origin)*distance(Point[i],origin);             // Distance from origin
        }

    int min_point_1 = 0 ,min_point_2 = 0;
    float min_1 = distance_square[0], min_2 = distance_square[0];
    for(int i=0; i<n; i++){
        if(distance_square[i] < min_1){
            min_1 = distance_square[i];
            min_point_1 = i;
            }
        }
     for(int i=0; i<n; i++){
        if(distance_square[i] < min_2 && min_point_1 != i){
            min_2 = distance_square[i];
            min_point_2 = i ;
            }
        }
    printf("The closest pair are: (%f,%f) and (%f,%f) \n\n", Point[min_point_1].x,Point[min_point_1].y,Point[min_point_2].x,Point[min_point_2].y);



    int max_point_1 = 0 ,max_point_2 = 0;
    float max_1 = distance_square[0], max_2 = distance_square[0];
    for(int i=0; i<n; i++){
        if(distance_square[i] > max_1){
            max_1 = distance_square[i];
            max_point_1 = i;
            }
        }
     for(int i=0; i<n; i++){
        if(distance_square[i] > max_2 && max_point_1 != i){
            max_2 = distance_square[i];
            max_point_2 = i ;
            }
        }
    printf("The farthest pair are: (%f,%f) and (%f,%f) \n\n", Point[max_point_1].x,Point[max_point_1].y,Point[max_point_2].x,Point[max_point_2].y);


    return 0;

}

float distance( point P1, point P2){
    float distance = sqrtf( (P1.x - P2.x)*(P1.x - P2.x) + (P1.y - P2.y)*(P1.y - P2.y));    //sqrtf : to  find square root
                                                                        // pow : to find the square
    return distance;                                                    //returnig the distance
}
