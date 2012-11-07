.PHONY: clean
TARGET = gol

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET) $(TARGET).o