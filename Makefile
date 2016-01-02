prefix=/usr/local
CXXFLAGS=-std=c++11

all: rc-rsl
	
rc-rsl: rc-rsl.o
	$(CXX) $(CXXFLAGS) $+ -o $@ -lwiringPi

install: rc-rsl
	install -m 755 rc-rsl $(prefix)/bin

uninstall:
	$(RM) $(prefix)/bin/rc-rsl

clean:
	$(RM) *.o rc-rsl