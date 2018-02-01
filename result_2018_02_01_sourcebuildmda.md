]0;IPython: past-projects/pbc_distancesVersion information
MDAnalysis =  0.17.1-dev
MDtraj =  1.9.1
scipy =  1.0.0

Benchmark TRICLINIC ######################################################
generate points
image search (float)
scalar
413 ms ± 2.84 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse3
345 ms ± 1.6 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse4
235 ms ± 3.94 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
avx
87.2 ms ± 113 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)

image search (double)
scalar
655 ms ± 7.96 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse3
279 ms ± 2.43 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse4
239 ms ± 8.87 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
avx
248 ms ± 717 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)

MDAnalysis
1.5 s ± 9.97 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)

mdtraj
3.8 s ± 6.11 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)

Benchmark ORTHO ######################################################
generate points
image search (float)
scalar
1.22 s ± 2.21 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse3
599 ms ± 3.1 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse4
496 ms ± 374 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)
avx
275 ms ± 885 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)

image search (double)
scalar
1.33 s ± 3.85 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse3
649 ms ± 3.78 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse4
581 ms ± 3.42 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
avx
457 ms ± 392 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)

MDAnalysis
1.51 s ± 1.85 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)

mdtraj
208 ms ± 1.07 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)

Benchmark NO PBC ######################################################
generate points
image search (float)
scalar
170 ms ± 717 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)
sse3
186 ms ± 483 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)
sse4
191 ms ± 970 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)
avx
196 ms ± 1.74 ms per loop (mean ± std. dev. of 7 runs, 10 loops each)

image search (double)
scalar
210 ms ± 514 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse3
217 ms ± 916 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)
sse4
217 ms ± 872 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)
avx
231 ms ± 475 µs per loop (mean ± std. dev. of 7 runs, 1 loop each)

MDAnalysis
166 ms ± 484 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)

mdtraj
126 ms ± 842 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)

scipy
167 ms ± 619 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)
