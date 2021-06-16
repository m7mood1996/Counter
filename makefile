TARGET=counter
SOURCES=$(wildcard *.cpp)
OBJS=$(SOURCES:.cpp=.o)

CC=g++
CFLAGS= -c -pedantic -Wall -Wconversion  -g
CXXFLAGS=$(CFLAGS)
LDFLAGS= -g -lgtest -lgtest_main -lpthread

.PHONY: clean run gdb
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)


clean:
	rm -f $(OBJS) $(TARGET) .depends
run:$(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb -q ./$(TARGET)
