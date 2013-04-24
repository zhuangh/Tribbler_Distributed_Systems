These files serve as the official distribution of source code,
documentation, executables, and compiled libraries for Lab 2.

The following files are included in the distribution

  Tribble.thrift               RPC service interface between your Tribble server and the Tribble client.
  KeyValueStore.thrift         RPC service interface between the Key Value Store and your TribbleServer.

  include:                     RPC code for message passing (Do not modify)
    KeyValueStore.*
    KeyValueStore_constants.*
    KeyValueStore_types.*
    Tribbler.*
    Tribbler_constants.*
    Tribbler_types.*

  src:
    Tribble_server.cpp       Skeleton code with empty functions that drive your Tribbler server.
    Tribble_client.cpp       Sample client program to post/view/ tribbles, add/remove subsribers.
                             This is for your testing purposes only. You can modify this file to add
                             more tests.
    Makefile

Running the Tribble server:
     cd src/
     make clean
     make
     ./tribble_server  <storageServerIP> <StorageServerPort> <tribblerServerPort>

Running the Tribble client (c++):
    ./tribble_client <tribbleServerIP> <tribbleServerPort>
