#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ModeValid(){                    //*Mode selection & input validation*//
    int imode;
    bool check;
    char mode[2];
    
    do{
        printf("\n1.Easy\n2.Medium\n3.Hard\n4.Impossible\nChoose game 's difficulty(#1-4):");
        scanf("%s", mode);
        check=true;   
        if (strlen(mode)>1) 
            check=false;
        if (!isdigit(mode[0])) 
            check=false;
        imode=atoi(mode);
        if (imode<1||imode>4) 
            check=false;
        if(check==false) 
            printf("\nWrong input!\n");
    }while(check==false);
    return imode;
}


int TableInVal(int i){
    char dimens[3]; 
    char rc[][10]={"rows","columns"};
    bool check;
    int idimens;

    printf("\nEnter the board's %s to play:", rc[i]);
    scanf("%s", dimens);
        do{  
            check=true;        /*Input Validation for boards' dimensions*/
            if (strlen(dimens)>2) 
                check=false;
            if (!isdigit(dimens[0])) 
                check=false;
            if (!isdigit(dimens[1]) && dimens[1]!='\0') 
                check=false;
            if(check==false){
                printf("\nWrong input! Please insert the number of %s again:\n", rc[i]);
                scanf("%s", dimens);
            }
            idimens=atoi(dimens); 
            if(idimens>52||idimens<4){
                check==false;
            }
        }while(check==false);    
    return idimens;
}

int ModeSelect(char **arr, int rows, int cols, int mode){
    int i, j, trpNum, obst, randRow, randCol;
    if(mode==1){                        //*Mode selection statements*//
        trpNum=(rows*cols)*0.02;
        obst=(rows*cols)*0.13;
    }else if(mode==2){
        trpNum=(rows*cols)*0.05;
        obst=(rows*cols)*0.1;
    }else if(mode==3){
        trpNum=(rows*cols)*0.1;
        obst=(rows*cols)*0.05;
    }else{
        trpNum=(rows*cols)*0.15;
        obst=0;
    }
    if(trpNum<2){
        trpNum=2;
    }
    srand(time(0));                         
                                    //*Obstacle generator*//
    for(i=0;i<obst;i++){
        randRow= rand()%rows;
        randCol= rand()%cols;
        if(arr[randRow][randCol]=='#'){
            arr[randRow][randCol]='X';
        }else{
            i--;
        }
    }
    return trpNum;
}

char** Board(int rows, int cols){
    int i,j;
    char** arr;

    arr=(char**)malloc(rows*sizeof(char*));     //*Board's memory allocation*//
    for(i=0;i<rows;i++){
        arr[i]=(char*)malloc(cols*sizeof(char));
    }
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            arr[i][j]='#';
        }
    }
    return arr;
}

typedef struct{
    int row;
    int col;
    int prevRow;
    int prevCol;
}Position;

typedef struct
{
   Position Leia;
   Position DVader;
   Position R2d2;
}Character;


Character InitialChar(char** arr, int rows, int cols){
    int corner, randRow, randCol;
    Character pos;

    srand(time(0));
    corner=rand()%4;                    //*Generate Vaders' starting point*//
    if(corner==0){
        arr[0][0]='D';
        pos.DVader.row= pos.DVader.prevRow= 0;
        pos.DVader.col= pos.DVader.prevCol= 0;
    }else if(corner==1){
        arr[0][cols-1]='D';
        pos.DVader.row= pos.DVader.prevRow= 0;
        pos.DVader.col= pos.DVader.prevCol= cols-1;
    }else if(corner==2){
        arr[rows-1][0]= 'D';
        pos.DVader.row= pos.DVader.prevRow= rows-1;
        pos.DVader.col= pos.DVader.prevCol= 0;
    }else{
        arr[rows-1][cols-1]= 'D';
        pos.DVader.row= pos.DVader.prevRow= rows-1;
        pos.DVader.col= pos.DVader.prevCol= cols-1;
    }
    do{                                      //*Generate R2D2s' starting point*//
        randRow= rand()%rows;
        randCol= rand()%cols;
    }while(arr[randRow][randCol]!='#');
    arr[randRow][randCol]='R';
    pos.R2d2.row= randRow;
    pos.R2d2.col= randCol;
    do{                                     //*Generate Leias' starting point//*
        randRow= rand()%rows;
        randCol= rand()%cols;
    }while(arr[randRow][randCol]!='#');
    arr[randRow][randCol]='L';
    pos.Leia.row= pos.Leia.prevRow= randRow;
    pos.Leia.col= pos.Leia.prevCol= randCol;

    return pos;

}

