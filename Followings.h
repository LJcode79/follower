#ifndef FOLLOWINGS_H
#define FOLLOWINGS_H
#include <string>
using namespace std;

struct Node {
  string username;
  Node* prev; //points to the Node object before the current Node
  Node* next; //points to the Node object after the current Node
};

class Followings {
  private:
    Node* head_;  //points to the first Node
    Node* tail_;  //points to the last Node
    void copy(const Followings&); 
    void clear();  
  public:
    Followings(); //provided
    Followings(const Followings&); //provided
    ~Followings();  //provided

    //mutators
    bool addFollowing(const string&);
    bool unFollow(const string&);
    Followings& operator=(const Followings&);

    //accessors
    string getFollowing(const string& key) const;
    void display() const;
};

#endif