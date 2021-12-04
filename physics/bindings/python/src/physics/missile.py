import ctypes
from ctypes import c_double, c_size_t, c_void_p

import numpy as np


class Missile:
    def __init__(self, *, missile, lib):
        self._missile = missile
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
        n = self._propagate(None, self._missile)

        class Trajectory(ctypes.Structure):
            _fields_ = [
                ('x', c_double * (n * 3)),
                ('v', c_double * (n * 3)),
            ]

        raw = ctypes.cast(self._missile, ctypes.POINTER(Trajectory))
        self.trajectory = {
            'x': np.ctypeslib.as_array(raw.contents.x).reshape(n, 3),
            'v': np.ctypeslib.as_array(raw.contents.v).reshape(n, 3),
        }

    def launch(self, *, lat, lon, psi):
        self._launch(self._missile, lat, lon, psi)
        self.propagate()


class Missiles:
    def __init__(self, *, n, lib):
        new_missiles = lib.new_missiles
        new_missiles.argtypes = [c_size_t, ]
        new_missiles.restype = c_void_p
        self._handle = new_missiles(n)

        getter = lib.get_trajectory
        getter.argtypes = [c_void_p, c_size_t]
        getter.restype = c_void_p

        self._missiles = [Missile(missile=getter(self._handle, i), lib=lib) for i in range(n)]

        delete_missiles = lib.delete_missiles
        delete_missiles.argtypes = [c_void_p, ]
        delete_missiles.restype = None
        self._delete_missiles = delete_missiles

    def __len__(self):
        return len(self._missiles)

    def __getitem__(self, i):
        return self._missiles[i]

    def __del__(self):
        self._delete_missiles(self._handle)
