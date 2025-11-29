CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++23 -O0

TARGET = rklog_test

$(TARGET): test.o gwat.o rklog.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

rklog.o: rklog/rklog.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -f $(TARGET) *.o logs.txt