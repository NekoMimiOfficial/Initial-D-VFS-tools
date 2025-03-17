from io import TextIOWrapper
from types import ModuleType
import requests
import json
import sys
from pyfiglet import Figlet
from importlib import import_module

"""
General set of useful utilities
"""


def figlet(text: str, font: str = "small", width: int = 80) -> str:
    """
    simple function for the pyfiglet rendering class
    @arg text: a string of text used by figlet
    @kwarg font: a string containing any figlet font(default:smal)
    @kwarg width: an integer describing the width of the generation
    @return: a string being the render
    >>> NekoMimi.utils.figlet("nya")
    *nya but generated as a figlet string (font:small, width: 80)
    """
    engine = Figlet(font, width=width)
    render: str = engine.renderText(text)
    return render


def API2Json(endpoint: str):
    """
    swift tool to convert a json response from an API endpoint
    to a python array
    @arg endpoint: a string containing the endpoint url
    @return: array
    >>> NekoMimi.utils.API2Json("http://ex.endpoint/api.php")
    {...}
    """
    try:
        buffer = requests.get(endpoint)
        response = json.loads(buffer.text)

    except Exception as e:
        print(e)
        del e

        return {}

    return response


def write(data: str, file: str) -> bool:
    """
    single line write command
    @arg data: string containing data to be written
    @arg file: string containing file to be written to
    @return: False on fail, True on success
    >>> NekoMimi.utils.write("some data", "./some_file.ext")
    True
    """
    try:
        buffer: TextIOWrapper = open(file, "w")
        buffer.write(data)
        buffer.close()

        return True

    except FileNotFoundError:
        print(f"the file requested \"{file}\" does not exist")

        return False

    except Exception as e:
        print(e)
        del e

        return False


def read(file: str) -> str:
    """
    single line read command
    @arg file: string containing file to read
    @return: file on fail, contents on success
    >>> NekoMimi.utils.read("path/to/file.ext")
    DATA_OF_FILE
    """
    try:
        buffer = open(file, "r")

    except FileNotFoundError:
        print(f"the file requested \"{file}\" does not exist")

        return file

    except Exception as e:
        print(e)
        del e

        return file

    content: str = buffer.read()
    buffer.close()

    return content

def isUp(url: str) -> int:
    """
    uptime command, checks if url is up
    @arg url: a string containing the url
    @return: 0 if down, requests.status_code if up
    >>> NekoMimi.utils.isUp("http://site.ex")
    200
    """
    
    try:
        req = requests.get(url)

    except Exception as e:
        print(e)
        del e

        return 0

    return req.status_code

def uwuport(module: str)-> bool:
    """
    ever wished to import a module in code?
    your wishes have come true :3
    @arg module: module name, including local modules and files
    @return: True on success, False otherwise
    >>> NekoMimi.utils.uwuport("NekoMimi")
    True
    """
    try:
        sys.path.append('.')
        mod= import_module(module)
    except Exception:
        return False

    sys.modules[module]= mod
    return True

def load_mod(module: str):
    """
    wrapper for uwuport  
    @arg module: module name, including local modules and files  
    @return: ModuleType (module)  
    >>> NekoMimi.utils.load_mod("os")
    os (module)  
    False  
    """
    if uwuport(module):
        return sys.modules[module];
    else:
        return False
