CFLAGS =  -Werror -Wall  
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(CFLAGS) # $(COVFLAGS) $(PROFFLAG)
clean:
	/bin/rm -f *.o
	/bin/rm -f pa15
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
test: all
	echo "test1"
	time ./shortestpath usa.txt usa1.txt
	# time ./shortestpath1 usa.txt usa1.txt

diff: all
	diff gophers_header expected/gophers_header
	diff basic_header expected/basic_header
	diff para_header expected/para_header
	diff prideandprejudice_header expected/prideandprejudice_header
	diff woods_header expected/woods_header

all: comp adjacent.o 
	$(GCC) adjacent.o -o shortestpath
	# $(GCC) shortestpath1.o -o shortestpath1
comp: adjacent.c 
	#gcc -Werror -Wall file1.c file2.c ... -o shortestpath
	$(GCC) adjacent.c -o adjacent -lm
memory: 
	# valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./pa15 inputs/gophers gophers_sorted gophers_huffman gophers_header
	# valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./pa15 inputs/basic basic_sorted basic_huffman basic_header
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./pa15 inputs/para para_sorted para_huffman para_header
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./pa15 inputs/prideandprejudice prideandprejudice_sorted prideandprejudice_huffman prideandprejudice_header
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./pa15 inputs/woods woods_sorted woods_huffman woods_header
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./pa15 inputs/test test_sorted test_huffman test_header