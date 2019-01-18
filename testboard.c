#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int build(char board[8][8]){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      board[x][y] = 0;
    }
  }
  return 0;
}

/*scrapped
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
*/

int place(char board[8][8], char x, char y, int boat, int rot){
  int sizes[5] = {4,3,3,2,5};
  int length = sizes[boat];
  boat += 4;
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
      board[x][y+l] = boat;
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
      board[x+l][y] = boat;
    }
    return 0;
  }
}

int hit(char board[8][8], int x, int y, int score[5], int *points){
  if(x<0 || x>7 || y<0 || y>7){
    return -1;
  }
  char* boats[5] = {"Battleship", "Destroyer", "Submarine", "Patrol Boat", "Carrier"};
  if(board[x][y] == 1 || board[x][y] > 3){
    printf("HIT!\n");
    printf("%d\n",score[board[x][y]-4]);
    score[board[x][y]-4]--;
    printf("%d\n",score[board[x][y]-4]);
    if(score[board[x][y]-4]<1){
      printf("YOU SUNK THEIR %s!!!\n", boats[board[x][y]-4]);
    }
    board[x][y] = 2;
    *points -= 1;
    return 1;
  }
  else{
    printf("MISS!\n");
    if(!board[x][y]){
      board[x][y] = 3;
      return 0;
    }
    if(board[x][y] == 2){
      printf("Already BOOMed!\n");
      return -1;
    }
    return -1;
  }
}

int display(char board[8][8], char op){
  printf("\n\e[0m  0 1 2 3 4 5 6 7\n");
  char * standards[] = {"\e[106m", "\e[100m", "\e[101m", "\e[47m"};
  for(int y = 0; y < 8; y++){
    printf("\e[0m%d ", y);
    for(int x = 0; x < 8; x++){
      if(op){
	int value;
	if(board[x][y]>3){
	  value = 1;
	}
	else{
	  value = board[x][y];
	}
	printf("%s%d ", standards[value], board[x][y]);
      }
      else{
	if(board[x][y] == 1||board[x][y] > 3){
	  printf("\e[106m0 ");
	}
	else{
	  printf("%s%d ", standards[board[x][y]], board[x][y]);
	}
      }
    }
    printf("\n");
  }
  printf("\e[0m\n");
}

/* scrapped
int hide(char fake[8][8], char board[8][8]){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      if(board[x][y] < 3){
	
      }
    }
  }
  return 0;
}
*/

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
    int good = place(board, x,y,s,rot);
    while(good == -1){
      printf("Place again!\n");
      display(board, 1);
      printf("Place %s(%d): ",boats[s],sizes[s]);
      scanf("%d %d %d", &x, &y, &rot);
      good = place(board, x,y,s,rot);
    }
    good = 0;
  }
  return 0;
}

int rinit(char board[8][8]){
  srandom(time(NULL));
  char* boats[5] = {"Battleship", "Destroyer", "Submarine", "Patrol Boat", "Carrier"};
  int sizes[5] = {4,3,3,2,5};
  for(int s = 0; s < 5; s++){
    int good = place(board, random()%8,random()%8,s,random()%2);
    while(good == -1){
      good = place(board, random()%8,random()%8,s,random()%2);
    }
    good = 0;
  }
  return 0;
}

int main(){
  int bluescore[5] = {4,3,3,2,5};
  int  redscore[5] = {4,3,3,2,5};
  int redhp = 17;
  int bluehp = 17;
  char red[8][8];
  char blue[8][8];
  build(blue);
  build(red);
  //initialize(red);
  //display(red, 1);
  int tarx;
  int tary;
  rinit(blue);
  display(blue, 1);
  system("clear");
  display(blue, 1);
  printf("Select your target: ");
  scanf("%d %d", &tarx, &tary);
  while(redhp && bluehp){
    system("clear");
    hit(blue, tarx, tary, bluescore,&bluehp);
    printf("[");
    for(int x = 0; x < 5; x++){
      printf(" %d,", bluescore[x]);
    }
    printf("]\nBlueHP: %d\n", bluehp);
    display(blue, 1);
    if(bluehp < 1){
      printf("Red Wins!");
      break;
    }
    printf("Select your target: ");
    scanf("%d %d", &tarx, &tary);
    
  }
}
