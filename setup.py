from Cython.Build import cythonize
from setuptools import Extension, setup


def extensions():
    exts = []
    exts.append(Extension('pbc_distances.distance',
                          sources=['pbc_distances/distance.pyx', ],
                          include_dirs=['pbc_distances/inastemp/Src', 'pbc_distances'],
                          extra_compile_args=['-msse4', '-funroll-loops', '-std=c++11'],
                          language='c++'))
    exts.append(Extension('pbc_distances.distance_scalar',
                          sources=['pbc_distances/distance_scalar.pyx', ],
                          include_dirs=['pbc_distances/inastemp/Src', 'pbc_distances'],
                          extra_compile_args=['-funroll-loops', '-std=c++11'],
                          language='c++'))
    return cythonize(exts)


setup(
    name='pbc_distances',
    version='0.1',
    description='pbc distance calculations',
    author='Max Linke',
    ext_modules=extensions(),
    zip_safe=False)
