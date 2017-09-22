Build with gcc 6.3

Benchmark TRICLINIC ######################################################
generate points
image search (float)
scalar
1 loop, best of 3: 1.78 s per loop
sse3
1 loop, best of 3: 914 ms per loop
sse4
1 loop, best of 3: 931 ms per loop
avx
1 loop, best of 3: 328 ms per loop

image search (double)
scalar
1 loop, best of 3: 1.85 s per loop
sse3
1 loop, best of 3: 1.49 s per loop
sse4
1 loop, best of 3: 1.51 s per loop
avx
1 loop, best of 3: 600 ms per loop

MDAnalysis
1 loop, best of 3: 374 ms per loop

mdtraj to slow
1 loop, best of 3: 4.54 s per loop

Benchmark ORTHO ######################################################
generate points
image search (float)
scalar
1 loop, best of 3: 1.13 s per loop
sse3
1 loop, best of 3: 705 ms per loop
sse4
1 loop, best of 3: 703 ms per loop
avx
10 loops, best of 3: 178 ms per loop

image search (double)
scalar
1 loop, best of 3: 847 ms per loop
sse3
1 loop, best of 3: 972 ms per loop
sse4
1 loop, best of 3: 977 ms per loop
avx
1 loop, best of 3: 329 ms per loop

MDAnalysis
1 loop, best of 3: 470 ms per loop

mdtraj to slow
1 loop, best of 3: 389 ms per loop

Benchmark NO PBC ######################################################
generate points
image search (float)
scalar
1 loop, best of 3: 278 ms per loop
sse3
1 loop, best of 3: 247 ms per loop
sse4
1 loop, best of 3: 250 ms per loop
avx
10 loops, best of 3: 135 ms per loop

image search (double)
scalar
1 loop, best of 3: 405 ms per loop
sse3
1 loop, best of 3: 310 ms per loop
sse4
1 loop, best of 3: 308 ms per loop
avx
1 loop, best of 3: 253 ms per loop

MDAnalysis
1 loop, best of 3: 203 ms per loop

mdtraj to slow
1 loop, best of 3: 190 ms per loop

scipy
10 loops, best of 3: 188 ms per loop

