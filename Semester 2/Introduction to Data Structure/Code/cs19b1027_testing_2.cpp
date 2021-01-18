#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Defining the struct as point containig two float values x and y
    typedef struct{
            float x, y ;
            } point ;
    point origin = {0,0};                //Defining origin


float distance(point P1 , point P2);

int main()
{
    int n;                  // The number of points
    printf("Give the number of points you want to give: ");
    scanf("%d",&n);


    point P[n];    //Defining the array of data type point in an array Point of n elements.

    printf("Give the values of points, first the x coordinate follwed by the y coordinate :");

    for(int i=0; i<n; i++)
          {  scanf("%f%f", &P[i].x , &P[i].y);
          }

    //Finding the minimum distance points
    int min_point_1, min_point_2;
    float min_distance = 0;
    for(int i=0; i<n; i++)
    {  for(int j=i+1; j<n; j++)
        {   if( min_distance > distance(P[i],P[j]))
                {min_distance = distance(P[i],P[j]);
                min_point_1 = i;
                min_point_2 = j;
                }
        }
     }

    printf("The closest pair are: (%f,%f) and (%f,%f) \n\n", P[min_point_1].x,P[min_point_1].y,P[min_point_2].x,P[min_point_2].y);


    //Finding the maximum distance point
    int max_point_1, max_point_2;
    float max_distance = 0;
    for(int i=0; i<n; i++)
    {  for(int j=i+1; j<n; j++)
        {   if( max_distance < distance(P[i],P[j]))
                {max_distance = distance(P[i],P[j]);
                max_point_1 = i;
                max_point_2 = j;
                }
        }
     }

    printf("The farthest pair are: (%f,%f) and (%f,%f) \n\n", P[max_point_1].x,P[max_point_1].y,P[max_point_2].x,P[max_point_2].y);



    return 0;

}

float distance( point P1, point P2){
    float distance = sqrtf( (P1.x - P2.x)*(P1.x - P2.x) + (P1.y - P2.y)*(P1.y - P2.y));    //sqrtf : to  find square root
                                                                        // pow : to find the square
    return distance;                                                    //returnig the distance
}
