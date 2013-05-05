
README for Lab 3 Dribbler

Hao Zhuang
email: hazhuang@ucsd.edu
ID account(sysnet): hazhuang
Ph.D. Student, Computer Science Department, UC San Diego




Dribbler System Design Approaches:
*   Using vector timestamp to maintain the partial order. By propogate the logical time step, 
    each 'put' operation will increase KV server's local logical time stamp. 
    --	I choose [1] as the timestamp algorithm in lab3.
    --	When a tribbler is posted in a tribbler server, the tribbler_server talks to KV Server #s_id.
	Then, KV server #s_id will broadcast this tribbler to every server alive, the dead or the server
	has not join yet will be ruled out by try-catch module in c++. 
    --  The hit makes their local logical time stamp increasing according to [1].  
    --  Algorithm: (n is the server number)
         ==========================================================================
	    local_timestamp[s_id] = 1 + other_timestamp[s_id] 
	    for i = 1 : n
		local_timestamp[i] = max(other_timestamp[i], local_timestamp[i])
         ==========================================================================

*   When a server join the network, I choose not to display previous tribblers before a server joining the network. 

*   I constraint that "id" in the "./kv_server id " should be consecutive.
    -- "id" starting from 1, not bigger than the server's number n;
    -- The order joining network is not constrain.  

*   For the tribbler server side, I borrow from my lab2's code (plus, this time new data 
    structure in class Tribble 'posted').

(Please, uses the head files contain "oneway" RPC. So I tar the whole code into the package, like lab2.)

References:
[1] Fidge, Colin J. "Timestamps in message-passing systems that preserve the partial ordering." 
Proceedings of the 11th Australian Computer Science Conference. Vol. 10. No. 1. 1988.


May 4th, 2013



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

