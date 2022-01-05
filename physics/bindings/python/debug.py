from src import physics

libphysics = physics.load_library("libs/libphysics.so")
planets = libphysics.new_planets([(10.0, 20.0), (-20.0, -30)])
missiles = libphysics.new_missiles(3)


def shoot(missile, *, n=6):
    x = np.empty((0, 3))
    v = np.empty((0, 3))

    premature = False
    while n > 0 and not premature:
        n -= 1
        premature = missile.propagate(planets, 1e-3)
        if premature:
            print("!!! PREMATURE !!!")

        x = np.concatenate((x, missile.trajectory["x"]), axis=0)
        v = np.concatenate((v, missile.trajectory["v"]), axis=0)

    lat = np.arcsin(x[:, 2])
    lon = np.arctan2(x[:, 0], x[:, 1])

    # vlat = np.arcsin(v[:, 2])
    # vlon = np.arctan2(v[:, 0], v[:, 1])

    return np.rad2deg(lat), np.rad2deg(lon)  # , np.rad2deg(vlat), np.rad2deg(vlon)


m = missiles[0]
m.launch(planets=planets, planet_id=0, v=50.0, psi=0.0)
