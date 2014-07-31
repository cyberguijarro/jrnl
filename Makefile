OBJECTS = $(subst .cpp,.o,$(wildcard *.cpp))
CXXFLAGS = -c -O3 -Wall -std=c++0x 
LIBS =
TARGET = jrnl

ifeq ($(USE_BOOST_REGEX),y)
	CXXFLAGS += -DUSE_BOOST_REGEX
	LIBS += -lboost_regex
endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
