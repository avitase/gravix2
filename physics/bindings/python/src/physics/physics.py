import ctypes
from pathlib import Path

from . import helper
from . import missile
from . import planet


class Physics:
    def __init__(self, lib):
        lib = Path(lib)
        if not lib.is_file():
            raise ValueError("Invalid library path")

        self._lib = ctypes.cdll.LoadLibrary(str(lib.resolve()))
        self._helper = helper.Helper(lib=self._lib)

    def new_planets(self, *args, **kwargs):
        return planet.Planets(*args, **kwargs, lib=self._lib)

    def new_missiles(self, *args, **kwargs):
        return missile.Missiles(*args, **kwargs, lib=self._lib)

    def get_lat(self, *args, **kwargs):
        return self._helper.get_lat(*args, **kwargs)

    def get_lon(self, *args, **kwargs):
        return self._helper.get_lon(*args, **kwargs)

    def get_vlat(self, *args, **kwargs):
        return self._helper.get_vlat(*args, **kwargs)

    def get_vlon(self, *args, **kwargs):
        return self._helper.get_vlon(*args, **kwargs)
