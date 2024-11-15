# CChess

**Important: This project is deprecated and no longer actively maintained. I got bored and gave up before implementing checkmate. If anyone wants to do it i'll accept a pull request.**

Please check out the new and improved version of the CChess engine, called [CChessV2](https://github.com/Entropy675/CChessV2).
It includes a much better architecture for interplatform interfaces.

Feel free to explore and contribute to the new repository for the latest updates and improvements. Thank you for your support!

---

An abstract implementation of Chess in C++.
The current game is built inside of the Linux terminal - that means that you can play Chess from your terminal!

For Linux, download the repo then:
```
Compile Command: make
Run command: ./CChess
```

Currently only builds on Linux or WSL with the KeX GUI (working on an actual windows port right now!).
If the game seems to be all messed up with no whitespaces, please change your terminal font to something monospace...
Many linux distributions come with monospace formats in terminals by default but there is no garutee that yours will.

 ** ->>> creating a Windows API based GUI for download as an executable windows binary (a .exe program).
 (Current build toolchain: MingW64 -> get windows environment installed, get dependencies -> make command at root of project -> produces CChess.exe)

The priorities of this Chess Engine are:
 1. <b>Secure</b>
 1. <b>Lightweight</b>
 1. <b>Portable</b>
 1. <b>Peer-to-peer (no central server)</b>
 
Plans to integrate with Web Assembly for a future web project, combining with one of my preexisting web socket based chat servers.
This would allow players to play either through my website or through their own downloaded file.

See: https://docs.google.com/document/d/1oaZmhNOmmDsz6Fmuz6LzkdWVBBkZxCUrXsQ7BhuDwwk/
For current documentation (WIP).
