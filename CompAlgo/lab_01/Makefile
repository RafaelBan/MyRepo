PSH := python3

CC := g++
CFLAGS := -ggdb -Wall

LFLAGS :=

SNAME1 := ftablegen.py
SNAME2 := fprocess.py
SNAME3 := sumup.py

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
save := save

build: $(PNAME)

run:
	@$(PSH) $(SNAME1) '--fstring=$(function)' '--xarg=$(xarg)' '--xstart=$(xstart)' '--xfinish=$(xfinish)' '--pquantity=$(pquantity)' '--output=$(soutput)'
	@echo 'Интерполяция:'
	@echo 'Степень полинома = $(polexp)'
	@echo '$(xarg) $(polexp)' | ./$(PNAME) $(pinput) $(save) 2>/dev/null
	@$(PSH) $(SNAME3) $(save)

manual_run:
	@$(PSH) $(SNAME1) '--fstring=$(function)' '--xarg=$(xarg)' '--xstart=$(xstart)' '--xfinish=$(xfinish)' '--pquantity=$(pquantity)' '--output=$(soutput)'
	@echo 'Интерполяция:'
	@echo 'Степень полинома = $(polexp)'
	@./$(PNAME) $(pinput) $(save)
	@$(PSH) $(SNAME3) $(save)


$(PNAME): $(OBJS.$(PNAME))
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.cpp *.hpp
	$(CC) $< $(CFLAGS) -c

clean:
	rm $(PNAME) -f
	rm $(OBJS.$(PNAME)) -f

