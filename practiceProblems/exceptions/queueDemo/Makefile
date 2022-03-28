EXEC=queueDemo
SRC=queue.cpp Stack.cpp
INCLUDES = queue.h Stack.h

${EXEC}:${INCLUDES} ${SRC} ${EXEC}.cpp Makefile
	g++ -g ${EXEC}.cpp ${SRC} -o $@

run: ${EXEC}
	./${EXEC}

debug: ${EXEC}
	gdb ${EXEC} #lldb

clean:
	rm ${EXEC}
