#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ppm_io.h"
#include "puzzle.h"

int main(int argc, char **argv) {
  if (argc < 1 || argc > 2) {
    fprintf(stderr, "Usage: ./puzzle [<command file>]\n");
    return 1;
  }
  // TODO: implement

  const char * inputFile = argv[1];
  FILE* input = fopen(inputFile, "r");

  Puzzle *puzzle;
  Image *background;
  //read

  while(!EOF){
    char tempc;
    fscanf(input, " %c",&tempc);

    if(tempc == 'C'){
      if(handle_C_command(input, &puzzle)==2){
        fprintf(stderr, "Invalid input");
      }
    }
    else if(tempc == 'T'){
      int commandT = handle_T_command(input, puzzle);
      if(puzzle == NULL){
        fprintf(stderr, "No puzzle");
      }
      if( commandT == 2){
        fprintf(stderr, "Invalid input");
      }
      if(commandT == 3){
        fprintf(stderr, "Invalid tile value");
      }
    }
    else if(tempc == 'I'){
      Image* background = NULL;
      int commandI = handle_I_command(input, &background); 
      if (commandI != 0) {
        fprintf(stderr, "Failed to load background image.\n");
      }
    }
    else if(tempc == 'P'){
      if(puzzle == NULL){
        fprintf(stderr, "No puzzle");
      }
      handle_P_command(input, puzzle);
    }
    else if(tempc == 'W'){
      if(puzzle == NULL){
        fprintf(stderr, "No puzzle");
      }
      int commandW = handle_W_command(input, background, puzzle);
      if (commandW != 0) {
        fprintf(stderr, "Failed to write puzzle image and configuration.\n");
      }
    }
    else if(tempc == 'S'){
      int commandS = handle_S_command(input, puzzle);
      if( commandS== 2){
        fprintf(stderr, "Invalid input");
      }
      if(commandS == 1){
        fprintf(stderr, "Puzzle cannot be moved in specified direction");
      }
    }
    else if(tempc == 'K'){
      if(puzzle == NULL){
        fprintf(stderr, "No puzzle");
      }
      handle_K_command(input, puzzle);
    }
    else if(tempc == 'V'){
      if(puzzle == NULL){
        fprintf(stderr, "No puzzle");
      }
      int commandV = handle_V_command(input, puzzle);
      if(commandV == 1){
        fprintf(stderr, "Attempts to solve puzzle did not succeed.");
      }
    }
    else if(tempc == 'Q'){
      handle_Q_command(input, puzzle);
    }
    else{
      fprintf(stderr, "Invalid command %c", tempc);
    }
  }

  fclose(input);
}
