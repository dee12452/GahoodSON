build:
	echo "Building..."
	g++ test.c ../src/parse.c -I../include -o test.out

test: build
	./test.out

test1: build
	./test.out test_json/test1.json

test2: build
	./test.out test_json/test2.json

test3: build
	./test.out test_json/test3.json

test4: build
	./test.out test_json/test4.json

test5: build
	./test.out test_json/test5.json

test6: build
	./test.out test_json/test6.json