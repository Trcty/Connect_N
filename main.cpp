//
//  main.cpp
//
//  Created by Zhiwen Cao on 5/8/21.
//

#include "provided.h"
#include <iostream>
using namespace std;

int main(){

    HumanPlayer a("a");
    HumanPlayer b1("b");
    BadPlayer c("c");
    BadPlayer d("d");

    SmartPlayer e("e");
    SmartPlayer e2("e2");
    
// create a board with 5 columns and 4 rows.
// connecting 3 is winning condition
    Game g(5,4,3,&a,&b1);
    g.play();
    



    return 0;
}
