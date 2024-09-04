#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ppm_io.h"
#include "puzzle.h"

// TODO: implement functions
Puzzle *puzzle_create(int size){
    //add the image
    //use malloc
    //int puzzle[][size] = {0};
    Puzzle *p = (Puzzle*) malloc(sizeof(Puzzle));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed for Puzzle\n");
        exit(1);
    }
    
    p->size = size;

    p->tiles = (int *) malloc(size * size * sizeof(int *)); //tiles -> 1D array
    
    if (p->tiles == NULL) {
        fprintf(stderr, "Memory allocation failed for tiles\n");
        free(p); 
        exit(1);
    }
    
    for (int i = 0; i < size*size; i++){
        p->tiles[i] = 0;

    }
    /*
    for (int i = 0; i < size; i++) {
        p->tiles[i] = (int *)malloc(size * sizeof(int));
    }

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            p->tiles[row][col] = 0; // Initialize to 0
        }
    }
    */
    return p;

    //Puzzle ___.image initialize
    //
}
void puzzle_destroy(Puzzle *p){
//deallocate 2d array (dynamic allocation)
//detroy entire puzzle
    if (p == NULL) {
        return;
    }

    free(p->tiles);
    
    //free the Puzzle struct
    free(p);

}

void puzzle_set_tile(Puzzle *p, int col, int row, int value){
    //maybe for swapping
    int index = row * p->size + col;
    p->tiles[index] = value;

}
int puzzle_get_tile(const Puzzle *p, int col, int row){
    //maybe for a temp while swapping
    int index = row * p->size + col;
    return p->tiles[index];
}


int handle_C_command(FILE *in, Puzzle **p){

    if(*p){
        puzzle_destroy(*p);
        printf("destroyed"); //debug
    }
    
    int num = 0;
    int pass = fscanf(in, " %d", &num);
    printf("%d", num); //debug
    if(pass == '\0'){
        printf("null"); //debug
        return 2;
    }
    if (pass>=2 || pass<=20) {
        *p = puzzle_create(num);
        printf("puzzle created"); //debug
           return 0;
    } 
    else {
        fprintf(stderr, "Error: can't read input");
        return 1;
    }

}
int handle_T_command(FILE *in, Puzzle *p){
    //T tile...
    //initial order of all the tiles unsolved

    int tilenum;
    int maxnum = (p->size)*(p->size);
    printf("max num %d\n", maxnum); //error handling

    for(int i = 0; i<maxnum; i++){
        fscanf(in, " %d", &tilenum);
        printf("%d", tilenum);
        if(tilenum>=maxnum){
            printf("over max %d\n", tilenum); //error handling
            return 3;
        }
        for(int j = 0; j<i; j++){
            if(p->tiles[j] == tilenum){
            printf("repeating number\n"); //error handling
            return 2;
            }
        }
        
        p->tiles[i] = tilenum;

        printf("%d\n", p->tiles[i]); //error handling
    
    }

    if(p->tiles[0] == '\0'){
        printf("tile is null ?"); //error handling
        return 2;
    }
    else{
    printf("success"); //error handling
    return 0;
    }
}

//S
int handle_I_command(FILE *in, Image** background){
    //I filename
    //Load the background image from specified PPM file
    char file[256]; // Maximum filename length
    if (fscanf(in, " %255s", file) != 1) {
        fprintf(stderr, "Invalid I command\n");
        return 1;
    }

    FILE* image_file = fopen(file, "rb");
    if (image_file == NULL) {
        fprintf(stderr, "Could not open image file '%s'\n", file);
        return 1;
    }

    *background = ReadPPM(image_file);//memory leak?2
    if (*background == NULL) {
        fprintf(stderr, "Error: Failed to read PPM image from file '%s'\n", file);
        return 1;
    }
    //free(background);
    fclose(image_file);
    //add more error handling?
    return 0;
}

