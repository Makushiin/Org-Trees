#include "orgtree.h"
#include <algorithm>
#include<iostream>
//Single Programmer Affidavit
//I the undersigned promise that the submitted assignment is my own work. While I was 
//free to discuss ideas with others, the work contained is my own. I recognize that 
//should this not be the case; I will be subject to penalties as outlined in the course 
//syllabus. 
//Name: Maxine Mayor
//Red ID: 825551461

/**
 * Check if an employee is present in an organization chart. 
 * 
 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false
 * @see         
 */
bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) { 
  // base case 1: empty organization chart, return false
  if (head == nullptr) { 
    return false;
  }

  // base case 2: if the employee is found, return true
  if (head -> getEmployeeID() == e_id) {
    return true;
  }

  // search employee from each child of the head
  // return true if the employee is found in one of the child subtree
  for (int i = 0; i < head -> getDirectReports().size(); i++) { //iterate through each directReport vector
    isEmployeePresentInOrg(head -> getDirectReports().at(i), e_id); 
    if (isEmployeePresentInOrg(head -> getDirectReports().at(i), e_id) == true) {
      return true;
    }
  }

  // if not found, return false
  return false;
}

/**
 * Find the level of an employee in an organization chart / tree. 
 * 
 * <p>
 * The head / root of the org chart has a level of 0, children of the head have
 * a level of head plus 1, and so on and so forth... 
 * 
 * <p>
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  head      the head / root Employee of the organization chart
 * @param  e_id      the employee id being searched
 * @param  headLevel the level of the head employee of the organization 
 * @return    level of the employee in the org chart
 *      returns Employee::NOT_FOUND if e_id is not present
 * @see         
 */
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {   
  // base case 1: empty organization chart
  if (head == nullptr || headLevel < 0) { 
    return Employee::NOT_FOUND;
  }

  // base case 2: the employee is found, returns the employee level
  if (head -> getEmployeeID() == e_id) {
    return headLevel;
  }

  int tempLevel = 0;

  // search employee from each child of the head
  for (int i = 0; i < head -> getDirectReports().size(); i++) { 
    tempLevel = findEmployeeLevel(head -> getDirectReports().at(i), e_id, headLevel + 1); 

    if (tempLevel != Employee::NOT_FOUND) { 
      return tempLevel; 
    }
  }

  // if not found
  return Employee::NOT_FOUND;
}

/**
 * Find the closest shared manager of two employees e1 and e2. 
 * 
 * <p>
 * There are two possible organizational relationships between two employees in the org chart:
 * case 1: e1 or e2 is a manager of the other employee; 
 * case 2: e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *
 * Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2 in the organization chart 
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   closest shared manager in the org chart between employee e1 and employee e2
 *               if e1 is present and e2 is not, returns e1
 *               if e2 is present and e1 is not, returns e2
 *               if neither e1 or e2 is present, returns empty employee
 * @see         
 */
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) { 
  // base case 1: empty organization chart
  if (head == nullptr) { 
    return NULL;
  }

  // base case 2: either e1_id or e2_id is the same as the head / root
  if(head -> getEmployeeID() == e1_id || head -> getEmployeeID() == e2_id) {
    return head;
  }

  int count = 0;
  Employee* temp = NULL;

  for(int i = 0; i < head -> getDirectReports().size(); i++) {
    Employee* manager = findClosestSharedManager(head -> getDirectReports().at(i), e1_id, e2_id);
    
    if(manager != NULL) {
      count++;
      temp = manager;
    }
  }

  if(count == 2) {
    return head;
  }

  return temp;
     
  return nullptr;
}


/**
 * Calculate the number of managers between employee e1 and employee e2. 
 * 
 * <p>
 * The number of managers between employee e1 and employee e2 can be calculated by: 
 *  number of edges between employee 1 and closest shared manager + 
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   number of managers between employee e1 and employee e2
 *           returns Employee::NOT_FOUND if either e1 or e2 is not present in the chart
 * @see         
 */
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {
  int distE1 = 0; //stores distance from closest manager to e1_id
  int distE2 = 0; //stores distance from closest manager to e2_id
  Employee* manager = nullptr;

  if(isEmployeePresentInOrg(head, e1_id) && isEmployeePresentInOrg(head, e2_id)) {//if both employees are in tree
    //finds closest manager and level of the manager
    manager = findClosestSharedManager(head, e1_id, e2_id); 
  }
  else {
    return Employee::NOT_FOUND; 
  }
    
  int managerID = manager -> getEmployeeID(); 
  int managerLevel = findEmployeeLevel(manager, managerID, 0);
  
  //find distance of e1 and e2 from closest manager
  distE1 = findEmployeeLevel(manager, e1_id, 0);
  distE2 = findEmployeeLevel(manager, e2_id, 0);

  //total distance
  int numManagers = distE1 + distE2 - 1;
  
  return numManagers;
  }

/** Recursively delete a tree 
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test. 
 * 
 * <p>
 * Starting from the head / root node, recursively deallocate 
 * the memory of the descendants. DO NOT worry about removing them from 
 * the vector directReports
 * 
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its employee ID and a new line
 *     This part will be autograded as well as manually inspected for grading
 * 
 * For example, with the following org chart, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root Employee of the organization chart
 * @return   None 
 * 
 * @see         
 */
void Orgtree::deleteOrgtree(Employee* head) { 
  // base case: empty tree or organization chart
  if (head == nullptr) { 
    return;
  }

  // delete children recursively
  if (!head -> getDirectReports().empty()) {
    for (int i = 0; i < head -> getDirectReports().size(); i++) {
      deleteOrgtree(head -> getDirectReports().at(i));
    }
  }
  
  cout << head -> getEmployeeID() << endl; // print current node's employee ID and a new line
  delete head; // delete the current node after deleting its children
  
}