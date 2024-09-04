#include <stdio.h>

#include "player_ops.h"
#include "player.h"

int main(void) {
  struct Player the_player = {
    .x = 10, .y = 5, .symbol = '@', .health = 121
  };

  printf("Player position %d,%d\n",
         the_player.x, the_player.y);

  move_player(&the_player, +3, -1);

  printf("New player position %d,%d\n",
         the_player.x, the_player.y);

  return 0;
}