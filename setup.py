from __future__ import print_function

from Cython.Build import cythonize
from setuptools import Extension, setup


def extensions():
    exts = []
    exts.append(Extension('pbc_distances.distance',
                          sources=['pbc_distances/distance.pyx', ],
                          include_dirs=['pbc_distances/inastemp/Src', 'pbc_distances'],
                          extra_compile_args=['-msse4', '-funroll-loops', '-g'],
                          language='c++'))
    return cythonize(exts)


setup(
    name='pbc_distances',
    version='0.1',
    description='pbc distance calculations',
    author='Max Linke',
    packages='pbc',
    ext_modules=extensions(),
    zip_safe=False)