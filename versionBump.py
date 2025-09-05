#!/bin/python3

import yaml
newVer= "0.0.0"
with open("./version.yaml", "r") as buffer:
    newVer= buffer.read()
newVer= yaml.safe_load(newVer)["version"]
oldVer= newVer
NVArray= newVer.split(".", 2)
NVArray[0]= int(NVArray[0])
NVArray[1]= int(NVArray[1])
NVArray[2]= int(NVArray[2])
if NVArray[1] == 9 and NVArray[2] == 9:
    NVArray[1]= 0
    NVArray[2]= 0
    NVArray[0]= NVArray[0]+ 1
elif NVArray[2] == 9 and not NVArray[1] == 9:
    NVArray[2]= 0
    NVArray[1]= NVArray[1]+ 1
else:
    NVArray[2]= NVArray[2]+ 1
newVer= f"{NVArray[0]}.{NVArray[1]}.{NVArray[2]}"

if not oldVer.count(".") == 2 and not len(oldVer) == 5:
    exit(1)

print(f"old version:    {oldVer}")
print(f"new version:    {newVer}")
print("~~~~~~~~~~~~~~~~~~~~~~")

def replace(file):
    newStr= ""
    try:
        with open(file, "r") as rbuffer:
            newStr= rbuffer.read().replace(oldVer, newVer)
        with open(file, "w") as wbuffer:
            wbuffer.write(newStr)
        print(f"[  ok  ] bumped {newStr.count(newVer)} versions in: {file}")
    except Exception as e:
        print(f"[ fail ] couldn't update: {file} | error: {e}")

replace("./build.sh")
replace("./debian/control")
replace("./debian/changelog")
replace("./CMakeLists.txt")
replace("./src/main.cpp")
replace("./python/processor.py")