int handle_W_command(FILE* in, const Image* background, const Puzzle* p){
    //W filename1 filename2	
    //might need to change, w function need two files
    //Write puzzle image to filename1 and puzzle configuration to filename2

    char image_filename[256]; //file1
    char config_filename[256]; //file2
    if (fscanf(in, " %255s %255s", image_filename, config_filename) != 2) {
        fprintf(stderr, "Invalid W command\n");
        return 1; // Handle invalid 'W' command
    }

    //open image file
    FILE* image_file = fopen(image_filename, "w");
    if (image_file == NULL) {
        fprintf(stderr, "Could not open output image file %s\n", image_filename);
        return 1; //file open error
    }

    // Write the puzzle image
    int pixels_written = WritePPM(image_file, &p->image);
    fclose(image_file);

    if (pixels_written == -1) {
        return 1; 
    }
    
    // config file
    FILE* config_file = fopen(config_filename, "w");
    if (config_file == NULL) {
        fprintf(stderr, "Could not open output puzzle file '%s'\n", config_filename);
        return 1;
    }
    
    //WritePPM(config_file, &p->image);
    // Write the current puzzle configuration to the configuration file
    
    for (int row = 0; row < p->size; row++) {
        for (int col = 0; col < p->size; col++) {
            fprintf(config_file, "%d ", p->tiles[row * p->size + col]);
        }
        fprintf(config_file, "\n");
    }
    

    // Close the configuration file
    if (fclose(config_file) != 0) {
        fprintf(stderr, "Could not write puzzle data '%s'\n", config_filename);
        return 1;
    }
    
    return 0;
}
int handle_K_command(FILE *in, Puzzle *p){
    //Check to see whether the puzzle is in the winning configuration
    int numRows = p->size;
    int expectedValue = 1;

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numRows; col++) {
            int tileValue = puzzle_get_tile(p, col, row);
            if (tileValue != expectedValue) {
                // The puzzle is not solved, print "Not solved" and return
                printf("Not solved\n");
                return 1;
            }
            expectedValue++;
        }
    }

    // If all tiles are in their expected positions, print "Solved"
    printf("Solved\n");
    return 0;
}

//E
int handle_S_command(FILE *in, Puzzle *p){
    //parameter: direction
    //sliding the tiles

    char command;
    fscanf(in, " %c", &command);

    //travel through the array to find the index of null
    int indexrow = 0;
    int indexcol = 0;
    /*
    for(int r = 0; r<(int)sizeof(*p); r++){
        for(int c = 0; c < p->size; c++){
            if(p->tiles[r][c] == '0'){
                indexrow = r;
                indexcol = c;
                break;
            }
        }
    }
    */
    for(int r = 0; r<(p->size); r++){
        for(int c = 0; c < (p->size); c++){
            if(p->tiles[r*(p->size)+c] == 0){
                indexrow = r;
                indexcol = c;
                break;
            }
        }
    }

    if (command == 'l'){
        //cannot move left if null is the last space in the row (aka in the last column)
        if (indexcol == (p->size)-1){
                return 1;
            }
        //move left by switching index of the null tile to the right
        else{
            /*
            int temp;
            temp = p->tiles[indexrow][indexcol];
            p->tiles[indexrow][indexcol] = p->tiles[indexrow][indexcol + 1];
            p->tiles[indexrow][indexcol + 1] = temp;
           */
            int temp;
            int index = indexrow*(p->size) + indexcol;
            temp = p->tiles[index];
            p->tiles[index] = p->tiles[index + 1];
            p->tiles[index + 1] = temp;
            return 0; 
            //int temp;
            //index of null = temp
            //tile to the right of null = index of null
            //temp (null) = tile to the right of null
        }
    }  
    else if (command == 'r'){
        //cannot move right if null is in the first column
        if (indexcol == 0){
                return 1;
            }
        else{
            /*
            int temp;
            temp = p->tiles[indexrow][indexcol];
            p->tiles[indexrow][indexcol] = p->tiles[indexrow][indexcol - 1];
            p->tiles[indexrow][indexcol - 1] = temp;
            */
            int temp;
            int index = indexrow*(p->size) + indexcol;
            temp = p->tiles[index];
            p->tiles[index] = p->tiles[index - 1];
            p->tiles[index - 1] = temp;

            return 0;
            //int temp;
            //index of null = temp
            //tile to the left of null = index of null
            //temp (null) = tile to the left of null
            }
    }
    else if(command == 'u'){
        //cannot move up if null is in the last row
        if (indexrow == (p->size)-1){
                return 1;
            }
        else{
            /*
            int temp;
            temp = p->tiles[indexrow][indexcol];
            p->tiles[indexrow][indexcol] = p->tiles[indexrow + 1][indexcol];
            p->tiles[indexrow + 1][indexcol] = temp;
            */
            int temp;
            int index = indexrow*(p->size) + indexcol;
            temp = p->tiles[index];
            int newindex = (indexrow+1) * (p->size) + indexcol;
            p->tiles[index] = p->tiles[newindex];
            p->tiles[newindex] = temp;
            
            return 0;
            //int temp;
            //index of null = temp
            //tile to the bottom of null (so the next row)= index of null
            //temp (null) = tile above null
        }
        
    }
    else if(command == 'd'){
        //cannot move down if null is in the first row
        if (indexrow == 0){
                return 1;
            }
        else {
            /*
            int temp;
            temp = p->tiles[indexrow][indexcol];
            p->tiles[indexrow][indexcol] = p->tiles[indexrow - 1][indexcol];
            p->tiles[indexrow - 1][indexcol] = temp;
            */
            int temp;
            int index = indexrow*(p->size) + indexcol;
            temp = p->tiles[index];
            int newindex = (indexrow-1) * (p->size) + indexcol;
            p->tiles[index] = p->tiles[newindex];
            p->tiles[newindex] = temp;
            return 0;
            }
        
    }
    else {
    return 2;
    }

}

