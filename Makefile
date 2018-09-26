src = $(wildcard src/*.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

name = assman
so_major = 0
so_minor = 1

lib_a = lib$(name).a
lib_so = lib$(name).so.$(so_major).$(so_minor)
soname = lib$(name).so.$(so_major)
devlink = lib$(name).so
shared = -shared -Wl,-soname,$(soname)

warn = -pedantic -Wall
dbg = -g
opt = -O0
def = -DBUILD_MOD_URL
pic = -fPIC

CFLAGS = $(warn) $(dbg) $(opt) $(pic) $(def) $(inc) -pthread
LDFLAGS = -pthread -lpthread -lcurl

.PHONY: all
all: $(lib_so) $(lib_a) $(soname) $(devlink)

$(lib_so): $(obj)
	$(CC) -o $@ $(shared) $(obj) $(LDFLAGS)

$(lib_a): $(obj)
	$(AR) rcs $@ $(obj)

$(soname): $(lib_so)
	rm -f $@ && ln -s $< $@

$(devlink): $(soname)
	rm -f $@ && ln -s $< $@

%.d: %.c
	@echo "generating depfile $< -> $@"
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(lib_a) $(lib_so) $(soname) $(devlink)

.PHONY: cleandep
cleandep:
	rm -f $(dep)
