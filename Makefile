FLAGS=-s -O2 -Wall -Wno-format
all:myjq

myjq:main.c cJSON.o
	cc $(FLAGS) -o $@ $^

%.o:%.c
	cc $(FLAGS) -c $^

clean:
	rm -f myjq
	rm -f *.o
