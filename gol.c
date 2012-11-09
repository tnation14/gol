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
  
  // Sets every value to '-'.
  for(i = 0; i< rows; i++){
  	for(j = 0; j< cols; j++){
  		array[i*rows+j]= '-';
  	 }	
  }
  
  // Reads config file, makes any coords in that file '!' to indicate
  // That they're active. 
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
  /* Counts the number of neighbors */
  int neighborcounter, i, j, k, x, y;  

  x = xcoord;
  y = ycoord;
  neighborcounter = 0;
  
  
  for(j = -1; j< 2; j++){
  
    /* Sets the row we're searching for live neighbors in.
       starts at the cell to the top left, or wraps arount
       if necessary. Checks every cell in a row (again
       wrapping to the other side if necessary), and 
       increments the counter by 1 if the cell is active.
    */
    int currentrow;
    currentrow = x+j;
    
    // Wraps other side of game board if the current row is too big or too
    // small.
    if(currentrow == rows){
      currentrow = 0;  	  
    }else if(currentrow ==-1){
      currentrow = rows-1;
    }

    for(k = -1;k<2;k++){
      int currentcol;
      currentcol = y +k;
      
      // Wrapping for columns.
      if(currentcol == cols){
          currentcol = 0;
      }else if(currentcol == -1){
        currentcol = cols-1;
      }  	  
      if(currentrow == x && currentcol == y){
      
        //avoids a cell counting itself as a neighbor.
        continue;
      }else if(board[currentrow*rows+currentcol] == '!'){
      	  // If a cell's value is '!', it's alive. Increment the counter.
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
    
  //Reads maze information from configuration file. 
  int rows,cols,iters,numCoords,counter,x,y,neighbors;
  fscanf(inFile, "%d %d %d %d", &rows, &cols, &iters, &numCoords);
  
  // Create game board
  char *board = NULL;
  board = make2DArray(rows,cols,inFile,numCoords);
  print(board,atoi(argv[2]),rows,cols);


  /*Slow, but works: iterates every element in the array, and checks its
    neighbors. If a cell has < 2 neighbors, it dies. More than 3 also dies.
    Exactly 3 neighbors brings the cell to life.
	*/

  for(x = 0; x < rows; x++){
    for(y = 0; y<cols; y++){
       neighbors = numNeighbors(x,y,rows,cols,board,numCoords);
       if(neighbors <2){
         //resets and redraws board
         board[x*rows+y]= '-';
         system("clear");
         print(board,atoi(argv[2]),rows,cols);
         usleep(200000);
       }else if(neighbors>3){
         system("clear");
         board[x*rows+y] = '-';
         print(board,atoi(argv[2]),rows,cols);
         usleep(200000);
       }else if(neighbors == 3){
         system("clear");
         board[x*rows+y] = '!';
         print(board,atoi(argv[2]),rows,cols);
         usleep(200000);
       }
    }
  }

  free(board);
  fclose(inFile);
 
  return 0;
}
