<h1 align="center">CChess</h1>
<p align="center">
  The beauty in a tiny piece of code is that it costs nothing to maintain. No dependencies to rot, nothing to keep up with.
</p>
<p align="center">
  <img src="https://raw.githubusercontent.com/Entropy675/CChess/refs/heads/main/piece_images/CChessStart.png" alt="CChess Start Position" style="width: 100%; max-width: 100%;" />
</p>


## Build & run (Linux)
make

Then:
./CChess

Builds on any Linux distribution with no per-environment variation. The only dependency is ncurses, the standard library for Linux terminal applications.

If the board renders with no alignment or whitespace, set your terminal to a monospace font. Most distributions ship one by default, but it isn't guaranteed.

## Build (Windows)
Toolchain: MinGW-w64. Install the Windows environment and dependencies, then run `make` at the project root to produce `CChess.exe`.

## Tests
Enter the tests folder, run make, the Makefile will build then run the tests.

## Direction
CChess is no longer developed as a standalone program (but of course, you can still compile it to be so on linux since ncurses implementation is so easy to keep). It's being integrated as an example LGPL provider for ETCS (Entity Tag Context System), my forthcoming super-type ontology, which is also LGPL on release.

ETCS acts as an OS abstraction, and as a kernel outright when compiled or run in kernel mode. Turning CChess into a type provider lets the ETCS substrate fulfill the P2P trust contract natively, through its existing synchronization primitives (the causal type lattice, the gap reorder buffer, and mirror-buffer RPC over compile-time-declared dependency graphs), and bridge to any target platform through separate OS variant instances of the same type provider module (Linux, Windows, WASM).

Rendering and search therefore lives outside this repository, wherever the CChess work-function interface is reached. **This is a chess engine only.** The OS-specific display has nothing to do with it. This will be sub-project to the actual ChessProvider module - serves as a demonstration of how you can take arbitrary code and create a work function interface for it that transforms it into a type provider for the ETCS runtime.

