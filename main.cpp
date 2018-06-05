#include <iostream>

#include "BankData.hpp"

void printTransactionList(CSE250::dTransactionNode* head) {
    if (head == nullptr) {
        return;
    }
    std::cout << "Transaction list:" << std::endl;
    while (head != nullptr) {
        std::cout << "(" << head->_tx._timestamp << ", " << head->_tx._tx_amt << ")" << std::endl;

        // What happens if you comment out this next line?
        head = head->_next;
    }

}

int main() {

    //Transaction tx1; // Invalid, default constructor is private.
    Transaction tx2(5, 3.5);
    std::cout << "Printing transaction data:" << std::endl;
    std::cout << tx2._timestamp << ", " << tx2._tx_amt << std::endl;

    // You can create transaction nodes like this:
    auto* txN = new CSE250::dTransactionNode(3, 8.7);

    //tx2 = txN->_tx; // Cannot copy transactions due to const data/no copy assignment defined.

    std::cout << txN->_tx._timestamp << ", " << txN->_tx._tx_amt << std::endl;
    delete txN;

    Customer cust{500, 1000.50};

    std::cout << "Printing customer data:" << std::endl;
    std::cout << "ID: " << cust._customer_id << ", balance: " << cust._account_balance << std::endl;

    // Adding some pending transactions.
    auto* _tx_node = new CSE250::dTransactionNode(1, 400.25);
    cust._pending_txs = _tx_node;

    _tx_node = new CSE250::dTransactionNode(4, -32.75);
    cust._pending_txs->_next = _tx_node;
    _tx_node->_prev = cust._pending_txs;

    printTransactionList(cust._pending_txs);

    // It's always good habit after deleting a pointer to set it to nullptr.
    delete cust._pending_txs->_next;
    cust._pending_txs->_next = nullptr;

    delete cust._pending_txs;
    cust._pending_txs = nullptr;

    return 0;
}

