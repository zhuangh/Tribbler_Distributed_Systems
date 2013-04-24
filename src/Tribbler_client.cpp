// Sample client

#include "Tribbler.h"
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <iostream>

#include <boost/lexical_cast.hpp>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Tribbler;
using namespace std;


using boost::lexical_cast;

void printSubscriptions(SubscriptionResponse& sr, string user) {
    unsigned int size = sr.subscriptions.size();
    if (sr.status != TribbleStatus::OK) {
       cout << "GetSubscriptions for user: "<< user << " failed. "
            << "Error code: " << sr.status << endl;
        return;
    }
    cout << user << ": has " << size << " subscribers " << endl;
    for (unsigned int i=0; i < size; i++) {
        cout << user << " is subscribed to " << sr.subscriptions[i] << endl;
    }
}


int main(int argc, char **argv) {
  if (argc != 3) {
      cerr << "Usage: " << argv[0] << " <tribblerServerIP> <tribblerServerPort>" << endl;
      exit(0);
  }
  string tribblerServer = string(argv[1]);
  int port = atoi(argv[2]);
  boost::shared_ptr<TSocket> socket(new TSocket(tribblerServer, port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  TribblerClient client(protocol);
  try {
    transport->open();
    TribbleStatus::type ts_create;
    string tmp = boost::lexical_cast<string>(time(NULL));
    string at = "alice"+tmp;
    ts_create = client.CreateUser(at);
    if (ts_create != TribbleStatus::OK) {
        cout << "Failed to create user: alice. Error code: " << ts_create << endl;
    }
    string bt = "bob"+tmp;
    ts_create = client.CreateUser(bt);
    if (ts_create != TribbleStatus::OK) {
        cout << "Failed to create user: bob. Error code: " << ts_create << endl;
    }
    string ct = "cindy"+tmp;
    ts_create = client.CreateUser(ct);
    if (ts_create != TribbleStatus::OK) {
        cout << "Failed to create user: cindy. Error code: " << ts_create << endl;
    }

    string dt = "dogg"+tmp;
    ts_create = client.CreateUser(dt);
    if (ts_create != TribbleStatus::OK) {
        cout << "Failed to create user: dogg. Error code: " << ts_create << endl;
    }


    TribbleStatus::type ts_add;
    ts_create = client.CreateUser(dt);
    if (ts_create != TribbleStatus::OK) {
        cout << "Failed to create user: cindy. Error code: " << ts_create << endl;
    }
    ts_add = client.AddSubscription(ct, bt);
    if (ts_add != TribbleStatus::OK) {
        cout << "alice failed to subscribe to bob. "
             << "Error code: " << ts_add << endl;
    }
    ts_add = client.AddSubscription(at , ct);
    if (ts_add != TribbleStatus::OK) {
        cout << "alice failed to subscribe to cindy. "
             << "Error code: " << ts_add << endl;
    }
    ts_add = client.AddSubscription(bt , at);
    if (ts_add != TribbleStatus::OK) {
        cout << "bob failed to subscribe to alice. "
             << "Error code: " << ts_add << endl;
    }


    ts_add = client.AddSubscription(ct , at );
    if (ts_add != TribbleStatus::OK) {
        cout << "cindy failed to subscribe to alice. "
             << "Error code: " << ts_add << endl;
    }

    SubscriptionResponse sr_alice;
    SubscriptionResponse sr_bob;
    SubscriptionResponse sr_cindy;

    client.GetSubscriptions(sr_alice, at );
    client.GetSubscriptions(sr_bob, bt );
    client.GetSubscriptions(sr_cindy, ct);

    printSubscriptions(sr_cindy, string(ct));
    printSubscriptions(sr_alice, string(at));
    printSubscriptions(sr_bob, string(bt));

    TribbleStatus::type ts_remove;
    ts_remove = client.RemoveSubscription(at, ct);
    if (ts_remove != TribbleStatus::OK) {
        cout << "alice failed to remove subscription to cindy. Error code: "
            << ts_add << endl;
    }

    client.GetSubscriptions(sr_alice, at );
    printSubscriptions(sr_bob, string(bt));

    TribbleResponse tr_alice;
    TribbleResponse tr_bob;
    TribbleResponse tr_dogg;
    TribbleStatus::type ts_post1;
    TribbleStatus::type ts_post2;
    TribbleStatus::type ts_post3;
    TribbleStatus::type ts_post4;
   for(int i = 0; i < 500 ; i++ )
    {
	timespec ts;
	// clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
	clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
	string  tweet = ( boost::lexical_cast<string> )(i/8.0);
			  //(ts.tv_sec * 1000000000 + ts.tv_nsec) );
	tweet  = "What a beautiful day! "+ tweet ;// boost::lexical_cast<string>(time(NULL));
	ts_post1 = client.PostTribble(at , tweet);

	clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
	string  tweet2 = ( boost::lexical_cast<string>) (i/4.0);//(ts.tv_sec * 1000000000 + ts.tv_nsec) );

	tweet2  = "Bad day! "+ tweet2 ;// boost::lexical_cast<string>(time(NULL));
	ts_post2 = client.PostTribble(bt , tweet2);

	clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
	string  tweet3 = ( boost::lexical_cast<string>) (i/2.0);//(ts.tv_sec * 1000000000 + ts.tv_nsec) );

	tweet3  = "Good day! "+ tweet3 ;// boost::lexical_cast<string>(time(NULL));
	ts_post3 = client.PostTribble(ct , tweet3);

	clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
	string  tweet4 = ( boost::lexical_cast<string>) (i/1.0);//(ts.tv_sec * 1000000000 + ts.tv_nsec) );

	tweet4  = "Good day! "+ tweet4 ;// boost::lexical_cast<string>(time(NULL));
	ts_post4 = client.PostTribble(dt , tweet4);
    
    }
    ts_post1 = client.PostTribble(at, "What a beautiful day!");
    ts_post2 = client.PostTribble(bt, "Bad day!");
    ts_post3 = client.PostTribble(ct, "Bad day!");
    ts_post4 = client.PostTribble(dt, "Bad day!");
 
    if (ts_post1 != TribbleStatus::OK) {
        cout << "Alice could not post "
             << "Error code: " << ts_post1 << endl;
    }
    else{
	cout<< "Alice Post PASS!"<<endl;
    }

    if (ts_post2 != TribbleStatus::OK) {
        cout << "Bob could not post "
             << "Error code: " << ts_post2 << endl;
    }
    else{
	cout<< "Bob Post PASS!"<<endl;
    }


    client.GetTribbles(tr_alice, at );
    if (tr_alice.status != TribbleStatus::OK) {
        cout << "Alice failed to get tribbles "
             << "Error code: " << tr_alice.status << endl;
    }
    else {
        cout << "Alice  to get tribbles PASS!!! "<<endl;
    }
    client.GetTribbles(tr_bob, bt );
    if (tr_bob.status != TribbleStatus::OK) {
        cout << "Bob failed to get tribbles "
             << "Error code: " << tr_bob.status << endl;
    }
    else {
        cout << "Bob  to get tribbles PASS!!! "<<endl;
    }



//     TribbleResponse tr_bob;
    client.GetTribblesBySubscription(tr_bob, bt );
    if (tr_bob.status != TribbleStatus::OK) {
        cout << "Bob failed to get tribbles by subscription. "
             << "Error code: " << tr_bob.status << endl;
    }
    else{
	cout<< "Bob get Tribble by subscription PASS!!!"<<endl;
    }

    TribbleResponse tr_cindy;
    client.GetTribblesBySubscription(tr_cindy, ct );
    if (tr_cindy.status != TribbleStatus::OK) {
        cout << "Cindy failed to get tribbles by subscription. "
             << "Error code: " << tr_cindy.status << endl;
    }
    else{
	cout<< "Cindy get Tribble by subscription PASS!!!"<<endl;
    }


    transport->close();
  } catch (TException &tx) {
    cout << "ERROR: %s" <<  tx.what() << endl;
  }

  return 0;
}
