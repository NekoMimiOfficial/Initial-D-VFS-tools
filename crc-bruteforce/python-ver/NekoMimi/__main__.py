from subprocess import getoutput
from os.path import exists, isdir
import pickle

from pyfiglet import os

from NekoMimi import consoleToys

init= [0]

class system:
    def __init__(self) -> None:
        self.modules:dict = {}

    class context:
        def __init__(self) -> None:
            self.args:str = ""
            self.name:str = ""
            self.result:str = ""

    def module(self, func) -> None:
        ctx = self.context()
        ctx = func(ctx)
        name = ctx.name
        self.modules[name] = func
        return

#############
#  Modules  #
#############

Factory = system()

@Factory.module
def __CMD_echo(ctx: system.context):
    ctx.name = "echo"
    ctx.result = ctx.args
    return ctx

@Factory.module
def __CMD_help(ctx: system.context):
    ctx.name= "help"
    helpmsg= """
NekoPyShell Help Page
~~~~~~~~~~~~~~~~~~~~~

echo:   echos the message appended
reg:    mini registry for single word values
--------------------------------------------
type help module_name, for more details about a specific command"""

    if " " in ctx.args:
        arg= ctx.args.split(" ")[0]
    else:
        arg= ctx.args

    match arg:
        case "echo":
            ctx.result= "\n[echo $msg] echos a message, takes one argument, not space seperated"
            return ctx
        case "reg":
            ctx.result= """
[reg $operation $cell $data]
stores single word data into cells
takes 3 arguments, seperated by spaces, each argument is one word long
$operation: [r:read] [w:write] [d:delete]
$cell:      cell to store data in, case sensitive
$data:      data to be stored into cells, still needed if the operation is read or delete
            can be any random data for reading, specifically 'conFirm' for deleting case sensitive""" 
            return ctx

    ctx.result = helpmsg
    return ctx

@Factory.module
def __CMD_ls(ctx: system.context):
    ctx.name= "ls"
    args= ctx.args

    if " " in args:
        ctx.result= "ls takes only 1 argument\nthis aint some advanced thing"
        return ctx

    if args == "":
        args= "./"

    if init[0] == 0:
        return ctx

    contents= os.listdir(args)
    for content in contents:
        if isdir(content):
            cls= "#89DCEB"
        elif content.endswith(".py"):
            cls= "#F9E2AF"
        elif content.endswith(".build"):
            cls= "#799DDB"
        elif content.endswith(".conf"):
            cls= "#799DDB"
        elif content.endswith(".txt"):
            cls= "#799DDB"
        elif content.endswith(".md"):
            cls= "#F5C2E7"
        else:
            cls= "#A2DCAA"

        consoleToys.kprint(content+" ", cls, False)
    ctx.result= " "
    return ctx

@Factory.module
def __CMD_cp(ctx: system.context):
    ctx.name= "cp"
    if len(ctx.args) > 1:
        getoutput(f"cp {ctx.args}")
    return ctx

@Factory.module
def __CMD_regTools(ctx: system.context):
    ctx.name = "reg"
    args = ctx.args

    _home = getoutput("echo $HOME")
    regFile = f"{_home}/.config/NekoPyReg/db.pkl"

    if not exists(regFile):
        getoutput("mkdir ~/.config/NekoPyReg/")
        regBuff = open(regFile, 'wb')
        reg = {}
        pickle.dump(reg, regBuff)
        regBuff.close()

    if " " in args:
        argvr = args.split(" ")
        if len(argvr) == 3:
            if argvr[0] == "r":
                regBuff = open(regFile, "rb")
                getReg = pickle.load(regBuff)
                if argvr[1] in getReg:
                    ctx.result = getReg[argvr[1]]
                    regBuff.close()
                    return ctx
                else:
                    ctx.result = "No cell found with name: "+argvr[1]
                    regBuff.close()
                    return ctx
            if argvr[0] == "w":
                regBuff = open(regFile, "rb")
                getReg = pickle.load(regBuff)
                regBuff.close()
                regBuff = open(regFile, "wb")
                getReg[argvr[1]] = argvr[2]
                pickle.dump(getReg, regBuff)
                regBuff.close()
                ctx.result = "Operation completed."
                return ctx
            if argvr[0] == "d":
                regBuff = open(regFile, "rb")
                getReg: dict = pickle.load(regBuff)
                regBuff.close()
                regBuff = open(regFile, "wb")
                if not argvr[2] == "conFirm":
                    ctx.result = "Please make sure your 3rd argument is conFirm case sensitive to confirm the deletion"
                    return ctx
                del getReg[argvr[1]]
                pickle.dump(getReg, regBuff)
                regBuff.close()
                ctx.result = "Operation completed."
                return ctx

    ctx.result = "Wrong formatting [reg {r/w/d} {cell} {data+w/confirm+r/conFirm+d}]"
    return ctx

#############
#############


modules = Factory.modules

def promptData():
    pwd= getoutput("pwd")
    if pwd.endswith("/"):
        pwd= pwd[:-1]
    shortwd= pwd.split("/")
    shortwd= shortwd[-2] + "/" + shortwd[-1] + "/"
    consoleToys.kprint("NekoPyShell ", "#799DDB", False)
    consoleToys.kprint(f"[{shortwd}] ", "#F3B993", False)
    return "$:"

def _start() -> None:

    com:str = input(promptData())
    init[0]= 1
    while True:
        name:str = ""
        args:str = ""

        if " " in com:
            name = com.split(" ", 1)[0]
            args = com.split(" ", 1)[1]
        else:
            name = com
            args = ""

        if name in modules:
            ctx = Factory.context()
            ctx.args = args
            ctx = modules[name](ctx)
            print(ctx.result)
        elif com == "exit" or com == "quit":
            exit(0)
        else:
            comNames = ""
            for mod in modules:
                comNames = comNames + mod + ", "
            comNames = comNames[:-2]
            print("Unknown command, List of available commands:")
            print(f"[{comNames}]")

        com = input(promptData())


#run
_start()
