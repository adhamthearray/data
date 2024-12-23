#pragma once
#include "HashTable.h"
#include "linkedList.h"
#include "Vector.h"
//#include "Pair.h"

#include "PriorityQueue.h"



//class accessnode;
//#include "UserNode.h"
class Graph
{
public:
	class UserNode {
		static int num_id;
	private:


	public:
		LinkedList<UserNode> requests;
		LinkedList<UserNode> friends;

		bool privacy;
		string address;
		string phone_number;
		//int id;
		string first_name;
		string last_name;
		string username;
		int index_of_hash;
		string password;
		//UserNode* getnext();
		
	
		UserNode(string first_name, string last_name, string nusername, string pass, bool privacy, string address, string phone_number);
		UserNode();
		UserNode(const UserNode& other);
		UserNode& operator=(const UserNode& other);
		~UserNode(); //destructor implementation //commented
		void set_name(string first, string last);
		void set_privacy(bool priv);
		void set_address(string address);
		void set_username(string name);
		void set_password(string pass);
		void set_phonenumber(string phone);
		string get_firstname() { return first_name; }
		string get_lastname() { return last_name; }
		//int get_index_of_hash();
		string get_password() {
			return password;
		}
		//int getID();
		string getUsername() { return this->username; }
		string get_phonenumber() { return phone_number; }
		string get_address() { return address; }
		bool get_privacy() { return privacy; }

		bool searchfriends(string username);
		bool searchrequests(string username);
		void send_request(UserNode& Sent_request_to);//tendah 3la add request 
		void accept(UserNode& Sender_of_request);//takhod ely ba3at tohoto 3andaha
		void decline(UserNode& Sender_of_request);
		void show_requests();
		//void update_priority();
		void view_profile(UserNode& to_view);//ba-view profile user tany
		void view_MY_profile();
		void view_myData();
		void view_myRealDATA();
		void view_friends();
		void modify_data();
		void searchByUsername(const string& username);
		//void remove(UserNode& friend_to_be_removed);
		//void add_to_friends(int index_of_hash, int id);
		UserNode* login();
		void signup();
		//bool operator==(const UserNode& other) const;
		friend std::ostream& operator<<(std::ostream& os, const UserNode& user);
		friend bool operator==(const UserNode& lhs, const UserNode& rhs);   //commented
		//UserNode(const UserNode& other);    //commented
		void people_you_may_know();
		Vector<string> mutual_friends();
		Vector<UserNode> degree();
		Vector<UserNode> randomized();

		bool operator<(const UserNode& other) const {
			return this->username < other.username;
		}

		// Overload > operator (compare based on username)
		bool operator>(const UserNode& other) const {
			return this->username > other.username;
		}

	};
	

	static HashTable <UserNode> hashex_login;
	//static HashTable <UserNode>hashex_database;








	

};
