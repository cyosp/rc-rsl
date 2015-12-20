prefix=/usr/local

all: rc-rsl
	
rc-rsl: RCSwitch.o rc-rsl.o
	$(CXX) $+ -o $@ -lwiringPi

install: rc-rsl
	install -m 755 rc-rsl $(prefix)/bin

uninstall:
	$(RM) $(prefix)/bin/rc-rsl

clean:
	$(RM) *.o rc-rsl