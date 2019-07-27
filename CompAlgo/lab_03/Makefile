CC := g++
CFLAGS := -Wall -ggdb

PNAME := fnabiev_lab03
OBJS.$(PNAME) := main.o ninterp.o

build: $(PNAME)

$(PNAME): $(OBJS.$(PNAME))
	$(CC) $^ -o $@

%.o: %.cpp *.hpp
	$(CC) $< $(CFLAGS) -c

clean:
	rm $(PNAME) -f
	rm $(OBJS.$(PNAME)) -f

