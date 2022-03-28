EXEC=StacksDemo
SRC=Stack.cpp

${EXEC}:Stack.h ${SRC} ${EXEC}.cpp
	g++ -g ${EXEC}.cpp ${SRC} -o $@

run: ${EXEC}
	./${EXEC}

debug: ${EXEC}
	gdb ${EXEC} #lldb

clean: 
	rm ${EXEC}
