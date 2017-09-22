from Cython.Build import cythonize
from setuptools import Extension, setup


def extensions():
    exts = []
    optimizations = ['sse3', 'sse4', 'avx']
    for opt in ['sse3', 'sse4', 'avx']:
        exts.append(Extension('pbc_distances.distance_{}'.format(opt),
                            sources=['pbc_distances/distance_{}.pyx'.format(opt), ],
                            include_dirs=['pbc_distances/inastemp/Src', 'pbc_distances'],
                            extra_compile_args=['-m{}'.format(opt), '-funroll-loops', '-std=c++11'],
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
    install_requires=[
        'numpy>=1.8',
    ],
    tests_require=[
        'pytest',
        'scipy'
    ],
    ext_modules=extensions(),
    zip_safe=False)
