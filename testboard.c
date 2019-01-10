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

int place(char board[8][8], char x, char y, char length, char rot){
  if(rot == 0){
    if(y + length > 8){
      return -1;
    }
    for(int l = 0; l < length; l++){
      board[x][y+l] = 1;
    }
    return 0;
  }
  if(rot == 1){
    if(x + length > 8){
      return -1;
    }
    for(int l = 0; l < length; l++){
      board[x+l][y] = 1;
    }
    return 0;
  }
}

int hit(char board[8][8], int x, int y){
  if(board[x][y] == 1){
    printf("%d HIT!\n", board[x][y]);
    board[x][y] = 2;
    return 1;
  }
  else{
    printf("%d MISS!\n", board[x][y]);
    board[x][y] = 3;
    return 0;
  }
}

int display(char board[8][8], char op){
  printf("  0 1 2 3 4 5 6 7\n");
  for(int y = 0; y < 8; y++){
    printf("%d ", y);
    for(int x = 0; x < 8; x++){
      if(op){
	printf("%d ", board[x][y]);
      }
      else{
	if(board[x][y] == 1){
	  printf("0 ");
	}
	else{
	  printf("%d ", board[x][y]);
	}
      }
    }
    printf("\n");
  }
}

int main(){
  
  char red[8][8];
  char blue[8][8];
  build(blue);
  build(red);
  place(red, 2, 3, 4, 0);
  place(red, 0, 4, 4, 1);
  display(red, 1);
  printf("\n");
  display(blue, 0);
  
}
