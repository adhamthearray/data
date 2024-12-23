#include "Graph.h"
using namespace std;

// Static member initialization (if needed)
int Graph::UserNode::num_id = 0;
HashTable<Graph::UserNode> Graph::hashex_login; //definition of hashtable object

Graph::UserNode::UserNode(string first_name, string last_name, string nusername, string pass, bool privacy, string address, string phone_number) {
    this->first_name = first_name;
    this->last_name = last_name;
    this->username = nusername;
    this->password = pass;
    this->privacy = privacy;
    this->address = address;
    this->phone_number = phone_number;
    int sum_username = 0;
    for (int i = 0; i < username.size(); i++) {
        sum_username += username[i];
    }
    /*int sum_off_name = 0;
    sum_off_name = first_name[0] + first_name[1] + last_name[0] + last_name[1];*/
    hashex_login.insert(this, sum_username);
    //hashex_database.insert(this, sum_off_name);
}

Graph::UserNode::~UserNode() {
    cout << "hii";
    requests.clear();
    friends.clear();

    // Output a message for debugging purposes (optional)
    std::cout << "Destructor called for UserNode: " << username << std::endl;
}



// Default constructor
Graph::UserNode::UserNode() : privacy(true) {}

Graph::UserNode::UserNode(const UserNode& other)
    : first_name(other.first_name), last_name(other.last_name), username(other.username), password(other.password),
    privacy(other.privacy), address(other.address), phone_number(other.phone_number),
    index_of_hash(other.index_of_hash) {
    // Deep copy of LinkedLists (assuming LinkedList has its own copy constructor)
    requests = other.requests;
    friends = other.friends;
}

  Graph::UserNode& Graph::UserNode:: operator=(const UserNode& other) {
    if (this != &other) {  // self-assignment check
        // Assign basic member variables
        first_name = other.first_name;
        last_name = other.last_name;
        username = other.username;
        password = other.password;
        privacy = other.privacy;
        address = other.address;
        phone_number = other.phone_number;
        index_of_hash = other.index_of_hash;

        // Deep copy of LinkedLists
        requests = other.requests;
        friends = other.friends;
    }
    return *this;  // return current object to allow assignment chaining
}

// Setters
void Graph::UserNode::set_name(string first, string last) {
    first_name = first;
    last_name = last;
}

void Graph::UserNode::set_privacy(bool priv) {
    privacy = priv;
}

void Graph::UserNode::set_address(string address) {
    this->address = address;
}

void Graph::UserNode::set_username(string name) {
    username = name;
}

void Graph::UserNode::set_password(string pass) {
    password = pass;
}

void Graph::UserNode::set_phonenumber(string phone) {
    phone_number = phone;
}








