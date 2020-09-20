Introduction
===============

Enlightenment is an extensible database software.

It is divided into the following modules:

| Module | Description |
| ------ | ----------- |
| enl-server-cli | Command-line tool to start a local server. |
| enl-server | Library to use when developing your application. |
| enl-api | Library to use when developing custom Engines or Drivers. |

More info about these modules can be found in [Project Structure](doc/images/enl-global-structure-dark.png) [(L)](doc/images/enl-global-structure-light.png) and [CMake Structure](doc/images/cmake-structure-dark.png) [(L)](doc/images/cmake-structure-light.png)

License
===============

Copyright (c) 2020 Hypothermic IT <br />

See COPYING file for license information.

Installation
===============

See build and installation instructions given in the [INSTALL](/INSTALL.md) file.

Documentation
===============

See the software manual for details on the software including a demonstration
of how to apply the software tools provided by this package.

Roadmap
===============

1. [x] Main library
2. [ ] CLI
3. [ ] Engines
    - [ ] In-memory engine
    - [ ] Disk storage engine
    - [ ] Hybrid engine
4. [ ] Drivers
    - [ ] ENL minimalistic driver
    - [ ] MySQL/MariaDB compatible
    - [ ] Mongo compatible driver (although ours is relational, it'll work probably)
5. [ ] Easier integration for library users through some sort of higher order control structure

Package Content
===============

Path                    | Content description
----------------------- | ----------------------------------------------------------
[BasisProject.cmake][1] | Meta-data used for the build configuration.
[CMakeLists.txt]    [2] | Root CMake configuration file.
[config/]           [3] | Package configuration files.
[data/]             [4] | Data files required by this software.
[doc/]              [5] | Documentation source files.
[example/]          [6] | Example files used for demonstration.
[include/]          [7] | Public header files.
[src/]              [8] | Source code files.
[test/]             [9] | Regression and unit tests.






<!-- --------------------------------------------------------------------------------- -->

<!-- Links to GitHub, see the local directory if you have downloaded the files already -->
[1]: /BasisProject.cmake
[2]: /CMakeLists.txt
[3]: /config
[4]: /data
[5]: /doc
[6]: /example
[7]: /include
[8]: /src
[9]: /test