int handle_P_command(FILE *in, Puzzle *p){
    //print the sequence of the current puzzle
    //does it have to be in the shape of a 2d array?
    /*
    for(int r = 0; r<p->size; r++){
       for(int c = 0; c<p->size; c++){
        fprintf(in, "%d ", p->tiles[r][c]);
        }  
    }
    */
    for (int i = 0; i < (p->size)*(p->size); i++){
        fprintf(in, "%d ", p->tiles[i]);
    }
    

    return 0;
}

int testL(Puzzle *p){
    printf("command u"); //debug

    int indexrow = 0;
    int indexcol = 0;

    for(int r = 0; r<(p->size); r++){
        for(int c = 0; c < (p->size); c++){
            if(p->tiles[r*(p->size)+c] == 0){
                indexrow = r;
                indexcol = c;
                break;
            }
        }
    }

    printf("index row: %d, index col: %d, value: %d\n", indexrow, indexcol, p->tiles[indexrow*(p->size)+indexcol]); //debug

        if (indexcol == (p->size)-1){
                printf("l failed\n"); //debug
                return 1;
            }
        //move left by switching index of the null tile to the right
        else{
            int temp;
            int index = indexrow*(p->size) + indexcol;
            temp = p->tiles[index];
            p->tiles[index] = p->tiles[index + 1];
            p->tiles[index + 1] = temp;

            printf("l succeeded\n"); //debug
            printf("previous index: %d, new index %d", p->tiles[index], p->tiles[index + 1]);

            return 0; 

    }  

}

int testR(Puzzle *p){

    int indexrow = 0;
    int indexcol = 0;

    for(int r = 0; r<(p->size); r++){
        for(int c = 0; c < (p->size); c++){
            if(p->tiles[r*(p->size)+c] == 0){
                indexrow = r;
                indexcol = c;
                break;
            }
        }
    }

    printf("entering command r\n"); //debug
    //cannot move right if null is in the first column
    if (indexcol == 0){
        printf("r failed\n"); //debug
        return 1;
        }
    else{
            
        int temp;
        int index = indexrow*(p->size) + indexcol;
        temp = p->tiles[index];
        p->tiles[index] = p->tiles[index - 1];
        p->tiles[index - 1] = temp;

        printf("r succeeded\n"); //debug
        printf("previous index: %d, new index %d", p->tiles[index], p->tiles[index + 1]);

        return 0;
        }
}

