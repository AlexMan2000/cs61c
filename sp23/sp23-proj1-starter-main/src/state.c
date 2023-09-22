#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAIL "wasd"
#define FRONT "WASD"
#define SNAKE "wasd^<v>WASDx"

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.

  // Initial parameters

  // Initialize the game_state_t in the heap
  game_state_t* game_state = (game_state_t*) malloc(sizeof(game_state_t));
  game_state -> num_rows = 18;
  game_state -> num_snakes = 1;

  // Initialize the snake array
  snake_t* snakes = (snake_t*) malloc(sizeof(snake_t) * game_state -> num_snakes);
  
  // Initialize the board(2d array)
  char** board = (char**) malloc(sizeof(char*) * game_state->num_rows);
  for (int i = 0; i < game_state -> num_rows; i++) {
    char* row = (char*) malloc(sizeof(char) * 21); // Careful here, dont' miss the null terminators
    board[i] = row;
  }

  strcpy(board[0], "####################");
  strcpy(board[game_state -> num_rows - 1], "####################");
  for (int i = 1; i < game_state -> num_rows - 1; i++){
    strcpy(board[i], "#                  #");
  }

  // Initialize the snake
  snakes[0].tail_row = 2;
  snakes[0].tail_col = 2;
  snakes[0].head_row = 2;
  snakes[0].head_col = 4;
  snakes[0].live = true;

  board[2][2] = 'd';
  board[2][3] = '>';
  board[2][4] = 'D';


  // Initialize the fruit
  board[2][9] = '*';


  // Assemble the game_state
  game_state -> board = board;
  game_state -> snakes = snakes;

  return game_state;
}

/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.

  // Free board
  char** board = state -> board;
  for (int i = 0; i < state -> num_rows; i++) {
    char* row_pointer = board[i];
    free(row_pointer); 
  }
  free(board);

  // Free snakes
  snake_t* snake_arr = state -> snakes;
  free(snake_arr);

  // Free game_state
  free(state);

  return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  unsigned int nrows = state -> num_rows;
  char** board = state -> board;
  for (int i = 0; i < nrows; i++) {
    char* row_pointer = board[i];
    fprintf(fp, "%s\n", row_pointer);
  }

  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  int i = 0;
  while (i < strlen(TAIL)) {
    if (TAIL[i] == c) {
      return true;
    }
    i++;
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  int i = 0;
  while (i < strlen(FRONT)) {
    if (FRONT[i] == c) {
      return true;
    }
    i++;
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  int i = 0;
  while (i < strlen(SNAKE)) {
    if (SNAKE[i] == c) {
      return true;
    }
    i++;
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return '?';
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  return;
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  return NULL;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  return NULL;
}
