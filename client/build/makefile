src=$(wildcard ../src/*.cpp)
obj=$(patsubst ../src/%.cpp,%.o,$(src))
target=main
CXX=g++
CPPFLAGS=-I../include
CXXFLAGS=-g

all:$(target)

$(target):$(obj)
	$(CXX) -o $@ $^

%.o:../src/%.cpp
	$(CXX) -o $@ -c $< $(CPPFLAGS) $(CXXFLAGS)

.PHONY:clean
clean:
	-rm -rf $(target) $(obj)
