#include "../src/Board.h"
#include <iostream>
#include <vector>
#include <utility>

// loadFEN must invert toFENString for CChess-canonical FENs (positions produced
// by the engine itself), across piece placement, turn, castling rights, ep, counters.
static bool roundtrip(const std::string& label, const std::vector<std::pair<Pos,Pos>>& moves,
                      bool epCaptureCheck = false, Pos epFrom = Pos(0,0), Pos epTo = Pos(0,0))
{
    Board a; a.setStartingBoard(true);
    for(auto& m : moves) a.movePiece(m.first, m.second);
    std::string fen = a.toFENString();

    Board b; b.loadFEN(fen);
    std::string back = b.toFENString();

    bool ok = (fen == back);
    if(!ok) std::cout << "  [" << label << "] MISMATCH\n    from move seq: " << fen
                      << "\n    from loadFEN : " << back << "\n";

    if(epCaptureCheck)
    {
        // the ep capture must still be legal on the LOADED board
        ChessStatus st = b.movePiece(epFrom, epTo);
        if(st == ChessStatus::FAIL) { std::cout << "  [" << label << "] ep capture illegal after load\n"; ok = false; }
    }
    return ok;
}

int main()
{
    int fail = 0;
    auto M = [](int fx,int fy,int tx,int ty){ return std::make_pair(Pos(fx,fy),Pos(tx,ty)); };

    // 1. starting position
    if(!roundtrip("start", {})) fail++;

    // 2. a few developing moves (castling rights intact)
    if(!roundtrip("develop", { M(4,6,4,4), M(4,1,4,3), M(6,7,5,5), M(1,0,2,2) })) fail++; // e4 e5 Nf3 Nc6

    // 3. rook move -> loses one castling right (derived flags must survive the round-trip)
    if(!roundtrip("rookmoved", { M(7,6,7,4), M(7,1,7,3), M(7,7,7,5) })) fail++; // h4 h5 Rh3

    // 4. king move -> loses both rights for that side
    if(!roundtrip("kingmoved", { M(4,6,4,4), M(4,1,4,3), M(4,7,4,6) })) fail++; // e4 e5 Ke2

    // 5. en passant available AND the ep capture legal after load:
    //    1.e4 a6 2.e5 d5  -> white e5 can take d5 ep (e5xd6). e5=(4,3) -> d6=(3,2)
    if(!roundtrip("enpassant", { M(4,6,4,4), M(0,1,0,2), M(4,4,4,3), M(3,1,3,3) },
                  /*epCaptureCheck*/true, Pos(4,3), Pos(3,2))) fail++;

    std::cout << (fail==0 ? "fenroundtriptest: PASS\n" : "fenroundtriptest: FAIL\n");
    return fail==0 ? 0 : 1;
}
