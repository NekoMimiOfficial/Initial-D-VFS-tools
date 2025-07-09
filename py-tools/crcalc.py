import crcmod
import sys

def calc_crc(bytes, poly):
    machine= crcmod.Crc(poly= poly, rev= False, initCrc= 0, xorOut=0xFFFFFFFF)
    machine.update(bytes)
    return int().from_bytes(machine.digest())

def crc32(msg, poly):
    crc = 0xffffffff
    for b in msg:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ poly if crc & 1 else crc >> 1
    return crc ^ 0xffffffff

def main():
    file= sys.argv[1]
    buffer= open(file, "rb")
    data= buffer.read()
    buffer.close()
    print(f"CRC32 initial d edition: {file}")
    print(hex(crc32(data, 0x001B563C)))

if __name__ == '__main__':
    main()