int testU(Puzzle *p){

    int indexrow = 0;
    int indexcol = 0;

    for(int r = 0; r<(p->size); r++){
        for(int c = 0; c < (p->size); c++){
            if(p->tiles[r*(p->size)+c] == 0){
                indexrow = r;
                indexcol = c;
                break;
            }
        }
    }
        printf("entering command u\n"); //debug
        //cannot move up if null is in the last row
        if (indexrow == (p->size)-1){
                printf("u failed\n"); //debug
                return 1;
            }
        else{

            int temp;
            int index = indexrow*(p->size) + indexcol;
            temp = p->tiles[index];
            int newindex = (indexrow+1) * (p->size) + indexcol;
            p->tiles[index] = p->tiles[newindex];
            p->tiles[newindex] = temp;
            
            printf("u succeeded\n"); //debug
            printf("previous index: %d, new index %d", p->tiles[index], p->tiles[newindex]);

            return 0;
        }
        
    }
int testD(Puzzle *p){

    int indexrow = 0;
    int indexcol = 0;

    for(int r = 0; r<(p->size); r++){
        for(int c = 0; c < (p->size); c++){
            if(p->tiles[r*(p->size)+c] == 0){
                indexrow = r;
                indexcol = c;
                break;
            }
        }
    }
        printf("entering command d\n"); //debug
        //cannot move down if null is in the first row
        if (indexrow == 0){
                printf("d failed\n"); //debug
                return 1;
            }
        else {
            int temp;
            int index = indexrow*(p->size) + indexcol;
            temp = p->tiles[index];
            int newindex = (indexrow-1) * (p->size) + indexcol;
            p->tiles[index] = p->tiles[newindex];
            p->tiles[newindex] = temp;

            printf("d succeeded\n"); //debug
            printf("previous index: %d, new index %d", p->tiles[index], p->tiles[newindex]); //debug

            return 0;
        }
        
    }

