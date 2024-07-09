comp1: cg.c expr.c gen.c interp.c main.c scan.c tree.c
	cc -o comp1 -g cg.c expr.c gen.c interp.c main.c scan.c tree.c

clean:
	rm -f comp1 compn *.o *.s out

test: comp1
	./comp1 test/input01
	cc -o out out.s
	./out
	./comp1 test/input02
	cc -o out out.s
	./out