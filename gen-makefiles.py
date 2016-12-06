#!/usr/bin/python
import os, re

src="src"
template = "template.make"
libs = [
    # subdir              # lib
    ("src/util",          "util"),
    ("src/backend",       "backend"),
    ("src/backend/term",  "term-backend"),
]


templ = []
with open(template) as fh:
    for line in fh:
        templ.append(re.split("#LIBNAME#", line))

for (subdir,lib) in libs:
    with open(os.path.join(subdir, ".make"), "w") as fh:
        for parts in templ:
            fh.write(lib.join(parts))
    print("- generated makefile in %s " % subdir)

with open("libs.make", "w") as fh:
    fh.write("libs = %s\n"
             % " ".join(os.path.join(subdir, "lib%s.a" % lib)
                        for (subdir,lib) in libs))
    for (subdir,lib) in libs:
        arpath = os.path.join(subdir, "lib%s.a" % lib)
        fh.write(".PHONY: %s\n" % arpath)
        fh.write("%s:\n" % arpath)
        fh.write("\t@$(MAKE) lib%s.a -C %s -f .make\n" % (lib, subdir))
        fh.write("\n")

    fh.write(".PHONY: clean-libs\nclean-libs:\n")
    for (subdir,lib) in libs:
        fh.write("\t@$(MAKE) clean -C %s -f .make\n" % subdir) 

    print("- generated libs.make")
