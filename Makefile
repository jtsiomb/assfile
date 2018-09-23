src = $(wildcard src/*.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

name = assman
lib_a = lib$(name).a

warn = -pedantic -Wall
dbg = -g
opt = -O0

CFLAGS = $(warn) $(dbg) $(opt) $(inc)
LDFLAGS =

$(lib_a): $(obj)
	$(AR) rcs $@ $(obj)

%.d: %.c
	@echo "generating depfile $< -> $@"
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(bin)

.PHONY: cleandep
cleandep:
	rm -f $(dep)
