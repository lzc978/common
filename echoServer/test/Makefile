############################################################# 
# Makefile for shared library.
# 编译动态链接库
#############################################################
#set your own environment option
CC = g++
CC_FLAG = -D_NOMNG -D_FILELINE

#set your inc and lib
INC = 
LIB = -lpthread -L./ -lsvrtool

#make target lib and relevant obj 
PRG = libsvrtool.so
OBJ = Log.o

#all target
all:$(PRG)

$(PRG):$(OBJ)
    $(CC) -shared -o $@ $(OBJ) $(LIB)

.SUFFIXES: .c .o .cpp
.cpp.o:
    $(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o

.PRONY:clean
clean:
    @echo "Removing linked and compiled files......;
    rm -f $(OBJ) $(PRG)
	
#############################################################
# Makefile for static library.
# 编译静态链接库
#############################################################
#set your own environment option
CC = g++
CC_FLAG = -D_NOMNG -D_FILELINE

#static library use 'ar' command 
AR = ar

#set your inc and lib
INC = 
LIB = -lpthread -L./ -lsvrtool

#make target lib and relevant obj 
PRG = libsvrtool.a
OBJ = Log.o

#all target
all:$(PRG)
$(PRG):$(OBJ)
    ${AR} rv ${PRG} $?

.SUFFIXES: .c .o .cpp
.cpp.o:
    $(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o

.PRONY:clean
clean:
    @echo "Removing linked and compiled files......"
    rm -f $(OBJ) $(PRG)
	
###########################################
#Makefile for simple programs
###########################################
INC=
LIB= -lpthread

CC=CC
CC_FLAG=-Wall

PRG=threadpooltest
OBJ=CThreadManage.o CThreadPool.o CThread.o CWorkerThread.o threadpooltest.o

$(PRG):$(OBJ)
    $(CC) $(INC) $(LIB) -o $@ $(OBJ)
    
.SUFFIXES: .c .o .cpp
.cpp.o:
    $(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o

.PRONY:clean
clean:
    @echo "Removing linked and compiled files......"
    rm -f $(OBJ) $(PRG)