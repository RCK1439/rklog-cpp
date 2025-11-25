CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++23 -O3

TARGET = rklog_test.exe

$(TARGET): test.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -f $(TARGET) *.o logs.txt