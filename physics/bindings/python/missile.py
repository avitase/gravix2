import ctypes
from ctypes import c_double, c_size_t, c_void_p
from pathlib import Path

import numpy as np


class Missile:
    def __init__(self, *, missile, lib):
        self.missile = missile
        self.trajectory = None

        launch = lib.launch_missile
        launch.argtypes = [c_void_p, c_double, c_double, c_double]
        launch.restype = None
        self._launch = launch

        propagate = lib.propagate_missile
        propagate.argtypes = [c_void_p, c_void_p, ]
        propagate.restype = c_size_t
        self._propagate = propagate

    def propagate(self):
        n = self._propagate(None, self.missile)

        class Trajectory(ctypes.Structure):
            _fields_ = [
                ('x', c_double * (n * 3)),
                ('v', c_double * (n * 3)),
            ]

        raw = ctypes.cast(self.missile, ctypes.POINTER(Trajectory))
        self.trajectory = {
            'x': np.ctypeslib.as_array(raw.contents.x).reshape(n, 3),
            'v': np.ctypeslib.as_array(raw.contents.v).reshape(n, 3),
        }

    def launch(self, *, lat, lon, psi):
        self._launch(self.missile, lat, lon, psi)
        self.propagate()


class Missiles:
    def __init__(self, *, n, lib):
        self.lib = lib

        new_missiles = self.lib.new_missiles
        new_missiles.argtypes = [c_size_t, ]
        new_missiles.restype = c_void_p
        self.handle = new_missiles(n)

        getter = self.lib.get_trajectory
        getter.argtypes = [c_void_p, c_size_t]
        getter.restype = c_void_p

        self.missiles = [Missile(missile=getter(self.handle, i), lib=lib) for i in range(n)]

    def __len__(self):
        return len(missiles)

    def __getitem__(self, i):
        return self.missiles[i]

    def __del__(self):
        f = self.lib.delete_missiles
        f.argtypes = [c_void_p, ]
        f.restype = None
        f(self.handle)


if __name__ == '__main__':
    lib = ctypes.cdll.LoadLibrary(Path('libphysics.so').resolve())
    missiles = Missiles(n=3, lib=lib)

    m = missiles[0]
    m.launch(lat=0., lon=0., psi=0.)

    trj = m.trajectory
    print('x')
    print(trj['x'])
    print('v')
    print(trj['v'])
    print('*' * 80)

    m.propagate()
    print('x')
    print(trj['x'])
    print('v')
    print(trj['v'])