void TablePrint(char** arr, int rows, int cols, int mode, Character *characters){         //Board  print//
    int i,j,corner,randRow,randCol;
    
    printf("   ");
    if(cols<=26){                              //*print boards' labels using ASCII code//
        for(i=65;i<(cols+65);i++){
            printf("%c ", i);
        }
    }
    else if(cols>26){
        for(i=65;i<=90;i++){
            printf("%c ", i);
        }
        for(i=97;i<(cols+70);i++){
            printf("%c ", i);
        }
    }
    printf("\n");
    for(i=0;i<=(2*cols+1);i++){
        printf("-");
    }
    printf("\n");
    for(i=0;i<rows;i++){
        if(i<9){
            printf(" %d|",i+1);
            for(j=0;j<cols;j++){
                if(i==characters->Leia.row||j==characters->Leia.col){
                    if(arr[i][j]=='#'){
                        printf(". ");
                    }else{
                        printf("%c ", arr[i][j]);
                    }
                }else{
                    if(arr[i][j]=='@'||arr[i][j]=='R'){
                    printf("# ");
                    }else{
                    printf("%c ", arr[i][j] );
                    }   
                }     
            }       
        }
        else{
            printf("%d|",i+1);
            for(j=0;j<cols;j++){
                if(i==characters->Leia.row||j==characters->Leia.col){
                    if(arr[i][j]=='#'){
                        printf(". ");
                    }else{
                        printf("%c ", arr[i][j]);
                    }
                }else
                    if(arr[i][j]=='@'||arr[i][j]=='R'){
                        printf("# ");
                    }else{
                        printf("%c ", arr[i][j] );
                    }
                }    
            }
            printf("\n");   
        }
        printf("\n");
    }

char* getLeiaMoves() {
    static char moves[1024];  
    char input[1024], move;
    int i,j = 0;

    printf("Enter your move(s): ");
    scanf("%s", input);
    for(i = 0;input[i]!='\0'&&j<sizeof(moves)-1; i++) {
        move = toupper(input[i]);
        if (move =='U'||move=='D'||move=='L'||move=='R') {
            moves[j]=move;
            j++;
        }else if(move=='X'){
            moves[j]=move;
            j++;
        }
    }
    moves[j]='\0';

    return moves;
}

int LeiaMoves(char **board, int rows, int cols, Character *characters, const char *moves, int *extralives){
    int leiaMovesCount,i;
    int newRow = characters->Leia.row, newCol = characters->Leia.col;
    characters->Leia.prevRow= characters->Leia.row;
    characters->Leia.prevCol= characters->Leia.col;
    for(i=0; moves[i]!='\0'; i++){
        if(moves[i]=='X'){
            (*extralives)=-4;
        }
        if(moves[i]=='U'){
            newRow--;  
        }else if(moves[i]=='D'){
            newRow++;  
        }else if(moves[i]=='L'){
            newCol--; 
        }else if(moves[i]=='R'){
            newCol++;  
        }
        if(newRow<0||newRow>=rows||newCol<0||newCol>=cols){
            printf("Leia tries to go out of the spaceship! No matter there are walls around.\n");
            continue;
        }
        if (board[newRow][newCol] == 'D') {
            printf("Leia encounters Vader! Game over.\n");
            board[characters->Leia.row][characters->Leia.col]='#';
            characters->Leia.row= newRow;
            characters->Leia.col= newCol;
            board[newRow][newCol]='D';
            (*extralives)= -2;
           
        } else if (board[newRow][newCol] == '@') {
            printf("Leia encounters a Stormtrooper!\n");
            board[characters->Leia.row][characters->Leia.col]='#'; 
            characters->Leia.row=newRow;
            characters->Leia.col=newCol;
            board[newRow][newCol]='L';
            (*extralives)--;
            leiaMovesCount++;
            
        } else if(board[newRow][newCol]=='X') {
            printf("Leia hits an obstacle. Move blocked.\n");
            
        } else {
            printf("Leia moves to (%d, %d).\n",newRow+1,newCol+1);
            board[characters->Leia.row][characters->Leia.col]= '#';
            characters->Leia.row= newRow;
            characters->Leia.col= newCol;
            board[newRow][newCol]='L';
            leiaMovesCount++;
        }
    }
    return leiaMovesCount;
}

