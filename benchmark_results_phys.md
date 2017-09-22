Build with gcc 6.3

Benchmark TRICLINIC ######################################################
generate points
image search (float)
scalar
1 loop, best of 3: 1.1 s per loop
sse3
1 loop, best of 3: 672 ms per loop
sse4
1 loop, best of 3: 672 ms per loop
avx
1 loop, best of 3: 227 ms per loop

image search (double)
scalar
1 loop, best of 3: 1.23 s per loop
sse3
1 loop, best of 3: 1.14 s per loop
sse4
1 loop, best of 3: 1.14 s per loop
avx
1 loop, best of 3: 450 ms per loop

MDAnalysis
1 loop, best of 3: 259 ms per loop

mdtraj to slow
1 loop, best of 3: 3.37 s per loop

Benchmark ORTHO ######################################################
generate points
image search (float)
scalar
1 loop, best of 3: 779 ms per loop
sse3
1 loop, best of 3: 525 ms per loop
sse4
1 loop, best of 3: 508 ms per loop
avx
10 loops, best of 3: 142 ms per loop

image search (double)
scalar
1 loop, best of 3: 596 ms per loop
sse3
1 loop, best of 3: 797 ms per loop
sse4
1 loop, best of 3: 798 ms per loop
avx
1 loop, best of 3: 278 ms per loop

MDAnalysis
1 loop, best of 3: 321 ms per loop

mdtraj to slow
1 loop, best of 3: 203 ms per loop

Benchmark NO PBC ######################################################
generate points
image search (float)
scalar
1 loop, best of 3: 240 ms per loop
sse3
1 loop, best of 3: 216 ms per loop
sse4
1 loop, best of 3: 217 ms per loop
avx
10 loops, best of 3: 119 ms per loop

image search (double)
scalar
1 loop, best of 3: 363 ms per loop
sse3
1 loop, best of 3: 273 ms per loop
sse4
1 loop, best of 3: 273 ms per loop
avx
1 loop, best of 3: 228 ms per loop

MDAnalysis
10 loops, best of 3: 142 ms per loop

mdtraj to slow
10 loops, best of 3: 123 ms per loop

scipy
10 loops, best of 3: 142 ms per loop

