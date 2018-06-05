// Some basic tests. Not full tests.
// DISCLAIMER: Make sure you add more tests to cover all edge cases. You can use this as a starting point.
// Note: this code does not create two BankData objects that exist at the same time. You should test this.

#include "BankData.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

void cleanupList(CSE250::dCustomerIDNode* head) {
    CSE250::dCustomerIDNode* tempNode = nullptr;
    if (head == nullptr) {
        return;
    }
    

    tempNode = head->_next;
    while (head != nullptr) {
        delete head;
        head = tempNode;
        if(head != nullptr) {
            tempNode = head->_next;
        }
    }
}

bool testCustomerAdd(size_t offset) {
    // BankData::add_customer // This would require the methods to be static, which they are not.

    size_t firstCustomerID = offset;
    size_t secondCustomerID = offset + 1;

    // Create a BankData object to perform actions.
    BankData bankInfo;
    bool opResult = false;

    if (bankInfo.customer_exists(firstCustomerID) || bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customers exist that were never added." << std::endl;
        return false;
    }

    // Add first customer.
    opResult = bankInfo.add_customer(firstCustomerID, 10000); // add a customer with starting balance 10,000.
    if (!opResult) {
        std::cerr << "add_customer returned false when adding a new customer (" << firstCustomerID << " ,10000)." << std::endl;
        return false;
    }

    // Add second customer.
    opResult = bankInfo.add_customer(secondCustomerID, 10000); // add a customer with starting balance 10,000.
    if (!opResult) {
        std::cerr << "add_customer returned false when adding a new customer (" << secondCustomerID << " ,10000)." << std::endl;
        return false;
    }

    // Add first customer again.
    opResult = bankInfo.add_customer(firstCustomerID); // add a customer with starting balance 0.
    if (opResult) {
        std::cerr << "add_customer returned true when adding a new customer (" << firstCustomerID << ") a second time." << std::endl;
        return false;
    }

    // Add second customer again.
    opResult = bankInfo.add_customer(secondCustomerID); // add a customer with starting balance 0.
    if (opResult) {
        std::cerr << "add_customer returned true when adding a new customer (" << secondCustomerID << ")    a second time." << std::endl;
        return false;
    }

    // Check that both customers are reported back to exist.
    if (bankInfo.customer_exists(firstCustomerID) && bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customers " << firstCustomerID << " and " << secondCustomerID << " successfully added." << std::endl;
        return true;
    }
    else if (bankInfo.customer_exists(firstCustomerID)) {
        std::cerr << "Customers " << firstCustomerID << " successfully added but customer " << secondCustomerID << " failed to be added." << std::endl;
    }
    else if (bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customer " << secondCustomerID << " successfully added but customer " << firstCustomerID << " failed to be added." << std::endl;
    }
    else {
        std::cerr << "Both customers " << firstCustomerID << " and " << secondCustomerID << " failed to be added." << std::endl;
    }
    return false;
}

