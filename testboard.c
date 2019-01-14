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

int place(char board[8][8], char x, char y, char length, int rot){
  if(rot == 0){
    if(y + length > 8){
      return -1;
    }
    for(int l = 0; l < length; l++){
      if(board[x][y+l]){
	return -1;
      }
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
      if(board[x+l][y]){
	return -1;
      }
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
    if(board[x-1][y] != 1 && board[x+1][y] != 1 && board[x][y-1] != 1 && board[x][y+1] != 1){
      printf("Ship sunk!");
    }
    return 1;
  }
  else{
    printf("%d MISS!\n", board[x][y]);
    board[x][y] = 3;
    return 0;
  }
}

int display(char board[8][8], char op){
  printf("\n  0 1 2 3 4 5 6 7\n");
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
  printf("\n");
}

int initialize(char board[8][8]){
  int x;
  int y;
  int rot;
  char* boats[5] = {"Battleship", "Destroyer", "Submarine", "Patrol Boat", "Carrier"};
  int sizes[5] = {4,3,3,2,5};
  for(int s = 0; s < 5; s++){
    display(board, 1);
    printf("Place %s(%d): ",boats[s],sizes[s]);
    scanf("%d %d %d", &x, &y, &rot);
    int good = place(board, x,y,sizes[s],rot);
    while(good == -1){
      printf("Place again!\n");
      display(board, 1);
      printf("Place %s(%d): ",boats[s],sizes[s]);
      scanf("%d %d %d", &x, &y, &rot);
      good = place(board, x,y,sizes[s],rot);
    }
    good = 0;
  }
  return 0;
}

int main(){
  int redscore = 17;
  int bluescore = 17;
  char red[8][8];
  char blue[8][8];
  build(blue);
  build(red);
  initialize(red);
  display(red, 1);
  int tarx;
  int tary;
  while(!(redscore && bluescore)){
    display(red, 0);
    printf("Select your target: ");
    scanf("%d %d", &tarx, &tary);
    hit(red, tarx, tary);
  }
}