Puzzle * copy_puzzle(Puzzle*p){
     Puzzle * copy = puzzle_create(p->size);
        copy->image = p->image;
        for (int r = 0; r<copy->size; r++){
          for (int c = 0; c<copy->size; c++){
            int index = r*(copy->size)+c;
            copy->tiles[index] = p->tiles[index];
            printf("copy:%d \n", copy->tiles[index]); //debug
          }  
        }
    return p;    
}
    
 int solve_puzzle(FILE *in, Puzzle *p, char steps[], int max_steps, int cur_steps) {
    
    printf("entering solve puzzle\n"); //debug
        if (handle_K_command(in, p)==0){
            printf("success!\n"); //debug
            return cur_steps;   // steps array has a complete sequence of steps
        }
        printf("current steps: %d", cur_steps); //debug
        if (cur_steps >= max_steps){
            printf("checking cur step < max\n"); //debug
            return 1;     // we reached the max number of steps
        }

    Puzzle copy = *copy_puzzle(p); 

        //for direction in 'u', 'd', 'l', 'r' 

    int switchD = 0; //off
    int switchU = 1; //on 
    int switchL = 0; //off
    int switchR = 1; //on 
    
    int cont = 1;
    
    switch (cont){
    case 1: 
        if((testU(&copy) == 0) && (switchU == 1)){
            switchD = 0;
            switchU = 1;
            switchL = 1;
            switchR = 1;
            if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
                printf("current steps (from test): %d\n", cur_steps); //debug
                steps[cur_steps] = 'u';
                return 0;
            }
            break;
        }
    case 2: 
         if((testD(&copy) == 0) && (switchD == 1)){
            switchD = 1;
            switchU = 0;
            switchL = 1;
            switchR = 1;
            if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
                printf("current steps (from test): %d\n", cur_steps); //debug
                steps[cur_steps] = 'd';
                return 0;
            }
            break;
        }
    case 3:
         if((testR(&copy) == 0) && (switchR == 1)){
            switchL = 0;
            switchR = 1;
            switchD = 1;
            switchU = 1;
            if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
                printf("current steps (from test): %d\n", cur_steps); //debug
                steps[cur_steps] = 'u';
                return 0;
            }
            break;
        }
    case 4:
         if((testL(&copy) == 0 )&& (switchL == 1)){
            switchL = 1;
            switchR = 0;
            switchD = 1;
            switchU = 1;
            if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
                printf("current steps (from test): %d\n", cur_steps); //debug
                steps[cur_steps] = 'u';
                return 0;
            }
            break;
        }

    default:
        return 1;
    }
        /*if(testU(&copy) == 0){
            if(cont == 1){
                return 1;
            }
            else if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
                printf("current steps (from test): %d\n", cur_steps);
                steps[cur_steps] = 'u';
                return 0;
        }
        }
            if(testR(&copy) ==0 ){
            if(cont == 2){
                return 1;
            }
            else if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
                printf("current steps (from test): %d\n", cur_steps);
                steps[cur_steps] = 'r';
                return 0;
            }
        }
    if(testD(&copy) ==0 ){
        if(cont == 3){
            return 1;
        }
        else if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
            printf("current steps (from test): %d\n", cur_steps);
            steps[cur_steps] = 'd';
            return 0;
        }
    }
    if(testL(&copy) ==0 ){
        if(cont == 4){
            continue;
        }
        else if(solve_puzzle(in, p, steps, max_steps, ++cur_steps)){
            printf("current steps (from test): %d\n", cur_steps);
            steps[cur_steps] = 'l';
            return 0;
        }*/
    }

    
    

        /*for(int i = 0; i<4; i++){
          printf("entering solve for loop");
            char test_dir[] = {'u', 'd', 'l', 'r'};

            if(cur_steps > max_steps){
                return 1;
            }
            if (test_dir[i] == 'u') {
                if(steps[cur_steps-1] == 'd' && (cur_steps - 1) != 0){
                    continue;
                }
                if(test(copy, 'u') == 0){
                    if (solve_puzzle(in, p, &steps[4], max_steps, ++cur_steps) != 1) {
                        // found a solution recursively!
                        //place direction in appropriate element of steps array
                        steps[cur_steps] = 'u';
                        return 0;
                        //return cur_steps;
                    }
                }
            }
            if (test_dir[i] == 'd') {
                if(test(copy, 'd') == 0){
                    if (solve_puzzle(in, p, &steps[4], max_steps, ++cur_steps) != 1) {
                        // found a solution recursively!
                        //place direction in appropriate element of steps array
                        steps[cur_steps] = 'd';
                        return 0;
                        //return cur_steps;
                    }
                }
            }
            if (test_dir[i] == 'l') {
                if(test(copy, 'l') == 0){
                    if (solve_puzzle(in, p, &steps[4], max_steps, ++cur_steps) != 1) {
                        // found a solution recursively!
                        //place direction in appropriate element of steps array
                        steps[cur_steps] = 'l';
                        return 0;
                        //return cur_steps;
                    }
                }
            }
            if (test_dir[i] == 'r') {
                if(test(copy, 'r') == 0){
                    if (solve_puzzle(in, p, &steps[4], max_steps, ++cur_steps) != 1) {
                        // found a solution recursively!
                        //place direction in appropriate element of steps array
                        steps[cur_steps] = 'r';
                        return 0;
                        //return cur_steps;
                    }
                }
            }
        }
        return 2;*/


int handle_V_command(FILE *in, Puzzle *p){
    printf("entering v\n"); //debugging

    //Compute a series of moves to solve the puzzle

    
    // Parameters:
    //   p - a Puzzle
    //   steps - array of directions (u/d/l/r)
    char steps[4] = {'\0'};
    //   max_steps - maximum number of steps to try
    //   cur_steps - how many steps have been considered so far
    int count = 0;
    int i;
    if((p->size) == 3){
        i = 32;
    }
    else if((p->size) == 4){
        i = 81;
    }

    printf("%d", i); //debug

    if(solve_puzzle(in, p, steps, i, count)==0){
        return 0;
    }
    else{
        return 1;    // attempts to solve recursively did not succeed
    }

} 

int handle_Q_command(FILE *in, Puzzle *p){
    //Quit the program
    char a;
    fscanf(in, "%c", &a);
    if(a == 'Q'){
        puzzle_destroy(p);
        exit(1); //exit the program
    }
    return 0;
}
