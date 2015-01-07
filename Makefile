CXXFLAGS=-std=c++11 -pedantic -Wall -Wextra -O0 -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo -g

CPPFLAGS+=$(shell pkg-config --cflags gtkmm-3.0)
LDLIBS+=$(shell pkg-config --libs gtkmm-3.0)

all: missile_command

missile_command: main.o gamewindow.o testincoming.o incoming.o outgoing.o
	g++ $^ $(LDLIBS) -o $@

main.o: main.cc gamewindow.h

gamewindow.o: gamewindow.cc gamewindow.h testincoming.h
#menuwindow.o: menuwindow.cc menuwindow.h levelwindow.h
#levelwindow.o: levelwindow.cc levelwindow.h menuwindow.h
testincoming.o: testincoming.cc testincoming.h incoming.h outgoing.h
incoming.o: incoming.cc incoming.h testincoming.h

clean:
	rm -rf *.o *~ missile_command

zip:
	tar zcvf cs120-assignment-9-ngreenb6-gadoff1-aharve13.tar.gz Makefile README main.cc gamewindow.h gamewindow.cc menuwindow.h menuwindow.cc levelwindow.h levelwindow.cc  incoming.cc incoming.h outgoing.cc outgoing.h testincoming.cc testincoming.h
