TARGET := openGLTest


SRCS :=
SRCS += main.cpp
SRCS += WaylandWindow.cpp


OBJ := $(subst .cpp,.o,$(SRCS) )

LIB :=
LIB += -lwayland-server
LIB += -lwayland-client
LIB += -lwayland-cursor
LIB += -lwayland-egl
LIB += -lEGL
LIB += -lGLESv2
LIB += -ltinyxml2


$(TARGET):$(OBJ)
	g++ $^ $(LIB) -o $@

%.o:%.cpp
	g++ -c $^ -o $@


clean:
	-rm $(OBJ)

