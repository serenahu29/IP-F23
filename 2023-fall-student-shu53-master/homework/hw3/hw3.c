//Serena Hu
//shu53
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"


#define MAX_WORD_NUM 1024
#define MAX_INPUT_SIZE 128
#define DEFAULT_RESTRICTION 10

int main(int argc, const char* argv[]) {
  char words[ MAX_WORD_NUM ][ MAX_WORD_SIZE + 1 ]; 
  //1042, 32
  //TODO
  //input file: command line arguments
  if (argc < 2){
    fprintf(stderr, "Usage: %s <input_file> [restriction]\n", argv[0]);
    return 1; //error
  }
  
  const char *inputFile = argv[1]; //number
  int restriction = DEFAULT_RESTRICTION;

  if (argc >= 3) {
    //restriction length
    restriction = atoi(argv[2]); //atoi:convert from command line to int
    if (restriction <= 0) {
      fprintf(stderr, "Invalid restriction length: %s\n", argv[2]);
      return 1; 
    }
  }

  //read input file
  FILE* input = fopen(inputFile, "r");
  if (input == NULL) {
    fprintf(stderr,"Error opening input file");
    return 1;  
  }

  //read_file(input,words,size);
  char sizetemp;
  fscanf(input, "%c",&sizetemp);
  //printf("%c\n",sizetemp);

  const char* s = &sizetemp;
  
  int size;
  sscanf(s,"%d",&size);
 
  //printf("%d\n",size);
  int readf = read_file(input,words,size); //should not be MAXWORDNUM, should be first line of input file
  //readfile modified first[] of the 2Darray words[][]

  //Check read_file errors
  if (readf != 0) {
    fclose(input);
    return 1;  
  }

  char regexPattern[MAX_INPUT_SIZE];

  while (1) {
    //printf("Enter a regex pattern (Ctrl-D to exit): ");
    if (fgets(regexPattern, sizeof(regexPattern), stdin) == NULL) {
      break;  // Exit the loop on Ctrl-D
    }

    // Remove newline character if present
    size_t len = strlen(regexPattern);
    if (len > 0 && regexPattern[len - 1] == '\n') {
      regexPattern[len - 1] = '\0';
    }
    

    int foundMatch = 0;
    
    for (int i = 0; i < size; i++) {
      if (match(regexPattern, words[i], restriction)) {
        printf("%s\n", words[i]);
        
      }
      foundMatch = 1;
    }

  
    if (!foundMatch) {
      fprintf(stdout,"No match found for regex '%s'\n", regexPattern);
    }
    
  }

  //clean up
  fclose(input);
  return 0;
}
