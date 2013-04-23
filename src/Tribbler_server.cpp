// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

// msg :  userid+hash
// userid:trib_index
// userid:subscriptions



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
// added by me
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/sha1.hpp>
#include <algorithm>

using boost::property_tree::ptree; 
using boost::property_tree::read_json; 
using boost::property_tree::write_json;



using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using boost::lexical_cast;

using namespace std;
using namespace  ::Tribbler;
using namespace  ::KeyValueStore;

static int message_memory = 5;

class TribblerHandler : virtual public TribblerIf {
public:


    TribblerHandler(std::string storageServer, int storageServerPort) {
	// Your initialization goes here
	_storageServer = storageServer;
	_storageServerPort = storageServerPort;
    }

    static bool compareTribbleFunc(const Tribbler::Tribble & a, const  Tribbler::Tribble & b){
	return (a.posted > b.posted); 
    }
    static bool compareTribbleFuncRev(const Tribbler::Tribble & a, const  Tribbler::Tribble & b){
	return (a.posted < b.posted); 
    }
    /*
  static bool compareIndices(const string & a, const string & b){
//     return (a.posted > b.posted); 
      ptree p1, p2;

      stringstream s1(a);
      printf("%s ", a.c_str());
      stringstream s2(b);
      read_json( s1, p1);
      read_json( s2, p2);
      int64_t a_time = (p1.get<int64_t>("time_stamp"));
      int64_t b_time = (p2.get<int64_t>("time_stamp"));
//      printf("a_time  = %d, b_time = %d\n", (int) a_time , (int) b_time);
      return (  a_time > b_time  );
  }
  */


  TribbleStatus::type CreateUser(const std::string& userid) {
    // Your implementation goes here
    printf("CreateUser\n");
    KeyValueStore::GetResponse validate_id = Get(userid);
    printf("After Validation the status is %d\n",validate_id.status);
    if( validate_id.status != KVStoreStatus::EKEYNOTFOUND  )
	return TribbleStatus::EEXISTS ;

    //     string uList = "USER_LIST";
    string uID = userid;
    // KeyValueStore::GetResponse res = AddToList(uList,userid);
    // string tweets_num = boost::lexical_cast<string>(1);   
    string tweets_num = "0";   
    // KVStoreStatus::type st = Put(userid,"" /*tweets_num.str() */);
    KVStoreStatus::type st = Put(userid,tweets_num);
    cout<< tweets_num<<endl;
    //    KVStoreStatus::type st = AddToList(uList,userid);
    //    string vID = "000"; 
    // EKEYNOTFOUND = 2,
    printf("Create User st = %d\n",st);
    return TribbleStatus::OK;
    // if (st == KVStoreStatus::EITEMNOTFOUND){
    //    if (st == KVStoreStatus::OK){
    //	printf("after creating, check it = %d\n", st);

    //   }
    //  else{
    //	printf("User Name Already Used. Create with New cool name! \n");
    //	return TribbleStatus::EEXISTS ;
    //   }
  }

  TribbleStatus::type AddSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("AddSubscription\n");

    KeyValueStore::GetResponse validate_id = Get(userid);
    printf("Validate the user  %d\n",validate_id.status);
    if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	return TribbleStatus::INVALID_USER;
    // is there the user existed?
    // verify the id is in the USER_LIST or not
    //    string user_list = "USER_LIST";
    // KeyValueStore::GetListResponse
    validate_id = Get(subscribeto);
    printf("Validate the subscrito %d\n",validate_id.status);
    if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	return TribbleStatus::INVALID_SUBSCRIBETO;

