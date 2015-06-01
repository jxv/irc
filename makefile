all:
	gcc src/irc.c -c -o src/irc.o -I./include -Wall -Werror -pedantic -std=c11 -g -O3 -lc -lparmach
	ar rvs libirc.a src/*.o
clean:
	rm libirc.a src/*.o
install:
	cp include/*.h /usr/include
	cp libirc.a /usr/lib/

gcw0:
	mipsel-gcw0-linux-uclibc-cc src/irc.c -c -o src/irc.o -I./include -Wall -Werror -pedantic -std=c11 -g -O2 -lc -lparmach -I./include
	mipsel-gcw0-linux-uclibc-ar rvs libirc.a src/*.o
install_gcw0:
	cp include/*.h /opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/include
	cp libirc.a /opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/lib
