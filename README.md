cyberlike
************

Building
----------

This project uses `make`, but includes a small python script that
automatically generates some makefiles. The generation of these
makefiles is controlled by `gen-makefiles.py` and `template.make`.

To build, run:

    $ make makefiles
    $ make

Additionally, build the doxygen docs with

    $ make docs

