import numpy as np

from src.physics.planet import World


def test_world(libphysics):
    world = World(planets=[(1., 2.), (3., 4.), (5., 6.)], lib=libphysics)
    assert np.all(np.array(world.planet_id) == np.array([0, 1, 2]))

    world.remove_planet(1)
    assert np.all(np.array(world.planet_id) == np.array([0, 2]))

    world.remove_planet(1)
    assert np.all(np.array(world.planet_id) == np.array([0, ]))

    world.remove_planet(0)
    assert len(world.planet_id) == 0
