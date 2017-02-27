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
	./P1.out TeamL.ss
	cat test.dbg
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
	cat test.dbg

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
