```cpp
[XBB Files]
---------------------------------------------------------------------------------------------------
XXXY Z...  .... ....
.... ....  .... ....
X: XBB header
Y: magic flag 4: usually equals 1, is present as a spacer for other 4 wide header types (@ANA)
Z: file count

this section below will continue a set amount of times (file count)
XXXX YYYY  ZZZZ CCCC
(read in big endian, so 4<-3<-2<-1)
>>> uint32_t pointer= buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
X: file start pointer
Y: amount of bytes to read after the start pointer
Z: file name pointer (file name ends at 0x00)
C: data hash, CRC32

some metadata and unknown stuff

file names seperated by "0x00" which start at the first file name pointer

some metadata and unknown stuff

raw data (including the header) and a small amount of unknown data at the end of each file segment
--------------------------------------------------------------------------------------------------

[ANA Files]
--------------------------------------------------------------------------------------------------
XXXX ....  .... ....
Y... ....  .... ....
X: @ANA header
Y: file count

this section below will continue a set amount of times (file count)
XXXX YYYY  ZZZZ ZZZ.
(read in big endian, so 4<-3<-2<-1)
>>> uint32_t pointer= buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
X: file start pointer
Y: amount of bytes to read after the start pointer
Z: partial file name (terminated by a hex 0x00)

some metadata and unknown stuff

raw data (including the header)

@ANT section (after start pointer + amount to read, of the last file)
this is a shared colour pallet that is appended to every GIM file
__________________________________________________________________________________________________
```
