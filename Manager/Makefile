CXX = g++
CXXFLAGS = -g $(INC)
LINK = g++
LIBS = -lcomm_log
LIBS_PATH = -L../Common/

# FILE
OBJS = Manager.o \

SRCS = $(OBJS:.o=.cpp)

TARGET = Manager

# build rule
all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS_PATH) $(LIBS) 

clean :
	rm -rf $(OBJS) $(TARGET) core

new : 
	$(MAKE) clean 
	$(MAKE) 