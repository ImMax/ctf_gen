# Examples of generating traces in Common Trace Format (CTF).

## barectf
This examples shows how to generate CTF file with [barectf](https://barectf.org)

### build
`mkdir cmake-build-debug && cd cmake-build-debug`

`cmake ../`

`cmake --build . --target ctf_gen -- -j 8`

### Description
After build you can find all generated code in `gen` directory. 
In `gen/traces` placed CTF metadata and traces itself.

This project could be open in CLion.
