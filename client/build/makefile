sh_path=../../shared_code
src=$(wildcard ../src/*.cpp)
sh_src=$(wildcard $(sh_path)/src/*.cpp)
obj=$(patsubst ../src/%.cpp,%.o,$(src))
sh_obj=$(patsubst $(sh_path)/src/%.cpp,sh_%.o,$(sh_src))
target=main
CXX=g++
CPPFLAGS=-I../include -I$(sh_path)/include
CXXFLAGS=-g

all:$(target)

$(target):$(obj) $(sh_obj)
	$(CXX) -o $@ $^

%.o:../src/%.cpp
	$(CXX) -o $@ -c $< $(CPPFLAGS) $(CXXFLAGS)

sh_%.o:$(sh_path)/src/%.cpp
	$(CXX) -o $@ -c $< $(CPPFLAGS) $(CXXFLAGS)

.PHONY:clean
clean:
	-rm -rf $(target) $(obj)
