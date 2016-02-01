/**
  @file venn.c
  @author Wesley Coats wrcoats
  
  Program that outputs a venn diagram given the center locations for 3 circles
  One circle is red, one is green, and the last one is blue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Width and height of the image. */
#define ISIZE 100

/** Radius of the circles we're drawing. */
#define RADIUS 45

/** Brightest color intensity, for the center of a circle */
#define CMAX 255

/** Half the color intensity, for the edge of a circle */
#define CHALF 128

/** Constant for zero */
#define ZERO 0

/**
  This function calculates and returns the distance between two locations both given as coordinates
  
  @return the distance between two locations
  @param x1 the x coordinate of one location
  @param y1 the y coordinate of one location
  @param x2 the x coordinate of the other location
  @param y2 the y coordinate of the other location
  */
double computeDistance( int x1, int y1, int x2, int y2 )
{
  double distance = (((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
  return sqrt(distance);
}

/**
  This function returns the intensity value that is used for red, green, and blue components of pixels inside a circle.

  @return the intensity value for pixels within the circle
  @param dist the distance from the center of the circle
*/
int distanceToShade( double dist )
{
if (dist == ZERO) {
    return CMAX;
  }
  else if (dist == RADIUS) {
    return CHALF;
  }
  else {
    return round((((double)CHALF - (double)CMAX)/(double)RADIUS) * (dist) + CMAX);
  }
}

/**
  Main function is responsible for reading input from standard input and writing the image out to standard output.
*/
int main()
{
  int redX = 0;
  int redY = 0;
  int greenX = 0;
  int greenY = 0;
  int blueX = 0;
  int blueY = 0;
  int circleInput = scanf("%d %d %d %d %d %d",&redX,&redY,&greenX,&greenY,&blueX,&blueY);
  if (circleInput != 6) {
    printf("Invalid input\n");
    exit(100);
  }
  printf("P3\n");
  printf("%d %d\n", ISIZE, ISIZE);
  printf("%d\n", CMAX);
  for (int i = 0; i < ISIZE; i++) {
    for (int j = 0; j < ISIZE; j++) {
      if(computeDistance(j,i,redX,redY) <= RADIUS) {
        printf("%3d ", distanceToShade(computeDistance(j,i,redX,redY)));
      }
      else {
        printf("%3d ",ZERO);
      }
      if(computeDistance(j,i,greenX,greenY) <= RADIUS) {
        printf("%3d ", distanceToShade(computeDistance(j,i,greenX,greenY)));
      }
      else {
        printf("%3d ",ZERO);
      }
      if(computeDistance(j,i,blueX,blueY) <= RADIUS) {
        printf("%3d ", distanceToShade(computeDistance(j,i,blueX,blueY)));
      }
      else {
        printf("%3d ",ZERO);
      }
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
