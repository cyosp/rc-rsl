prefix=/usr/local
CXX=$(CROSS_COMPILE)-g++
CXXFLAGS=-std=c++11

all: rc-rsl

rc-rsl: rc-rsl.cpp
	$(CXX) -I $(SYSTEM_ROOT)/usr/include $(CXXFLAGS) -c $@.cpp -o $@.o
	$(CXX) -lgpiod -L$(SYSTEM_ROOT)/usr/lib/$(CROSS_COMPILE) --sysroot=$(SYSTEM_ROOT)  $@.o -o $@

install: rc-rsl
	install -m 755 rc-rsl $(prefix)/bin

uninstall:
	$(RM) $(prefix)/bin/rc-rsl

clean:
	$(RM) *.o rc-rsl