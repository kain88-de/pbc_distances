import itertools
import numpy as np
from scipy.spatial.distance import cdist

# import pytest

import pbc_distances
from pbc_distances import distance_scalar


def slow_shifts(box):
    neighbors = []
    a, b, c = box.T
    for i, j, k in itertools.product(range(-1, 2), repeat=3):
        neighbors.append(i * a + j * b + k * c)
    return np.asarray(neighbors)


def slow_brute_force(pos_a, pos_b, h):
    images = pos_b + slow_shifts(h)
    dist = np.linalg.norm(pos_a - images, axis=1)**2
    return dist.min()


def pair_dist(pos, box):
    num = pos.shape[0]
    ref_dist = np.zeros((num, num))
    for i, j in itertools.combinations_with_replacement(range(num), 2):
        ref_dist[i, j] = slow_brute_force(pos[i], pos[j], box)
        ref_dist[j, i] = ref_dist[i, j]

    return ref_dist


def gen_points(d, box_type, num=50):
    if box_type == 'triclinic':
        box = np.array([[d, .5 * d, .5 * d],
                        [0, .5 * np.sqrt(3) * d, 1 / 6 * np.sqrt(3) * d],
                        [0, 0, 1 / 3 * np.sqrt(6) * d]])
    elif box_type == 'ortho':
        box = np.eye(3) * d
    else:
        box = np.eye(3)

    a, b, c = box.T
    pos = np.random.uniform(0, 1, size=(num, 3))
    pos = (pos[:, 0][:, np.newaxis] * a + pos[:, 1][:, np.newaxis] * b +
           pos[:, 2][:, np.newaxis] * c)
    return pos, box


def test_triclinic():
    points, box = gen_points(2, 'triclinic')
    ref_dist = pair_dist(points, box)
    dist = pbc_distances.pairwise_distance(
        points, points, box, precision='double')
    np.testing.assert_almost_equal(ref_dist, dist)


def test_ortho():
    points, box = gen_points(2, 'ortho')
    ref_dist = pair_dist(points, box)
    dist = pbc_distances.pairwise_distance(
        points, points, box, precision='double')
    np.testing.assert_almost_equal(ref_dist, dist)


def test_none():
    points, box = gen_points(2, 'ortho')
    ref_dist = cdist(points, points) ** 2
    dist = pbc_distances.pairwise_distance(
        points, points, None, precision='double')
    np.testing.assert_almost_equal(ref_dist, dist)


def test_triclinic_scalar():
    points, box = gen_points(2, 'triclinic')
    ref_dist = pair_dist(points, box)
    dist = distance_scalar.pairwise_distance(
        points, points, box, precision='double')
    np.testing.assert_almost_equal(ref_dist, dist)


def test_ortho_scalar():
    points, box = gen_points(2, 'ortho')
    ref_dist = pair_dist(points, box)
    dist = distance_scalar.pairwise_distance(
        points, points, box, precision='double')
    np.testing.assert_almost_equal(ref_dist, dist)


def test_none_scalar():
    points, box = gen_points(2, 'ortho')
    ref_dist = cdist(points, points) ** 2
    dist = distance_scalar.pairwise_distance(
        points, points, None, precision='double')
    np.testing.assert_almost_equal(ref_dist, dist)
