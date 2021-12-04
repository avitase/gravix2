from src.physics.missile import Missiles


def test_missiles(libphysics):
    missiles = Missiles(n=3, lib=libphysics)
    assert len(missiles) == 3

    mm = [m for m in missiles]
    assert len(mm) == 3

    for m in mm:
        m.launch(lat=0., lon=0., psi=0.)

        trj = m.trajectory
        assert 'x' in trj
        assert 'v' in trj
        assert trj['x'].shape == trj['v'].shape

        m.propagate()
        assert 'x' in trj
        assert 'v' in trj
        assert trj['x'].shape == trj['v'].shape
