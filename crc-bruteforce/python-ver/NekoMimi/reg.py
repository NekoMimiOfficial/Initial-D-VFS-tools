import pickle
from subprocess import getoutput
from os.path import exists

from NekoMimi.utils import write

"""
registry reading tools for the reg module in __main__
good for saving single line strings and tokens (unencrypted)
"""

def readCell(cell: str)->str:
    """
    retrieve data from cells in the neko py registry
    @arg cell: the cell of which data will be returned
    >>> NekoMimi.reg.readCell("cellname")
    REG UNINIT ERR "or" CELL NOT FOUND ERR "or" DATA
    """
    _home = getoutput("echo $HOME")
    if not exists(f"{_home}/.config/NekoPyReg/db.pkl"):
        return "Registry uninitialized, please use the neko shell to initialize it"
    buffer = open(f"{_home}/.config/NekoPyReg/db.pkl", "rb")
    db = pickle.load(buffer)
    if not cell in db:
        return f"cell: {cell} is not in database"
    return db[cell]

class Database:
    """
    full pointer based solution for working with fields in a cell
    @arg accessName: the cell of which fields are written into
    >>> pointer= NekoMimi.reg.Database("db1")
    >>> pointer.query("field")
    returns field data
    """
    def __init__(self, accessName: str):
        home= getoutput("echo $HOME")
        getoutput(f"mkdir $HOME/.config/NekoPyReg")
        getoutput(f"mkdir $HOME/.config/NekoPyReg/{accessName}")
        self.pointer= f"{home}/.config/NekoPyReg/{accessName}/"

    def query(self, field):
        if exists(f"{self.pointer}{field}"):
            buffer= open(f"{self.pointer}{field}", "r")
            data= buffer.read()
            buffer.close()
            return data
        else:
            return ""

    def store(self, field, data):
        try:
            buffer= open(f"{self.pointer}{field}", "w")
            buffer.write(data)
            buffer.close()
            return True
        except Exception:
            return False

    def remove(self, field):
        getoutput(f"rm $HOME/.config/NekoPyReg/{self.pointer}{field}")
