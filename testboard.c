#include <stdio.h>
#include <stdlib.h>

int build(char board[8][8]){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      board[x][y] = 0;
    }
  }
  return 0;
}

int hit(char board[8][8], int x, int y){
  board[x][y] = 2;
  if(board[x][y] == 2){
    return 0;
  }
  return -1;
}

int main(){
  
  char board[8][8];
  build(board);
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      //printf("%d %d \n", x,y);
      printf("%d", board[x][y]);
    }
    printf("\n");
  }
}
