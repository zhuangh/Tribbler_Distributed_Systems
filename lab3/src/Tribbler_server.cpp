// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.


#include <stdio.h>
#include <errno.h>
#include <iostream>
#include "Tribbler.h"
#include "KeyValueStore.h"
#include <transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace std;
using namespace  ::Tribbler;
using namespace  ::KeyValueStore;
#define DEBUG_TS

class TribblerHandler : virtual public TribblerIf {
 public:

  TribblerHandler(std::string kvServer, int kvServerPort) {
    // Your initialization goes here
    _kvServer = kvServer;
    _kvServerPort = kvServerPort;
  }

  TribbleStatus::type CreateUser(const std::string& userid) {
    // Your implementation goes here
    printf("CreateUser\n");
    KeyValueStore::GetResponse validate_id = Get(userid);
    if( validate_id.status != KVStoreStatus::EKEYNOTFOUND  )
	return TribbleStatus::EEXISTS ;

    string uID = userid;
    string tweets_num = "0";   
    Put(userid,tweets_num);
    return TribbleStatus::OK;
  }

  TribbleStatus::type AddSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("AddSubscription\n");
    return TribbleStatus::NOT_IMPLEMENTED;
  }

  TribbleStatus::type RemoveSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("RemoveSubscription\n");
    return TribbleStatus::NOT_IMPLEMENTED;
  }

  TribbleStatus::type PostTribble(const std::string& userid, const std::string& tribbleContents) {
    // Your implementation goes here
    printf("PostTribble\n");
    return TribbleStatus::NOT_IMPLEMENTED;
  }

  void GetTribbles(TribbleResponse& _return, const std::string& userid) {
    // Your implementation goes here
    _return.status = TribbleStatus::NOT_IMPLEMENTED;
    printf("GetTribbles\n");
  }

  void GetTribblesBySubscription(TribbleResponse& _return, const std::string& userid) {
    // Your implementation goes here
    _return.status = TribbleStatus::NOT_IMPLEMENTED;
    printf("GetTribblesBySubscription\n");
  }

  void GetSubscriptions(SubscriptionResponse& _return, const std::string& userid) {
    // Your implementation goes here
    _return.status = TribbleStatus::NOT_IMPLEMENTED;
    printf("GetSubscriptions\n");
  }

  // Functions from interacting with the kv RPC server
  KVStoreStatus::type AddToList(std::string key, std::string value) {
    boost::shared_ptr<TSocket> socket(new TSocket(_kvServer, _kvServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient kv_client(protocol);
    // Making the RPC Call
    KVStoreStatus::type st;
    transport->open();
    string clientid("tribbleserver");
    st = kv_client.AddToList(key, value, clientid);
    transport->close();
    return st;
  }

  KVStoreStatus::type RemoveFromList(std::string key, std::string value) {
    // Making the RPC Call to the kv server
    boost::shared_ptr<TSocket> socket(new TSocket(_kvServer, _kvServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    KVStoreStatus::type st;
    transport->open();
    string clientid("tribbleserver");
    st = client.RemoveFromList(key, value, clientid);
    transport->close();
    return st;
  }

  KVStoreStatus::type Put(std::string key, std::string value) {
    // Making the RPC Call to the kv server
    boost::shared_ptr<TSocket> socket(new TSocket(_kvServer, _kvServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    KVStoreStatus::type st;
    transport->open();
    string clientid("tribbleserver");
    st = client.Put(key, value, clientid);
    transport->close();
    return st;
  }

  KeyValueStore::GetResponse Get(std::string key) {
    KeyValueStore::GetResponse response;
    // Making the RPC Call to the kv server
    boost::shared_ptr<TSocket> socket(new TSocket(_kvServer, _kvServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    transport->open();
    client.Get(response, key);
    transport->close();
    return response;
  }

 private:
  std::string _kvServer;
  int _kvServerPort;
};

int main(int argc, char **argv) {
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <kvServerIP> <kvServerPort> <tribbleServerPort>" << endl;
    exit(0);
  }
  std::string kvServer = std::string(argv[1]);
  int kvServerPort = atoi(argv[2]);
  int tribblerPort = atoi(argv[3]);

  shared_ptr<TribblerHandler> handler(new TribblerHandler(kvServer, kvServerPort));
  shared_ptr<TProcessor> processor(new TribblerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(tribblerPort));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  cout << "Starting Tribbler Server" << endl;
  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
