import ctypes
from ctypes import c_double, c_int, c_size_t, c_void_p
from pathlib import Path

import numpy as np


class World:
    def __init__(self, *, planets, lib):
        new_world = lib.new_world
        new_world.argtypes = [c_size_t, ]
        new_world.restype = c_void_p
        self._handle = new_world(len(planets))

        set_planet = lib.set_planet
        set_planet.argtypes = [c_void_p, c_size_t, c_double, c_double]
        set_planet.restype = c_int

        for i, (lat, lon) in enumerate(planets):
            rc = set_planet(self._handle, i, lat, lon)
            assert rc == 0

        self.planet_id = list(range(len(planets)))

        pop_planet = lib.pop_planet
        pop_planet.argtypes = [c_void_p, ]
        pop_planet.restype = c_size_t
        self._pop_planet = pop_planet

        delete_world = lib.delete_world
        delete_world.argtypes = [c_void_p, ]
        delete_world.restype = None
        self._delete_world = delete_world

    def remove_planet(self, i):
        if i < 0 or i >= len(self.planet_id):
            raise IndexError(f'Invalid index {i}')

        n = self._pop_planet(self._handle)
        assert n == len(self.planet_id) - 1

        self.planet_id[i] = self.planet_id[-1]
        self.planet_id.pop()

    def __del__(self):
        self._delete_world(self._handle)


if __name__ == '__main__':
    lib = str(Path('libphysics.so').resolve())
    lib = ctypes.cdll.LoadLibrary(lib)

    world = World(planets=[(1., 2.), (3., 4.), (5., 6.)], lib=lib)
    assert np.all(np.array(world.planet_id) == np.array([0, 1, 2]))

    world.remove_planet(1)
    assert np.all(np.array(world.planet_id) == np.array([0, 2]))

    world.remove_planet(1)
    assert np.all(np.array(world.planet_id) == np.array([0, ]))

    world.remove_planet(0)
    assert len(world.planet_id) == 0
