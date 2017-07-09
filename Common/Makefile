CXX = g++
CXXFLAGS = -g $(INC)
AR = ar
RANLIB = ranlib
ARFLAGS = -rv


# FILE
OBJS = comm_log.o \

SRCS = $(OBJS:.o=.cpp)

LIB_FULL_NAME = lib$(OBJS:.o=.a)
 
# build rule
all : $(LIB_FULL_NAME)

$(LIB_FULL_NAME) : $(OBJS)
	$(AR) rcv $@ $(OBJS)
	$(RANLIB) $@

clean :
	rm -rf $(OBJS) $(TARGET) core

new : 
	$(MAKE) clean 
	$(MAKE) 