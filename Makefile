THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include
INCLUDE := ../include
TRIBBLER_SRC := Tribbler.cpp Tribbler_constants.cpp Tribbler_types.cpp
TRIBBLER_OBJ := $(patsubst %.cpp,%.o, $(TRIBBLER_SRC))
KV_SRC := KeyValueStore.cpp KeyValueStore_types.cpp KeyValueStore_constants.cpp
KV_OBJ := $(patsubst %.cpp,%.o, $(KV_SRC))

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR) -I$(INCLUDE)

.PHONY: all clean

all: tribbler_server tribbler_client

%.o: ../include/%.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

storage_server: KeyValueStore_server.o $(KV_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift

tribbler_server: Tribbler_server.o $(TRIBBLER_OBJ) $(KV_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift

tribbler_client: Tribbler_client.o $(TRIBBLER_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift

clean:
	$(RM) *.o tribbler_server tribbler_client storage_server

turnin:
	make clean; tar cvfz `whoami`-turnin.tgz *
	chmod 600 `whoami`-turnin.tgz
	cp `whoami`-turnin.tgz /classes/cse223b/sp13/turnin/lab2/

