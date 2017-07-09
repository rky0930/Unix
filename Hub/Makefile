CXX = g++
CXXFLAGS = -g $(INC)
LINK = g++
LIBS = -lcomm_log
LIBS_PATH = -L../Common/

# FILE
OBJS = Controller.o \
	Distributer.o \
	HubMain.o \
	MQueue.o \
	MThread.o \
	pClient.o \
 

SRCS = $(OBJS:.o=.cpp)

TARGET = Hub

# build rule
all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS_PATH) $(LIBS) 

clean :
	rm -rf $(OBJS) $(TARGET) core

new : 
	$(MAKE) clean 
	$(MAKE) 