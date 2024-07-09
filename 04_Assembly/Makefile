scanner: expr.c interp.c main.c scan.c
	cc -o parser -g expr.c interp.c main.c scan.c tree.c
clean:
	rm -f parser *.o

test: parser
	-(./parser test/input01; \
	  ./parser test/input02; \
	  ./parser test/input03; \
	  ./parser test/input04; \
	  ./parser test/input05)