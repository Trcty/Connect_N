//
//  main.cpp
//
//  Created by Zhiwen Cao on 5/8/21.
//

#include "provided.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    //check whether the given column has empty space
    bool checkemptycol(int column) const;
    
    
private:
    int m_row;
    int m_col;
    vector<vector<char>> board;
    vector<vector<int>> move;
    
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels):m_row(nLevels),m_col(nColumns)
{
    if(nColumns<1 ||nLevels<1){
        exit(1);
    }else{//create a board
        board.resize(nLevels);
        for(int i=0;i<nLevels;i++){
            board[i].resize(nColumns);
        }
        for (int i = 0; i < nLevels; i++){
            for (int j = 0; j < nColumns; j++){
                board[i][j] =' ';
            }
        }
    }
}

//check if there is empty spot left in a column
bool ScaffoldImpl::checkemptycol(int column)const{
    int count=0;
    for(int i=0;i<m_row;i++){
        if(board[i][column-1]==' '){
            count++;
        }
        if(count>0){
            return true;
        }
    }
    return false;
}


int ScaffoldImpl::cols() const
{
    return m_col;
}

int ScaffoldImpl::levels() const
{
    return m_row;  
}

int ScaffoldImpl::numberEmpty() const
{
    int empty=0;
    for (int i=0;i<m_row;i++){
        for (int j=0;j<m_col;j++){
            if(board[i][j]==' '){
                empty++;
            }
        }
    }
    return empty;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if(level>=1&&level<=m_row&&board[m_row-level][column-1]=='R'){
        return RED;
    }else if (level>=1&&level<=m_row&&board[m_row-level][column-1]=='B'){
        return BLACK;
    }else{
        return VACANT;
        
    }
}

void ScaffoldImpl::display() const
{
    
    for(int i=0;i<m_row+1;i++){
        if(i<m_row){
            for(int j=0;j<m_col;j++){
                cout<<'|'<<board[i][j];
            }
            cout<<'|'<<endl;
        }
        else{
            for(int j=0;j<m_col;j++){
                cout<<"+-";
            }
            cout<<'+'<<endl;
        }
        
    }
    cout<<endl;
  

    
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    char c;
    vector<int> current;
    
    if(column>0&&column<=m_col && checkemptycol(column)&&(color==RED||color==BLACK)){
        if(color==RED){
            c='R';
        }
        else{
            c='B';
        }
        int i=0;
        while(i<m_row &&board[i][column-1]==' '){
            i++;
        }
        i--;
        
        board[i][column-1]=c;
        
        current.push_back(i);
        current.push_back(column);
        move.push_back(current);//store the move into vector move
        return true;
    }
    
    return false;
}

int ScaffoldImpl::undoMove()
{
    int last=0;
    if (move.empty()){//empty vector means no move has been made
        return 0;
    }
    vector<int> end=move[move.size()-1];
    last=end[1];
    board[end[0]][last-1]=' ';
    move.pop_back();
    return last;

}



Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}



