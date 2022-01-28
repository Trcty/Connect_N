//
//  Game.cpp
//
//  Created by Zhiwen Cao on 5/9/21.
//

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    
    //return the biggest level that is nonempty in a given column or level1 is it is empty
    int get_nonemepty_maxlevel(const Scaffold& b,int col) const;
    
    
   
  
private:
    Scaffold board;
    int rowtowin;
    int turn;
    Player* player1;
    Player* player2;
    int currentcol;
    int curr_level;
    int m_color;
    int winner;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black):board(nColumns, nLevels),rowtowin(N),turn(0),player1(red),player2(black),currentcol(1),curr_level(1),winner(5)
{
    
}


int GameImpl::get_nonemepty_maxlevel(const Scaffold& b,int col) const{
    int i=1;
    if(b.checkerAt(col, i)==VACANT){// return first level if it is empty
        return 1;
    }
    else{
        while(i<b.levels() &&b.checkerAt(col, i+1)!=VACANT){
            i++;
        }
        
        
    }
    
    return i;
}

//if there is a winner or board is full, it is completed
bool GameImpl::completed(int& winner) const
{
    
        if (board.numberEmpty()==0){
            return false;
        }
    winner=check_everything(board, currentcol, curr_level, rowtowin, m_color);
    
    if(winner==BLACK||winner==RED){
        return true;
    }else{
        return false;
    }
}

//make a move, store the move's column and level, and change player for the next turn
bool GameImpl::takeTurn()
{
    
    if(board.numberEmpty()==0||winner==RED||winner==BLACK){
        return false;
    }
    
    if(turn%2==0){//red move
        cout<<"Red's turn (press enter to continue if nonhuman player)"<<endl;
        int col1=player1->chooseMove(board, rowtowin, RED);
        m_color=RED;
        board.makeMove(col1, RED);
        currentcol=col1;
        curr_level=get_nonemepty_maxlevel(board, currentcol);
        turn++;
        return true;
    }else {
        cout<<"Black's turn (press enter to continue if nonhuman player)"<<endl;
        
        int col2=player2->chooseMove(board, rowtowin, BLACK);
        m_color=BLACK;
        board.makeMove(col2, BLACK);
        currentcol=col2;
        curr_level=get_nonemepty_maxlevel(board, currentcol);
        turn++;
        return true;
    }
   
}

void GameImpl::play()
{
    while (!(winner==RED||winner==BLACK||board.numberEmpty()==0)) {
        board.display();
        takeTurn();
        cin.ignore();
        
        completed(winner);
    }
    board.display();
    string win;
    if(winner==RED){
        win="Red wins";
    }else if (winner==BLACK){
        win="Black wins";
    }else if (winner==TIE_GAME){
        win="It is a tie";
    }
    
    cout<<win<<endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    if(board.checkerAt(c, r)==RED){
        return RED;
    }else if (board.checkerAt(c, r)==BLACK){
        return BLACK;
    }
    return VACANT;
}



Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}


