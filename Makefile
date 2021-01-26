CXX=g++
CCLINK=$(CXX) 
CXXFLAGS=-g -Wall 
OBJS=string.o field.o ip.o port.o main.o 
EXEC=firewall.exe
RM=rm -rf *.o *.exe libfirewall.so

firewall.exe: $(OBJS) libfirewall.so
	$(CCLINK) $(OBJS) -o $(EXEC) -L. -lfirewall -L. -linput

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp 

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp 

ip.o: ip.cpp ip.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp 

main.o:	main.cpp string.h field.h ip.h port.h input.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp 

libfirewall.so: field.o port.o ip.o string.o
	$(CCLINK) -shared field.o ip.o port.o string.o -o libfirewall.so	


#clean
clean:
	$(RM)