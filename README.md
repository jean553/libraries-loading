# Libraries loading

This is a short personal memo about static/shared libraries loading process.

## Table of content

- [Static libraries](#static-libraries)
    * [Write C code](#write-c-code)
    * [Generate object files](#generate-object-files)
    * [Generate archive file](#generate-archive-file)

## Static libraries

Static libraries on Linux have the `.a` extension (for `archive`).
This section goes througout the static library creation process in details.

### Write C code

First, let's write some C code for our library. Our library is divided into four files:
 * `sum.c` and `sum.h` that contains a sum function definition and declaration,
 * `mul.c` and `mul.h` that contains a multiplication function definition and declaration

```c
/* sum.c */

#include "sum.h"

#include "mul.h" // declaration required as mul() is used below

int sum_and_mul(int first, int second) {
    return first + mul(first, second);
}
```

```c
/* mul.c */

#include "mul.h"

int mul(int first, int second) {
    return first * second;
}
```

```c
/* sum.h */

int sum_and_mul(int first, int second);
```

```c
/* mul.h */

int mul(int first, int second);
```

### Generate object files

Object files are `compiled` files but not `linked` files.
That means `symbols` are `not resolved` from one object to another.

For example, two object files are generated for the two sources files `sum.c` and `mul.c`:
 * `mul.o` has no symbols to other objects, so it has no unresolved symbols,
 * `sum.o` has the symbol `mul` that is defined into the `mul.o` object, this symbol is unresolved

This is fine for now, the files are supposed to be grouped together later.

The two generated object files can be represented as follow:

![Image 1](images/first.png)

The files are generated through the following command:

```sh
gcc -c mul.c -o mul.o
gcc -c sum.c -o sum.o
```

### Generate archive file

The archive file `.a` is a group of `object` files, all together.

![Image 2](images/second.png)

The archive file is generated through the `ar` command:

```sh
ar rvs libstatic_library.a sum.o mul.o
```

The `rvs` option stand for: replacement, verbosity and add new "objects" (indices) to the archive,
replace them if necessary.

Note that no linking is done here. The unresolved symbols remain unresolved after the archive creation, even if the two concerned objects are part of the archive.
