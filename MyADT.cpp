/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 * 
 * Class Invariant: Data collection with the following characteristics:
 *                  - This is a value-oriented data collection and 
 *                    the elements are kept in ascending sort order of search key.
 *                  - Each element is unique (no duplicates). 
 *                  - Its data structure (CDT) is not expandable. This signifies that 
 *                    when this data collection becomes full, you do not have to resize 
 *                    its data structure (not in this Assignment 1). 
 *
 * Author: AL and David Xia 301464095
 * Last modified on: Feb.2 2024
 */


#include <iostream>
#include <cctype>
#include "MyADT.h"     // Header file of MyADT file
#include "Profile.h"   // Header file of Profile class

using std::cout;
using std::endl;

    
// Default constructor.
MyADT::MyADT() {
   // cout << "MyADT::default constructor executed!" << endl;   // For testing purposes ...
   // You can also use the above to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
 
   /* Put your code here */
   // Allocating memory for each element array slot.
    for(int i = 0; i < MAX_ALPHA; i++){
      elements[i] = new Profile[MAX_ELEMENTS];
      elementCount[i] = 0;
   }
}  // end of default constructor

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   // cout << "MyADT::copy constructor executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

   /* Put your code here */
   // Creates a 2D array that is same as original with 26 slots and 5 slots in each of the 26.
   for(int i = 0; i < MAX_ALPHA; i ++){
      elements[i] = new Profile[MAX_ELEMENTS];
      elementCount[i] = rhs.elementCount[i];
      for(int j = 0; j < elementCount[i]; j++){
         elements[i][j] = rhs.elements[i][j];
      }
   }
   
}  // end of copy constructor

// Overloaded assignment operator - Covered in Lab 5
// Therefore, we shall not be overloading this operator in our Assignment 1
// MyADT & MyADT::operator=(const MyADT& rhs) {
   // cout << "MyADT::operator= executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this overloaded assignment = operator is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
   
   /* Put your code here */

//}
    
// Destructor
// Description: Destroys this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   // cout << "MyADT::destructor" << endl;  // For testing purposes ...
   // You can also use the above to figure out when this destructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
  
   /* Put your code here */
    for(int i = 0; i < MAX_ALPHA; i++){
      delete[] elements[i];
   } 
}  // end of destructor


// Description: Returns the total number of elements currently stored in the data collection MyADT.  
unsigned int MyADT::getElementCount() const {

    /* Put your code here */
    int count = 0;
    for(int i = 0; i < MAX_ALPHA; i++){
       count += elementCount[i];
    }
    return count;

} // end of getElementCount


// Description: Inserts an element in the data collection MyADT.
// Precondition: newElement must not already be in the data collection MyADT.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
//                Returns "true" when the insertion is successfull, otherwise "false".
bool MyADT::insert(const Profile& newElement) {
 
   /* Put your code here */
    int index = int(tolower(newElement.getSearchKey()))-97;

   // If there are too many profiles with the same username first letter and the username of newElement is this letter, return false.
    if (elementCount[index] >= MAX_ELEMENTS){
        cout << "Failed to join FriendsBook, MAX_ELEMENTS exceeded." << endl;
        return false;
    }

   // If there exists a profile with the same username as newElement, return false.
    if(search(newElement) != nullptr){
        cout << "Failed to join FriendsBook, profile already exists." << endl;
        return false;
    }

    int insertAt = elementCount[index];

   // If the newElement is the first element in elements[index], insert immediately.
    if(insertAt == 0){
        elements[index][insertAt] = newElement;
        elementCount[index]++;
    }

    /* Otherwise, iterate backwards through elements at the index that matches newElement's username first letter
    * If last element is alphabetically before newElement on current index, the insertion index will be the index of
    * the last element.
    */
    else{
        for(int i = insertAt; i > 0; i--){
            Profile thisElement = elements[index][i-1];
            if(thisElement > newElement){
                insertAt = i-1;
                break;
            }
        }


        // Shift every element after the insertion point one index to the right.
        for(int i = MAX_ELEMENTS-1; i > insertAt; i--){
            elements[index][i] = elements[index][i-1];
        }

        // Insert newElement into the array.
        elements[index][insertAt] = newElement;
        elementCount[index]++;
   }

   
   return true;
   
}  // end of insert

// Description: Removes an element from the data collection MyADT. 
// Postcondition: toBeRemoved (if found) is removed and the appropriate elementCount is decremented.
//                Returns "true" when the removal is successfull, otherwise "false".  
bool MyADT::remove(const Profile& toBeRemoved) {

   /* Put your code here */
    int index = int(tolower(toBeRemoved.getSearchKey()))-97;
    int removalIndex = -1;

    // Iterating through elements to find toBeRemoved. If toBeRemoved is found, track index and remove that index from array.
    for(int i = 0; i < elementCount[index]; i++){
        if(elements[index][i] == toBeRemoved){
            removalIndex = i;
            break;
        }
    }

    // If not found, print error message.
    if(removalIndex == -1) {
        cout << "Failed to remove profile, profile not found." << endl;
        return false;
    }

    // Iterate over elements to move them up.
    for(int i = removalIndex; i < elementCount[index]; i++){
        elements[index][i] = elements[index][i+1];
    }

    elementCount[index]--;
    cout << "Profile successfully removed." << endl;
    return true;
   
}  // end of remove


// Description: Removes all elements from the data collection MyADT. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
void MyADT::removeAll() {
    
    /* Put your code here */
    for(int i = 0; i < MAX_ALPHA; i++){
        delete[] elements[i];
        elements[i] = nullptr;
   }

}   // end of removeAll

// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {
    
    /* Put your code here */
    int index = int(tolower(target.getSearchKey()))-97;

    // Iterating through elements[elementCount][index] to find the target. If the target is not found, return nullptr.
    for(int i = 0; i < elementCount[index]; i++){
        if(elements[index][i] == target){
            return &elements[index][i];
        }
    }
    return nullptr;

}  // end of search


// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
void MyADT::print() {
  
    /* Put your code here */  
    for(int i = 0; i < MAX_ALPHA; i++){
        for(int j = 0; j < elementCount[i]; j++){
            cout << elements[i][j];
        }
    }

} // end of print

//  End of implementation file