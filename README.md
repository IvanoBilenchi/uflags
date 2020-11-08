## uFlags - collection of C primitives to safely manipulate bitmasks.

### Author

[Ivano Bilenchi](https://ivanobilenchi.com)

### Description

Implementation of bitmask manipulation primitives focused on safety with regards to
unexpected type promotions.

### Usage

If you are using [CMake](https://cmake.org) as your build system, you can add `uFlags` as
a subproject, then link against the `uflags` target. Otherwise, in general you just need
the [uflags.h](include/uflags.h) header.

### Documentation

Documentation for the project is provided in form of docstrings in the *Public API* section
of [uflags.h](include/uflags.h). You can also generate HTML docs via CMake, though you will
also need [Doxygen](http://www.doxygen.nl). For usage examples, see [test.c](test/test.c).

### CMake targets

- `uflags`: interface library target, which you can link against.
- `uflags-docs`: generates documentation via Doxygen.
- `uflags-test`: generates the test suite.

### License

`uFlags` is available under the MIT license. See the [LICENSE](./LICENSE) file for more info.
