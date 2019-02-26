PSH := python3

CC := g++
CFLAGS := -ggdb -Wall

LFLAGS :=

SNAME1 := ftablegen.py
SNAME2 := fprocess.py

PNAME := fnabiev_lab01
OBJS.$(PNAME) := main.o myio.o ninterp.o

function := cos(pi/2 * x)
xarg := 0.6
xstart := -2
xfinish := 2.75 
pquantity := 20
polexp := 4
soutput := ftable.out
pinput := ftable.out

buld: $(PNAME)

run:
	@$(PSH) $(SNAME1) '--fstring=$(function)' '--xarg=$(xarg)' '--xstart=$(xstart)' '--xfinish=$(xfinish)' '--pquentity=$(pquantity)' '--output=$(soutput)'
	@echo 'Интерполяция:'
	@echo 'Степень полинома = $(polexp)'
	@echo '$(xarg) $(polexp)' | ./$(PNAME) $(pinput) 2>/dev/null

$(PNAME): $(OBJS.$(PNAME))
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.cpp *.hpp
	$(CC) $< $(CFLAGS) -c

clean:
	rm $(PNAME) -f
	rm $(OBJS.$(PNAME)) -f

