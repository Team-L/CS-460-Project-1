P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch

run_test_file:
	./P1.out test_file.txt

run_L_ss:
	./P1.out TeamL.ss
	cat TeamL.p1

run_test_individuals:
	./P1.out test_individuals.txt
run_all_tests:
	./P1.out L.ss
	cat L.dbg
	./P1.out test1.ss
	cat test.dbg
	./P1.out test2.ss
	cat test.dbg
	./P1.out test3.ss
	cat test.dbg
	./P1.out test4.ss
	cat test.dbg
	./P1.out test5.ss
	cat test.dbg
	./P1.out test6.ss
	cat test.dbg
	./P1.out test7.ss
	cat test.dbg
	./P1.out test8.ss
	cat test.dbg
run_test_9:
	./P1.out test9.ss
	#cat test9.p1
	cat test9.dbg
	cat test9.lst
	#diff test9.p1 ../P1Tests/test9.p1
	#diff test9.dbg ../P1Tests/test9.dbg
	diff test9.lst ../P1Tests/test9.lst
run_test_8:
	./P1.out test8.ss
	cat test8.p1
	cat test8.dbg
	cat test8.lst
	#diff test8.p1 ../P1Tests/test8.p1
	diff test8.dbg ../P1Tests/test8.dbg
	diff test8.lst ../P1Tests/test8.lst
submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamLP1
	mkdir TeamLP1
	cp Project1.cpp TeamLP1
	cp LexicalAnalyzer.h TeamLP1
	cp LexicalAnalyzer.cpp TeamLP1
	cp SyntacticalAnalyzer.h TeamLP1
	cp SyntacticalAnalyzer.cpp TeamLP1
	cp makefile TeamLP1
	cp README.txt TeamLP1
	tar cfvz TeamLP1.tgz TeamLP1
	cp TeamLP1.tgz ~tiawatts/cs460drop
