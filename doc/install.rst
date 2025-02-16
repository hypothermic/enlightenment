.. meta::
    :description: Build and installation instructions for Enlightenment.

============
Installation
============

See the `BASIS guide on software installation`_ for a complete list of build tools and
detailed installation instructions.


Prerequisites
=============

.. raw:: html
    
    <br />

.. The tabularcolumns directive is required to help with formatting the table properly
   in case of LaTeX (PDF) output.

.. tabularcolumns:: |p{3.75cm}|m{1.5cm}|p{9.8cm}|

+---------------------+---------+--------------------------------------------------------------------------------------+
| Dependency          | Version | Description                                                                          |
+=====================+=========+======================================================================================+
| BASIS_              | 3.2.0   | Utility to automate and standardize creating, documenting, and sharing software.     |
+---------------------+---------+--------------------------------------------------------------------------------------+

.. _BASIS: https://cmake-basis.github.io/


.. raw:: html
    
    <br />


Configure
=========

1. Extract source files::

    tar -xzf enlightenment-1.0.0-source.tar.gz

2. Create build directory::

    mkdir enlightenment-1.0.0-build

3. Change to build directory::

    cd enlightenment-1.0.0-build

4. Run CMake_ to configure the build tree::

    ccmake -DBASIS_DIR:PATH=/path/to/basis ../enlightenment-1.0.0-source

   - Press ``c`` to configure the build system and ``e`` to ignore warnings.
   - Set ``CMAKE_INSTALL_PREFIX`` and other CMake variables and options.
   - Continue pressing ``c`` until the option ``g`` is available.
   - Then press ``g`` to generate the `GNU Make`_ configuration files.


Build
=====

After the configuration of the build tree, the software can be build using `GNU Make`_::

    make


Test
====

After the build of the software, optionally run the tests using the command::

    make test

In case of failing tests, re-run the tests, but this time by executing CTest_
directly with the ``-V`` option to enable verbose output and redirect the output
to a text file:

.. code-block:: bash

    ctest -V >& enlightenment-test.log

and attach the file ``enlightenment-test.log`` to the issue report.


Install
=======

The final installation copies the built files and additional data and documentation
files to the installation directory specified using the ``CMAKE_INSTALL_PREFIX``
option during the configuration of the build tree::

    make install
    
After the successful installation, the build directory can be removed again.

.. _BASIS: https://cmake-basis.github.io/
.. _BASIS guide on software installation: https://cmake-basis.github.io/howto/install.html
.. _CMake: http://www.cmake.org/
.. _CTest: http://www.cmake.org/cmake/help/v2.8.8/ctest.html
.. _GNU Make: http://www.gnu.org/software/make/
