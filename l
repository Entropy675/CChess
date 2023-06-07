warning: in the working copy of '.github/workflows/bishopmovestest.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/c-cpp.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/invalidpostest.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/kingcheckstest.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/knightmovetest.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/pawncapturetest.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/pawnpromotiontest.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/pawnpush2test.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of '.github/workflows/rookmovestest.yml', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'LICENSE', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'helpfulcommands.txt', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'ncurses.supp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/Board.h', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/ChessGame.h', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/Log.cc', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/Log.h', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/NcView.h', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/Pos.cc', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/Pos.h', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/View.h', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/defs.h', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'src/main.cc', LF will be replaced by CRLF the next time Git touches it
[1mdiff --git a/src/Board.cc b/src/Board.cc[m
[1mindex 24ac618..14ced69 100644[m
[1m--- a/src/Board.cc[m
[1m+++ b/src/Board.cc[m
[36m@@ -443,10 +443,9 @@[m [mconst Bitboard& Board::getBlackMoveMap() const[m
 	return blackMoveMap;[m
 }[m
 [m
[31m-[m
 Bitboard Board::getWhiteAttackMap(const Piece& p, Pos* to, bool includePiecesAttacks) const[m
 {[m
[31m-	return conditionalGetMap(p, to, includePiecesAttacks, [](const Piece& piece) {return piece.validCaptures();}, whitePieces);[m
[32m+[m	[32mreturn conditionalGetMap(p, to, includePiecesAttacks, [](const Piece& piece) {return piece.validCaptures();}, whitePieces);[m[41m [m
 }[m
 [m
 Bitboard Board::getBlackAttackMap(const Piece& p, Pos* to, bool includePiecesAttacks) const[m
[36m@@ -471,6 +470,8 @@[m [mBitboard Board::conditionalGetMap(const Piece& p, Pos* to, bool includePiecesAtt[m
 	for(long unsigned int i = 0; i < pieces->size(); i++)[m
 		if(pieces->at(i) != &p)[m
 			tmp = tmp | func(*pieces->at(i));[m
[32m+[m	[32m// we assume that Function type = lambda function, thus calling that lambda function we defined with *pieces->at(i) and returning the corresponding piece.validMoves(); bitboard.[m[41m[m
[32m+[m	[32m// Remember, compiler just creates different copies of this function based on the input passed! Validity is entirly based on whats passed... seems a little wacky but its good[m[41m[m
 	[m
 	if(includePiecesAttacks)[m
 		tmp = tmp | p.validCaptures(to);[m
