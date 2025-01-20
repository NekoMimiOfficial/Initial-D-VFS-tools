# Initial D VFS tools, Based on street stage for the PSP  
this is a tool to extract and repack the virtual filesystem for initial D on the PSP and possibly other initial D titles  
  
this tool supports unpacking the VFS including XBB and ANA files  
we plan to add support for repacking once we figure out the crc  

# running  
all params could be found in the `--help` option  
to extract files from an XBB/ANA file:  
`./initial-d-vfs-tools --extract --vfs some_vfs_file.extension`  

# building  
```sh
cmake -L ./ \
make
```
The files will be found in the `build/` directory  
debug flag can be turned on inside the `src/utils.cpp` file  
  
# credit  
although I decided to rediscover things myself but this repo helped me a lot  
https://github.com/derplayer/Initial-D-PSP-Tools/wiki/Reserve-engineering-Writeup  

# discord  
main IDSS ENG patch project server:  
http://discord.gg/W9fgesMaau  
  
or any of my socials included in my github profile page :3  
