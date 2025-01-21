import os
import sys

file= sys.argv[1]+os.path.sep+"src"+os.path.sep+"vfs.cpp"
win_file= sys.argv[1]+os.path.sep+"src"+os.path.sep+"win_vfs.cpp"
os.remove(file)
os.rename(win_file, file)
