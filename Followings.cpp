#include <string>
#include <iostream>
#include <string.h> //for strcmpi
#include "Followings.h"
using namespace std;

Followings::Followings() {
  this->head_ = this->tail_ = nullptr;
}

//rule of three
Followings::Followings(const Followings& original){
  cout << "copying ... ";
  this->copy(original);
  cout << " done." << endl;
}

Followings::~Followings(){
  cout << "destructor invoked:\n";
  this->display();
  this->clear();
}

Followings& Followings::operator=(const Followings& original){
  this->clear();
  cout << "copying ... ";
  this->copy(original);
  cout << " done." << endl;
  return *this;
}

void Followings::copy(const Followings& original) {
  Node *sPtr = original.head_;
  this->head_ = this->tail_ = nullptr;
  if(original.head_->username == original.tail_->username){//if source sequence has 1 node
    this->head_ = this->tail_ = new Node{original.head_->username, nullptr, nullptr};
    cout << this->head_->username << " ";
  }
  else{
    while(sPtr != nullptr){
      Node *temp = new Node{sPtr->username,nullptr,nullptr};
      if(this->head_ == nullptr){//Copying first node
        this->head_ = this->tail_ = temp;
      }
      else{//Copying nodes after first
        this->tail_->next = temp;
        this->tail_->next->prev = this->tail_;
        this->tail_ = temp;
      }
      cout << sPtr->username << " ";
      sPtr = sPtr->next; 
    }
  }
} //end of copy

void Followings::clear() {
  if(this->head_->username!=""){
  cout << "releasing ... ";
  Node* ptr = this->head_;
    while(ptr != nullptr){
      cout << ptr->username << " ... ";
      ptr = ptr->next;
      delete this->head_;
      this->head_ = ptr;
    }
    cout << " done" << endl;
  }
} //end of clear

void Followings::display() const {
  if (this->head_->username != ""){
    cout << "List content, forward: ";
    Node* ptr = this->head_;
    while(ptr!=nullptr){
      cout<<ptr->username << "   ";
      ptr = ptr->next;
    }
    cout << endl;
    cout << "List content, backward: ";
    Node* ptrB = this->tail_;
    while(ptrB!=nullptr){
      cout<<ptrB->username << "   ";
      ptrB = ptrB->prev;
    }
    cout << endl;
  }
  else{
    cout << "The list is currently empty." << endl;
  }
} //end of display

//mutators
bool Followings::addFollowing(const string& s){
  Node* ptr = this->head_;
  if ((this->head_ == nullptr) && (this->tail_ == nullptr)){//Dealing with no element
    this->tail_ = this->head_ = new Node{s,nullptr,nullptr};
    return true;
  }
  else if(this->head_->next == nullptr) {//Dealing with one element
    if(s < this->head_->username){
      this->head_ = new Node{s,nullptr,ptr};
      this->tail_->prev = this->head_;
      return true;
    } 
    else if(this->head_->username == s){
         cout << "Error: " << s << " is already in the following list. " << endl;
         return false;
    }
    else{
      this->head_->next = new Node{s,this->head_, nullptr};
      this->tail_ = this->head_->next;
      return true;
    }
  }
  else{//Dealing with multiple elements
    if(s < this->head_->username){//adding s to the beginning of a list of elements
      this->head_->prev = new Node{s,nullptr,this->head_};
      this->head_ = this->head_->prev;
      return true;
    }
    else if(s > this->tail_->username){//adding s to the end of a list of elements
      this->tail_->next = new Node{s,this->tail_,nullptr};
      this->tail_ = this->tail_->next;
      return true;
    }
    else{//adding s to the middle of a list of elements
      Node* ptr = this-> head_; 
      while(s > ptr->username){
        ptr = ptr->next;
      }
      if(s == ptr->username){
          cout << "Error: " << s << " is already in the following list. " << endl;
          return false;
      }
      else{
      Node* temp = ptr->prev;
      ptr->prev = new Node{s, temp, ptr};
      temp->next = ptr->prev;
      return true;
      }
    }
  } 
  return false;
}

bool Followings::unFollow(const string& s){
  Node* ptr = this->head_;
  if((s == this->head_->username) && (this->tail_!= this->head_)){//Unfollow first user
  ptr = ptr->next;
  ptr->prev = nullptr;
  delete this->head_;
  this->head_ = ptr;
  return true;
  }
  else if((s == this->tail_->username) && (this->tail_!= this->head_)){//unfollow last user
    ptr = this->tail_->prev;
    ptr->next = nullptr;
    delete this->tail_;
    this->tail_ = ptr;
    return true;
  }
  else if((this->head_->username == s) && (this->tail_->username == s)){//unfollow only user
    delete this->head_;
    this->head_ = this->tail_ = new Node{"",nullptr, nullptr};
    return true;
  }
  else if((s > this->head_->username) && (s < this->tail_->username)){//unfollow user in middle
    ptr = this->head_;
    while((ptr->username!=s) && (ptr->next!=nullptr)){
      ptr = ptr->next;
    }
    if(ptr->next == nullptr){
      cout << "Error, name not in list" << endl;
      return false;
    }
    else{
      ptr->next->prev = ptr->prev;
      ptr->prev->next = ptr->next;
      delete ptr;
      return true;
    }
  }
  else{
    cout << "Error, name not in list" << endl;
    return false;
  }
  return false;
}

string Followings::getFollowing(const string& key) const{
  Node *ptr = this->head_;
  string s = "";
  while(ptr!=nullptr){
    if((ptr->username).find(key)!=string::npos){
      s=s+(ptr->username)+" ";
    }
    ptr=ptr->next;
  }
  if(s==""){
    return "No Match";
  }
  else{
    return s;
  }
}