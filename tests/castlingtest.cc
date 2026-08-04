#include "../src/Board.h"
#include <iostream>

// Castling spec. Input model: the king's target square IS its own rook
// (e1->h1 kingside, e1->a1 queenside). x=file(a=0..h=7), y=rank(8=0..1=7).
static bool at(Board* g, int x, int y, char t){ Piece* p=(*g)[x][y]; return p && p->getCharacter()==t; }

int main(){
    int fail=0;

    // 1. legal kingside O-O: Ke1,Rh1 -> king g1, rook f1
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(7,7,'R',true); g->placePiece(4,0,'K',false);
      ChessStatus r=g->movePiece(Pos(4,7),Pos(7,7));
      bool ok = r==ChessStatus::SUCCESS && at(g,6,7,'K') && at(g,5,7,'R') && (*g)[4][7]==nullptr && (*g)[7][7]==nullptr;
      if(!ok){ std::cout<<"case1 kingside FAIL: "<<g->toFENString()<<"\n"; fail++; } delete g; }

    // 2. legal queenside O-O-O: Ke1,Ra1 -> king c1, rook d1
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(0,7,'R',true); g->placePiece(4,0,'K',false);
      ChessStatus r=g->movePiece(Pos(4,7),Pos(0,7));
      bool ok = r==ChessStatus::SUCCESS && at(g,2,7,'K') && at(g,3,7,'R') && (*g)[4][7]==nullptr && (*g)[0][7]==nullptr;
      if(!ok){ std::cout<<"case2 queenside FAIL: "<<g->toFENString()<<"\n"; fail++; } delete g; }

    // 3. blocked between (Bf1) -> FAIL, unchanged
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(7,7,'R',true); g->placePiece(5,7,'B',true); g->placePiece(4,0,'K',false);
      bool ok = g->movePiece(Pos(4,7),Pos(7,7))==ChessStatus::FAIL && at(g,4,7,'K') && at(g,7,7,'R');
      if(!ok){ std::cout<<"case3 blocked FAIL\n"; fail++; } delete g; }

    // 4. king currently in check -> FAIL (black Re5 checks e1)
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(7,7,'R',true); g->placePiece(4,0,'K',false); g->placePiece(4,3,'R',false);
      bool ok = g->movePiece(Pos(4,7),Pos(7,7))==ChessStatus::FAIL;
      if(!ok){ std::cout<<"case4 in-check FAIL\n"; fail++; } delete g; }

    // 5. king passes through attacked f1 -> FAIL (black Rf8 attacks f1)
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(7,7,'R',true); g->placePiece(4,0,'K',false); g->placePiece(5,0,'R',false);
      bool ok = g->movePiece(Pos(4,7),Pos(7,7))==ChessStatus::FAIL;
      if(!ok){ std::cout<<"case5 through-attack FAIL\n"; fail++; } delete g; }

    // 6. king has moved -> FAIL (move it out and back)
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(7,7,'R',true); g->placePiece(4,0,'K',false); g->placePiece(0,1,'P',false);
      g->movePiece(Pos(4,7),Pos(4,6)); g->movePiece(Pos(0,1),Pos(0,2));
      g->movePiece(Pos(4,6),Pos(4,7)); g->movePiece(Pos(0,2),Pos(0,3));
      bool ok = g->movePiece(Pos(4,7),Pos(7,7))==ChessStatus::FAIL;
      if(!ok){ std::cout<<"case6 king-moved FAIL\n"; fail++; } delete g; }

    // 7. a REJECTED king move must NOT forfeit castling (moved flag is deferred to a real move)
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(7,7,'R',true); g->placePiece(4,0,'K',false);
      g->placePiece(3,0,'R',false); // black rook d8 attacks d1
      g->movePiece(Pos(4,7),Pos(3,7)); // Ke1-d1 is illegal (into check) -> FAIL, must not mark king moved
      ChessStatus r=g->movePiece(Pos(4,7),Pos(7,7)); // O-O must still be legal
      bool ok = r==ChessStatus::SUCCESS && at(g,6,7,'K') && at(g,5,7,'R');
      if(!ok){ std::cout<<"case7 castle-after-rejected-move FAIL: "<<g->toFENString()<<"\n"; fail++; } delete g; }

    // 8. standard input form: king TWO squares (e1->g1 kingside, e1->c1 queenside)
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(7,7,'R',true); g->placePiece(4,0,'K',false);
      ChessStatus r=g->movePiece(Pos(4,7),Pos(6,7)); // e1-g1
      bool ok = r==ChessStatus::SUCCESS && at(g,6,7,'K') && at(g,5,7,'R') && (*g)[4][7]==nullptr && (*g)[7][7]==nullptr;
      if(!ok){ std::cout<<"case8 e1-g1 FAIL: "<<g->toFENString()<<"\n"; fail++; } delete g; }
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(0,7,'R',true); g->placePiece(4,0,'K',false);
      ChessStatus r=g->movePiece(Pos(4,7),Pos(2,7)); // e1-c1
      bool ok = r==ChessStatus::SUCCESS && at(g,2,7,'K') && at(g,3,7,'R') && (*g)[4][7]==nullptr && (*g)[0][7]==nullptr;
      if(!ok){ std::cout<<"case8 e1-c1 FAIL: "<<g->toFENString()<<"\n"; fail++; } delete g; }

    // 9. both input forms land the king on the SAME standard square (g1)
    { Board* g1b=new Board(); g1b->setEmptyBoard(true);
      g1b->placePiece(4,7,'K',true); g1b->placePiece(7,7,'R',true); g1b->placePiece(4,0,'K',false);
      g1b->movePiece(Pos(4,7),Pos(7,7)); // e1->h1 (onto-rook form)
      Board* g2b=new Board(); g2b->setEmptyBoard(true);
      g2b->placePiece(4,7,'K',true); g2b->placePiece(7,7,'R',true); g2b->placePiece(4,0,'K',false);
      g2b->movePiece(Pos(4,7),Pos(6,7)); // e1->g1 (standard form)
      if(g1b->toFENString() != g2b->toFENString()){ std::cout<<"case9 forms diverge: "<<g1b->toFENString()<<" vs "<<g2b->toFENString()<<"\n"; fail++; }
      delete g1b; delete g2b; }

    // 10. king moving one square onto an ADJACENT own rook is NOT castling -> FAIL
    { Board* g=new Board(); g->setEmptyBoard(true);
      g->placePiece(4,7,'K',true); g->placePiece(5,7,'R',true); g->placePiece(7,7,'R',true); g->placePiece(4,0,'K',false);
      bool ok = g->movePiece(Pos(4,7),Pos(5,7))==ChessStatus::FAIL && at(g,4,7,'K'); // e1->f1 onto own rook
      if(!ok){ std::cout<<"case10 onto-adjacent-rook wrongly allowed\n"; fail++; } delete g; }

    std::cout<<(fail==0?"castlingtest: PASS\n":"castlingtest: FAIL\n");
    return fail==0?0:1;
}
