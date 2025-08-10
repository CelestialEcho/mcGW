OBJDIR = objs

SRCS = $(wildcard ../src/*.c)
OBJS = $(patsubst ../include/%.c, $(OBJDIR)/%.o, $(SRCS))

all: mcgw

$(OBJDIR)/%.o: ../src/%.c ../include/%.c | $(OBJDIR)
	gcc -I../include -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

mcgw: $(OBJS)
	g++ -g -std=c++20 -I../include -L../lib ../src/*.cpp $(OBJS) -o mcgw -lws2_32
