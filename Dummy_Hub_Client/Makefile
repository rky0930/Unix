CXX = g++
CXXFLAGS = -g $(INC)
LINK = g++
LIBS = -lcomm_log
LIBS_PATH = -L../Common/

# FILE
OBJS = Hub_Client.o \
	Hub_Connecter.o \

SRCS = $(OBJS:.o=.cpp)

TARGET = HubClient

# build rule
all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS_PATH) $(LIBS) 

clean :
	rm -rf $(OBJS) $(TARGET) core

new : 
	$(MAKE) clean 
	$(MAKE) 