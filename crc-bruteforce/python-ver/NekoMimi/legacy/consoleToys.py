from NekoMimi import colourimi

_cFac = colourimi.colourFactory
_defColour = "FFDDDD"

def kprint(text, colour=None, inline=True, escape=None):
    _cFac.text = text
    if colour == None:
        pass
    else:
        _cFac.colour = colour
    _cFac.newline = inline
    _cFac.cinit()
    if escape == None:
        pass
    else:
        _cFac.suffix = escape
    _cFac.cprint()
    return

def debug(debug):
    if "DEBUG" in sys.argv:
        yellow("[DEBUG] "+debug)
    else:
        pass
