//
//  Player.cpp
//
//  Created by Zhiwen Cao on 5/8/21.
//

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int big=100000;
class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
   
    int chooseMove(const Scaffold& s, int N, int color);
 

    
};


int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int column=0;
    bool flag=true;
    cout<<"Please enter a valid column number:";
    cin>>column;

    while (flag){//stop when a valid input is received
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a valid column number:"<<endl;
            cin>>column;
        }else{
            if (column>=1 &&column<=s.cols()&&s.checkerAt(column, s.levels())==VACANT) {
                flag=false;
            }
            else{
                cout<<"Please enter a valid column number:"<<endl;
                cin>>column;
            }
        }
    }
   

    
    return column;
}

//always make move at left most valid column
int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int column=1;
    bool flag=true;
    while(flag){
        if(s.checkerAt(column, s.levels())==VACANT &&column<=s.cols()){
            flag=false;
        }else{
            column++;
        }
    }
    
    return column;
}

int rate(const Scaffold& board, int N){
    
    for(int i=1;i<=board.levels();i++){
        for(int j=1;j<=board.cols();j++){
            if(board.checkerAt(j, i)!=VACANT){
               
                int c=board.checkerAt(j, i);
                if(check_everything(board, j, i, N, c)==c){
                    //check whether the given color reaches a win
                    if(c==BLACK){// give black win score 1
                        return 1;
                    }
                    else if (c==RED){// give red win score -1
                        return -1;
                    
                    }
                }
        }
        }
        
    }
    return 0;//give tie score 0
}

vector<int> determinemove(AlarmClock& ac, const Scaffold& s, int N, int color, int depth);

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    AlarmClock ac(9900);
    return determinemove(ac,s, N, color, 0).at(1);
}

vector<int> determinemove(AlarmClock& ac, const Scaffold& s, int N, int color, int depth){

    vector<int> outcome;
    vector<int> posible_move;
    
    //get opponent color
    int opponentcolor=0;
    if(color==BLACK){
        opponentcolor=RED;
    }
    else if(color==RED){
        opponentcolor=BLACK;
    }

    //check all available move
    for(int col=1;col<=s.cols();col++){
        int available_level=next_level_available(s, col);
        if(available_level<=s.levels()){
            posible_move.push_back(col);
        }
    }
    
    //for every possible move, make the move until a score is produced
    for(int i=0;i<posible_move.size();i++){
        Scaffold temp=s;
        temp.makeMove(posible_move.at(i), color);
        if(rate(temp,  N)==1||rate(temp, N)==-1||(rate(temp,  N)==0 &&temp.numberEmpty()==0)){
            outcome.push_back(rate(temp,  N)*(big-depth));
        }
        else{
            if(!ac.timedOut()){
                outcome.push_back(determinemove(ac,temp, N, opponentcolor, depth+1).at(0));
            }else{
                outcome.push_back(0);
                
            }
        }
    }
    
  
   //get corresponding score and  column that leads to that score
       auto max=max_element(outcome.begin(), outcome.end());
        auto maxindex=distance(outcome.begin(), max);
        
   if(color==RED){
        max=min_element(outcome.begin(), outcome.end());
       maxindex=distance(outcome.begin(), max);
    }
    
    //store those two values and return them
    vector<int> result;

        result.push_back(*max);
        result.push_back(posible_move.at(maxindex));
   
        return result;
  
}







HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

