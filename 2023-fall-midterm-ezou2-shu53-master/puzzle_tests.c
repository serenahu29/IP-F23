#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ppm_io.h"
#include "puzzle.h"


// also tests puzzle_destroy
void test_puzzle_create(void) {

  Puzzle *p3 = puzzle_create(3);
  Puzzle *p5 = puzzle_create(5);

  assert(p3->size == 3);
  for (int i = 0; i < 9; ++i) {
    assert(p3->tiles[i] == 0);
  }
  
  assert(p5->size == 5);
  for (int i = 0; i < 25; ++i) {
    assert(p5->tiles[i] == 0);
  }

  puzzle_destroy(p3);
  puzzle_destroy(p5);
}

// also tests puzzle_get_tile
void test_puzzle_set_tile(void) {
  int init[4][4] = {
    { 5, 7, 1, 2 },
    { 13, 9, 3, 4 },
    { 0, 8, 6, 11 },
    { 14, 15, 10, 12 },
  };

  Puzzle *p4 = puzzle_create(4);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      puzzle_set_tile(p4, j, i, init[i][j]);

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      assert(puzzle_get_tile(p4, j, i) == init[i][j]);

  puzzle_destroy(p4);
}

// ...other test functions...
void test_command_C(){ //segmentation fault (core dumped)
  Puzzle *p5; 
  FILE * in1 = fopen("testC1.txt", "r");
  //FILE * in2 = fopen("testC2.txt", "r");
  //FILE * in3 = fopen("testC3.txt", "r");
  //FILE * in4 = fopen("testNULL.txt", "r");
  printf("%d", handle_C_command(in1, &p5));
  assert(handle_C_command(in1, &p5)==0);
  //assert(handle_C_command(in2, &p5)==2);
  //assert(handle_C_command(in3, &p5)==1);
  //assert(handle_C_command(in4, &p5)==2);

}
void test_command_T(){
  Puzzle *p6 = puzzle_create(3);
  FILE * in1 = fopen("testT1.txt", "r");
  FILE * in2 = fopen("testT2.txt", "r");
  FILE * in3 = fopen("testT3.txt", "r");
  FILE * in4 = fopen("testNULL.txt", "r");
  assert(handle_T_command(in1, p6)==0); //success
  assert(handle_T_command(in2, p6)==2); //success
  assert(handle_T_command(in3, p6)==3); //success  
  assert(handle_T_command(in4, p6)==2); //failed - taking in a num from a null file
}

void test_command_I(){
  //valid command
  
  FILE* in1 = fopen("testI1.txt", "r");
  Image* background = NULL;
  int result1 = handle_I_command(in1, &background);
  assert(result1 == 0); //success
  assert(background != NULL); //success
  assert(background->rows > 0); 
  assert(background->cols > 0); 
  free(background);
  fclose(in1);
  
}

void test_command_P(){
  Puzzle *p8 = puzzle_create(3);
  FILE * in1 = fopen("testP1.txt", "r");
  assert(handle_P_command(in1, p8)==0);
  puzzle_destroy(p8);

}

void test_command_W(){
  Puzzle* puzzle = puzzle_create(3);
  for (int i = 0; i < 9; i++) {
    puzzle_set_tile(puzzle, i % 3, i / 3, i + 1);
  }

  FILE* sample = fopen("SP2_Aryll.ppm","r");
  Image* background = ReadPPM(sample);

  //valid command- success
  FILE* in1 = fopen("testW1.txt", "r");
  int result1 = handle_W_command(in1, background, puzzle);
  assert(result1 == 0);

  //invalid command- success
  FILE* in2 = fopen("testW2.txt", "r");
  int result2 = handle_W_command(in2, background, puzzle);
  assert(result2 == 1);

  puzzle_destroy(puzzle);
  free(background->data);
  free(background);

}
void test_command_S(){
    Puzzle* p1 = puzzle_create(3);
    int init[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {0, 8, 7}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p1, col, row, init[row][col]);
      }
    }
    FILE * in1 = fopen("testSL.txt", "r");
    assert(handle_S_command(in1, p1) == 0); //success valid command l

  Puzzle* p2 = puzzle_create(3);
      int init1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 8, 7}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p2, col, row, init1[row][col]);
        }
      }
    FILE * in2 = fopen("testSR.txt", "r");
    assert(handle_S_command(in2, p2) == 1); //success invalid command r

    Puzzle* p3 = puzzle_create(3);
    int init2[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 0}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p3, col, row, init2[row][col]);
      }
    }
        FILE * in3 = fopen("testSL.txt", "r");
        assert(handle_S_command(in3, p3) == 1); //invalid command l success

  Puzzle* p4 = puzzle_create(3);
      int init3[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p4, col, row, init3[row][col]);
        }
      }
    FILE * in4 = fopen("testSR.txt", "r");  
    assert(handle_S_command(in4, p4) == 0); //valid command r success

    Puzzle* p5 = puzzle_create(3);
    int init5[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {0, 8, 7}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p5, col, row, init5[row][col]);
      }
    }
    FILE * in5 = fopen("testSD.txt", "r");
    assert(handle_S_command(in5, p5) == 0); // valid command d

  Puzzle* p6 = puzzle_create(3);
      int init6[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 8, 7}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p6, col, row, init6[row][col]);
        }
      }
    FILE * in6 = fopen("testSU.txt", "r");
    assert(handle_S_command(in6, p6) == 1); // invalid command u

    Puzzle* p7 = puzzle_create(3);
    int init7[3][3] = {
      {1, 0, 3},
      {4, 5, 6},
      {7, 8, 2}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p7, col, row, init7[row][col]);
      }
    }
        FILE * in7 = fopen("testSD.txt", "r");
        assert(handle_S_command(in7, p7) == 1); //invalid command d

  Puzzle* p8 = puzzle_create(3);
      int init8[3][3] = {
        {1, 0, 3},
        {4, 5, 6},
        {7, 8, 2}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p8, col, row, init8[row][col]);
        }
      }
    FILE * in8 = fopen("testSU.txt", "r");  
    assert(handle_S_command(in8, p8) == 0); //valid command u
    FILE * in20 = fopen("testNULL.txt", "r");
    assert(handle_S_command(in20, p8)==2);
