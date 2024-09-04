#ifndef PUZZLE_H
#define PUZZLE_H

#include "ppm_io.h" // for Image data type

typedef struct {
  //image;
  Image image;
  //config
  //int * config;
  //num of rows and columns
  //int * numRows;

  int size;
  int * tiles;
  //int ** tiles;

} Puzzle;

// TODO: function declarations
Puzzle *puzzle_create(int size);
void puzzle_destroy(Puzzle *p);
void puzzle_set_tile(Puzzle *p, int col, int row, int value);
int puzzle_get_tile(const Puzzle *p, int col, int row);

int handle_C_command(FILE *in, Puzzle **p);
int handle_T_command(FILE *in, Puzzle *p);
int handle_I_command(FILE *in, Image** background);
int handle_P_command(FILE *in, Puzzle *p);
int handle_W_command(FILE* in, const Image* background, const Puzzle* p);
int handle_S_command(FILE *in, Puzzle *p);
int handle_K_command(FILE *in, Puzzle *p);
int handle_V_command(FILE *in, Puzzle *p);
int handle_Q_command(FILE *in, Puzzle *p); 

#endif // PUZZLE_H
