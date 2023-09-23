#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ONLY REQUIRED ON WINDOWS SYSTEM
// #include <io.h>
// #include <fcntl.h>


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
  // Setting mode to binary for this file stream, ONLY ON WINDOWS
  // _setmode(_fileno(fp), _O_BINARY); 
    
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
  char output = '?';
  switch (c) {
    case '^':
      output = 'w';
      break;
    case '<':
      output = 'a';
      break;
    case 'v':
      output = 's';
      break;
    case '>':
      output = 'd';
      break;
  }
  return output;
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  char output = '?';
  switch (c) {
    case 'W':
      output = '^';
      break;
    case 'A':
      output = '<';
      break;
    case 'S':
      output = 'v';
      break;
    case 'D':
      output = '>';
      break;
  }
  return output;
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if (c == 'v' || c == 's' || c == 'S') {
    return cur_row + 1;
  } else if (c == '^' || c == 'w' || c == 'W'){
    return cur_row - 1;
  } else {
    return cur_row;
  }
}


/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (c == '>' || c == 'd' || c == 'D') {
    return cur_col + 1;
  } else if (c == '<' || c == 'a' || c == 'A'){
    return cur_col - 1;
  } else {
    return cur_col;
  }
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  snake_t snake = (state -> snakes)[snum];
  unsigned int snake_head_col = snake.head_col;
  unsigned int snake_head_row = snake.head_row;
  char snake_head = get_board_at(state, snake_head_row, snake_head_col);
  return get_board_at(state, get_next_row(snake_head_row, snake_head), get_next_col(snake_head_col, snake_head));
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
  snake_t curr_snake = (state -> snakes)[snum];
  snake_t* next_snake_pointer = state -> snakes + snum;

  unsigned int curr_snake_head_row = curr_snake.head_row;
  unsigned int curr_snake_head_col = curr_snake.head_col;

  char curr_snake_head = get_board_at(state, curr_snake_head_row, curr_snake_head_col);
  
  unsigned int next_snake_head_row = get_next_row(curr_snake_head_row, curr_snake_head);
  unsigned int next_snake_head_col = get_next_col(curr_snake_head_col, curr_snake_head);
  
  next_snake_pointer -> head_row = next_snake_head_row;
  next_snake_pointer -> head_col = next_snake_head_col;

  set_board_at(state, next_snake_head_row, next_snake_head_col, curr_snake_head);
  switch (curr_snake_head) {
    case 'W':
      set_board_at(state, curr_snake_head_row, curr_snake_head_col, '^');
      break;
    case 'A':
      set_board_at(state, curr_snake_head_row, curr_snake_head_col, '<');
      break;
    case 'S':
      set_board_at(state, curr_snake_head_row, curr_snake_head_col, 'v');
      break;
    case 'D':
      set_board_at(state, curr_snake_head_row, curr_snake_head_col, '>');
      break;
  }

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
  snake_t curr_snake = (state -> snakes)[snum];
  snake_t* next_snake_pointer = state -> snakes + snum;

  unsigned int curr_snake_tail_row = curr_snake.tail_row;
  unsigned int curr_snake_tail_col = curr_snake.tail_col;

  char curr_snake_tail = get_board_at(state, curr_snake_tail_row, curr_snake_tail_col);
  
  unsigned int next_snake_tail_row = get_next_row(curr_snake_tail_row, curr_snake_tail);
  unsigned int next_snake_tail_col = get_next_col(curr_snake_tail_col, curr_snake_tail);

  char next_snake_body = get_board_at(state, next_snake_tail_row, next_snake_tail_col);

  switch (next_snake_body) {
    case '^':
      set_board_at(state, next_snake_tail_row, next_snake_tail_col, 'w');
      break;
    case '<':
      set_board_at(state, next_snake_tail_row, next_snake_tail_col, 'a');
      break;
    case 'v':
      set_board_at(state, next_snake_tail_row, next_snake_tail_col, 's');
      break;
    case '>':
      set_board_at(state, next_snake_tail_row, next_snake_tail_col, 'd');
      break;
  }

  next_snake_pointer -> tail_row = next_snake_tail_row;
  next_snake_pointer -> tail_col = next_snake_tail_col;

  set_board_at(state, curr_snake_tail_row, curr_snake_tail_col, ' ');
  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.

  snake_t* all_snakes_arr_pointer = state -> snakes;
  unsigned int snakes_num = state -> num_snakes;

  for (unsigned int i = 0; i < snakes_num; i++) {
    snake_t* curr_snake_pointer = all_snakes_arr_pointer + i; 
    char next_square_value = next_square(state, i);
    if (next_square_value == '*') {
      // If the next square for i-th snake is a fruit, lengthen the snake by 1
      update_head(state, i);
      // Generate a random fruit elsewhere.
      add_food(state);
    } else if (next_square_value == '#' || is_snake(next_square_value)) {
      // If the next square for i-th snake is a wall/snake body, update the head to be 'x' and declare its death
      set_board_at(state, curr_snake_pointer -> head_row, curr_snake_pointer -> head_col, 'x');
      curr_snake_pointer -> live = false;
    } else {
      update_head(state, i);
      update_tail(state, i);
    }
  }
  return;
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  // 1. Initialize the game_struct_t
  game_state_t* game_state = (game_state_t*) malloc(sizeof(game_state_t));

  int board_capacity = 1;
  game_state -> board = (char**) malloc(sizeof(char*) * board_capacity);
  game_state -> num_snakes = 0;
  game_state -> snakes = NULL;

  // 2. Load the board from file
  FILE* fp = fopen(filename, "r");
  int ch;
  if (fp == NULL) {
    perror("Error opening file.");
    return NULL;
  }

  // 3. Get the board dpointer
  // 3.1 Allocate memory for borad_pointer
  char** board_pointer = game_state -> board;

  unsigned int row_index = 0;

  size_t len = 0;
  
  size_t capacity = 16; // Initial buffer size, can be extended or shrinked.
  char* buf = (char*) malloc(capacity + 1); // Initial buffer, allowing for null terminator
  
  // 4. Start injecting into the game_state_object
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      char* row_string = (char*) malloc(len + 1); // Allow for the null terminator.
      strncpy(row_string, buf, len);
      row_string[len] = '\0';
      board_pointer[row_index] = row_string;
      free(buf);
      len = 0;  // Reset the length accumulator for the current row
      row_index++;
      // Allocate new memory for new buffer
      buf = (char*) malloc(capacity + 1);
      // Allocate new memory for new row
      board_capacity++;
      board_pointer = (char**) realloc(board_pointer, sizeof(char*) * board_capacity);
      game_state -> board = board_pointer; // Be really careful, we have to update the memory pointer.
    } else {
      buf[len] = (char) ch;
      len++;
      if (len >= capacity) {
        // Expand the buffer
        size_t new_capacity = capacity * 2;
        buf = (char*) realloc(buf, new_capacity);
        capacity = new_capacity;
      }
    }
  }

  // Initialize the height
  game_state -> num_rows = row_index;

  free(buf);

  fclose(fp);

  return game_state;
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
  snake_t* snake_pointer = state -> snakes + snum;

  unsigned int start_row = snake_pointer -> tail_row; 
  unsigned int start_col = snake_pointer -> tail_col;

  char curr_char = get_board_at(state, start_row, start_col);

  while (curr_char != 'W' && curr_char != 'A'
  && curr_char != 'S' && curr_char != 'D') {
      start_row = get_next_row(start_row, curr_char);
      start_col = get_next_col(start_col, curr_char);
      curr_char = get_board_at(state, start_row, start_col);
  }

  snake_pointer -> head_row = start_row;
  snake_pointer -> head_col = start_col;

  return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  char** board = state -> board;

  int snake_capacity = 1;
  int snake_num = 0;
  state -> snakes = (snake_t*) malloc(sizeof(snake_t) * snake_capacity);

  int board_row_length = state -> num_rows;

  for (unsigned int i = 0 ; i < board_row_length; i++) {
    char* row_pointer = board[i];
    for (unsigned int j = 0; j < strlen(row_pointer); j++) {
      if (row_pointer[j] == 'w' || row_pointer[j] == 'a' 
      || row_pointer[j] == 's' || row_pointer[j] == 'd') {
        if (snake_num >= snake_capacity) {
          int new_snake_capacity = snake_capacity * 2;
          snake_capacity = new_snake_capacity;
          state -> snakes = (snake_t*) realloc(state -> snakes, sizeof(snake_t) * snake_capacity);
        }
        // Find tails
        (state -> snakes + snake_num)->tail_row = i;
        (state -> snakes + snake_num)->tail_col = j;
        // FInd heads
        find_head(state, snake_num);
        snake_num++;
        }
      }
    }

    state -> num_snakes = snake_num;
  
  return state;
}