//handling 5x5
    Puzzle* p9 = puzzle_create(3);
    int init9[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {0, 8, 7}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p9, col, row, init9[row][col]);
      }
    }
    FILE * in9 = fopen("testSL.txt", "r");
    assert(handle_S_command(in9, p9) == 0); //success valid command l

  Puzzle* p10 = puzzle_create(3);
      int init10[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 8, 7}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p10, col, row, init10[row][col]);
        }
      }
    FILE * in10 = fopen("testSR.txt", "r");
    assert(handle_S_command(in10, p10) == 1); //success invalid command r

    Puzzle* p11 = puzzle_create(3);
    int init11[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 0}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p11, col, row, init11[row][col]);
      }
    }
        FILE * in11 = fopen("testSL.txt", "r");
        assert(handle_S_command(in11, p11) == 1); //invalid command l success

  Puzzle* p12 = puzzle_create(3);
      int init12[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p12, col, row, init12[row][col]);
        }
      }
    FILE * in12 = fopen("testSR.txt", "r");  
    assert(handle_S_command(in12, p12) == 0); //valid command r success

    Puzzle* p13 = puzzle_create(3);
    int init13[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {0, 8, 7}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p13, col, row, init13[row][col]);
      }
    }
    FILE * in13 = fopen("testSD.txt", "r");
    assert(handle_S_command(in13, p13) == 0); // valid command d

  Puzzle* p14 = puzzle_create(3);
      int init14[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 8, 7}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p14, col, row, init14[row][col]);
        }
      }
    FILE * in14 = fopen("testSU.txt", "r");
    assert(handle_S_command(in14, p14) == 1); // invalid command u

    Puzzle* p15 = puzzle_create(3);
    int init15[3][3] = {
      {1, 0, 3},
      {4, 5, 6},
      {7, 8, 2}
    };

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        puzzle_set_tile(p15, col, row, init15[row][col]);
      }
    }
        FILE * in15 = fopen("testSD.txt", "r");
        assert(handle_S_command(in15, p15) == 1); //invalid command d

  Puzzle* p16 = puzzle_create(3);
      int init16[3][3] = {
        {1, 0, 3},
        {4, 5, 6},
        {7, 8, 2}
      };

      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          puzzle_set_tile(p16, col, row, init16[row][col]);
        }
      }
    FILE * in16 = fopen("testSU.txt", "r");  
    assert(handle_S_command(in16, p16) == 0); //valid command u
    FILE * in17 = fopen("testNULL.txt", "r");
    assert(handle_S_command(in17, p16)==2);
}
void test_command_K(){
  Puzzle *p = puzzle_create(3);
  
  int init[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
  };

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      puzzle_set_tile(p, col, row, init[row][col]);
    }
  }
  // Test the handle_K_command function- success
  FILE *in = fopen("test_input.txt", "w");
  fprintf(in, "K\n");
  fclose(in);

  in = fopen("test_input.txt", "r");
  int result = handle_K_command(in, p);
  fclose(in);
  assert(result == 1); // Should print "Not solved" and return 0
  // Destroy the puzzle
  puzzle_destroy(p);
}
void test_command_V(){
   Puzzle *p12 = puzzle_create(3);
   int init[3][3] = {
    {3, 0, 1},
    {2, 4, 8},
    {7, 6, 5}
  };

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      puzzle_set_tile(p12, col, row, init[row][col]);
    }
  }
  FILE * in1 = fopen("testT1.txt", "r");  
  assert(handle_V_command(in1, p12) == 0);
}
void test_command_Q(){
  Puzzle *p13 = puzzle_create(3);
  FILE * in1 = fopen("testQ1.txt", "r");  
  assert(handle_Q_command(in1, p13)==0);
}



int main(void) {
  test_puzzle_create();//good
  test_puzzle_set_tile();//good
  test_command_W();//good? still reachable
  test_command_K();//good
  test_command_S();//have memory leak
  test_command_P();//have memory leak
  test_command_I();//1 error (definitely lost)

  // ...call other test functions...
  test_command_C();
  //test_command_T();
  test_command_V();
  
  
  

  printf("All tests passed!\n");
  return 0;
}
