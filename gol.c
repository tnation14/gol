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

char* make2DArray(int rows, int cols, FILE* file, int numCoords);
void print(char* arr, int willPrint, int rows, int cols);
void verifyCmdArgs(int argc, char *argv[]);
int numNeighbors(int xcoord, int ycoord, int rows, int cols, char *board, int numcoords);

char* make2DArray(int rows, int cols, FILE* file, int numCoords){
  // Creates a 2D array by dynamically allocating space for a
  // 1 x (rows*cols) array
  char* array = NULL;
  array = (char *)malloc(sizeof(char)*(rows*cols));
  if (array == NULL) {
    printf("malloc failed");
    exit(1);
  } 
  int i,j,x,y,counter;
  x = 0;
  y = 0;
  counter = 0;
  
  for(i = 0; i< rows; i++){
  	for(j = 0; j< cols; j++){
  		array[i*rows+j]= '-';
  	 }	
  }
  
  while(counter < numCoords){
    fscanf(file, "%d%d", &x,&y);
	array[x*rows+y]='!';
	counter++;  				
  }	
  return array;
}


void print(char* arr, int willPrint,int rows,int cols) {
  // Prints arr as a matrix
  if (!willPrint) {
    printf("Not printing board.\n");
    return;
  }
  int i;
  for (i = 0; i < rows*cols; i++) {
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

int numNeighbors(int xcoord, int ycoord, int rows, int cols, char *board, int numcoords){
  int neighborcounter, i, j, k, x, y;  
  /*
  0 1 2 3 4 5
  */
  x = xcoord;
  y = ycoord;
  neighborcounter = 0;
  	for(j = -1; j< 2; j++){
          int currentrow;
          currentrow = x+j;
          if(currentrow == rows){
            currentrow = 0;  	  
          }else if(currentrow ==-1){
            currentrow = rows-1;
          }

  	  for(k = -1;k<2;k++){
  	    int currentcol;
  	    currentcol = y +k;
  	    if(currentcol == cols){
  	    	currentcol = 0;
  	    }else if(currentcol == -1){
              currentcol = cols-1;
            }  	  
  	    if(currentrow == x && currentcol == y){
  	      continue;
  	    }else if(board[currentrow*rows+currentcol] == '!'){
                printf("Neighbor: (%d,%d)\n", currentrow, currentcol);
  	      neighborcounter++;
  	    }

  	}
  }
  


  printf("(%d,%d) has %d live neighbors.\n",x,y,neighborcounter);
  return neighborcounter;
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
    
  // TODO: Keep this around while I test something else
  int rows,cols,iters,numCoords,counter,x,y;
  fscanf(inFile, "%d %d %d %d", &rows, &cols, &iters, &numCoords);
  
  // Create game board
  char *board = NULL;
  board = make2DArray(rows,cols,inFile,numCoords);
  print(board,atoi(argv[2]),rows,cols);
  int* coords=NULL;
  coords = (int *)malloc(8*sizeof(int));
  if (coords == NULL) {
    printf("malloc failed");
    exit(1);
  } 
  counter = 0;
  int index;
  index = 0;
  fseek(inFile, 0, SEEK_SET);
  fscanf(inFile, "%d %d %d %d", &rows, &cols, &iters, &numCoords);

  while(counter < numCoords){
  	fscanf(inFile, "%d %d", &coords[index],&coords[index+1]);	
  	index +=2;
  	counter ++;
  } 
  for(counter = 0; counter <2*numCoords-1; counter+=2){
  	int neighbors;
  	printf("(%d,%d)\n",coords[counter], coords[counter+1]);
  	neighbors = numNeighbors(coords[counter],coords[counter+1],rows,cols,
            board,numCoords);
  	
  }
 
  
  free(board);
  free(coords);
  fclose(inFile);
 
  return 0;
}
