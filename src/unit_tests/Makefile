CC          := g++
CSTANDARTS  := -std=c++17 -lstdc++
CWARNS      := -Wall -Werror -Wextra
CFLAGS      := $(CSTANDARTS) $(CWARNS) -I.
LIBS		:=-lgtest

TARGET		:= run_tests.exe

all: $(TARGET)

$(TARGET): 
	$(CC) run_all_tests.cpp count_letter_frq_test.cpp ../server/count_letter_frq.cpp -o $(TARGET) $(LIBS)

./build/run_all_tests.o: ./run_all_tests.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

./build/count_letter_frq.o: ../server/count_letter_frq.cpp
	$(CC) $(CFLAGS) -c $< -o $@	

./build/count_letter_frq_test.o: ./count_letter_frq_test.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	cd ./build && rm -rf *.o *.a *.exe *.so 
	rm -rf *.o *.a *.exe *.so 

