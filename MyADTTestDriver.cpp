/*
 * MyADTTestDriver.cpp
 *
 * Class Description: A test driver for the MyADT class.
 * 
 * Author: David Xia 301464095
 * Last modified on: Feb.2 2024 by David Xia 301464095
 */


#include <iostream>
#include <string>
#include <cctype>
#include "Profile.h"
#include "MyADT.h"

using namespace std;

int main(){

    // MyADT object that will be storing future profile objects.
    MyADT fbMembers = MyADT();

    /*
    Testing the joining of members.
    Expected output:

        beep, tbd, tbd, born on tbd
        boom, tbd, tbd born on tbd
        boop, Robot, BoopBoop@gmail.com born on January 1, 2000
        lie, tbd, tbd born on tbd
        sadCoder, David Xia, dgx1@sfu.ca born on December 12, 2003
        soda, tbd, tbd born on tbd

    */

    // Creating profile objects to add to fbMembers
    Profile Boom("boom");
    Profile Beep("beep");
    Profile Boop("boop", "Robot", "BoopBoop@gmail.com", "January 1, 2000");
    Profile David("sadCoder", "David Xia", "dgx1@sfu.ca", "December 12, 2003");
    Profile watermelon("soda");
    Profile NF("lie");

    /*
    Testing getElementCount
    Expected output:
        0
    */

    int count = fbMembers.getElementCount();
    cout << "The number of fbMembers = " << count << endl;

    /*
    Testing inserting members
    Expected output: Nothing cause no prints
    */
    fbMembers.insert(Boom);
    fbMembers.insert(Beep);
    fbMembers.insert(Boop);
    fbMembers.insert(David);

    cout << "Adding profiles" << endl;
    fbMembers.print(); // Prints the list of all FriendsBook members.
    cout << endl;

    /*
    Testing getElementCount
    Expected output:
        4
    */

    count = fbMembers.getElementCount();
    cout << "The number of fbMembers = " << count << endl;

    fbMembers.insert(watermelon);
    fbMembers.insert(NF);


    /*
    Trying to insert a profile that is already existing, or a new profile with the same username as an existing profile.
    Expected output:
        Failed to join FriendsBook, profile already exists.
        Failed to join FriendsBook, profile already exists.
    */

   cout << "Inserting a profile that exists already" << endl;
   fbMembers.insert(David);

   Profile Laptop("boom", "Macbook Pro", "macbook@gmail.com", "January 2, 2000");
   fbMembers.insert(Laptop);

   cout << endl;

//     /*
//     Trying to exceed MAX_ELEMENTS
//     MAX_ELEMENTS = 5

//         Expected output:
//         Failed to join FriendsBook, MAX_ELEMENTS exceeded.
//         a, tbd, tbd born on tbd
//         ab, tbd, tbd born on tbd
//         abc, tbd, tbd born on tbd
//         abcd, tbd, tbd born on tbd
//         abcde, tbd, tbd born on tbd
//         boom, tbd, tbd born on tbd
//         beep, tbd, tbd, born on tbd
//         boop, Robot, BoopBoop@gmail.com born on January 1, 2000
//         sadCoder, David Xia, dgx1@sfu.ca born on December 12, 2003
//         watermelon, Soda, tbd, tbd born on tbd
//         lie, tbd, tbd born on tbd
//     */

    cout << "Exceeding MAX_ELEMENTS" << endl;
    Profile prof1("a");
    Profile prof2("ab");
    Profile prof3("abc");
    Profile prof4("abcd");
    Profile prof5("abcde");
    Profile prof6("abcdefghijklmn");

    fbMembers.insert(prof1);
    fbMembers.insert(prof2);
    fbMembers.insert(prof3);
    fbMembers.insert(prof4);
    fbMembers.insert(prof5);
    fbMembers.insert(prof6);

    cout << endl;
    fbMembers.print();
    cout << endl;


//     /*
//     Testing the searching of profiles.
//     Expected output:
//         boom, tbd, tbd born on tbd
//         boop, Robot, BoopBoop@gmail.com born on January 1, 2000

//     */

    cout << "Searching for profiles" << endl;
    cout << *fbMembers.search(Boom);
    cout << *fbMembers.search(Boop);
    cout << endl;

//     /*
//     Testing the removal of profiles.
//     Expected output:
//         Profile successfully removed.
//         a, tbd, tbd born on tbd
//         ab, tbd, tbd born on tbd
//         abc, tbd, tbd born on tbd
//         abcd, tbd, tbd born on tbd
//         abcde, tbd, tbd born on tbd

//         Failed to remove profile, profile not found.
//     */
    
    cout << "Removing profiles" << endl;
    fbMembers.remove(David);
    fbMembers.print();
    cout << endl;

    fbMembers.remove(David);
    cout << endl;

//     /*
//     Checking to see that the search method will return a nullptr when searching for a removed profile.
//     Expected value:
//         nullptr
//     */
    cout << "Checking for search nullptr" << endl;
    if(fbMembers.search(David) == nullptr) cout << "nullptr" << endl;
    cout << endl;

//     /*
//     Testing the modification of profiles.
//         -> Modifying name, email, and birthday
//     Expected output:
//         a, tbd, tbd born on tbd
//         ab, tbd, tbd born on tbd
//         abc, tbd, tbd born on tbd
//         abcd, tbd, tbd born on tbd
//         abcde, tbd, tbd born on tbd
//         beep, beep2, tbd, tbd, born on tbd
//         lie, tbd, tbd born on March 30, 1991
//         soda, tbd, watermelon@gmail.com born on tbd
//     */

    (fbMembers.search(Beep))->setName("beep2");
    (fbMembers.search(watermelon))->setEmail("watermelon@gmail.com");
    (fbMembers.search(NF))->setBirthday("March 30, 1991");
    
    cout << "Modifying profiles" << endl;
    fbMembers.print();
    cout << endl;

//     /*
//     Testing the removeAll method.
//     */

    cout << "Removing all" << endl;
    fbMembers.removeAll();

    return 0;

} // end of MyADTTestDriver