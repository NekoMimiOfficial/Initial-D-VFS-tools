import zlib
import time
import signal
import multiprocessing

from pyfiglet import os
from NekoMimi import utils as nm

threads= []

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

    # Convert checksums to hexadecimal format
    crc32_hex = format(crc32 & 0xFFFFFFFF, '08X')  # Ensure it is 8 hex digits
    adler32_hex = format(adler32 & 0xFFFFFFFF, '08X')  # Ensure it is 8 hex digits

    return crc32_hex, adler32_hex

def worker(i, c, steps):
    r= c
    while True:
        crc32_checksum, adler32_checksum = calculate_checksums(file_path, r, r)
        if crc32_checksum == 0x03252feb:
            print("crc32 found!  "+str(r))
            break

        if adler32_checksum == 0x03252feb:
            print("adler32 found!   "+str(r))
            break

        r= r+1

        if r%10000 == 0:
            print(f"[W{str(i)}] P:{str(r*100/steps)[4]}% C:{hex(r)}")
            nm.write(str(r), f"thread{str(i)}-save.txt")

        if r == steps:
            break

def stopper(sig, frame):
    for w in threads:
        w.kill()

    exit()

def constr(i, s):
    if os.path.exists(f"thread{str(i)}-save.txt"):
        c= nm.read("thread{str(i)}-save.txt")
        return multiprocessing.Process(target=worker, args=[i, c, s])
    else:
        return multiprocessing.Process(target=worker, args=[i, s*i, s*(i+1)])


if __name__ == "__main__":
    file_path = "rivalface.bin"
    signal.signal(signal.SIGINT, stopper)
    threads.append(constr(0, 0x20000000))
    threads.append(constr(1, 0x20000000))
    threads.append(constr(2, 0x20000000))
    threads.append(constr(3, 0x20000000))
    threads.append(constr(4, 0x20000000))
    threads.append(constr(5, 0x20000000))
    threads.append(constr(6, 0x20000000))
    threads.append(constr(7, 0x20000000))

    for w in threads:
        w.start()

    while True:
        time.sleep(1)
        pass
