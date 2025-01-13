```cpp
[XBB Files]
0x00 - 0x03: header "XBB"       (58, 42, 42)
0x04:        unknown flags      (01)
0x05:        file count "int"   (1 byte)
0x06 - 0x1F: filler for header  ()
0x20 - 0x7F: main VFS           (4 chunks)
0x20 - 0x23: start pointer      (byte array)
0x24 - 0x27: end pointer        (byte array)
// start + end pointer = pointer to end of the file
0x28 - 0x2B: filename string    (byte array)
// 0x00 is the string seperator
0x2C - 0x2F: CRC


[ANA Files]
0x00 - 0x03: header "@ANA"      (40, 41, 4E, 41)
0x04:        honestly no idea   (16)
0x05 - 0x07: empty data
0x08 - 0x0B: random data
0x0C:        empty data
0x0D:        unknown flag       (01)
0x0E - 0x0F: empty data
0x10:        file count
0x14 - 0x1F: filler for header
0x20 - 0x23: start pointer      (byte array)
0x24 - 0x27: end pointer        (byte array)
// same comment
0x28 - 0x2F: filename string    (byte array)
// 0x00 is the string seperator

```
