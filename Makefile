CC          := g++
CFLAGS      := -O -Iinclude
CLIBS_TEST  := -lboost_system -lboost_thread -lboost_unit_test_framework

prefix	    := /usr/local

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

all: bin/libsimple_tokenizer.a

bin/libsimple_tokenizer.a: src/simple_tokenizer.o
	ar rcs $@ $^
	make clean_obj

test: bin/testcase

bin/testcase: src/simple_tokenizer.o test/test_case.o
	$(CC) $(CLIBS_TEST) -o $@ $^ $(CLIBS)
	make clean_obj

.PHONY: clean install

clean:
	rm -f test/*.o src/*.o bin/*

clean_obj:
	rm -f test/*.o src/*.o
	
install: all bin/libsimple_tokenizer.a include/simple_tokenizer.h
	test -d $(prefix) || mkdir $(prefix)
	test -d $(prefix)/lib || mkdir $(prefix)/lib
	test -d $(prefix)/include || mkdir $(prefix)/include
	test -d $(prefix)/include/simple_tokenizer || mkdir $(prefix)/include/simple_tokenizer
	install -m 0755 bin/libsimple_tokenizer.a $(prefix)/lib
	install -m 0755 include/simple_tokenizer.h $(prefix)/include/simple_tokenizer/