    string userid_subs = userid+":subscriptions";
    KeyValueStore::GetListResponse subs = GetList(userid_subs);
    vector<string> subs_vec = subs.values;
    int sz = subs_vec.size();
    if ( sz > 0) {
	//	for(int i = 0 ; i < sz; i++){
	for(vector<string>::iterator it = subs_vec.begin() ; it != subs_vec.end(); it++)
	{
	    if ( *it == subscribeto){
		return TribbleStatus::OK;
	    } 
	}
    }
    //    KVStoreStatus::type st =	
    AddToList(userid_subs,subscribeto);
    return TribbleStatus::OK;
    
/* 
    KVStoreStatus::type res_id =   AddToList(user_list, userid);
    if(res_id != KVStoreStatus::EITEMEXISTS ){
	printf("not %s found in our system...\n", userid.c_str());
	RemoveFromList(user_list,userid);
	return TribbleStatus::INVALID_SUBSCRIBETO;
    }

    if(userid == subscribeto ) return TribbleStatus::INVALID_SUBSCRIBETO;
    KVStoreStatus::type usercheck = AddToList(user_list, subscribeto);
    if( usercheck == KVStoreStatus::EITEMEXISTS){
	//	KVStoreStatus::type st =
	string user_friends = userid+":friends";
	AddToList(user_friends, subscribeto);
	printf("%s Add Subscription %s\n", user_friends.c_str(), subscribeto.c_str());
	////
	string befriended = subscribeto+ ":befriended"; 
	AddToList(befriended, userid);
	////
	return TribbleStatus::OK;

    }
    RemoveFromList(user_list, subscribeto);
    printf("Fail to add a subscription to %s for %s", subscribeto.c_str(), userid.c_str());	

    return TribbleStatus::INVALID_SUBSCRIBETO;

//    KVStoreStatus::type st = AddToList(sub, subscribeto.c_str());
    if( st == KVStoreStatus::OK){
	printf("Add a subscription to %s for %s", subscribeto.c_str(), sub.c_str());	
	return TribbleStatus::OK;
    }

    if( st == KVStoreStatus::EITEMEXISTS){
	printf("Not add a subscription to %s for %s", subscribeto.c_str(), sub.c_str());	
	return TribbleStatus::OK;

     // return TribbleStatus::NOT_IMPLEMENTED;
    */
  }

  TribbleStatus::type RemoveSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("RemoveSubscription\n");

    KeyValueStore::GetResponse validate_id = Get(userid);
    printf("Validate the user  %d\n",validate_id.status);
    if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	return TribbleStatus::INVALID_USER;

    validate_id = Get(subscribeto);
    printf("Validate the user  %d\n",validate_id.status);
    if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	return TribbleStatus::INVALID_USER;

    string userid_subs = userid+":subscriptions";
    //    KVStoreStatus s
    // KVStoreStatus::type;
    RemoveFromList(userid_subs, subscribeto);
    return TribbleStatus::OK;
    /*
    printf("%s Remove Subscription %s\n",userid.c_str(), sub.c_str());
    // if( st == KVStoreStatus::EITEMEXISTS){
	printf("Remove a subscription to %s for %s", subscribeto.c_str(), sub.c_str());	
	string to_rm = subscribeto+":befriended";
	RemoveFromList(to_rm, userid);
	printf("Remove %s from %s's friend\n",to_rm.c_str(), userid.c_str());
	return TribbleStatus::OK;
   // }
   // printf("Fail to remove a subscription to %s for %s", subscribeto.c_str(), sub.c_str());	
    return TribbleStatus::OK;
    // return TribbleStatus::INVALID_SUBSCRIBETO;
    // return TribbleStatus::NOT_IMPLEMENTED;
    */
  }

  TribbleStatus::type PostTribble(const std::string& userid, const std::string& tribbleContents) {
    // Your implementation goes here
    printf("PostTribble\n");
    // trib.userid 
    KeyValueStore::GetResponse validate_id = Get(userid);
    printf("Validate the user  %d\n",validate_id.status);
    if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	return TribbleStatus::INVALID_USER;

    // trib posted = timestamp
    // trib contents
    // json trib => jsonstr
    // hash str => hashstr
    // add index to user's tribindex (userid:tribindex)
    // add tribble to hashtable (userid:hashstr,jsonstr)

    // string user_tribbles = userid+":tribble";
      string grp_no = validate_id.value ;// 
  //  string user_tribbles = userid+":tribble"+grp_no;
   // string timestamp = boost::lexical_cast<string> (time(NULL)); 
   // string time_tribble = timestamp+":"+tribbleContents ;

    ptree pt; 
    pt.put("user_id", userid);
    pt.put("time_stamp", time(NULL));
    pt.put("tribble", tribbleContents);
//    write_json("tribble.json",pt);
//    string marshal_tribble="";
    std::stringstream marshal_tribble_tmp;
    write_json(marshal_tribble_tmp,pt);
    string marshal_tribble = marshal_tribble_tmp.str();
    
//    printf("tribble in json %s\n", marshal_tribble.c_str());

    // for hash function just like Git, do not treat it as security protection 
    // it is tweeting ... not password .
    boost::uuids::detail::sha1 hash_sha1 ;
    // hash_sha1.process_bytes(marshal_tribble.c_str(),marshal_tribble.size());
    string hash_trib =  Sha1sum(marshal_tribble.c_str(),marshal_tribble.size());

 //   printf("hashing tribble in json %s\n",hash_trib.c_str());

    int cur_msg =  boost::lexical_cast<int> (validate_id.value);
    cur_msg++;
//     validate_id = Get(userid) ;
  //  cout<<validate_id.value<<endl;
//    int tweet_num = boost::lexical_cast<int>( validate_id.value);
 //   tweet_num++;
    Put(userid,boost::lexical_cast<string>(cur_msg) );
    int group = cur_msg / message_memory;
    string str_group = ":"+boost::lexical_cast<string>(group);
    string user_trib_index = userid+":trib_index"+str_group;

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    cout<<"add to ---> "<< user_trib_index<<endl;
//    printf("before update tweets number: %d\n", boost::lexical_cast<int> (validate_id.value));
    validate_id = Get(userid) ;
    cout<<validate_id.value<<endl;

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    /*

    int64_t tweets_num = boost::lexical_cast<int64_t>( validate_id.value) ;
    printf("before update tweets number: %d\n", (int) tweets_num );
    tweets_num++;
    stringstream tn;
    tn <<tweets_num;
    Put(userid,tn.str()) ;
    validate_id = Get(userid);
    printf("after update tweets number: %s\n",((validate_id.value)).c_str() );
    */
  //  printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    AddToList(user_trib_index , hash_trib);
    string user_hashtrib = userid+hash_trib;
   //  KVStoreStatus::type uhres = 
    Put(user_hashtrib, marshal_tribble); // record the real tweets
  //  printf("Put the trib in KV. The status: %d\n", uhres);

/*
    KVStoreStatus::type st = AddToList(user_tribbles, time_tribble);
    printf("Post status %d\n",st);
    if(st == KVStoreStatus::OK){
	printf("%s just post %s\n",user_tribbles.c_str(), tribbleContents.c_str());
    }
    // propagate to the people subscribe `me`
    string befriended = userid + ":befriended"; 
    KeyValueStore::GetListResponse res =  GetList(befriended);
    vector<string> bef = res.values;
    string key ;
    KVStoreStatus::type st_prop ;
    string time_tribble_tmp;
    for(vector<string>::iterator it = bef.begin(); it != bef.end(); it++){
       key = (*it)+":friends_tweets" ;	
       time_tribble_tmp = userid+":"+time_tribble;
       st_prop = AddToList(key,time_tribble_tmp); 
       printf("\" %s \" from me and propagate to %s. Return the state %d\n", time_tribble_tmp.c_str() , key.c_str(), st_prop);
    }
    */
    return TribbleStatus::OK;

//    return TribbleStatus::NOT_IMPLEMENTED;
  }

  void GetTribbles(TribbleResponse& _return, const std::string& userid) {
      // Your implementation goes here
      printf("---------------------------------\n");
      printf("---------------------------------\n");
      printf("---------------------------------\n");
      printf("GetTribbles\n");
      printf("---------------------------------\n");
      printf("---------------------------------\n");
      printf("---------------------------------\n");
      
 
      // get userid:tribindex => list
      // get userid:list(i) =>  jsontrib 
      // unmashal(jsontrib) => trib 

      KeyValueStore::GetResponse validate_id = Get(userid);
      printf("Validate the user  %d\n",validate_id.status);
      if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	  return ;//TribbleStatus::INVALID_USER;

      int cur_message = boost::lexical_cast<int> (validate_id.value);
      int cur_group = cur_message / message_memory; 
      int cnt = 0;

      while(cnt < 100 && cur_group >= 0  ){
	  string group = ":"+lexical_cast<string> (cur_group);
//	  string group ="";
	  string user_trib_index = userid+":trib_index"+group;
	  cout<<"in the group ---> "<<user_trib_index<<endl;
	  // Get My tweets/tribbles' index
	  KeyValueStore::GetListResponse index = GetList(user_trib_index);
	  //    string uID = userid + ":tribble"; 
	  //   KeyValueStore::GetListResponse res = GetList(uID);
	  vector<string> get_t_list = index.values;
	  //  size_t sz = get_t_list.size();
	  //     for( size_t i = sz-1; i >= 0 ; i--   )
	  string tmp = "";
	  ptree trib;
	  //    stringstream trib = ""; 
	  string tribstr ="";
	  KeyValueStore::GetResponse ind ; 
	  Tribbler::Tribble tmptrib_class;
	  if(get_t_list.size()>0){
	      printf("the index size = %d\n",(int)get_t_list.size());
	      printf("%s\n", (get_t_list[0]).c_str());
	      // some boundary concerns 
	      for(vector<string>::iterator it = get_t_list.end()-1; it != get_t_list.begin()-1; it--)
	      {
		  tmp = userid+(*it);
		  printf("username and index = %s\n",tmp.c_str()/*,tmp.c_str()*/);
		  ind = Get(tmp);
		  stringstream tribss(ind.value);
		  read_json(tribss,trib);
		  printf("Readin the trib from json %s\n",(ind.value).c_str());
		  tribstr = trib.get<string>("tribble");
		  tmptrib_class.contents = tribstr;
		  tmptrib_class.userid = trib.get<string>("user_id");
		  tmptrib_class.posted = trib.get<int64_t>("time_stamp");
		  // insert a binarry tree 
		  // remove the push back here
		  (_return.tribbles).push_back(tmptrib_class);
		  sort( (_return.tribbles).begin(), (_return.tribbles).end(), compareTribbleFunc);
		  cnt++;
		  if ( cnt == 100 ) { 
		      // build into return.tribbles use push_back
		      _return.status = TribbleStatus::OK;
		      return ;
		  }
	      }
	      // build into return.tribbles use push_back
//	      _return.status = TribbleStatus::OK;
	  }
	  else{
	      _return.status = TribbleStatus::OK;
	      return ;// 
	  }
	  cur_group--;
	  _return.status = TribbleStatus::OK;
      }
      // while

  }

  void GetTribblesBySubscription(TribbleResponse& _return, const std::string& userid) {
      // Your implementation goes here

      printf("---------------------------------\n");
      printf("---------------------------------\n");
      printf("---------------------------------\n");
      printf("GetTribblesBySubscription\n");
      printf("---------------------------------\n");
      printf("---------------------------------\n");
      // initilizaion the subscriptions 
      // get userid -> verify the user
      // getlist(userid:subscriptions) => list_sub_string
      // getlist(list_sub_string(i):tribindex) => list_sub_string(i).Indices 

      KeyValueStore::GetResponse validate_id = Get(userid);
      printf("Validate the user  %d\n",validate_id.status);
      if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	  return ;//TribbleStatus::INVALID_USER;
      string userid_subs = userid+":subscriptions";

      KeyValueStore::GetListResponse  subs_string = GetList(userid_subs); 
      // the subscriptions list
      vector<string> subs = subs_string.values;
      vector< vector<string> > subs_indices ;  
    //   vector<size_t> subs_index;  
      vector<int> subs_index;  
      vector<int> subs_msg;  
      vector<int> subs_cur_group;  
      vector<string> subs_userid;  
      Tribbler::Tribble tmptrib_class;
      vector< Tribbler::Tribble > subs_current_trib;
      vector< Tribbler::Tribble > friend_cur_trib;
      vector< vector< Tribbler::Tribble > >  friends_arrays;
      // tmp trib
      ptree trib;

      int flag = 0;
      string uidx ="";
      KeyValueStore::GetListResponse tmp_indices; //  GetList(user_trib_index);
      KeyValueStore::GetResponse trib_marsh; //  GetList(user_trib_index);
      
//      vector< vector<string> >::iterator it_ind = subs_indices.begin();  
      for(vector<string>::iterator it = subs.begin();it != subs.end(); it++){
	  validate_id = Get(*it);
	  int tmp_num = boost::lexical_cast<int> (validate_id.value); 
	  cout<<"FETCH the msg for "<< (*it) <<"   ---> "<< validate_id.value<<endl;
	  subs_msg.push_back(tmp_num );
	  subs_cur_group.push_back(tmp_num/ message_memory  );

	  // uidx = (*it)+":trib_index";
	  uidx = (*it)+":trib_index"+":"+(boost::lexical_cast<string>(subs_cur_group[flag]));
	  // can tag the current number and transfer smaller index for subs
	  printf("%d The subs people = %s\n", flag, uidx.c_str());
	  tmp_indices    = GetList(uidx ); 
	  subs_userid.push_back(*it);
	  vector<string> tmp_ind = tmp_indices.values; 
	  subs_index.push_back(tmp_ind.size()-1);
	  printf("%d\n",(int) tmp_ind.size()); 
	  printf("userid=%s, user_index size = %d\n", (subs_userid[flag]).c_str(), (int) subs_index[flag]);

	  // the real infomation are stored in the indices contains time stamp, id, tweets 
	  subs_indices.push_back(tmp_ind);
	  // --- 
	  // fetch in the group tweets for one friend
	  string uid_tmp=""; 
	  // get the current list for this firend

	  for(int jj = 0; jj < subs_index[flag] + 1 ; jj++){
	      uid_tmp = subs_userid[flag] + (subs_indices[flag])[ jj ];
	      printf("uid_tmp = %s\n", uid_tmp.c_str());
	      trib_marsh = Get( uid_tmp );
	      // printf("get the %s\n", (trib_marsh.value).c_str() );
	      stringstream  tmp_msh(trib_marsh.value);
	      printf("Read to sort %s    " , (tmp_msh.str()).c_str());
	      read_json(tmp_msh, trib);

	      tmptrib_class.contents = trib.get<string>("tribble");
// 	      printf("tmptrib contents %s\n", (tmptrib_class.contents).c_str());
	      tmptrib_class.userid = trib.get<string>("user_id");
	      tmptrib_class.posted = trib.get<int64_t>("time_stamp");
	      friend_cur_trib.push_back(tmptrib_class);
	      // (friends_arrays[flag]).push_back(tmptrib_class);
	  }
	  printf("current clas s size %d",(int) friend_cur_trib.size());

	  friends_arrays.push_back(friend_cur_trib);


	  printf("before sorting ?!@!@#@!# %d,    ", (int) (friends_arrays[flag]).size() ); 
	  // for(vector<Tribble>::iterator fit = (friends_arrays[flag]).begin();
	    //  fit != (friends_arrays[flag]).end(); fit++){
	  // }
	  sort( (friends_arrays[flag]).begin(), (friends_arrays[flag]).end(), compareTribbleFuncRev);

	  printf("after sorting ?!@!@#@!# %d\n  ", (int) (friends_arrays[flag]).size() ); 

	  for(vector<Tribble>::iterator fit = (friends_arrays[flag]).begin();
	      fit != (friends_arrays[flag]).end(); fit++){
	      printf("?!@!@#@!# timestamp = %d, ", (int) ((*fit).posted) ); 
	      printf("?!@!@#@!# content = %s\n", ((*fit).contents).c_str() ); 
	  }
// --- 


	  //	  (subs_indices[i]).insert( (subs_indices[i]).begin(), tmp_ind.begin(), tmp_ind.end());
//	  (*it_ind)=(tmp_ind);

/*	  printf("before sort\n");
	  for( vector<string>::iterator itt = (subs_indices[flag]).begin(); itt!= (subs_indices[flag]).end(); itt++  ){
	      printf("%s  ", (*itt).c_str());
	  }
	  printf("\n");
	  printf("\n");
	  printf("begin rearrange !! \n");

	  sort( (subs_indices[flag]).begin(), (subs_indices[flag]).end(),compareIndices);
	  for( vector<string>::iterator itt = (subs_indices[flag]).begin(); itt!= (subs_indices[flag]).end(); itt++  ){
	      printf("%s  ", (*itt).c_str());
	  }

	  printf("after  sort\n");
	  printf("\n");
 */
	  printf("subs_indices's size = %d\n",(int)  (subs_indices).size()); 
	  printf("current element of subs_indices's size = %d\n",(int)  (subs_indices[flag]).size()); 
	  printf("\n\n");

	  // initized the friends
	  // add non empty tribbers from friends
	  if(subs_index[flag] >= 0 ){
	      printf("subs_index[flag] = %d\n", (int) subs_index[flag]);
	      
	      // reduce the index to get the last element

//	      string uid_tmp = subs_userid[flag] + (subs_indices[flag])[ subs_index[flag] ];
//	      printf("uid_tmp = %s\n", uid_tmp.c_str());
//	      trib_marsh = Get( uid_tmp );
	      // printf("get the %s\n", (trib_marsh.value).c_str() );
//	      stringstream tmp_msh(trib_marsh.value);
//	      read_json(tmp_msh, trib);

	      printf("????????????????????????????????????????The friends array size %d and subs_index is %d,   ", 
		     (int ) (friends_arrays[flag]).size(), (int) subs_index[flag]);
	      printf("!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~ \n\n %s ",( (( friends_arrays[flag]).at(subs_index[flag])).contents).c_str());
	      tmptrib_class.contents = (( friends_arrays[flag]).at(subs_index[flag])).contents;
	      // trib.get<string>("tribble");// 	      printf("tmptrib contents %s\n", (tmptrib_class.contents).c_str());
	      tmptrib_class.userid =( (friends_arrays[flag]).at(subs_index[flag])).userid ;// trib.get<string>("user_id");
	      tmptrib_class.posted =( (friends_arrays[flag]).at(subs_index[flag])).posted  ;// trib.get<int64_t>("time_stamp");

	      subs_current_trib.push_back(tmptrib_class);
//	      tmptrib_class =l/
//	       subs_current_trib.push_back(friends_arrays[flag])[ subs_index[flag] ];

	      printf("tmptrib contents after getting !! %s\n", 
		     (subs_current_trib[flag].contents).c_str());
//	      subs_index[flag]-- ;
	      printf("after reduce subs_index[flag] = %d\n",(int) subs_index[flag]);
	  }

	  flag++;
      }

      //compare the current subscrip and find out the current latest, and iteration till 100
      printf("The Flag final value = %d !!!!!!!!!!!!!!!!!!!!\n",flag);

      int cnt_subs_trib = 100; 
      int min_int  = -1;

      for(int i = 0 ; i < cnt_subs_trib ; i++){
	  min_int  = -1;
	  for (int j = 0; j<flag ; j++){
	      printf("subs_index[%d]=%d    ", j,subs_index[j]);
	      if( ( min_int == -1 && subs_index[j] > -1 ) || (   min_int > -1 &&  subs_index[j] > -1  
								 && (subs_current_trib[j].posted > subs_current_trib[min_int].posted )  ) ){
		  min_int = j;
	      }
	  } // for j
	  printf("\n the min_int in iteration #%d is %d\n ",i, min_int);	

	  if(min_int > -1) {
	      (_return.tribbles).push_back(subs_current_trib[min_int]);
	      subs_index[min_int]--;

	      if(subs_index[min_int] <= -1 && subs_cur_group[min_int] > 0     )
	      {
		  subs_cur_group[min_int]--; 
		  // update this friend with previous page index 
		  uidx = subs[min_int] +":trib_index"+":"+(boost::lexical_cast<string>(subs_cur_group[min_int]));
		  // can tag the current number and transfer smaller index for subs
		  printf("%d The subs people = %s\n", flag, uidx.c_str());
		  tmp_indices    = GetList(uidx ); 
		  vector<string> tmp_ind = tmp_indices.values; 
		  subs_index[min_int] = (tmp_ind.size()-1);
		  printf("%d\n",(int) tmp_ind.size()); 
		  // the real infomation are stored in the indices contains time stamp, id, tweets 
		  subs_indices[min_int] = (tmp_ind);
		  // --- 
		  // fetch in the group tweets for one friend
		  string uid_tmp=""; 
		  // get the current list for this firend
		  friends_arrays[min_int].resize(subs_index[min_int]+1  );

		  for(int jj = 0; jj < subs_index[min_int] + 1 ; jj++){
		      uid_tmp = subs_userid[min_int] + (subs_indices[min_int])[ jj ];
		      printf("uid_tmp = %s\n", uid_tmp.c_str());
		      trib_marsh = Get( uid_tmp );
		      // printf("get the %s\n", (trib_marsh.value).c_str() );
		      stringstream  tmp_msh(trib_marsh.value);
		      printf("Read to sort %s    " , (tmp_msh.str()).c_str());
		      read_json(tmp_msh, trib);

		      tmptrib_class.contents = trib.get<string>("tribble");
		      // 	      printf("tmptrib contents %s\n", (tmptrib_class.contents).c_str());
		      tmptrib_class.userid = trib.get<string>("user_id");
		      tmptrib_class.posted = trib.get<int64_t>("time_stamp");
		      // friend_cur_trib.push_back(tmptrib_class);
		      // (friends_arrays[min_int]).push_back(tmptrib_class);
		      (friends_arrays[min_int])[jj]= tmptrib_class ;
		  }
		  printf("current clas s size %d",(int) friend_cur_trib.size());

		 // friends_arrays[min_int]=friend_cur_trib;
		  printf("before sorting ?!@!@#@!# %d,    ", (int) (friends_arrays[flag]).size() ); 
		  // for(vector<Tribble>::iterator fit = (friends_arrays[flag]).begin();
		  //  fit != (friends_arrays[flag]).end(); fit++){
		  // }
		  sort( (friends_arrays[min_int]).begin(), (friends_arrays[min_int]).end(), compareTribbleFuncRev);
	      }
	      // next update the min_int  after pop out 

	      if(subs_index[min_int] > -1       )
	      { // current index > -1 means there still exist tribbles
		  string uid_tmp = subs_userid[min_int] + (subs_indices[min_int])[ subs_index[min_int] ];
		  //		  trib_marsh = Get( uid_tmp );
		  //		  stringstream tmp_msh(trib_marsh.value);
		  //		  read_json(tmp_msh, trib);
		  //		  tmptrib_class.contents = trib.get<string>("tribble");
		  //		  printf("tmptrib contents %s\n", (tmptrib_class.contents).c_str());
		  //		  tmptrib_class.userid = trib.get<string>("user_id");
		  //  tmptrib_class.posted =  ;// trib.get<int64_t>("time_stamp");
		  tmptrib_class.contents = (( friends_arrays[min_int]).at(subs_index[min_int])).contents;
		  // trib.get<string>("tribble");// 	      printf("tmptrib contents %s\n", (tmptrib_class.contents).c_str());
		  tmptrib_class.userid =( (friends_arrays[min_int]).at(subs_index[min_int])).userid ;// trib.get<string>("user_id");
		  tmptrib_class.posted =( (friends_arrays[min_int]).at(subs_index[min_int])).posted  ;// trib.get<int64_t>("time_stamp");
		  subs_current_trib[min_int] = tmptrib_class;
	      }
	  }
	  else {
	      _return.status = TribbleStatus::OK;
	      //	      sort( (_return.tribbles).begin(), (_return.tribbles).end(), compareTribbleFunc);
	      return;
	  }
      }
      _return.status = TribbleStatus::OK;
      //      sort( (_return.tribbles).begin(), (_return.tribbles).end(), compareTribbleFunc);
/*
      string user_get_friends = userid + ":friends_tweets" ;	
      printf("fetch %s\n", user_get_friends.c_str());
      KeyValueStore::GetListResponse res = GetList(user_get_friends);
      vector<string> get_t_list = res.values;
      printf("Getlist Response Status: %d ; Tribble size : %d \n",res.status, (int)get_t_list.size());
      //    vector<Tribble> t_list ;
      Tribbler::Tribble t_list_node;
      for(vector<string>::iterator it = get_t_list.begin(); it != get_t_list.end(); ++it)
      {
	  t_list_node.contents = *it ;// it;
	  (_return.tribbles).push_back(t_list_node);
      }
      //     _return.tribbles = t_list;
      // _return.status = TribbleStatus::NOT_IMPLEMENTED;

      //    _return.status = TribbleStatus::NOT_IMPLEMENTED;
      */
  }

  void GetSubscriptions(SubscriptionResponse& _return, const std::string& userid) {
    // Your implementation goes here

    printf("GetSubscriptions\n");

    KeyValueStore::GetResponse validate_id = Get(userid);
    printf("After Validation the status is %d\n",validate_id.status);
    if( validate_id.status == KVStoreStatus::EKEYNOTFOUND  )
	return; //;TribbleStatus::INVALID_USER ;
    string userid_subs = userid+":subscriptions";
    KeyValueStore::GetListResponse res =  GetList(userid_subs);
    printf("After Getlist the status is %d\n",res.status);
    vector<string> get_t_list = res.values;
    printf("Subs list size: %d\n",(int)get_t_list.size());
    /*
    for(vector<string>::iterator it = get_t_list.begin();
	it != get_t_list.end(); ++it)
    {
	(_return.subscriptions).push_back(*it);
    }
    */

    _return.subscriptions = res.values;
    _return.status = TribbleStatus::OK;
/*
    string uID = userid + ":friends"; 
    KeyValueStore::GetListResponse res = GetList(uID); vector<string> get_t_list = res.values;
    printf("Getlist Response Status: %d ; Tribble size : %d \n",res.status, (int)get_t_list.size());
//    vector<Tribble> t_list ;
//    Tribbler::Tribble t_list_node;
    for(vector<string>::iterator it = get_t_list.begin();
	it != get_t_list.end(); ++it)
    {
	(_return.subscriptions).push_back(*it);
    }

//     _return.tribbles = t_list;
    // _return.status = TribbleStatus::NOT_IMPLEMENTED;
    */
 

  }

  // Functions from interacting with the storage RPC server
  KVStoreStatus::type AddToList(std::string key, std::string value) {
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient kv_client(protocol);
    // Making the RPC Call
    KVStoreStatus::type st;
    transport->open();
    st = kv_client.AddToList(key, value);
    transport->close();
    return st;
  }

  KeyValueStore::GetListResponse GetList(std::string key) {
      KeyValueStore::GetListResponse response;
      // Making the RPC Call to the Storage server
      boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
      boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
      boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
      KeyValueStoreClient client(protocol);
      transport->open();
      client.GetList(response, key);
      transport->close();
      return response;
  }

  KVStoreStatus::type RemoveFromList(std::string key, std::string value) {
    // Making the RPC Call to the Storage server
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    KVStoreStatus::type st;
    transport->open();
    st = client.RemoveFromList(key, value);
    transport->close();
    return st;
  }

  KVStoreStatus::type Put(std::string key, std::string value) {
    // Making the RPC Call to the Storage server
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    KVStoreStatus::type st;
    transport->open();
    st = client.Put(key, value);
    transport->close();
    return st;
  }

  KeyValueStore::GetResponse Get(std::string key) {
    KeyValueStore::GetResponse response;
    // Making the RPC Call to the Storage server
    //
    printf("In the Get... \n");
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    transport->open();
    printf("Open Transport... \n");
    client.Get(response, key);
    transport->close();
    printf("Close Transport... \n");
    return response;
  }
  // acknowledge github here  
  std::string Sha1sum(const void *data, std::size_t count) {
      boost::uuids::detail::sha1 hasher;
      char hash[20];
      hasher.process_bytes(data, count);
      unsigned int digest[5];
      hasher.get_digest(digest);
      for(int i = 0; i < 5; ++i) {
	  const char *tmp = reinterpret_cast<char *>(digest);
	  hash[i * 4] = tmp[i * 4 + 3];
	  hash[i * 4 + 1] = tmp[i * 4 + 2];
	  hash[i * 4 + 2] = tmp[i * 4 + 1];
	  hash[i * 4 + 3] = tmp[i * 4];
      }
      std::stringstream res;
      res << std::hex;
      for(int i = 0; i < 20; ++i) {
	  res << ((hash[i] & 0x000000F0) >> 4)
	      <<  (hash[i] & 0x0000000F);
      }
      return res.str();
  }

 private:
  std::string _storageServer;
  int _storageServerPort;
};

int main(int argc, char **argv) {
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <storageServerIP> <storageServerPort> <tribbleServerPort>" << endl;
    exit(0);
  }
  std::string storageServer = std::string(argv[1]);
  int storageServerPort = atoi(argv[2]);
  int tribblerPort = atoi(argv[3]);

  shared_ptr<TribblerHandler> handler(new TribblerHandler(storageServer, storageServerPort));
  shared_ptr<TProcessor> processor(new TribblerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(tribblerPort));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  cout << "Starting Tribbler Server" << endl;
  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
