#include "../src/Board.h"
#include <iostream>

// Bug 4: an attack map means "squares this side controls", including squares
// occupied by its own pieces (defended). Move maps must still exclude friendly.
int main(){
    int fail=0;

    // 1. a defended slider is in the attack map: Black Ra5 defended by Black Ra1
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(4,0,'K',false);
      g->placePiece(0,3,'R',false); // black Ra5
      g->placePiece(0,7,'R',false); // black Ra1 (defends a5 up the a-file)
      g->placePiece(7,6,'P',true);  // white h2 (waiting move)
      g->movePiece(Pos(7,6),Pos(7,5)); // h2-h3 -> triggers updateMaps
      if(!g->getBlackAttackMap()[Pos(0,3)]){ std::cout<<"case1: defended Ra5 NOT in black attack map\n"; fail++; }
      delete g; }

    // 2. a king controls (defends) a friendly-occupied neighbour
    { Board* g=new Board(); g->setEmptyBoard(false); // black to move
      g->placePiece(4,7,'K',true); g->placePiece(4,0,'K',false);
      g->placePiece(5,6,'P',true);  // white f2, diagonally adjacent to Ke1
      g->placePiece(0,1,'P',false); // black a7 (waiting)
      g->movePiece(Pos(0,1),Pos(0,2)); // a6 -> updateMaps
      if(!g->getWhiteAttackMap()[Pos(5,6)]){ std::cout<<"case2: king does not defend friendly f2\n"; fail++; }
      delete g; }

    // 3. move map still excludes friendly: Ke1 cannot move onto its own pawn f2
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(4,0,'K',false); g->placePiece(5,6,'P',true);
      if(g->movePiece(Pos(4,7),Pos(5,6))!=ChessStatus::FAIL){ std::cout<<"case3: king moved onto own pawn\n"; fail++; }
      delete g; }

    // 4. a bishop defends a friendly piece (Cross): white Bc1 defends a pawn on e3
    { Board* g=new Board(); g->setEmptyBoard(false);
      g->placePiece(4,7,'K',true); g->placePiece(4,0,'K',false);
      g->placePiece(2,7,'B',true); g->placePiece(4,5,'P',true); // Bc1, Pe3 on c1-h6 diagonal
      g->placePiece(0,1,'P',false); g->movePiece(Pos(0,1),Pos(0,2)); // black a6 -> updateMaps
      if(!g->getWhiteAttackMap()[Pos(4,5)]){ std::cout<<"case4: bishop does not defend friendly e3\n"; fail++; }
      delete g; }

    // 5. a knight defends a friendly piece: white Nc3 defends a pawn on e4
    { Board* g=new Board(); g->setEmptyBoard(false);
      g->placePiece(4,7,'K',true); g->placePiece(4,0,'K',false);
      g->placePiece(2,5,'N',true); g->placePiece(4,4,'P',true); // Nc3, Pe4 (c3->e4 is a knight move)
      g->placePiece(0,1,'P',false); g->movePiece(Pos(0,1),Pos(0,2)); // black a6 -> updateMaps
      if(!g->getWhiteAttackMap()[Pos(4,4)]){ std::cout<<"case5: knight does not defend friendly e4\n"; fail++; }
      delete g; }

    std::cout<<(fail==0?"attackmaptest: PASS\n":"attackmaptest: FAIL\n");
    return fail==0?0:1;
}
