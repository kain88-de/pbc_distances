=========================================
  Periodic Boundary Conditions Distances
=========================================

High Performance package to calculate various distances with periodic boundary
conditions.


Using pbc_distances
===================

To calculate all pair wise distances without periodic boundaries and double precision use.

.. code:: python

   import pbc_distances
   import numpy as np

   pos = np.random.uniform(-1, 1, size=(5000, 3))

   dist = pbc_distances.pairwise_distance(pos, pos, box=None, precision='double')

If you have periodic boundary condition just supply the box argument.
pbc_distances will try to figure out what box you supplied and use the
appropriate algorithm.

Besides pairwise distances `pbc_distances` also supports bond, angle and dihedral.

Building
========

build only the extension

.. code:: bash
   python setup.py build_ext -i

installation

.. code:: bash
   python setup.py install

Guide for Developers
====================

The library achieves it's performance by using SIMD instructions. To be able to
run on many different platforms it uses inastemp_. This allows the library to be
compiled against many different SIMD instructions and always choosing the best
possible option.

The pbc algorithms are implemented as c++ functors in `mic_*.h`. Having these
functors allows to decouple them from the actual distance calculations. This
results in just having to write one distance algorithm and have c++ templates
figure out the concrete types.

To expose the distance to cython it's best to only have pod data types (double,
float) as a template parameter. Therefore you might need to create one distance
function that takes an template parameter for the SIMD type to use called
`__distance_...(...)` and expose it to cython as

.. code:: c++
   // vectorized version
   template<typename T>
   _distance_...(...) {
   using VecType = InaVecBestType<T>;
   __distance<VecType, T, mic_func>(...);
   }

   // non vectorized version
   template<typename T>
   _distance_..._single(...) {
   using VecType = InaVecSCALAR<T>;
   __distance<VecType, T, mic_func>(...);
   }


 As one should note creating a non vectorized version is also simple with
 inastemp as the example above shows.
