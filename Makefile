PROGRAM = imascii
OBJS = main.o
CXXFLAGS = -g -std=c++2a

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $(OBJS) -lmain -lssp -limagedecoderclient -Wl,-lgcc_s,-lcore

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm $(OBJS) $(PROGRAM)

run:
	./$(PROGRAM)
