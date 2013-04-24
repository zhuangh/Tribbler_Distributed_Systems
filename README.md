Tribbler
========

Hao Zhuang, 
Ph.D Student, Computer Science Department, University of California, San Diego
A53029734
hazhuang@ucsd.edu

Lab2
For CSE223B Winter 2013, Distributed Computing and Systems
--------------------------------------------------
--------------------------------------------------

The basic idea is the distributed the tweet via pages via index which uses SHA1 
(not to store all the tweets in one giant list). 

I design pages for each user, each time the latest page will be loaded and feedback to the user. Or gather a group of pages from all user's friends and compare the timestamp, then return to the client. 

( Attention: Key Value does not enforce the order, so we should sort the tweets from current page 
after downloading. )

My strategy
-- Every tweets has its own hash key (by SHA1 method).

-- Use A = (userid, its current message number)  

-- Each user has several index table (pages) with a fixed size (e.g. 50), when post a tweets, 
then increase A's the "current message number". It also put to a List with current index page number
and hash key by manipulating the contents, which will help to GET the tweets from server quickly.

-- GetTribbles will download user's most recently page and so the page according to the timestamp. 
If it does not satisfy the user number requirement (e.g. 100), it will download another page of most
recent;
-- GetTribblesBySubscriptions method will download the latest pages from all friends of the user's. 
Then it will sort the page according to their timestamp respectively. Then the method compared the 
most latest one at each friends' page, and pop out the latest one. Then continue, till the number 
requirement is met, or one of page is empty (then refill the page by downloading from corresponding 
friend's), or the pages are eaten up.

by Hao Zhuang

--------------------------------------------------
--------------------------------------------------


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



