//
//  support.hpp
//
//  Created by Zhiwen Cao on 5/9/21.
//

#ifndef support_h
#define support_h
#include "provided.h"
#include <vector>

int next_level_available(const Scaffold& b,int col);

int checkvertical(const Scaffold& board,int rowtowin, int currentcol, int curr_level, int input_color);

void checktogether(std::vector<int>& postion, const Scaffold& b, int rowtowin, int input_color, int& number, int col, int level ,int& result);

int checkhorizontal(const Scaffold& board, int curr_level, int input_color, int rowtowin);

int check_short(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color);

int check_tall(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color);

int checkdiagnal(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color);

int check_everything(const Scaffold& board, int currentcol, int curr_level, int rowtowin, int input_color);


int rate(const Scaffold& board,int color, int N);
#endif /* support_hpp */
