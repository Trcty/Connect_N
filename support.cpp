//
//  support.cpp
//
//  Created by Zhiwen Cao on 5/9/21.
//

#include "support.h"
#include "provided.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;



//get the next available level for the player
int next_level_available(const Scaffold& b,int col){
    int i=1;
    if(b.checkerAt(col, i)==VACANT){// return first level if it is empty
        return 1;
       
    }
    else{
        while(i<b.levels() &&b.checkerAt(col, i+1)!=VACANT){
            i++;
        }
    }
    
    return i+1;
}

//check vertically if the input color is winner, if not return tie
int checkvertical(const Scaffold& board,int rowtowin, int currentcol, int curr_level, int input_color){
    if(curr_level<rowtowin){
        //if the column has less checkers than the number required to win, no winner
        return TIE_GAME;
    }
    int number=0;
 
    for(int i=0;i<rowtowin;i++){
        if(board.checkerAt(currentcol, curr_level-i)==input_color){
            number++;
        }
        if(number==rowtowin){
            return input_color;
        }
    }
    
    return TIE_GAME;
    
}

void checktogether(vector<int>& postion, const Scaffold& b, int rowtowin, int input_color, int& number, int col, int level ,int& result){
    if(b.checkerAt(col, level)==input_color){
        number++;
        postion.push_back(col);
        if(number==rowtowin){// check if they are together
            int start= *min_element(postion.begin(), postion.end());
            int end=*max_element(postion.begin(), postion.end());
            if(end-start==rowtowin-1){
                result=input_color;
            }else{//clear the vector and start again
                postion.clear();
                postion.push_back(col);
            }
        }
    }
}

//check horizontall if input color is winner, if not return tie
int checkhorizontal(const Scaffold& board, int curr_level, int input_color, int rowtowin){
    int result=TIE_GAME;
    int number_of_color=0;
    vector<int> positioncolor;
    for(int j=1;j<=board.cols();j++){
        checktogether(positioncolor, board, rowtowin, input_color, number_of_color, j, curr_level, result);
        if(result==input_color){
            return result;
        }
    }
    return TIE_GAME;
}

// when the board is m*n where n>m, check diagonally if input color is winner, if not return tie
int check_short(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color) {
    int result=TIE_GAME;
    //check in the"/" direction
    
    int startlevel=curr_level;
    int startcol=currentcol;
    int endcol=startcol;
    int endlevel=startlevel;
    
    int number_of_color=0;
    vector<int> positioncolor;
    
    if(curr_level<=currentcol){
        // all diagonals with bottom left cell in level 1
        while (endlevel!=1) {
            endlevel--;
            endcol--;
        }
        if(endcol<=board.cols()-board.levels()){
            startlevel=board.levels();
            startcol=endcol+board.levels()-1;
        }else{
            startcol=board.cols();
            startlevel=board.cols()-endcol+1;
        }
    }else{//rest of diagonals
        while(endcol!=1){
            endlevel--;
            endcol--;
        }
        startcol=board.levels()-endlevel+1;
        startlevel=board.levels();
        
    }
    
    int index=startcol;
    for(int i=startlevel;i>=endlevel;i--){
        checktogether(positioncolor, board, rowtowin, input_color, number_of_color, index, i, result);
        if(result==input_color){
            return result;
        }
        index--;
    }
    
    //check "\" direction
    
   
    
    int startlevel2=curr_level;
    int startcol2=currentcol;
    int endcol2=startcol2;
    int endlevel2=startlevel2;
    
    int number_of_color2=0;
    vector<int> positioncolor2;
    
    if(curr_level<=board.cols()-currentcol+1){
        // all diagonals with bottom right end cell in level 1
        
        while(endlevel2!=1){
            endcol2++;
            endlevel2--;
        }
        if(endcol2<=board.levels()){
            startcol2=1;
            startlevel2=endcol2;
        }else{
            startlevel2=board.levels();
            startcol2=endcol2-board.levels()+1;
        }

        
    }else{//rest diagonals
        while(startlevel2!=board.levels()){
            startlevel2++;
            startcol2--;
        }
        endcol2=board.cols();
        endlevel2=board.levels()-( board.cols()-startcol2);

    }
    int index2=startcol2;
    for(int i=startlevel2;i>=endlevel2;i--){

        
        checktogether(positioncolor2, board, rowtowin, input_color, number_of_color2, index2, i, result);
        
        if(result==input_color){
            return result;
        }
        index2++;
    }

    
    return TIE_GAME;
}

// when the board is m*n where m>=n, check diagonally if input color is winner, if not return tie

int check_tall(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color){
    int result=TIE_GAME;
    
    //check"\" direction
 
    int startlevel=curr_level;
    int startcol=currentcol;
    int endcol=startcol;
    int endlevel=startlevel;
    int number_of_color=0;
    vector<int> positioncolor;
    
    
    if(startlevel<=board.levels()-currentcol+1){
        //find diagnols that are starts with level equal or less than board's level, with topleft cell in column 1
        
        while(startcol!=1){
            startcol--;
            startlevel++;
        }
        if(startlevel<=board.cols()){
            endcol=startlevel;
            endlevel=1;
        }else{
            endcol=board.cols();
            endlevel=startlevel-board.cols()+1;
        }
       
    }else{// get rest "\" diagonals
        while(startlevel!=board.levels()){
            startcol--;
            startlevel++;
        }
        endcol=board.cols();
        endlevel=board.levels()-( board.cols()-startcol);
    }
    
    int index=startcol;
    for(int i=startlevel;i>=endlevel;i--){
        
        checktogether(positioncolor, board, rowtowin, input_color, number_of_color, index, i, result);
        if(result==input_color){
            return result;
        }
        index++;
    }
    
    
    //check"/" direction

   
    
    int startlevel2=curr_level;
    int startcol2=currentcol;
    int endcol2=startcol2;
    int endlevel2=startlevel2;
    
    
    int number_of_color2=0;
    vector<int> positioncolor2;
    
    if (startlevel2<=curr_level+board.levels()-board.cols()){
        //find diagnols that are starts with level equal or less than board's level, with top right cell in the last column
        while(startcol2!=board.cols()){
            startcol2++;
            startlevel2++;
        }
       
        if(startlevel2<=board.cols()){
            endlevel2=1;
            endcol2=board.cols()-startlevel2+1;
        }else{
            endcol2=1;
            endlevel2=startlevel2-board.cols()+1;
        }

    }else{// get rest of "/" diagonals
        while(startlevel2!=board.levels()){
            startlevel2++;
            startcol2++;
        }
        endcol2=1;
        endlevel2=board.levels()-startcol2+1;

    }
    int index2=startcol2;
    for(int i=startlevel2;i>=endlevel2;i--){
      
        checktogether(positioncolor2, board, rowtowin, input_color, number_of_color2, index2, i, result);
        if(result==input_color){
            return result;
        }
        index2--;
    }
  
    return TIE_GAME;
}

int checkdiagnal(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color){
    int result=5;
    if(board.levels()>=board.cols()){
        result=check_tall( board,  currentcol,  curr_level,  rowtowin,  input_color);
    }else if(board.levels()<board.cols()){
        result=check_short(board, currentcol,  curr_level,  rowtowin,  input_color);
    }
    return result;
}

// return whether the input checker reach win, if not return tie game
int check_everything(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color){
    if(checkvertical(board, rowtowin, currentcol, curr_level, input_color)==input_color||checkhorizontal(board, curr_level, input_color, rowtowin)==input_color||checkdiagnal(board, currentcol, curr_level, rowtowin, input_color)==input_color){
        return input_color;
    }else{
        return TIE_GAME;
    }
}
