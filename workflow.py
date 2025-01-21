from NekoMimi import utils as nm
import os
import sys

print(nm.figlet("VFS Workflow", "small"))
print("setting up test...")
os.mkdir(sys.argv[1]+os.pathsep+"TESTS")
