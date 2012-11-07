//
// Zach Lockett-Streiff; Taylor Nation
// Implementation of Conway's Game of Life 
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>


// NOTE: Our code must pass, at minimum, the following criteria:
  // TODO: Error check EVERYTHING that returns a value! (Yeah, everything)
  // TODO: Read the requirements...
  // TODO: No Valgrind errors
  // TODO: Comment every function
  // TODO: Code shall not wrap

// Design suggestion: Create/test code segments in main, move into separate
//                    functions when complete

char *make2DArray(int rows, int cols);
void print(char* arr, int willPrint, int rows, int cols);
void verifyCmdArgs(int argc, char *argv[]);


char *make2DArray(int rows, int cols){
  // Creates a 2D array by dynamically allocating space for a
  // 1 x (rows*cols) char array, initializing all values to -
  char* array = NULL;
  array = (char *)malloc(sizeof(char)*(rows*cols));
  if (array == NULL) {
    printf("malloc failed");
    exit(1);
  }

  // Initialize all indices of arrays to "-" to prevent junk data
  int i = 0;
  while (i < rows*cols) {
    array[i] = '-';
    i++;
  }
  return array;
}


void print(char* arr, int willPrint, int rows, int cols) {
  // Prints arr as a matrix
  if (!willPrint) {
    printf("Not printing board.\n");
    return;
  }
  
  int i;
  for (i = 0; i < cols*rows; i++) {
    printf("%c ",arr[i]);
    if (!((i+1) % cols)) {
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

FILE *openFile(char *filename[]) {
  FILE *inFile;
  inFile = fopen(filename[1],"r");
  if (inFile == NULL) {
    printf("Unable to load test parameters.\n");
    exit(1);
  } 
  return inFile;
}

int main(int argc, char *argv[]) {                                          
  system("clear");
  // Process command line arguments
  verifyCmdArgs(argc, argv);
  
  // Opens test parameter file for reading
  FILE *inFile = openFile(argv);
    
  // Read in data from input file
  int rows,cols,iters,numCoords,x,y;
  int i = 0;
  fscanf(inFile, "%d %d %d %d", &rows, &cols, &iters, &numCoords);
  while (i < 2*numCoords-1) {
    fscanf(inFile,"%d%d",&x,&y);
    printf("%d %d\n",x,y);
    i+=2;
  }

  fclose(inFile);

  // Create game board
  char *board = NULL;
  board = make2DArray(rows,cols);
  print(board,atoi(argv[2]),rows,cols);
  free(board);

 
  return 0;
}
