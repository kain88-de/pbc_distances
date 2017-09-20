 ##################################################################
 # pbc_distances - Max Linke - 2017                               #
 # Under MIT Licence, please you must read the LICENCE.txt file.  #
 ##################################################################
import numpy as np
from . import box_types

cdef extern from 'distances.h':
    cdef void _pairwise_distance_triclinic[T](const T *, const int , const T *, const int ,
                                              const T *, T *)
    cdef void _pairwise_distance_ortho[T](const T *, const int , const T *, const int ,
                                          const T *, T *)
    cdef void _pairwise_distance[T](const T *, const int , const T *, const int ,
                                    const T *, T *)

def _pairwise_distance_single(in_pos_a, in_pos_b, in_box, box_type):
    dtype = np.float32

    cdef float[::1, :] pos_a = np.asarray(in_pos_a, dtype=dtype, order='F')
    cdef float[::1, :] pos_b = np.asarray(in_pos_b, dtype=dtype, order='F')
    cdef float[:, ::1] box = np.asarray(in_box, dtype=dtype, order='C')
    cdef int m = pos_a.shape[0]
    cdef int n = pos_b.shape[0]
    cdef float[:, ::1] out = np.empty((m, n), dtype=dtype)
    if box_type == 'triclinic':
        _pairwise_distance_triclinic(<float*>&pos_a[0, 0], m, <float*>&pos_b[0, 0], n, <float*>&box[0, 0], <float*>&out[0, 0])
    elif box_type == 'ortho':
        _pairwise_distance_ortho(<float*>&pos_a[0, 0], m, <float*>&pos_b[0, 0], n, <float*>&box[0, 0], <float*>&out[0, 0])
    elif box_type == 'none':
        _pairwise_distance(<float*>&pos_a[0, 0], m, <float*>&pos_b[0, 0], n, <float*>&box[0, 0], <float*>&out[0, 0])
    else:
        raise ValueError("Unkown box-type '{}' has to be one of triclinic, ortho, none".format(box_type))
    return np.asarray(out)

def _pairwise_distance_double(in_pos_a, in_pos_b, in_box, box_type):
    dtype = np.float64

    cdef double[::1, :] pos_a = np.asarray(in_pos_a, dtype=dtype, order='F')
    cdef double[::1, :] pos_b = np.asarray(in_pos_b, dtype=dtype, order='F')
    cdef double[:, ::1] box = np.asarray(in_box, dtype=dtype, order='C')
    cdef int m = pos_a.shape[0]
    cdef int n = pos_b.shape[0]
    cdef double[:, ::1] out = np.empty((m, n), dtype=dtype)
    if box_type == 'triclinic':
        _pairwise_distance_triclinic(<double*>&pos_a[0, 0], m, <double*>&pos_b[0, 0], n, <double*>&box[0, 0], <double*>&out[0, 0])
    elif box_type == 'ortho':
        _pairwise_distance_ortho(<double*>&pos_a[0, 0], m, <double*>&pos_b[0, 0], n, <double*>&box[0, 0], <double*>&out[0, 0])
    elif box_type == 'none':
        _pairwise_distance(<double*>&pos_a[0, 0], m, <double*>&pos_b[0, 0], n, <double*>&box[0, 0], <double*>&out[0, 0])
    else:
        raise ValueError("Unkown box-type '{}' has to be one of triclinic, ortho, none".format(box_type))
    return np.asarray(out)


def pairwise_distance(a, b, box, precision='single'):
    """calculate the all pairwise squared distances between particles in `a` and
    `b`. This function uses specialized SIMD instructions.

    Parameters
    ==========
    a : ndarray (m, 3)
       particle positions
    b : ndarray (n, 3)
       particle positions
    box : array-like / None
       periodic boundary box,
    precision : string (optional)
        use single or double precision calculations

    Returns
    =======
    ndarray (m, n)
       squared distance between all particles in a and b.

    See Also
    ========
    box_types.normalize_box
    box_types.box_check
    distances_scalar.pairwise_distance
    """
    box = box_types.normalize_box(box)
    box_type = box_types.box_check(box)

    if a.shape[1] != 3 or b.shape[1] != 3:
        raise ValueError("a/b shape has to be (m, 3) or (n, 3)")

    precision = precision.lower()
    if precision == 'single':
        return _pairwise_distance_single(a, b, box, box_type)
    elif precision == 'double':
        return _pairwise_distance_double(a, b, box, box_type)
    else:
        raise ValueError("precision can only be 'single' or 'double'")
