from NekoMimi import colourimi

"""
Simple tools and wrappers for CLI tools
mostly neko-fied :3
"""

_Factory = colourimi.colourFactory()

def kprint(text: str, colour: str= "fcfcff", newline: bool= True)-> None:
    _Factory.text= text
    _Factory.colour= colour
    _Factory.newline= newline
    _Factory.cinit()
    _Factory.cprint()
    return
