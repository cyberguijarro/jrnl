SOURCES=jrnl.cpp entry.cpp utility.cpp traverser.cpp

jrnl: $(SOURCES)
	$(CXX) -O3 -Wall -std=c++0x $^ -o $@

clean:
	rm -rf *.o jrnl
