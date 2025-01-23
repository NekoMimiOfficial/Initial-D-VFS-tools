to help cracking the polynomial you should:  
- compile the project  
- copy the `./this_file_as_argv1.txt` file to the output dir of the build  
- run `./vfs-crc-poly-brute-9000 this_file_as_argv1.txt`  
- profit  

you can ctrl+c to stop the program and it'll save the progress to a save.bin file  
it also saves every 0xFFFF entries in case of a power loss or program termination  
when the hash is found the program will terminate and the result is the save.bin file  
