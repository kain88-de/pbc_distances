=========================================
  Periodic Boundary Conditions Distances
=========================================

High Performance package to calculate various distances with periodic boundary
conditions.

.. warning::
   This project is **alpha software** and not API stable. It serves as an
   example how to write reusable code with specialized compilation units.


Using pbc_distances
===================

To calculate all pair wise distances without periodic boundaries and double precision use.

.. code:: python

   from pbc_distances import distance_sse3 as pbc
   import numpy as np

   pos = np.random.uniform(-1, 1, size=(5000, 3))

   dist = pbc.pairwise_distance(pos, pos, box=None, precision='double')

If you have periodic boundary condition just supply the box argument.
pbc_distances will try to figure out what box you supplied and use the
appropriate algorithm.

The above example uses the SSE3 implementation. Please have a look into the
setup.py which SIMD instruction sets are currently compiled.

Besides pairwise distances `pbc_distances` also supports bond, angle and dihedral.

Building
========

build only the extension

.. code:: bash

   python setup.py build_ext -i

installation

.. code:: bash

   python setup.py install


Benchmark Results
================

The repository contains some benchmark results in the `results_***.md` files.
It compares the performance of this module with MDAnalysis and mdtraj. The
possible performance gains using this module are up to a factor of 10. 
Below is the used CPU and compiler.

gcc = 7.2.1
CPU = Intel(R) Core(TM) i7-4600U CPU @ 2.10GHz

Guide for Developers
====================

The library achieves it's performance by using SIMD instructions. To be able to
run on many different platforms it uses inastemp_. This allows the library to be
compiled against many different SIMD instructions and always choosing the best
possible option.

The pbc algorithms are implemented as c++ functors in `mic_*.h`. Having these
functors allows to decouple them from the actual distance calculations. This
results in just having to write one distance algorithm and have c++ templates
figure out the concrete types. This design let's us reuse code as much as
possible and with enabled optimizations `-O3` the compiler is also able to
remove all boiler plate we created.

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
   _distance_..._scalar(...) {
   using VecType = InaVecSCALAR<T>;
   __distance<VecType, T, mic_func>(...);
   }


 As one should note creating a non vectorized version is also simple with
 inastemp as the example above shows.


Testing
=======

Due to the code reuse design we only need to test the minimal image convention
distances once for every box type. This means there is no need to test all box
types for all the different distances (pairwise/bond/angle/dihedral) that
pbc_distances provides.

The different distances can then be tested using no pbc conditions.
