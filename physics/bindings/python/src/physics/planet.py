from ctypes import c_double, c_int, c_uint, c_void_p


class Planets:
    def __init__(self, planets, *, lib):
        new_planets = lib.new_planets
        new_planets.argtypes = [c_uint, ]
        new_planets.restype = c_void_p
        self.handle = new_planets(len(planets))

        set_planet = lib.set_planet
        set_planet.argtypes = [c_void_p, c_uint, c_double, c_double]
        set_planet.restype = c_int

        for i, (lat, lon) in enumerate(planets):
            rc = set_planet(self.handle, i, float(lat), float(lon))
            assert rc == 0

        self.planet_pos = planets
        self.planet_id = list(range(len(planets)))

        pop_planet = lib.pop_planet
        pop_planet.argtypes = [c_void_p, ]
        pop_planet.restype = c_uint
        self.pop_planet = pop_planet

        delete_planets = lib.delete_planets
        delete_planets.argtypes = [c_void_p, ]
        delete_planets.restype = None
        self._delete_planets = delete_planets

    def remove_planet(self, i):
        if i < 0 or i >= len(self.planet_id):
            raise IndexError(f'Invalid index {i}')

        n = self._pop_planet(self.handle)
        assert n == len(self.planet_id) - 1

        self.planet_id[i] = self.planet_id[-1]
        self.planet_pos[i] = self.planet_pos[-1]
        self.planet_id.pop()
        self.planet_pos.pop()

    def __getitem__(self, i):
        return self.planet_pos[i]

    def __del__(self):
        self._delete_planets(self.handle)
