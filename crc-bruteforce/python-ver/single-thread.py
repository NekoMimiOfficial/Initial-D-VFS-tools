import zlib
from NekoMimi import utils as nm

def calculate_checksums(file_path, crc32, adler32):
    # Read the file in binary mode
    with open(file_path, 'rb') as f:
        while True:
            # Read a chunk of the file
            data = f.read(4096)  # Read in 4KB chunks
            if not data:
                break
            
            # Update CRC32 checksum
            crc32 = zlib.crc32(data, crc32)
            
            # Update Adler-32 checksum
            adler32 = zlib.adler32(data, adler32)

    return crc32, adler32

if __name__ == '__main__':
    i= 0
    while True:
        c, a= calculate_checksums("./rivalface.bin", i, i)
        i= i+1
        if i%10000 == 0:
            print(f"I:{str(i)} | H:{hex(i)} | C:{hex(c)} | A:{hex(a)}")

        if c == 0x03252feb:
            print("C:"+str(i))
            nm.write(str(i), "c.txt")
            break

        if a == 0x03252feb:
            print("A:"+str(i))
            nm.write(str(i), "a.txt")
            break
