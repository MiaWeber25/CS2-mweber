#My name of my exe
EXEC=integrate
#My source file
SRC=
INCLUDES=

${EXEC}:${INCLUDES} ${SRC} ${EXEC}.cpp Makefile
	g++ -g -Wall ${EXEC}.cpp ${SRC} -o $@
	
run: ${EXEC}
	./${EXEC}
	
debug: ${EXEC}
	gdb ${EXEC}
	
clean: 
	rm ${EXEC}