void VaderMoves(char **board, int rows, int cols, Character *characters, int leiaMovesCount) {
    int dist,newRow,newCol,vaderRow,vaderCol,leiaRow,leiaCol,i;
    int dRow[]= {-1, -1, -1, 0, 0, 1, 1, 1};
    int dCol[]= {-1, 0, 1, -1, 1, -1, 0, 1};
    int bestMove= -1;
    int minDistance = rows * cols;
    if(leiaMovesCount%2==0&&leiaMovesCount>1){
        vaderRow= characters->DVader.row;
        vaderCol= characters->DVader.col;
        leiaRow= characters->Leia.row;
        leiaCol= characters->Leia.col;

        for(i=0;i<8;i++){
             newRow=vaderRow+dRow[i];
             newCol=vaderCol+dCol[i];
            if (newRow>=0&&newRow<rows&&newCol>=0&&newCol<cols&&board[newRow][newCol]=='#'){
                 dist= abs(newRow-leiaRow)+abs(newCol-leiaCol);
                if (dist<minDistance) {
                    minDistance= dist;
                    bestMove= i;
                }
            }
        }
        if(bestMove!=-1){
            board[vaderRow][vaderCol]='#'; 
            vaderRow+=dRow[bestMove];
            vaderCol+=dCol[bestMove];
            characters->DVader.row=vaderRow;
            characters->DVader.col=vaderCol;
            board[vaderRow][vaderCol]='D';
            if(vaderRow==leiaRow&&vaderCol==leiaCol){
                board[vaderRow][vaderCol]='D';
            }
        }
    }
}

typedef struct{
    int row;
    int col;
    int drow;
    int dcol;
} Stormtrooper;

Stormtrooper* TroopGen(char** arr, int rows, int cols, int trpNum) {
    int randRow, randCol, i= 0;
    int attempts= 0;
    Stormtrooper* troopers;

    troopers=(Stormtrooper*)malloc(trpNum*sizeof(Stormtrooper));

    while (i<trpNum&&attempts<trpNum*10) { 
        randRow= rand()%rows;
        randCol= rand()%cols;

        if (arr[randRow][randCol]=='#') {
            arr[randRow][randCol]= '@';
            troopers[i].row= randRow;
            troopers[i].col= randCol;

            if (rand()%2==0){ 
                troopers[i].drow= 0; //no movement//
                troopers[i].dcol= (rand()%2)*2-1; //-1 left,1 right//
            }else{
                troopers[i].drow= (rand()%2)*2-1; //-1 up,1 down//
                troopers[i].dcol= 0; //no movement//
            }
            i++;
        } else {
            attempts++;
        }
    }
    return troopers;
   
}

