import ctypes
from pathlib import Path

from . import missile
from . import planet


class Physics:
    def __init__(self, lib):
        lib = Path(lib)
        if not lib.is_file():
            raise ValueError('Invalid library path')

        self._lib = ctypes.cdll.LoadLibrary(str(lib.resolve()))

    def new_planets(self, *args, **kwargs):
        return planet.Planets(*args, **kwargs, lib=self._lib)

    def new_missiles(self, *args, **kwargs):
        return missile.Missiles(*args, **kwargs, lib=self._lib)