bool Graph::UserNode::searchfriends(string username)
{
    LinkedList<UserNode>::accessnode* ptr = this->friends.head;
    while (ptr != nullptr) {
        if (ptr->OG_NODE->getUsername() == username) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool Graph::UserNode::searchrequests(string username)
{
    LinkedList<UserNode>::accessnode* ptr = this->requests.head;
    while (ptr != nullptr) {
        if (ptr->OG_NODE->getUsername() == username) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void Graph::UserNode::send_request(UserNode& newnode) {

    newnode.requests.append(this);
}

void Graph::UserNode::accept(UserNode& Sender_of_request) {
    UserNode* f = &Sender_of_request;

    friends.append(f);

    Sender_of_request.friends.append(this);
    requests.remove(Sender_of_request);
    cout << Sender_of_request.getUsername() << " is accepted successfully!\n";
}

void Graph::UserNode::decline(UserNode& Sender_of_request) {

    requests.remove(Sender_of_request);
    cout << Sender_of_request.getUsername() << " has been declined successfully! ";
}

void Graph::UserNode::show_requests() {

    requests.IterateByIndex();
    int n;
    if (requests.empty()) {
        cout << "List is empty!\n";
        return;
    }
    cout << "\n Enter index of your choice<3\n[-1]Back \n";
    cin >> n;
    if (n == -1) {
        return;
    }
    UserNode& userrr = *(requests.search_by_index(n));

    // UserNode & userrr = *(anode->OG_NODE); /

        short x = 0;
    while (x != 4)
    {
        cout << "[1]Accept\n[2]Decline\n[3]View Profile\n[4]Back";
        cin >> x;
        if (x == 1) {
            this->accept(userrr);
            break;
        }
        else if (x == 2) {
            this->decline(userrr);
            break;
        }
        else if (x == 3) {
            this->view_profile(userrr);
            break;

        }
        else {
            cout << "Invalid\n";

        }
    }
}

void Graph::UserNode::view_profile(UserNode& to_view) {

    bool k = 1;
    UserNode* point = &to_view;
    while (k == 1)
    {

        cout << "Profile Of " << point->getUsername() << endl;
        cout << "------------" << endl;

        if (point->get_privacy() == 1)
        {
            if (!(this->searchfriends(point->getUsername())))
            {
                std::cout << "Sorry,This account is private\n";
                k = 0;
                return;
            }
        }

        (*(point)).view_myData();
        std::cout << "[1]View friends\n[2]back\n";
        short a;
        std::cin >> a;
        if (a == 1)
        {

            (*(point)).view_friends();
            int n;
            std::cout << "Enter index < 3 \n[-1] Back to main\n";
            std::cin >> n;
            if (n == -1)
            {
                return;
            }
            else
            {
                UserNode* anode = (*(point)).friends.search_by_index(n);
                /* UserNode* userh = anode->OG_NODE;*/
                // UserNode& userrr = (anode->OG_NODE);
                 UserNode* userp = point;
                // string username = userrr.username;
                 // Check if the username is in the friends list

                 std::cout << "Checking if username is in friends list..." << endl;
                 bool friendd = this->searchfriends(anode->getUsername());
                 if (friendd)
                 {
                     std::cout << "[1]View Profile\n[2]Remove Friend \n [3]Back\n";
                     short x;
                     std::cin >> x;
                     if (x == 1)
                     {
                         std::cout << "user name: " << endl;
                         std::cout << anode->getUsername() << endl;
                         anode->view_myData();
                     }
                     else if (x == 2)
                     {
                         this->friends.remove(*anode);
                         anode->friends.remove(*this);
                         std::cout << anode->getUsername() << " Removed Successfully!" << endl;
                     }
                     else if (x == 3)
                     {

                         return;
                     }
                     else {
                         std::cout << "Invalid Input" << endl;
                         break;
                     }
                 }
                 else if (this->searchrequests(anode->getUsername()))
                 {
                     std::cout << "[1]View Profile\n[2]Accept \n [3] Decline\n [4] Back\n";
                     short x;
                     std::cin >> x;
                     if (x == 1) {
                         std::cout << "user name: " << endl;
                         std::cout << anode->getUsername() << endl;
                         anode->view_myData();
                     }
                     else if (x == 2) {
                         this->accept(*anode);
                         std::cout << "ACCEPTED" << endl;
                     }
                     else if (x == 3) {

                         this->decline(*anode);
                         std::cout << "DECLINED" << endl;

                     }
                     else if (x == 4) {

                         break;
                     }
                     else {
                         std::cout << "Invalid Input" << endl;
                     }

                 }
                 else if (anode->searchrequests(this->username)) {
                     std::cout << "[1]View Profile\n[2] Remove Request \n [3]Back \n";
                     short x;
                     std::cin >> x;
                     if (x == 1) {
                         std::cout << "user name: " << endl;
                         std::cout << anode->getUsername() << endl;
                         anode->view_myData();

                     }
                     else if (x == 2) {
                         anode->requests.remove(*this);
                         std::cout << "REQUEST REMOVED \n";

                     }
                     else if (x == 3) {

                         break;
                     }
                     else {
                         std::cout << "Invalid Input" << endl;
                     }

                 }
                 else if (this->username == anode->getUsername()) {
                     this->view_MY_profile();
                 }
                 else
                 {
                     int x = 0;

                     while (true)
                     {

                         std::cout << "[1]View Profile \n [2]Add Friend \n [3] Back\n";
                         short x;
                         std::cin >> x;
                         if (x == 1)

                         {
                             std::cout << "user name: " << endl;
                             std::cout << anode->getUsername();
                             view_profile(*anode);
                             break;


                         }
                         else if (x == 2)
                         {
                             this->send_request(*anode);
                             std::cout << "Added successfully!" << endl;
                             break;
                         }
                         else if (x == 3)
                         {

                             break;
                         }
                     }
                 }
             }
         }
         else if (a == 2)
         {
             return;
         }
         else
         {
             std::cout << "Invalid" << endl;
             return;
         }






     }
     cout << "----------------------------------------" << endl;


 }

 void Graph::UserNode::view_MY_profile() {

     bool c = 1;
     while (c == 1) {
         cout << "--------------------------------------" << endl;
         this->view_myRealDATA();
         cout << "[1]Modify Data\n[2]Back \n";
         short choice;
         cin >> choice;
         if (choice == 1)
             this->modify_data();
         else if (choice == 2) {
             return;

         }
         else {
             cout << "Invalid\n";
             break;
         }
         cout << "--------------------------------------" << endl;
     }
 }


 void Graph::UserNode::view_myData() {
     cout << "First name: " << this->get_firstname() << endl << "Last name:  " << this->get_lastname() << endl;
     cout << "Username: " << this->getUsername() << endl;

      cout << "Phone number: " << this->get_phonenumber() << "\nAddress: " << this->get_address() << endl;

            }

 void Graph::UserNode::view_myRealDATA() {
                cout << "--------------------------------------------------------------------------" << endl;
                cout << "First name: " << this->get_firstname() << endl << "Last name:  " << this->get_lastname() << endl;
                cout << "Username: " << this->getUsername() << endl;
                cout << "Phone number: " << this->get_phonenumber() << "\nAddress: " << this->get_address() << endl;
                cout << "PassWord: " << this->password;
            }

 void Graph::UserNode::view_friends() {
                friends.IterateByIndex();

                cout << "" << endl;
            }

 void Graph::UserNode::modify_data() {
                cout << "What data do you want to modify?\n";
                cout << "[1] Password\n[2]Address\n[3]Phone Number\n[4]Return Home\n";
                short option;
                string password;
                string address;
                string phone;
                cin >> option;
                switch (option)
                {
                case 1:
                    cout << "Enter new password: ";
                    cin >> password;
                    this->set_password(password);
                    cout << "password updated succeessfully!";
                    break;
                case 2:
                    cout << "Enter new Address: ";
                    cin >> address;
                    this->set_address(address);
                    cout << "address updated succeessfully!";
                    break;
                case 3:
                    cout << "enter new phone number: ";
                    cin >> phone;
                    this->set_phonenumber(phone);
                    cout << "phone number updated succeessfully!";
                    break;

                case 4:
                    cout << "returning home...";
                    return;

                default:
                    cout << "Invalid";
                    break;
                }

                cout << "---------------------------------------------------------------" << endl;

            }

 void Graph::UserNode::searchByUsername(const string & username) {
                // Calculate the sum of username characters
                int sum_username = 0;
                for (char c : username) {
                    sum_username += c;
                }
                cout << "Sum of username characters: " << sum_username << endl;

                // Hash the username to find the index
                int index = hashex_login.hash(sum_username);
                cout << "Calculated hash index: " << index << endl;
                LinkedList<UserNode>::accessnode* temp = hashex_login.buckets[index].head;
                // Declare a pointer to hold the UserNode
                UserNode* temp1 = nullptr;
                try {
                    // Retrieve the UserNode from the hash table
                    cout << "Calling HASHget..." << endl;
                    cout << "Searching at index: " << index << endl;


                    while (temp != nullptr) {
                        cout << "Checking username: " << temp->OG_NODE->getUsername() << ", password: " << temp->OG_NODE->get_password() << endl;
                        if (temp->OG_NODE->getUsername() == username) {
                            temp1 = temp->OG_NODE;
                            break;
                        }
                        temp = temp->next;
                    }
                    // This now returns a pointer to the UserNode
                }
                catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << endl;
                    return; // Exit the function if the user is not found in the hash table
                }
                if (temp1 != nullptr) {
                    bool v = 1;
                    while (v) {
                        cout << "Successfully retrieved targetNode" << endl;
                        UserNode& ref = *temp1;
                        // Check if the username is in the friends list
                        cout << "Checking if username is in friends list..." << endl;
                        bool friendd = this->searchfriends(username);
                        if (friendd) {
                            cout << "[1]View Profile\n[2]Remove Friend \n [3]Back \n";
                            short x;
                            cin >> x;
                            if (x == 1) {
                                cout << "user name: " << endl;
                                cout << temp1->getUsername();
                                view_profile(ref);
                                break;
                            }
                            else if (x == 2) {
                                this->friends.remove(*temp1);
                                temp1->friends.remove(*this);
                                cout << temp1->getUsername() << " Removed Successfully!\n";
                            }
                            else if (x == 3) {
                                v = 0;
                                break;
                            }
                            else {
                                cout << "Invalid Input";
                            }
                        }
                        else if (this->searchrequests(username)) {
                            cout << "[1]View Profile\n[2]Accept \n [3] Decline\n [4] Back\n";
                            short x;
                            cin >> x;
                            if (x == 1) {
                                cout << "user name: " << endl;
                                cout << temp1->getUsername();
                                view_profile(*temp1);

                            }
                            else if (x == 2) {
                                this->accept(ref);
                                cout << "ACCEPTED";
                            }
                            else if (x == 3) {

                                this->decline(ref);
                                cout << "DECLINED";

                            }
                            else if (x == 4) {
                                v = 0;
                                break;
                            }
                            else {
                                cout << "Invalid Input";
                            }

                        }
                        else if (ref.searchrequests(this->username)) {
                            cout << "[1]View Profile\n[2] Remove Request \n [3]Back \n";
                            short x;
                            cin >> x;
                            if (x == 1) {
                                cout << "user name: " << endl;
                                cout << temp1->getUsername();
                                view_profile(ref);
                            }
                            else if (x == 2) {
                                ref.requests.remove(*this);
                                cout << "REQUEST REMOVED \n";

                            }
                            else if (x == 3) {
                                v = 0;
                                break;
                            }
                            else {
                                cout << "Invalid Input";
                            }

                        }
                        else if (this->getUsername() == temp1->username) {
                            this->view_MY_profile();
                            break;
                        }
                        else {
                            int x = 0;
                            while (true) {
                                cout << "[1]View Profile \n [2]Add Friend \n [3] Back\n";
                                short x;
                                cin >> x;
                                if (x == 1) {
                                    view_profile(ref);

                                }
                                else if (x == 2) {
                                    send_request(*temp1);
                                    cout << "Added successfully!";
                                    break;
                                }
                                else if (x == 3) {
                                    v = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                else {
                    cout << "Invalid username\n";
                    return;
                }
                cout << "------------------------------------------------------------" << endl;

            }

 Graph::UserNode* Graph::UserNode::login() {
                string username;
                string password;
                while (true) {
                    std::cout << "Enter your username: \n";
                    std::cin >> username;
                    cout << "Enter your password: \n";
                    cin >> password;

                    int sum = 0;
                    for (char c : username) {
                        sum += c;
                    }

                    int index = hashex_login.hash(sum);
                    cout << "Searching at index: " << index << endl;
                    //UserNode* temp = hashex_login.table[index];
                    LinkedList<UserNode>::accessnode* temp = hashex_login.buckets[index].head;

                    while (temp != nullptr) {
                        cout << "Checking username: " << temp->OG_NODE->getUsername() << ", password: " << temp->OG_NODE->get_password() << endl;
                        if (temp->OG_NODE->getUsername() == username && temp->OG_NODE->get_password() == password) {
                            return temp->OG_NODE;
                        }
                        temp = temp->next;
                    }

                    cout << "Invalid username or password. Try again.\n";
                    bool flag = true;

                    while (flag) {
                        cout << "Do you want to sign up?\n[1] Yes\n[2] No\n";
                        short x;

                        // Input validation
                        cin >> x;
                        if (cin.fail()) {
                            cout << "Invalid input! Please enter 1 or 2.\n";
                            cin.clear();        // Clear the input stream
                            cin.ignore(1000, '\n'); // Discard invalid input
                            continue;           // Retry
                        }

                        if (x == 1) {
                            signup(); // Call the signup function
                            flag = false; // Exit the loop after signing up
                        }
                        else if (x == 2) {
                            cout << "Login again.\n";
                            flag = false; // Exit the loop, returning to login prompt
                        }
                        else {
                            cout << "Invalid choice! Please enter 1 or 2.\n";
                        }
                    }


                }
            }

            void Graph::UserNode::signup() {

                string fname;
                string lname;
                string nusername;
                string password;
                string phoneNumber;
                string address;
                bool priv;


                cout << "Enter your first name: \n";
                cin >> fname;
                cout << "Enter your last name: \n";
                cin >> lname;

                bool flag = true;
                while (flag) {
                    cout << "Enter your username: \n";
                    cin >> nusername;

                    int sum = 0;
                    for (char c : nusername) {
                        sum += c;
                    }

                    int index = hashex_login.hash(sum);
                    //UserNode* temp = hashex_login.table[index];
                    LinkedList<UserNode>::accessnode* temp = hashex_login.buckets[index].head;
                    flag = false;
                    while (temp != nullptr) {
                        if (nusername == temp->OG_NODE->getUsername()) {
                            cout << "This username is already taken. Please try another.\n";
                            flag = true;
                            break;
                        }
                        temp = temp->next;
                    }
                }

                cout << "Enter your password: \n";
                cin >> password;
                cout << "Enter your phone number: \n";
                cin >> phoneNumber;
                cout << "Enter your address: \n";
                cin >> address;

                while (true) {
                    cout << "Do you want your account to be private?\n[1] Yes\n[2] No\n";
                    short x;
                    cin >> x;
                    if (x == 1) {
                        priv = true;
                        break;
                    }
                    else if (x == 2) {
                        priv = false;
                        break;
                    }
                    else {
                        cout << "Invalid choice. Please enter 1 or 2.\n";
                    }
                }

                UserNode* user = new UserNode(fname, lname, nusername, password, priv, address, phoneNumber);

                
            }
            

           

            void Graph::UserNode::people_you_may_know()
            {
                 Vector<string> aywa =mutual_friends();

                
                 int back =99;
                 while (back != -1) {
                     for (int i = 0; i < aywa.getSize(); i++) {
                         cout << i + 1 << "-" << aywa[i] << endl;

                     }
                     cout << "choose index to act on \n [-1]Back" << endl;
                     cin >> back;
                     if (back == -1)
                     {
                         return;
                     }
                     else if(back>aywa.getSize()||back<=0){
                         cout << "INVALID INDEX" << endl;

                     }
                     else {
                        
                         searchByUsername(aywa[back - 1]);

                        
                        
                         
                     }
                 }
            }

            Vector<string> Graph::UserNode::mutual_friends()
            {

                Vector<pair<int, string>> pair_vector;
                Vector<string> visited;
                LinkedList<UserNode>::accessnode* temp1 = friends.head;
                LinkedList<UserNode>::accessnode* temp2;
                pair< int,string> pairNode;
                while (temp1 != nullptr) {
                    temp2 = temp1->OG_NODE->friends.head;
                    while (temp2 != nullptr) {
                       
                       
                       
                        if (temp2->OG_NODE != this && !(temp2->OG_NODE->searchfriends(this->getUsername())) && !(temp2->OG_NODE->searchrequests(this->getUsername())) && !(this->searchrequests(temp2->OG_NODE->getUsername()))) {
                            
                            if (!visited.contains((temp2->OG_NODE->getUsername()))) {
                              
                                visited.push_back(temp2->OG_NODE->getUsername());
                              
                                
                                pairNode.second=(temp2->OG_NODE->getUsername());
                               
                                pairNode.first=1;
                               
                               
                                pair_vector.push_back(pairNode);
                               

                            }
                            else {
                                for (int i = 0; i < pair_vector.getSize(); i++) {
                                    if (pair_vector[i].second == temp2->OG_NODE->getUsername()) {
                                       
                                        pair_vector[i].first=pair_vector[i].first + 1;
                                        break;

                                    }
                                    
                                }

                            }

                        }

                        temp2 = temp2->next;
                        
                       
                    }
                    temp1 = temp1->next;
                    
                }
               
                PriorityQueue<pair<int,string>> priority;
                Vector <string> to_be_returned;
                for (int i = 0; i < pair_vector.getSize(); i++) {
                    priority.push(pair_vector[i]);
                }
                pair_vector.clear();
                while (!priority.empty()) {
                    to_be_returned.push_back(priority.top().second);
                    priority.pop();
                }
                for (int i = 0; i < to_be_returned.getSize(); i++) {
                    cout<<i+1 <<"-" << to_be_returned[i] << endl;
                }
                cout << "bykhalas" << endl;
                return to_be_returned;
                
            }
            // Updated mutual_friends() method
            //Vector<Graph::UserNode> Graph::UserNode::mutual_friends() {
            //    Vector<Pair<UserNode, int>> pair_vector;
            //    Vector<UserNode> visited;
            //    LinkedList<UserNode>::accessnode* temp1 = friends.head;
            //    LinkedList<UserNode>::accessnode* temp2 = nullptr;  // Initialize temp2
            //
            //    Pair<UserNode, int> pairNode;
            //
            //    while (temp1 != NULL) {
            //        // Ensure temp1 and its associated members are not NULL
            //        if (temp1->OG_NODE != NULL && temp1->OG_NODE->friends.head != NULL) {
            //            temp2 = temp1->OG_NODE->friends.head;
            //        }
            //        else {
            //            temp1 = temp1->next;
            //            continue;  // Skip to the next temp1 node if current one is invalid
            //        }
            //
            //        while (temp2 != NULL) {
            //            // Ensure temp2 and its associated members are not NULL
            //            if (temp2->OG_NODE != NULL) {
            //                cout << "carolll1   ";
            //                cout << "temp2->OG_NODE: " << temp2->OG_NODE->getUsername() << endl;
            //                cout << "searchfriends: " << temp2->OG_NODE->searchfriends(this->getUsername()) << endl;
            //                cout << "searchrequests: " << temp2->OG_NODE->searchrequests(this->getUsername()) << endl;
            //                cout << "this->searchrequests: " << this->searchrequests(temp2->OG_NODE->getUsername()) << endl;
            //
            //                // Check mutual friends condition with additional null checks
            //                if (temp2->OG_NODE != this &&
            //                    !(temp2->OG_NODE->searchfriends(this->getUsername())) &&
            //                    !(temp2->OG_NODE->searchrequests(this->getUsername())) &&
            //                    !(this->searchrequests(temp2->OG_NODE->getUsername()))) {
            //
            //                    cout << "carolll9     ";
            //                    // Check if the friend is not already in the visited list
            //                    if (!visited.contains(*(temp2->OG_NODE))) {
            //                        visited.push_back(*(temp2->OG_NODE));
            //
            //                        // Create a new pair and add to the pair vector
            //                        pairNode.setFirst(*(temp2->OG_NODE));
            //                        pairNode.setSecond(1);
            //                        pair_vector.push_back(pairNode);  // Safe push_back
            //                    }
            //                    else {
            //                        // If the friend is already visited, increment the counter
            //                        bool found = false;
            //                        for (int i = 0; i < pair_vector.getSize(); i++) {
            //                            // Ensure vector access is safe
            //                            if (pair_vector[i].getFirst() == *(temp2->OG_NODE)) {
            //                                pair_vector[i].setSecond(pair_vector[i].getSecond() + 1);
            //                                found = true;
            //                                break;
            //                            }
            //                        }
            //
            //                        // If no match was found, create a new pair
            //                        if (!found) {
            //                            pairNode.setFirst(*(temp2->OG_NODE));
            //                            pairNode.setSecond(1);
            //                            pair_vector.push_back(pairNode);
            //                        }
            //                    }
            //                }
            //            }
            //
            //            temp2 = temp2->next;
            //            cout << "Updated temp2 to the next node." << endl;
            //        }
            //        temp1 = temp1->next;
            //        cout << "Updated temp1 to the next node." << endl;
            //    }
            //
            //    // Push elements into the priority queue
            //    PriorityQueue<Pair<UserNode, int>> priority;
            //    Vector<UserNode> to_be_returned;
            //
            //    for (int i = 0; i < pair_vector.getSize(); i++) {
            //        priority.push(pair_vector[i]);
            //    }
            //
            //    // Clear the vector and return sorted friends based on priority
            //    pair_vector.clear();
            //    while (!priority.empty()) {
            //        to_be_returned.push_back(priority.top().getFirst());
            //        priority.pop();
            //    }
            //
            //    return to_be_returned;
            //}



            Vector<Graph::UserNode> Graph::UserNode::degree()
            {
                return Vector<Graph::UserNode>();
            }

            Vector<Graph::UserNode> Graph::UserNode::randomized()
            {
                return Vector<Graph::UserNode>();
            }

            bool operator==(const Graph::UserNode & lhs, const Graph::UserNode & rhs) {

                return lhs.username == rhs.username;

            }
            std::ostream& operator<<(std::ostream & os, const Graph::UserNode & user) {
                os << "Username: " << user.username;
                return os;
            }

           

            