int Patrol(Stormtrooper* troopers, char** board, int rows, int cols,
             int numTroopers, int deadTroop,Character *characters) {
    int i,newRow,newCol;
    for (i=0; i<numTroopers; i++){
        if(board[characters->Leia.row][characters->Leia.col]==board[troopers[i].row][troopers[i].col]){
                troopers[i].drow=0;
                troopers[i].dcol=0;
                board[troopers[i].row][troopers[i].col]= '#';
                deadTroop=i;
        }else{
            if(i!=deadTroop){    
            newRow= troopers[i].row+troopers[i].drow;
            newCol= troopers[i].col+troopers[i].dcol;
            if(newRow<0||newRow>=rows||newCol<0||newCol>=cols||
                board[newRow][newCol]=='X'||  
                board[newRow][newCol]=='R'||  
                board[newRow][newCol]=='@'){  
                
                troopers[i].drow= -troopers[i].drow;
                troopers[i].dcol= -troopers[i].dcol;
                newRow= troopers[i].row+troopers[i].drow;
                newCol= troopers[i].col+troopers[i].dcol;
                board[troopers[i].row][troopers[i].col] = '#';  
                troopers[i].row=newRow;
                troopers[i].col=newCol;
                board[newRow][newCol]='@';  
            } else if (board[newRow][newCol]=='L'){
                troopers[i].drow =0;
                troopers[i].dcol=0;
                board[troopers[i].row][troopers[i].col]='#';
                board[newRow][newCol]='L';
                deadTroop=i;
            }else{
                if(board[troopers[i].row][troopers[i].col]!='L'){
                    board[troopers[i].row][troopers[i].col]='#';  
                }
                troopers[i].row=newRow;
                troopers[i].col=newCol;
                board[newRow][newCol]='@';  
            }  
        }
        }    
    }
    return deadTroop;
}

typedef enum {
    GameContinue,
    GameWin,
    GameLose
} GameState;

GameState CheckWinLose(char **board, int rows, int cols, Character *characters, int *extralives) {
   
    if(characters->Leia.row == characters->R2d2.row && characters->Leia.col == characters->R2d2.col) {
        return GameWin;
    }
    if(*extralives==-4){
        printf("\nGood bye\nGame exiting...");
        return GameLose;
    }
   
        if(*extralives==0){
            
            
            printf("\nLeia met a stormtrooper! She vanished him, but got injured!");
            return GameContinue;
        }
        else if (*extralives==-1)
        {
            printf("\nStormtroopers on the way again! Leia is dead! You Lose!");
            return GameLose;
        }else if(characters->Leia.row==characters->DVader.row&&characters->Leia.col==characters->DVader.col||*extralives==-2) {
        printf("\nLeia met Darth Vader! She is sturdust by now! You Lost!");
        return GameLose;
        }else{
        return GameContinue;
        }   
}

int main(){
    char* moves;
    int rows,cols,i,j,mode,Lmoves,count,troopNum,extralives=1,deadTroop=-1;
    int* extraptr;
    char** arr;
    Character pos;
    Stormtrooper* troopers;
    GameState winLoss;
    printf("Welcome to A New Hope!\nThe Star Wars Saga.\n");            /*Intro, user input*/
    rows= TableInVal(0);
    cols= TableInVal(1);
    mode= ModeValid();
    printf("We have a %d x %d board! Let 's smash it!\n", rows, cols);
    while((rows>=4||cols>=4)&&extralives>=0){
        arr= Board(rows, cols);
        troopNum= ModeSelect(arr, rows, cols, mode);
        troopers= TroopGen(arr, rows, cols, troopNum);
        pos= InitialChar(arr, rows, cols);
        extraptr=&extralives;
        extralives=1;
        winLoss=GameContinue;
        TablePrint(arr, rows, cols, mode, &pos);
        do{
            moves=getLeiaMoves();
            Lmoves=LeiaMoves(arr, rows, cols, &pos, moves,extraptr);
            count+=Lmoves;
            VaderMoves(arr,rows,cols,&pos,count);
            deadTroop=Patrol(troopers,arr,rows,cols,troopNum,deadTroop,&pos);
            TablePrint(arr,rows,cols,mode, &pos);
            winLoss=CheckWinLose(arr,rows,cols,&pos,extraptr);
            printf("\nextralives :%d\n",*extraptr);
        }while(winLoss==GameContinue);
    
        for(i=0;i<rows;i++){
            free(arr[i]);
        }
        free(arr);
        free(troopers);
        rows--;
        cols--;
    }
    
    return 0;
}