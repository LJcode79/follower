/* 
 * Name: Lawrence John Balanza
 * Course: CS 211
 * Date: 11/13/2021
 * Project 4: Followings
 * Description: Manage the followings of one social media account using a doubly-linked sorted list according to the alphabetical order of the usernames.
*/
#include <iostream>
#include <string>
#include <fstream>
#include "Followings.h"
using namespace std;

int main() {
  Followings spongebob;
  string action, target, rationale;
  ifstream input("testcases.csv");
  if (!input.is_open()) {
    cout << "Input file not ready.\n";
    return 1;
  }

  cout << boolalpha;
  while (!input.eof()) {
    getline(input, action, ',');
    getline(input, target, ',');
    getline(input, rationale);
    cout << "Testing " << rationale << " with " << target;
    cout << " returns ";    
    if (action == "Following") {
      cout << spongebob.addFollowing(target) << endl;
      spongebob.display();
    } else if (action == "Unfollow") {
      cout << spongebob.unFollow(target) << endl;
      spongebob.display();
    } else if (action == "Search") {
      cout << endl << spongebob.getFollowing(target)<<endl;
    }
  } //end of while
  cout << "\nEnd of testing from the testcase file.\n";
  spongebob.display();

  cout << "================ Testing rule of 3 ================" << endl << endl;

  cout << "Creating list 1" << endl;
  Followings list1;
  cout << "Following Katara" << endl;
  list1.addFollowing("Katara");
  cout << "Following Sokka" << endl;
  list1.addFollowing("Sokka");
  cout << "Following Aang" << endl;
  list1.addFollowing("Aang");
  list1.display();

  cout << endl << "Creating list 2" << endl;
  Followings list2;
  cout << "Following Westbrook" << endl;
  list2.addFollowing("Westbrook");
  cout << "Following Anthony" << endl;
  list2.addFollowing("Anthony");
  cout << "Following James" << endl;
  list2.addFollowing("James");
  list2.display();
  cout << endl;

  //Followings list3;
  cout << "Copying list 2 into an empty list " << endl;
  Followings list3(list2);
  list3.display();
  cout << endl;

  cout << "list2 before: " << endl;
  list2.display();
  list2 = list1;
  cout << "list2 after: " << endl;
  list2.display();
  cout << endl << "================ Testing rule of 3 end ================" << endl << endl;
  return 0;

}
