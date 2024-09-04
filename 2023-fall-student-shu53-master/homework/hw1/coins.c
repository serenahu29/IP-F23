

//coins.c
#include <stdio.h>
#define MAX_DENOMINATIONS 20

int main(){
  //denomination
  int denomination = 0;
  
  printf("How many denominations? ");
  scanf(" %d", &denomination);

  if (denomination < 1 || denomination > MAX_DENOMINATIONS) {
    fprintf(stderr, "Invalid input\n");
    return 1;
  }
  
  
  //coin identifier and value
  char identifiers[MAX_DENOMINATIONS];
  int value[MAX_DENOMINATIONS];
  for(int i = 0; i<denomination; i++){
    printf("Enter coin identifier and value in cents: ");
    //scanf(" %c %d", &identifiers[i],&value[i]);
    // printf("Entered %c and %d\n", identifiers[i], value[i]);  
    if (scanf(" %c %d", &identifiers[i], &value[i]) != 2) {
       fprintf(stderr, "Invalid input\n");
       return 1;
    }
  }
  
  int counts[MAX_DENOMINATIONS] = {0}; // Initialize counts to zero
  
  while(1){
    char command;
    int val;
    printf("Enter a command: ");
    val = scanf(" %c", &command); 
    if(val != 1){
      printf("Bye!\n");
      return 0;
    }
    switch(command){
      case 'a':
      case 'r': {
	char idtf;
	int count;
	int check;
	check = scanf(" %c %d", &idtf,&count);
	if(check !=2){
	  fprintf(stderr, "Invalid input\n");
	  return 1;
	}
	//printf("Count is %d\n",count);

	int found = 0;
	for(int i = 0; i < denomination; i++){
	  if(identifiers[i] == idtf){
	    if(command == 'a'){
	      counts[i] += count;
	      // printf("count add now is %d\n",count);
	    }else{
	      counts[i] -= count;
	      //printf("cound r now is %d\n",count);
	    }
	    found = 1;
	    break;
	    //found - 1 add break
	  }
	  /* else{
	    found = 1;
	    //break;
	  }*/
	 
	}

	if(!found){
	  fprintf(stderr, "Unknown coin identifier\n");
	  return 2;
	}
	break;
      }
      case 's': 
	printf("Identifier,Face Value,Count,Total Value\n");
	//for each type of coin
	int overallValue = 0;
	for(int i = 0; i < denomination; i++){
	  int totalValue = counts[i] * value[i];
	  printf("%c,%d,%d,%d\n", identifiers[i],value[i],counts[i],totalValue);
	  overallValue += totalValue;
	}
	printf("Overall value of collection: $%d.%02d\n", overallValue/100,overallValue%100);
	break;

      case 'q':
	printf("Bye!\n");
        return 0;
      default:
	fprintf(stderr, "Invalid command\n");
	return 3;

    }
  }
  return 0;
}
   
                                           
