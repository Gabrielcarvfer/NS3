#!/usr/bin/env python
from setuptools import setup

with open('README.rst') as file_:
    LONG_DESCRIPTION = file_.read()


setup(name='PyBindGen',
      use_scm_version={"version_scheme": "post-release",
                       "write_to": "pybindgen/version.py"},
      setup_requires=['setuptools_scm'],
      description='Python Bindings Generator',
      author='Gustavo Carneiro',
      author_email='gjcarneiro@gmail.com',
      url='https://launchpad.net/pybindgen',
      packages=['pybindgen',
                'pybindgen.typehandlers',
                'pybindgen.typehandlers.ctypeparser',
                ],
      long_description=LONG_DESCRIPTION,
      )
