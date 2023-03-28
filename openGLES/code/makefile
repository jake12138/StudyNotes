TARGET := openGLTest

SRC := \
	main.cpp \
	WindowSurface.cpp

OBJ := $(subst .cpp,.o,$(SRC) )

LIB := \
	-lwayland-server \
	-lwayland-client \
	-lwayland-cursor \
	-lEGL \
	-lGLESv2 \
	-ltinyxml2

$(TARGET):$(OBJ)
	g++ $^ $(LIB) -o $(TARGET)

main.o : main.cpp
	g++ -c main.cpp -o main.o

WindowSurface.o : WindowSurface.cpp
	g++ -c WindowSurface.cpp -o WindowSurface.o

clean:
	-rm main.o WindowSurface.o openGLTest

