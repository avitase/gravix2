import ctypes
from pathlib import Path

import pytest


@pytest.fixture
def libphysics():
    f = Path(__file__).parent.parent / 'libs' / 'libphysics.so'
    assert f.is_file(), f

    return ctypes.cdll.LoadLibrary(str(f.resolve()))
