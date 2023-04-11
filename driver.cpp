/**
 * Start of a driver file to test orgtree.cpp
 * CS 210/496 Summer 2022
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date June 2022
 */

//Name: Maxine Mayor
//Red ID: 825551461

#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void assert(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */

    Employee *head = new Employee(1, vector<int>{2, 3, 4});
    Employee *e2 = head->getDirectReports().at(0);
    Employee *e3 = head->getDirectReports().at(1);
    Employee *e4 = head->getDirectReports().at(2);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    Employee *e5 = e2->getDirectReports().at(0);
    Employee *e6 = e2->getDirectReports().at(1);
    Employee *e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);

    // Begin Testing
    
    // IMPORTANT: You should also construct at aleast one different chart 
    // Also make sure to check edge cases, such as empty chart, or one employee chart.

    // Test isEmployeePresentInOrg function
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 1); //test head node
    assert(employeePresent, "ID 1 Present in tree");
    
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 9); //test a normal node
    assert(employeePresent, "ID 9 Present in tree");

    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2); //test negative node
    assert(employeePresent == false, "ID -2 Not present in tree");
    
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 13); //test non existent node
    assert(employeePresent == false, "ID 13 Not present in tree");

    // Test findEmployeeLevel function
    int employeeLevel = Orgtree::findEmployeeLevel(head, 1, 0); //test head node
    assert(employeeLevel == 0, "Level of ID 1 returns " + to_string(employeeLevel) + ", expected 0");
    
    employeeLevel = Orgtree::findEmployeeLevel(head, 3, 0); //test level 1
    assert(employeeLevel == 1, "Level of ID 3 returns " + to_string(employeeLevel) + ", expected 1");

    employeeLevel = Orgtree::findEmployeeLevel(head, 6, 0); //test level 2
    assert(employeeLevel == 2, "Level of ID 6 returns " + to_string(employeeLevel) + ", expected 2");

    employeeLevel = Orgtree::findEmployeeLevel(head, 10, 0); //test level 3
    assert(employeeLevel == 3, "Level of ID 10 returns " + to_string(employeeLevel) + ", expected 3");

    employeeLevel = Orgtree::findEmployeeLevel(head, -5, 0); //test negative node
    assert(employeeLevel == -1, "Level of ID -5 returns " + to_string(employeeLevel) + ", expected -1");

    employeeLevel = Orgtree::findEmployeeLevel(head, 13, 0); //test non existent node
    assert(employeeLevel == -1, "Level of ID 13 returns " + to_string(employeeLevel) + ", expected -1");

    //Test findClosestSharedManager function
    Employee *manager = Orgtree::findClosestSharedManager(head, 8, 8); //test both nodes are the same
    assert(manager->getEmployeeID() == 8, "Closest managers between 8 and 8 returns " + to_string(manager->getEmployeeID()) + ", expected 8");
    
    manager = Orgtree::findClosestSharedManager(head, 8, 15); //test one node does not exist
    assert(manager->getEmployeeID() == -1, "Closest manager between 8 and 15 returns " + to_string(manager->getEmployeeID()) + ", expected -1");

    manager = Orgtree::findClosestSharedManager(head, 54, 91); //test both nodes do not exist
    assert(manager->getEmployeeID() == -1, "Closest manager between 54 and 91 returns " + to_string(manager->getEmployeeID()) + ", expected -1");
    
    manager = Orgtree::findClosestSharedManager(head, 4, 9); //test 4,9
    assert(manager->getEmployeeID() == 4, "Closest manager between 4 and 9 returns " + to_string(manager->getEmployeeID()) + ", expected 4");
    
    manager = Orgtree::findClosestSharedManager(head, 5, 2); //test 5,2
    assert(manager->getEmployeeID() == 2, "Closest manager between 5 and 2 returns " + to_string(manager->getEmployeeID()) + ", expected 2");
    
    manager = Orgtree::findClosestSharedManager(head, 1, 6); //test if one of the nodes is the root
    assert(manager->getEmployeeID() == 1, "Closest manager between 1 and 6 returns " + to_string(manager->getEmployeeID()) + ", expected 1");
    
    manager = Orgtree::findClosestSharedManager(head, 7, 1);//test if one of the nodes is the root but reversed
    assert(manager->getEmployeeID() == 1, "Closest manager between 7 and 1 returns " + to_string(manager->getEmployeeID()) + ", expected 1");
    
    manager = Orgtree::findClosestSharedManager(head, 2, -3); //test if negative node
    assert(manager->getEmployeeID() == -1, "Closest manager between 2 and -3 returns " + to_string(manager->getEmployeeID()) + ", expected -1");

    // Test findNumOfManagersBetween function
    int numManagers = Orgtree::findNumOfManagersBetween(head, 3, 3); //test if e1 and e2 are the same node
    assert(numManagers == 0, "Managers between 3 and 3 returns " + to_string(numManagers) + ", expected 0");

    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 1); //test if it is the head twice
    assert(numManagers == 0, "Managers between 1 and 1 returns " + to_string(numManagers) + ", expected 0");

    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 13); //test if one node doesn't exist in tree
    assert(numManagers == -1, "Managers between 1 and 13 returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 15, 17); //test if both nodes don't exist in tree
    assert(numManagers == -1, "Managers between 15 and 17 returns " + to_string(numManagers) + ", expected -1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 12, 6); //test 12, 6
    assert(numManagers == 4, "Managers between 12 and 6 returns " + to_string(numManagers) + ", expected 4");

    numManagers = Orgtree::findNumOfManagersBetween(head, 12, 8); //test 12, 8
    assert(numManagers == 4, "Managers between 12 and 8 returns " + to_string(numManagers) + ", expected 4");

    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 5); //test if one of the nodes is the head
    assert(numManagers == 1, "Managers between 1 and 5 returns " + to_string(numManagers) + ", expected 1");

    numManagers = Orgtree::findNumOfManagersBetween(head, 9, 1); //test if one of the nodes is the head
    assert(numManagers == 1, "Managers between 9 and 1 returns " + to_string(numManagers) + ", expected 1");

    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree. 

    Orgtree::deleteOrgtree(head);

    // Use the printed employee ID along the sequence of deletion to verify your implementation
    // This part will be autograded as well as manually inspected for grading

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}