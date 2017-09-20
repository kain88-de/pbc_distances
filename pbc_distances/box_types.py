import numpy as np


def box_check(box):
    """Take a box input and deduce what type of system it represents based
    on the shape of the array and whether all angles are 90.

    Parameters
    ----------
    box : array-like (3, 3)
        Box information of unknown format.

    Returns
    -------
    boxtype : str
        * ``ortho`` orthogonal box
        * ``triclinic`` triclinic box vectors
        * ``none`` no box
    """
    box = np.asarray(box)
    if box.shape != (3, 3):
        raise ValueError("expect triclinic formatted box")

    if np.all(box == np.zeros((3, 3))):
        return 'none'
    elif np.all([
            box[0][1] == 0.0,  # Checks that tri box is properly formatted
            box[0][2] == 0.0,
            box[1][2] == 0.0
    ]):
        return 'ortho'
    else:
        return 'triclinic'


def normalize_box(box):
    """
    Normalize box to the triclinic format

    Parameters
    ----------
    box : array-like or None or scalar
        original box format

    Returns
    -------
    ndarray (3, 3)
        box in triclinic format
    """
    if box is None:
        return np.zeros((3, 3))
    if np.isscalar(box):
        return np.eye(3) * box
    elif box.shape == (3, ):
        return np.eye(3) * box
    elif box.shape == (3, 3):
        return box
    elif box.shape == (6, ):
        return to_triclinic(box)
    else:
        raise ValueError("Unkown box format")


def to_triclinic(box):
    """Convert `[A,B,C,alpha,beta,gamma]` to a triclinic box representation.

    Original `code by Tsjerk Wassenaar`_ posted on the Gromacs mailinglist.

    .. _code by Tsjerk Wassenaar:
       http://www.mail-archive.com/gmx-users@gromacs.org/msg28032.html

    Parameters
    ----------
    box : array_like (6, )
        list of box lengths and angles (in degrees) such as
        ``[A,B,C,alpha,beta,gamma]``

    Returns
    -------
    tri_box, ndarray (3, 3)
       with `a, b, c = tri_box` the triclinic box vectors
    """
    tri_box = np.zeros((3, 3))
    x, y, z, a, b, c = box

    if np.all(box[:3] == 0):
        return tri_box

    tri_box[0][0] = x
    if a == 90. and b == 90. and c == 90.:
        tri_box[1][1] = y
        tri_box[2][2] = z
    else:
        a = np.deg2rad(a)
        b = np.deg2rad(b)
        c = np.deg2rad(c)
        tri_box[1][0] = y * np.cos(c)
        tri_box[1][1] = y * np.sin(c)
        tri_box[2][0] = z * np.cos(b)
        tri_box[2][1] = z * (np.cos(a) - np.cos(b) * np.cos(c)) / np.sin(c)
        tri_box[2][2] = np.sqrt(z * z - tri_box[2][0]**2 - tri_box[2][1]**2)
    return tri_box