bool testAddCustomerList(size_t offset) {
    size_t firstCustomerID = offset;
    size_t secondCustomerID = offset + 1;

    // Create a BankData object to perform actions.
    BankData bankInfo;
    bool opResult = false;

    if (bankInfo.customer_exists(firstCustomerID) || bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customers exist that were never added." << std::endl;
        return false;
    }

    // Create a list of customers and add them to the bank info.
    CSE250::dCustomerIDNode* customerList = nullptr;
    CSE250::dCustomerIDNode* tempNode = nullptr;

    // Create a node for the first customer to add.
    tempNode = new CSE250::dCustomerIDNode(firstCustomerID);

    // Put the first customer into the customer list.
    customerList = tempNode;

    // Create a second node under next for a second customer to add.
    tempNode = new CSE250::dCustomerIDNode(secondCustomerID);

    // Link up the second customer into the list.
    customerList->_next = tempNode;
    tempNode->_prev = customerList;

    opResult = bankInfo.add_customer(customerList);
    if (!opResult) {
        std::cerr << "add_customer returned false when adding a list of 2 new customers (" << firstCustomerID << " and " << secondCustomerID << ")." << std::endl;

        // Clean up list memory.
        cleanupList(customerList);

        // Good habit to nullify pointers, just in case we use them later.
        customerList = nullptr;
        tempNode = nullptr;

        // Test failed.
        return false;
    }

    if (bankInfo.customer_exists(firstCustomerID) && bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customers " << firstCustomerID << " and " << secondCustomerID << " successfully added." << std::endl;
        opResult = true;
    }
    else if (bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customer " << secondCustomerID << " successfully added but customer " << firstCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }
    else if (bankInfo.customer_exists(firstCustomerID)) {
        std::cerr << "Customer " << firstCustomerID << " successfully added but customer " << secondCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }
    else {
        std::cerr << "Both customers " << firstCustomerID << " and " << secondCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }

    // Clean up list memory.
    cleanupList(customerList);

    // Good habit to nullify pointers, just in case we use them later.
    customerList = nullptr;
    tempNode = nullptr;

    // return test result.
    return opResult;
}

bool testAddCustomerAddBoth(size_t offset) {
    // BankData::add_customer // This would require the methods to be static, which they are not.

    size_t firstCustomerID = offset;
    size_t secondCustomerID = offset + 1;
    size_t thirdCustomerID = offset + 2;
    size_t fourthCustomerID = offset + 3;

    // Create a BankData object to perform actions.
    BankData bankInfo;
    bool opResult = false;

    if (bankInfo.customer_exists(firstCustomerID) || bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customers exist that were never added." << std::endl;
        return false;
    }

    if (bankInfo.customer_exists(thirdCustomerID) || bankInfo.customer_exists(fourthCustomerID)) {
        std::cerr << "Customers exist that were never added." << std::endl;
        return false;
    }

    // Add first customer.
    opResult = bankInfo.add_customer(firstCustomerID, 10000); // add a customer with starting balance 10,000.
    if (!opResult) {
        std::cerr << "add_customer returned false when adding a new customer (" << firstCustomerID << " ,10000)." << std::endl;
        return false;
    }

    // Add second customer.
    opResult = bankInfo.add_customer(secondCustomerID, 10000); // add a customer with starting balance 10,000.
    if (!opResult) {
        std::cerr << "add_customer returned false when adding a new customer (" << secondCustomerID << " ,10000)." << std::endl;
        return false;
    }

    // Create a list of customers and add them to the bank info.
    CSE250::dCustomerIDNode* customerList = nullptr;
    CSE250::dCustomerIDNode* tempNode = nullptr;

    // Create a node for the first customer to add.
    tempNode = new CSE250::dCustomerIDNode(thirdCustomerID);

    // Put the first customer into the customer list.
    customerList = tempNode;

    // Create a second node under next for a second customer to add.
    tempNode = new CSE250::dCustomerIDNode(fourthCustomerID);

    // Link up the second customer into the list.
    customerList->_next = tempNode;
    tempNode->_prev = customerList;

    opResult = bankInfo.add_customer(customerList);
    if (!opResult) {
        std::cerr << "add_customer returned false when adding a list of 2 new customers (" << thirdCustomerID << " and " << fourthCustomerID << ")." << std::endl;

        // Clean up list memory.
        cleanupList(customerList);

        // Good habit to nullify pointers, just in case we use them later.
        customerList = nullptr;
        tempNode = nullptr;

        // Test failed.
        return false;
    }

    // Add first customer again.
    opResult = bankInfo.add_customer(firstCustomerID); // add a customer with starting balance 0.
    if (opResult) {
        std::cerr << "add_customer returned true when adding a new customer (" << firstCustomerID << ") a second time." << std::endl;

        // Clean up list memory.
        cleanupList(customerList);

        // Good habit to nullify pointers, just in case we use them later.
        customerList = nullptr;
        tempNode = nullptr;

        return false;
    }

    // Add second customer again.
    opResult = bankInfo.add_customer(secondCustomerID); // add a customer with starting balance 0.
    if (opResult) {
        std::cerr << "add_customer returned true when adding a new customer (" << secondCustomerID << ")    a second time." << std::endl;

        // Clean up list memory.
        cleanupList(customerList);

        // Good habit to nullify pointers, just in case we use them later.
        customerList = nullptr;
        tempNode = nullptr;

        return false;
    }

    opResult = bankInfo.add_customer(customerList);
    if (opResult) {
        std::cerr << "add_customer returned false when adding a list of 2 new customers (" << thirdCustomerID << " and " << fourthCustomerID << ")." << std::endl;

        // Clean up list memory.
        cleanupList(customerList);

        // Good habit to nullify pointers, just in case we use them later.
        customerList = nullptr;
        tempNode = nullptr;

        // Test failed.
        return false;
    }

    // Check that both customers are reported back to exist.
    if (bankInfo.customer_exists(firstCustomerID) && bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customers " << firstCustomerID << " and " << secondCustomerID << " successfully added." << std::endl;
        opResult = true;
    }
    else if (bankInfo.customer_exists(firstCustomerID)) {
        std::cerr << "Customers " << firstCustomerID << " successfully added but customer " << secondCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }
    else if (bankInfo.customer_exists(secondCustomerID)) {
        std::cerr << "Customer " << secondCustomerID << " successfully added but customer " << firstCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }
    else {
        std::cerr << "Both customers " << firstCustomerID << " and " << secondCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }


    if (bankInfo.customer_exists(thirdCustomerID) && bankInfo.customer_exists(fourthCustomerID)) {
        std::cerr << "Customers " << thirdCustomerID << " and " << fourthCustomerID << " successfully added." << std::endl;
        opResult = opResult && true;
    }
    else if (bankInfo.customer_exists(fourthCustomerID)) {
        std::cerr << "Customer " << fourthCustomerID << " successfully added but    customer " << thirdCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }
    else if (bankInfo.customer_exists(thirdCustomerID)) {
        std::cerr << "Customer " << thirdCustomerID << " successfully added but    customer " << fourthCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }
    else {
        std::cerr << "Both customers " << thirdCustomerID << " and " << fourthCustomerID << " failed to be added." << std::endl;
        opResult = false;
    }

    // Clean up list memory.
    cleanupList(customerList);

    // Good habit to nullify pointers, just in case we use them later.
    customerList = nullptr;
    tempNode = nullptr;

    // return test result.
    return opResult;
}

bool testCustomerGet(size_t offset) {
    // Create two customer IDs.
    std::vector<size_t> customerIDs{offset, offset + 1, offset + 2, offset + 3};
    std::vector<double> customerBalances{10000, 10000, 0, 0};

    // Create a BankData object to perform actions.
    BankData bankInfo;
    bool opResult = false;

    bankInfo.add_customer(customerIDs.at(0), customerBalances.at(0)); // add a customer with starting balance 10,000.

    bankInfo.add_customer(customerIDs.at(1), customerBalances.at(1)); // add a customer with starting balance 10,000.

    // Create a list of customers and add them to the bank info.
    CSE250::dCustomerIDNode* customerList = nullptr;
    CSE250::dCustomerIDNode* tempNode = nullptr;

    // Create a node for the first customer to add.
    tempNode = new CSE250::dCustomerIDNode(customerIDs.at(2));

    // Put the first customer into the customer list.
    customerList = tempNode;

    // Create a second node under next for a second customer to add.
    tempNode = new CSE250::dCustomerIDNode(customerIDs.at(3));

    // Link up the second customer into the list.
    customerList->_next = tempNode;
    tempNode->_prev = customerList;

    bankInfo.add_customer(customerList);


    opResult = true;
    for (size_t index = 0; index < 4; ++index) {
        // Check the customer at index was found.

        const size_t customerID = customerIDs.at(index);
        const double customerBalance = customerBalances.at(index);
        const Customer& tempCustomer = bankInfo.get_customer_data(customerID);

        if (tempCustomer._customer_id == customerID && tempCustomer._account_balance == customerBalance) {
            std::cerr << "Customer " << customerID << " successfully retrieved." << std::endl;
            opResult = opResult && true;
        }
        else {
            std::cerr << "Failed to retrieve customer " << customerID << "." << std::endl;
            opResult = false;
        }
    }

    // Clean up list memory.
    cleanupList(customerList);

    // Good habit to nullify pointers, just in case we use them later.
    customerList = nullptr;
    tempNode = nullptr;

    return opResult;
}

void testOutcome(bool pass, string function){
    if(pass){
        std::cout << function + ": PASS" << std::endl;
    }
    else{
        std::cout << function + ": FAIL" << std::endl;
    }
}

void myTestAllCase(){
    BankData* bank = new BankData();
    for(int i=0; i<10; ++i){
        testOutcome((*bank).add_customer(i,10*i), "add_customer with vaild member");
    }
    testOutcome((*bank).remove_customer((size_t)0), "Remove single vaild Customer");
    testOutcome(!(*bank).remove_customer((size_t)0), "Remove single invaild Customer");
    CSE250::dCustomerIDNode node(1);
    CSE250::dCustomerIDNode node2(2);
    node._next = &node2;
    testOutcome((*bank).remove_customer(&node), "Remove list of vaild Customer");
    testOutcome(!(*bank).remove_customer(&node), "Remove list of invaild Customer");
    testOutcome((*bank).add_transaction(3,0,10), "Add Transcation to single vaild Customer");
    testOutcome(!(*bank).add_transaction(0,0,0), "Add Transcation with invaild memmber");
    testOutcome((*bank).void_transaction(3,0), "void_Transcation with vaild member and vaild timestamp");
    testOutcome(!(*bank).void_transaction(3,1), "void_Transcation with vaild member and invaild timestamp");
    testOutcome(!(*bank).void_transaction(0,0), "void_Transcation with invaild member and invaild timestamp");
    for(int i=3; i <10 ; ++i){
        testOutcome((*bank).get_customer_data(i)._account_balance == i*10, ("Check the Reset Customer's balance"));
    }
    (*bank).add_transaction(5,0,100);
    testOutcome((*bank).get_customer_transaction(5,0)._tx_amt == 100, "Check the amount in Customer's transcation list");
    testOutcome((*bank).transaction_exists(5,0), "trasncation_exists with vaild member and vaild timestamp");
    testOutcome(!(*bank).transaction_exists(5,1), "trasncation_exists with vaild member and invaild timestamp");
    testOutcome(!(*bank).transaction_exists(2,1), "trasncation_exists with invaild member and invaild timestamp");
    testOutcome((*bank).customer_exists(6), "customer_exists with vaild member");
    testOutcome(!(*bank).customer_exists(0), "customer_exists with invaild member");
    (*bank).add_transaction(6,0,-100);
    (*bank).add_transaction(7,0,100);
    CSE250::dCustomerIDNode overdraw = *((*bank).process_transactions());
    testOutcome(overdraw._customer_id == 6, "process_transcation with all vaild member and return one overdraw member");
    testOutcome((*bank).get_customer_data(7)._account_balance == 170, "Chech process_transcation process other Customer's transcation");
    testOutcome((*bank).get_customer_data(5)._pending_txs == nullptr, "Chech the transcation list should be empty");
    testOutcome((*bank).get_customer_data(6)._pending_txs == nullptr, "Chech the transcation list should be empty");
    testOutcome((*bank).get_customer_data(7)._pending_txs == nullptr, "Chech the transcation list should be empty");
    (*bank).add_transaction(8,10,10);
    (*bank).add_transaction(8,11,11);
    (*bank).add_transaction(8,3,13);
    testOutcome((*bank).get_customer_data(8)._pending_txs != nullptr, "Check the transcation list is not nullptr");
    testOutcome(((((*bank).get_customer_data(8)._pending_txs)->_next)) != nullptr, "Check Successful Add Transcation");
    for(int i=3; i<10; ++i){
        (*bank).add_transaction(i,i,i);
        CSE250::dTransactionNode* head = (*bank).get_customer_data(i)._pending_txs;
        testOutcome(head != nullptr, "We dont have nullptr, OhYa!");
        while(head != nullptr){
            testOutcome((head->_tx)._timestamp, "Add_Transcation");
            head = (head->_next);
        }
    }
    testOutcome((*bank).get_customer_transaction(8,11)._timestamp == 11, "FInd Transcation with timestamp 11 in Customer ID: 8");
    testOutcome((*bank).void_transaction(8,10), "void_trasncation with vaild Customer and vaild timestamp");
    testOutcome((*bank).get_customer_transaction(8,11)._timestamp == 11, "FInd Transcation with timestamp 11 in Customer ID: 8");
    testOutcome((*bank).void_transaction(8,8), "void_trasncation with vaild Customer and vaild timestamp");
    testOutcome((*bank).get_customer_transaction(8,11)._timestamp == 11, "FInd Transcation with timestamp 11 in Customer ID: 8");
    testOutcome((*bank).void_transaction(8,11), "void_trasncation with vaild Customer and vaild timestamp");
    testOutcome((*bank).void_transaction(8,3), "void_trasncation with vaild Customer and vaild timestamp");
    testOutcome((*bank).get_customer_data(8)._pending_txs == nullptr, "Successful void all transcation with Customer ID: 8");
    testOutcome(!(*bank).void_transaction(8,10), "void_trasncation with vaild Customer and invaild timestamp");
    testOutcome(!(*bank).void_transaction(10,10), "void_trasncation with invaild Customer and vaild timestamp");
    testOutcome(!(*bank).transaction_exists(8,10), "Successful void_transcation");

    for(int i=3; i<10; ++i){
        testOutcome((*bank).add_transaction(i,(size_t)i*100,1000), "Adding Transcation");
        testOutcome((*bank).add_transaction(i,(size_t)i*10,1000), "Adding Transcation");
        testOutcome((*bank).add_transaction(i,(size_t)i*1000,1000), "Adding Transcation");
    }
    (*bank).add_transaction(4,111,111);
    (*bank).add_transaction(4,112,112);
    (*bank).add_transaction(4,113,113);
    (*bank).add_transaction(4,114,114);
    for(int i=3; i<10;++i){
        while((*bank).get_customer_data(i)._pending_txs != nullptr){
            testOutcome((*bank).void_transaction(i, (((*bank).get_customer_data(i)._pending_txs)->_tx)._timestamp), "Voiding transcation");
        }
        testOutcome((*bank).get_customer_data(i)._pending_txs == nullptr, "Transcation List is clean!");
    }
    for(int i=3; i<10; ++i){
        testOutcome((*bank).remove_customer(i), "Remove vaild Customer");
    }
    testOutcome(!(*bank).remove_customer(3), "Remove invaild Customer");
    CSE250::dCustomerIDNode* cNode = (new CSE250::dCustomerIDNode(100));
    cNode->_next = new CSE250::dCustomerIDNode(110);
    cNode->_next->_next = new CSE250::dCustomerIDNode(120);
    cNode->_next->_next->_next = new CSE250::dCustomerIDNode(130);
    testOutcome((*bank).add_customer(cNode), "Test Add list of vaild Customer");
    testOutcome((*bank).remove_customer(cNode), "Test Remove list of vaild Customer");
    testOutcome(!(*bank).remove_customer(100), "Remove invaild Customer");
    testOutcome((*bank).remove_customer(nullptr), "Remove empty list of CUstomer");
    (*bank).add_customer(11,0);
    testOutcome((*bank).add_transaction(11,112,13),"Add Transcation");
    testOutcome((*bank).get_customer_transaction(11,112)._timestamp == 112, "Check Transcation 112 is successful added");
    testOutcome((*bank).add_transaction(11,113,13),"Add Transcation");
    testOutcome((*bank).get_customer_transaction(11,113)._timestamp == 113, "Check Transcation 113 is successful added");
    testOutcome((*bank).add_transaction(11,114,13),"Add Transcation");
    testOutcome((*bank).get_customer_transaction(11,114)._timestamp == 114, "Check Transcation 114 is successful added");
    (*bank).process_transactions();
    testOutcome((*bank).get_customer_data(11)._account_balance == 39, "Test the transcation is process");
    testOutcome((*bank).get_customer_data(11)._pending_txs == nullptr, "Check the pendind list is empty after process transcation");
    delete bank;
}

int main() {
    std::cerr << "testCustomerAdd requires addCustomer(size_t,double) to be completed as well as customer_exists(size_t)." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testCustomerAdd(1)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed test checking if 2 customers added are found." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding a customer and checking that they exist." << std::endl;
        return -1;
    }

    std::cerr << "\nTesting that a second call with the same values still works." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testCustomerAdd(1)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test a second time." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding customers the second time through." << std::endl;
        return -1;
    }

    std::cerr << "\nTesting that a third call with different values also works." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testCustomerAdd(5)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test of adding a customer and checking that they exist a second time." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding a customer and checking that they exist the second time around." << std::endl;
        return -1;
    }

    std::cerr << "\ntestCustomerAdd requires addCustomer(CSE250::dCustomerIDNode) to be completed as well as customer_exists(size_t)." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testAddCustomerList(1)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test of adding a customer list." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding customer list." << std::endl;
        return -1;
    }

    std::cerr << "\nTesting testCustomerAdd works on a second call with the same values." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testAddCustomerList(1)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test of adding a customer list a second time." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding customer list a second time." << std::endl;
        return -1;
    }

    std::cerr << "\nTesting testCustomerAdd works on a third call with different values." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testAddCustomerList(3)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test of adding a customer list a third time." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding customer list a third time." << std::endl;
        return -1;
    }

    std::cerr << "\ntestCustomerAddBoth requires addCustomer(CSE250::dCustomerIDNode) and addCustomer(size_t, double) to be completed as well as customer_exists(size_t)." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testAddCustomerAddBoth(1)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test of adding a customer list." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding customer list." << std::endl;
        return -1;
    }

    std::cerr << "\ntestCustomerAddBoth running a second time." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testAddCustomerAddBoth(2)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test of adding a customer list." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding customer list." << std::endl;
        return -1;
    }

    std::cerr << "\ntestCustomerGet requires addCustomer(CSE250::dCustomerIDNode) and addCustomer(size_t, double) to be completed as well as get_customer_data(size_t)." << std::endl;
    std::cerr << "-------------------------" << std::endl;
    if (testCustomerGet(1)) {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Successfully passed basic test of adding a customer list." << std::endl;
    }
    else {
        std::cerr << "-------------------------" << std::endl;
        std::cerr << "Failed basic test of adding customer list." << std::endl;
        return -1;
    }

    std::cerr << "\n Final note: you should not be seeing any memory leaks after running this code." << std::endl;


    myTestAllCase();
    //FIXME need more test to check memory leak

}