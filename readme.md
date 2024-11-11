# Simple software timer module

- This is a simple software timer module implemented in C;
- The idea is to, through one source of time base, be able to enable a pre-defined max number of independent, asynchronous timers with callback capabilities;
- This is a personal project focused on experimenting with such skills:
    - Jenkins;
    - CMake;
    - Bash scripting;
    - Unity test;
    - Clang formatter;
    - GIT;
    - C programing language;

- Examples of commands to operate the repository:

```bash
# [r]ebuild and [e]xecute the example
$ ./bbuild.sh -r -e example

# [r]ebuild and [e]xecute the (unit) tests
$ ./bbuild.sh -r -e tests

# [r]ebuild the shared library (.so file)
$ ./bbuild.sh -r lib
```