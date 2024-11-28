# cargo-c corrupt dll.lib repro

Reproduction steps:

### Install the ffi library with `cargo capi`:

```ps
cd example-ffi
cargo capi install --prefix build
```

The `build` subdir of `example-ffi` should now contain:

* `bin/` with `example-ffi.dll` and `exmaple-ffi.pdb`
* `include/` with `example-ffi.h`
* `lib/` with `example-ffi.def`, `example-ffi.dll.lib` and `example.ffi.lib` (as well as a `pkgconfig` subdir)

### Try to build the C application:

1. Update `example-c/CMakeLists.txt` to set the `find_library` directory path to
the location you cloned this repo. e.g.

```cmake
find_library(EXAMPLE_FFI_LIB example-ffi
    PATHS "C:/Users/danie/Code/Rust/example-ffi/example-ffi/build/lib"
    REQUIRED
)
```


2. Run the build:
```ps
cd example-c
cmake -S . -B build
cmake --build build
```

3. Observe the error output:
```
PS C:\Users\danie\Code\Rust\example-ffi\example-c> cmake -S . -B build
-- Building for: Visual Studio 17 2022
-- Selecting Windows SDK version 10.0.22621.0 to target Windows 10.0.22631.
-- The C compiler identification is MSVC 19.41.34123.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.41.34120/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found example-ffi library: C:/Users/danie/Code/Rust/example-ffi/example-ffi/build/lib/example-ffi.dll.lib
-- Configuring done (2.0s)
-- Generating done (0.0s)
-- Build files have been written to: C:/Users/danie/Code/Rust/example-ffi/example-c/build
PS C:\Users\danie\Code\Rust\example-ffi\example-c> cmake --build build
MSBuild version 17.11.9+a69bbaaf5 for .NET Framework

  1>Checking Build System
  Building Custom Rule C:/Users/danie/Code/Rust/example-ffi/example-c/CMakeLists.txt
  main.c
C:\Users\danie\Code\Rust\example-ffi\example-ffi\build\lib\example-ffi.dll.lib : fatal error LNK1127: library is corrupt [C:\Us
ers\danie\Code\Rust\example-ffi\example-c\build\example-c.vcxproj]
```

4. Optionally, confirm with `dumpbin`:

```ps
cd example-c\build\lib
dumpbin /exports example-ffi.dll.lib
```

Produces:
```
Microsoft (R) COFF/PE Dumper Version 14.41.34123.0
Copyright (C) Microsoft Corporation.  All rights reserved.


Dump of file example-ffi.dll.lib

File Type: LIBRARY
example-ffi.dll.lib : fatal error LNK1107: invalid or corrupt file: cannot read at 0x42A
```

The same command works if provided the static `example-ffi.lib` instead of `example-ffi.dll.lib` as an argument.