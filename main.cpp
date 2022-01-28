//
//  main.cpp
//
//  Created by Zhiwen Cao on 5/8/21.
//

    #include "provided.h"
    #include <iostream>
    #include <cassert>
    using namespace std;

    void doGameTests()
    {
        BadPlayer bp1("a1");
        BadPlayer bp2("a2");
        Game g(2, 2, 2, &bp1, &bp2);
        int winner;
        assert(!g.completed(winner));
        g.takeTurn();
        assert(!g.completed(winner)  &&
                    (g.checkerAt(1, 1) == RED  ||  g.checkerAt(2, 1) == RED));
        g.takeTurn();
        assert(!g.completed(winner));
        g.takeTurn();
        assert(g.completed(winner)  &&  winner == RED);
      
    }

int main(){

//doGameTests();
//cout << "Passed all tests" << endl;


    HumanPlayer a("a");
    HumanPlayer b1("b");
    BadPlayer c("c");
    BadPlayer d("d");

    SmartPlayer e("e");
    SmartPlayer e2("e2");
    
// create a board with 5 columns and 4 rows.
// connect 3 is winning condition
    Game g(5,4,3,&a,&b1);
    g.play();
    



    return 0;
}
