//
// Zach Lockett-Streiff; Taylor Nation
// Implementation of Conway's Game of Life 
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define ROW 4
#define COL 5

// NOTE: Our code must pass, at minimum, the following criteria:
  // TODO: Error check EVERYTHING that returns a value! (Yeah, everything)
  // TODO: Read the requirements...
  // TODO: No Valgrind errors
  // TODO: Comment every function
  // TODO: Code shall not wrap

// Design suggestion: Create/test code segments in main, move into separate
//                    functions when complete

int* make2DArray(int rows, int cols);
void print(int* arr, int willPrint);
void verifyCmdArgs(int argc, char *argv[]);
// char readFile(FILE *inFile);


int* make2DArray(int rows, int cols){
  // Creates a 2D array by dynamically allocating space for a
  // 1 x (rows*cols) array
  int* array = NULL;
  array = (int *)malloc(sizeof(int)*(rows*cols));
  if (array == NULL) {
    printf("malloc failed");
    exit(1);
  } 
  return array;
}


void print(int* arr, int willPrint) {
  // Prints arr as a matrix
  if (!willPrint) {
    printf("Not printing board.\n");
    return;
  }
  int i;
  for (i = 0; i < COL*ROW; i++) {
    printf("%d ",arr[i]);
    if (!((i+1) % COL)) {
      printf("\n");
    }
  }
}

void verifyCmdArgs(int argc, char *argv[]) {
  // Verify valid number of command line arguments
  if (argc != 3) {
   printf("usage: ./gol configFile printCondition\n");
   exit(1);
  }
  
  // Verify caller passed in .txt file
  if (!strstr(argv[1],".txt")) {
    printf("Invalid test parameter file, must be a .txt file.\n");
    exit(1);
  }
  
  // Verify valid printCondition
  if (atoi(argv[2]) != 1 && atoi(argv[2]) != 0) {
    printf("Invalid printCondition, must be either 0 or 1.\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {                                          
  system("clear");
  // Process command line arguments
  verifyCmdArgs(argc, argv);
  
  // opens test parameter file for reading
  FILE *inFile;
  inFile = fopen(argv[1],"r");
  if (inFile == NULL) {
    printf("Unable to load test parameters.\n");
    exit(1);
  }
  int *fileParams;  
  // TODO: Keep this around while I test something else
  // Simplify this...just change the board directly
  int rows = 0;
  int cols = 0;
  int iters = 0;
  int numCoords = 0;
  fscanf(inFile, "%d %d %d %d", &rows, &cols, &iters, &numCoords);
  char coords[numCoords+1];
  int i = 0;
  while (i < 2*numCoords-1) {
    fgets(coords, 4, inFile);
    fgets(coords, 4, inFile);
    printf("%c %c\n",coords[i],coords[i+1]);
    i+=2;
  }

  fclose(inFile);

  // Create game board
  int *board = NULL;
  board = make2DArray(ROW,COL);
  print(board,atoi(argv[2]));
  free(board);

 
  return 0;
}
