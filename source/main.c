#include "bitboard.h"
#include "bitboard_func.h"
#include "board.h"
#include "engine.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"

#define ONBOARD_LED 25
#define PLAYER_COLOR 1

int main(void)
{
  stdio_init_all();
  gpio_init(ONBOARD_LED);
  gpio_set_dir(ONBOARD_LED, GPIO_OUT);
    
  sleep_ms(5000);
  printf("starting now...\n");
  gpio_put(ONBOARD_LED, 1);

  BOARD_Board board = BOARD_SetupBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
  // BOARD_Board board = BOARD_SetupBoard("k7/6P1/8/8/8/8/8/K7 w");
  // BOARD_Board board = BOARD_SetupBoard("r3k2r/r3P3/6n1/4b3/1K6/8/4p3/8 b kq");
  // BOARD_Board board = BOARD_SetupBoard("2R5/1k6/8/8/8/8/K7/8 w ");
  // BOARD_Board board = BOARD_SetupBoard("7R/k7/8/8/8/8/K7/8 w ");
      
  BOARD_PrintPrettyBoard(&board.board);
  
  while(1){
    // gpio_put(ONBOARD_LED, 1);
    // printf("on\n");
    // sleep_ms(500);
    // gpio_put(ONBOARD_LED, 0);
    // printf("off\n");
    // sleep_ms(500);

    if(UTIL_GetBoolFromBools(board.board.bools, INDEX_GAME_END)==0){
      // BOARD_PrintPrettyBoard(&board.board);
      // BOARD_PrintBitmaps(&board.board);
      // sleep_ms(2000);
      if(UTIL_GetBoolFromBools(board.board.bools, INDEX_ON_TURN)==PLAYER_COLOR){
        BOARD_PlayTurn(&board);
      }
      else{
        
        ENGINE_PlayTurn(&board);
        BOARD_PrintPrettyBoard(&board.board);

        // BOARD_PlayTurn(&board);
      }
    }
    else{
      // BOARD_DrawBoard(&board, TS, TS, &board.board.bools);
      BOARD_PrintPrettyBoard(&board.board);
      if(UTIL_GetBoolFromBools(board.board.bools, INDEX_DRAW)){
        printf("Game ended in Draw\n");
      }
      else{
        if(UTIL_GetBoolFromBools(board.board.bools, INDEX_WIN)){
          printf("White won by checkmate\n");
        }
        else{
          printf("Black won by checkmate\n");
        }
      } 
    }

  } 

  return 0;
}
