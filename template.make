# include
inc=-I$(SRC_DIR)

# compilers
cflags=$(inc) -Wall -g
cxxflags=$(cflags) -std=c++14

cc=gcc $(cflags)
cxx=g++ $(cxxflags)
ar=ar cr

# sources & objects
obj=.obj
srcs=$(wildcard *.c *.cpp)
objs=$(srcs:%=$(obj)/%.o)
objdirs=$(patsubst %,.obj/%,$(shell find * -type d -not -name $(obj)))

lib#LIBNAME#.a: $(objdirs) $(obj) $(objs)
	$(ar) $@ $(objs)
	@echo -e "Built library \x1b[33;1m-#LIBNAME#-\x1b[0m"

$(obj):
	mkdir -p $@
$(obj)/%:
	mkdir -p $@

-include $(wildcard $(obj)/*.dep)

$(obj)/%.c.o: %.c
	$(cc) $< -c -o $@
	@$(cc) $< -MM -MT $@ -o $(obj)/$<.dep

$(obj)/%.cpp.o: %.cpp
	$(cxx) $< -c -o $@
	@$(cxx) $< -MM -MT $@ -o $(obj)/$<.dep

.PHONY: clean
clean:
	rm -rf $(obj) lib#LIBNAME#.a
