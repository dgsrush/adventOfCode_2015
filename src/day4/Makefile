OBJS=\
	main.o

CFLGS=-c -mconsole -O2

LIBS=libcryptopp.a

day4.exe : $(OBJS) $(INCS)
	g++ -o day4.exe -mconsole $(OBJS) $(LIBS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

clean :
	rm *.o
