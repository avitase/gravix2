import numpy as np


def sph2car(lat, lon):
    """Converts spherical into cartesian coordinates on a unit sphere.

    Args:
         lat: Latitude in radians.
         lon: Longitude in radians.

    Returns:
         x, y and z coordinates.
    """
    x = np.cos(lat) * np.sin(lon)
    y = np.cos(lat) * np.cos(lon)
    z = np.sin(lat)
    return x, y, z


def car2sph(x, y, z):
    """Converts cartesian into spherical coordinates on an unit sphere.

    Args:
        x: x coordinate.
        y: y coordinate.
        z: z coordinate.

    Returns:
        Latitude and longitude in radians.
    """
    lat = np.arcsin(z)
    lon = np.arctan2(x, y)
    return lat, np.where(y > 0, lon, lon + np.pi)


def wrap_angle_once(x):
    """Wraps angle from interval [a, b] onto [a + 2pi, b - 2pi] for a < -pi and pi < b.

    If the input angle is lower (greater) than -pi (+pi) then 2pi is added (subtracted) once. In the
    special case -3pi < a < -pi and +pi < b < +3pi the reduced interval is [-pi, +pi].

    Args:
        x: Angle from interval [a, b].

    Returns:
        x, x + 2pi or x - 2pi.
    """
    return np.where(x < -np.pi, x + 2. * np.pi, np.where(x > np.pi, x - 2. * np.pi, x))


def circle(lat0, lon0, r, t):
    """Parametrization of a circle on a unit sphere.

    2pi periodic parametrization of a circle on a unit sphere chosen such that ``t=0`` is the point
    closest to the north pole.

    Args:
        lat0: Latitude in radians of circle center on a unit sphere.
        lon0: Longitude in radians of circle center on a unit sphere.
        r: Radius of circle, measured along the curved surface of a unit sphere.
        t: Parametrization points.

    Returns:
        Latitude and longitude in radians of circle at given parametrization points.
    """
    x = np.cos(t) * np.sin(r)
    y = np.sin(lat0) * np.sin(t) * np.sin(r) - np.cos(lat0) * np.cos(r)
    z = np.cos(lat0) * np.sin(t) * np.sin(r) + np.sin(lat0) * np.cos(r)

    lat, lon = car2sph(x, y, z)
    return lat, wrap_angle_once(lon + lon0)


def great_circle_distance(lat, lon, *, lat2, lon2):
    """Distance between two points on a great circle of a unit sphere.

    Args:
        lat: Latitude in radians of first point.
        lon: Longitude in radians of first point.
        lat2: Latitude in radians of second point.
        lon2: Longitude in radians of second point.

    Returns:
        Shortest distance between given points on a unit sphere.
    """
    arg = np.sin(lat) * np.sin(lat2) + np.cos(lat) * np.cos(lat2) * np.cos(lon - lon2)
    return np.arccos(np.clip(arg, -1, 1.0))
