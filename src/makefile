BINDIR=../bin
OBJ1= main.o CEventObserver.o COutDataWkThreadPool.o CThreadPool.o CThread.o COutDataWkThread.o CMutex.o CException.o CAnonymSem.o CReator.o CLocalThreadLog.o CLocalLog.o CLog.o CSimpleConfig.o CConfig.o CMsgQueue.o
INCDIR=.
CFLAG=-g -c
BFLAG=-g
MYDYNLIBNAME=-lpthread

main:$(OBJ1)
	@echo "linking $@ begin .."
	g++ $(BFLAG) -o $@ $(OBJ1) $(MYDYNLIBNAME)
	mv $@ $(BINDIR)
	@echo "linking $@ end .."

# COutDataWkThreadPool.o: COutDataWkThreadPool.cpp COutDataWkThreadPool.h CThreadPool.h CThread.h COutDataWkThread.h CMutex.h CException.h CAnonymSem.h Message.h CReator.h CEventObserver.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# COutDataWkThread.o: COutDataWkThread.cpp COutDataWkThread.h CMutex.h CException.h CAnonymSem.h Message.h CThread.h CReator.h CEventObserver.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CEventObserver.o: CEventObserver.cpp CEventObserver.h Message.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CThreadPool.o: CThreadPool.cpp CThreadPool.h CThread.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CThread.o: CThread.cpp CThread.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CMutex.o: CMutex.cpp CMutex.h CException.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CException.o: CException.cpp CException.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CAnonymSem.o: CAnonymSem.cpp CAnonymSem.h CException.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CReator.o: CReator.cpp CReator.h CEventObserver.h Message.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."
#
# CEventObserver.o: CEventObserver.cpp CEventObserver.h Message.h
# 	@echo "compiling "$<" begin .."
# 	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
# 	@echo "compiling "$<" end .."


.cpp.o: $<
	@echo "compiling "$<" begin .."
	g++ -o $@ $(CFLAG) -I$(INCDIR)  $<
	@echo "compiling "$<" end .."

clean:
	-rm -f *.o
	-rm -f *.gch
