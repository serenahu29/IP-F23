//Serena Hu
//shu53
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {

  //number of words read
  int wordCount = 0;

  //loops through file
  while (wordCount <= size && fscanf(fp, "%s", words[wordCount]) == 1) {
    //memory leak printf test
    //printf("%s,%d\n",words[wordCount],wordCount);
    wordCount++;
  }
  //printf("%d\n",size);
  
  if (wordCount < size) {
    fprintf(stderr, "Error: Not enough words in the file.\n");
    return 1;  //error
  }
  
  return 0;
}

int match(const char *regex, const char *word, int restriction) {
  //return 1 if match
  if (*regex == '\0' && *word == '\0') {
    return 1;
  }

  //abc abc
  if (*word != '\0' && *word == *regex) {
    return match(regex+1, word+1, restriction);
  }
  
  //check a*a   a
  if (*(regex+1) == '*') {
    if (*word != *regex) {
      if (match(regex+2, word, restriction)) {
        return 1;
      }
    }
  }else{
    //c*d ccd
    if (*regex == '*'){
      //something wrong here, a*a a case doesn't work
      return match(regex-1, word, restriction);
    }
  }

  if (*(regex+1) == '?') {
    if (*word == '\0') {
      return match(regex+2, word, restriction);
    }
    
    if (*word != '\0' && *regex == *word) {
      if (match(regex+2, word+1, restriction)) {
        return 1;
      }
    }

    if(*word != '\0' && *word != *regex){
      if(*(regex+2) == *word){
        return match(regex+2,word,restriction);
      }
    }

    if (*(word+1) == '\0') {
      if (*word != *regex) {
        return 0;
      } 
    }
    /*
    if(*regex != *word){
      if(*regex+2 == *word){
        return match(regex+3,word+1,restriction);
      }
    }
    */
  }else{
    //a? a
    if (*regex == '?' ) {
      if (*word == '\0') {
        return match(regex+1,word,restriction);
      }
      else{
        return match(regex+2,word+1,restriction);
      }
    }
  }

  int groupLength = 0;
  if (*regex == '~') {
    
    const char *groupStart = regex + 1;
    while (*groupStart != '\0' && *groupStart != '~') {
      groupStart++;
      groupLength++;
    }
    
    while(*groupStart == '\0' && *word != '\0'){
      groupLength++;
      if(groupLength <= restriction){
        return match(groupStart,word+1,restriction - groupLength);
      }
    }
    
    if (groupLength <= restriction) {
      if (match(groupStart, word, restriction - groupLength)) {
        return 1;
      }
    }
    
  }else{
    if(*(regex-1) == '~'){
      
      const char *groupStart = regex;
      while(*groupStart == '\0' && *word != '\0'){
        groupLength++;
        if(groupLength <= restriction){
          return match(groupStart,word+1,restriction - groupLength);
        }
      }

    }
  }

  
  return 0; 
}

