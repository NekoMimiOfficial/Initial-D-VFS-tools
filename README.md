# Initial D VFS tools, Based on street stage for the PSP  
this is a tool to extract and repack the virtual filesystem for initial D on the PSP and possibly other initial D titles  
  
this tool supports unpacking the VFS including XBB and ANA files  
packing custom files is almost complete and does exist however until the polynomial is cracked the crc will be mismatched and the game wont start  

# running  
all params could be found in the `--help` option  
to extract files from an XBB/ANA file:  
`./initial-d-vfs-tools --extract --vfs=vfs_file.extension`  

to pack an XBB file:  
`./initial-d-vfs-tools --pack=XBB --path=directory_including_the_files`  

to pack an ANA file:
`./initial-d-vfs-tools --pack=ANA --path=directory_including_the_files`  

# building  
```sh
cmake -L ./ \
make
```
due to the many issues we are facing with windows and msvc this project will need to be built in WSL if you're planning to build it on windows  
The files will be found in the `build/` directory  
debug flag can be turned on inside the `src/utils.cpp` file  
  
# story  
Once apon a time there was... *A princess!* the young viewers would shout out, no young ones, once apon a time there was a piece of ~wood~ hex data  
that hex data was Sega's attempt at obfuscating the Initial D street stage files so that no one could dream of patching them to english, or so you'd think but rather it was a mesure to insure that data would load correctly from a spinning universal media disc due to its unreliability similar to Lego Island  
However noble it may be to provide such a nice way to reliably read data it also made unpacking it a horror story  
Our story isn't as such but rather a nightmare that all started with "Oi Akira I'll create you a patcher, how hard could it be?" and soon the story begins to spiral downwards to hell and beyond, what? you thought this was a cheerful story?, too naive my young ones, no such story exists in real life  
Ah yes, now where were we?, the hex data of course, following Sega's attempt to thrash away any force to patch this game a team stood up sharpening their keyboards and ~drawing tablets~ phones to make a clever comeback  
Neko, the protagonist of this story creates a repository on GitHub and pushes the first commit with a readme and a license, then they decend to the depths of obfuscation hell and on the first glance of the data it looked kind of hard to notice but there were a handful of strings, Filenames!  
These filenames were a sign of relief but not so much for the unknowing cat who only affirmed the fact that the files arent encrypted  
after ~years~ days of *anal-yzing* and becoming an enterpreneur with a sick POS (Piece Of Software) joke, Neko found a nice discovery all of which it decided to write in a guide for hex data analyzation for other crackers to use, pointers!, but!, those pointers where in big endian (definitely a way of making discoveries hard on crackers)  
Alas we had end and start and filename pointers, but there remained a 32bit data blob after each of these pointers, the way it looked seemed like a hash but what hash? Neko was puzzled  
Soon after Neko learned it was almost impossible they decided to search the interwebs in frustration, then behold the holy grail!, someone has already attempted to document this weird filesystem produced by Sega, and in their findings they wrote that it may very well be a crc32  
This brought joy to Neko as it solved most problems facing the completion of this project, afterall, it had the data and the filename, that much is more than enough for the extraction and indeed it was as in 3 more days the first build of this project emerged that allowed for file extraction  
However not satisfied, the cat wanted more, the entire reason this project started was to patch the game to english, and it shant stop here  
All was left was to calculate the crc32, so an efficient and powerful bruteforce tool was created that managed to complete over 25 thousand hashes per second!!!  
It was a marvelous tool and so begun the journey to crack the polynomial  
The evil enemy standing in face of this project's completion, Neko and its friend MJ spun up their cores and went on fighting to find the hostage polynomial  
In the end they emerged out victorious and went on to place the last piece of the puzzle which completes this project  
Searching for "The End." my young readers? oh are you so wrong!  
The story will never end here as I said it goes on beyond hell, the hellish task of creating appealing patched textures and patching the non texture parts of the game still remains on our noble swordsmen, they might have won the battle, but not the war...  
what comes next is up to them, and we end *this* story here, wishing that our swordsmen return safe winning their war.  
  
# credit  
although I decided to rediscover things myself but this repo helped me a lot  
https://github.com/derplayer/Initial-D-PSP-Tools/wiki/Reserve-engineering-Writeup  

# links  
Neko's links are found at [neko's github profile](https://github.com/NekoMimiOfficial/NekoMimiOfficial)  
Main IDSS ENG patch project server: [link](http://discord.gg/W9fgesMaau)  
