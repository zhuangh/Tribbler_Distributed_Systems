
README for Lab 3

Hao Zhuang
email: hazhuang@ucsd.edu
ID account(sysnet): hazhuang
Ph.D. Student, Computer Science Department, UC San Diego


Use vector timestamp to maintain the partial order. 
By propogate the logical time step, each put will increase logical time stamp.

I choose [1] as the timestamp algorithm.

When a tribbler is posted from a tribbler server, who talks to KV Server #s_id, it will hit every server alive, so that make their local logical time stamp increasing.  

I choose not to display previous tribblers before a server joining the network. 

I constrain the ./kv_server id is consecutive, and increase 1 by 1, but the order joining network is not constrain.  




References:
[1] Fidge, Colin J. "Timestamps in message-passing systems that preserve the partial ordering." 
Proceedings of the 11th Australian Computer Science Conference. Vol. 10. No. 1. 1988.



----------------------------------------------------------------------
These files serve as the official distribution of source code,
documentation, executables, and compiled libraries for Lab 3.

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
    KeyValue_server.cpp      Skeleton code with empty functions that drive the Key Value storage server.
    Makefile

Running the Key Value server:
     cd src/
     make clean
     make
     ./kv_server <id> <port> <peer1> <peerport1> ....

Running the Tribble server:
     ./tribble_server  <kvServerIP> <kvServerPort> <tribblerServerPort>

Running the Tribble client (c++):
    ./tribble_client <tribbleServerIP> <tribbleServerPort>

