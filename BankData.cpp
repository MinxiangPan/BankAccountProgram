
#include "BankData.hpp"

BankData::~BankData() {
    for(auto i : _customer){
        delete i;
        i = nullptr;
    }
}

/**
 * Add a customer to the stored customers if no customer with the same id is present.
 * Initialize the customer balance to the value provided.
 *
 * @param customer_id - id to assign the new customer.
 * @param balance - starting balance for the customer.
 * @return  true - if customer was successfully added.
 *         false - if the customer was previously added.
 */
bool BankData::add_customer(const size_t& customer_id, const double& balance) {
    if(((this->_customer)).empty()){
        Customer* newCustomer = new Customer(customer_id,balance);
        (this->_customer).push_back(newCustomer);
        return true;
    }
    for(auto i : (this->_customer)){
        if(((i->_customer_id)) == customer_id){
            return false;
        }
    }
    Customer* newCustomer = new Customer(customer_id,balance);
    (this->_customer).push_back(newCustomer);
    return true;
}

/**
 * Add a list of customers to the stored customers with the ids within this list.
 * You should initialize the customers with an account balance of 0.
 * All values in the list should be processed, even if a customer already exists.
 *
 * @param customer_list - list of customer ids to add.
 * @return  true - if all customers were successfully added.
 *         false - if some customer was previously added (including if there are duplicates in the list itself).
 */
bool BankData::add_customer(const CSE250::dCustomerIDNode* customer_list) {
    bool returnVal = true;
    while(customer_list != nullptr){
        returnVal = BankData::add_customer((customer_list->_customer_id),0) && returnVal;
        customer_list = (customer_list->_next);
    }
    return returnVal;
}

/**
 * Remove a customer from the stored customers.
 *
 * @param customer_id - id of customer to remove.
 * @return  true - if customer was successfully removed.
 *         false - if the customer was not present.
 */
bool BankData::remove_customer(const size_t& customer_id) {
    if(((this->_customer)).empty()){
        return false;
    }
//    for(auto i : (this->_customer)){
    for(vector<Customer*>::iterator i = (this->_customer).begin(); i != (this->_customer).end(); ++i ){
        if((*i)->_customer_id == customer_id){
            delete &(*(*i));
//            (&(*(*i))) = nullptr;
            (this->_customer).erase(i);
            return true;
        }
    }
    return false;
}

/**
 * Remove a list of customer to the stored customers with an account balance of 0.
 * All values in the list should be processed, even if an ID is for a customer that
 * was already removed or doesn't exist.
 *
 * @param customer_list - list of customer ids to remove.
 * @return  true - if all customers were successfully removed.
 *         false - if some customer was not removed (including if there are duplicates in the list itself).
 */
bool BankData::remove_customer(const CSE250::dCustomerIDNode* customer_list) {
    bool returnVal = true;
    if(((this->_customer)).empty() && customer_list != nullptr){
        return false;
    }
    while(customer_list != nullptr){
        returnVal = BankData::remove_customer((customer_list->_customer_id)) && returnVal;
        customer_list = (customer_list->_next);
    }
    return returnVal;
}

/**
 * Add a transaction for to the transaction list for the specified customer.
 *
 * You may assume that each timestamp will be unique between each call to process transactions.
 * You may not assume that the timestamps will be given in any particular order.
 *
 * @param customer_id - id of the customer to add the transaction under.
 * @param timestamp - timestamp the transaction should be created with.
 * @param amount - amount the transaction will change their account balance
 * @return  true - if the transaction was successfully added to the customer's account.
 *         false - if the customer didn't exist.
 */
bool BankData::add_transaction(const size_t& customer_id, const size_t& timestamp, const double& amount) {
    if(((this->_customer)).empty()){
        return false;
    }
    for(auto i : (this->_customer)){
        if((i->_customer_id) == customer_id){
            CSE250::dTransactionNode* newTranscation = new CSE250::dTransactionNode(timestamp,amount);
            if((i->_pending_txs) == nullptr){
                (i->_pending_txs) = newTranscation;
                return true;
            }
            CSE250::dTransactionNode* head = (i->_pending_txs);
            CSE250::dTransactionNode* tail;
            while(head != nullptr){
                if((head->_tx)._timestamp > timestamp){
                    if((head->_prev) == nullptr){
                        (i->_pending_txs) = newTranscation;
                    }
                    else{
                        CSE250::dTransactionNode* prev = head->_prev;
                        (prev->_next) = newTranscation;
                        (newTranscation->_prev) = prev;
                    }
                    (newTranscation->_next) = head;
                    (head->_prev) = newTranscation;
                    return true;
                }
                tail = head;
                head = (head->_next);
            }
            (tail->_next) = newTranscation;
            (newTranscation->_prev) = tail;
            return true;
        }
    }
    return false;
}

/**
 * Void the transaction with the specified customer id and timestamp
 * (i.e., remove it from the customer's transaction list).
 *
 * You may assume that each timestamp will be unique between each call to process transactions.
 *
 * @param customer_id - id of the customer the transaction is under.
 * @param timestamp - timestamp the transaction was created with.
 * @return  true - if the transaction was successfully added to the customer's account.
 *         false - if the customer didn't exist or there is no transaction with the given timestamp
 *                 for that customer.
 */
bool BankData::void_transaction(const size_t& customer_id, const size_t& timestamp) {
    if(((this->_customer)).empty()){
        return false;
    }
    for(auto i : (this->_customer)){
        if((i->_customer_id) == customer_id){
            CSE250::dTransactionNode* head = (i->_pending_txs);
            while(head != nullptr){
                if(((head->_tx)._timestamp) == timestamp){
                    if((head->_prev) != nullptr && (head->_next) != nullptr){
                        ((head->_prev)->_next) = (head->_next);
                        ((head->_next)->_prev) = (head->_prev);
                        (head->_next) = nullptr;
                        delete head;
                        return true;
                    }
                    if((head->_prev) == nullptr && (head->_next) != nullptr){
                        ((head->_next)->_prev) = nullptr;
                        (i->_pending_txs) = (head->_next);
                        (head->_next) = nullptr;
                        delete head;
                        return true;
                    }
                    if((head->_prev) != nullptr && (head->_next) == nullptr){
                        ((head->_prev)->_next) = nullptr;
                        delete head;
                        return true;
                    }
                    if((head->_prev) == nullptr && (head->_next) == nullptr){
                        (i->_pending_txs) = nullptr;
                        delete head;
                        return true;
                    }
                    return true;
                }
                head = (head->_next);
            }
            return false;
        }
    }
    return false;
}

/**
 * Process each transaction for each customer.
 * At the end, all transaction lists should be empty and account balances should reflect all changes
 * dictated by the respective lists of transactions.
 * Transactions should be processed in increasing order of timestamp (within the Customer's pending transactions).
 * Create a list of all customers that had overdrawn their account.
 * @return double linked list of all customer IDs that overdrew their account.
 */
CSE250::dCustomerIDNode* BankData::process_transactions() {
    //FIXME Problem with this functiont that exit code 134 invaild access permission
    CSE250::dCustomerIDNode* overdrew = nullptr;
    CSE250::dCustomerIDNode* tail = nullptr;
    for(auto i : (this->_customer)){
        while((i->_pending_txs) != nullptr){
            BankData::process_transactions((*i));
//            CSE250::dTransactionNode* prev = nullptr;
//            if((i->_pending_txs)->_prev != nullptr){
//                prev = (i->_pending_txs)->_prev;
//            }
//            else{
//                prev = (i->_pending_txs);
//            }
//            (i->_account_balance) = (i->_account_balance) + ((i->_pending_txs)->_tx)._tx_amt;
//            if((i->_account_balance) < 0){
//                (i->_overdrawn) = true;
//            }
//            (i->_pending_txs) = (i->_pending_txs)->_next;
//            delete prev;
//            prev = nullptr;
////            (*this).void_transaction((i->_customer_id),(i->_pending_txs)->_tx._timestamp);
        }
        if(i->_overdrawn){
            if(overdrew != nullptr){
                CSE250::dCustomerIDNode* node = new CSE250::dCustomerIDNode((i->_customer_id));
                (tail->_next) = node;
                (node->_prev) = tail;
                tail = node;
            }
            else{
                overdrew = new CSE250::dCustomerIDNode((i->_customer_id));
                tail = overdrew;
            }
        }
    }
    return overdrew;
}


/**
 * Process each transaction for a single customer.
 * Transactions should be processed in increasing timestamp order.
 * While processing the transactions, if the customer's balance becomes negative,
 * then the _overdrawn flag should be set to true.
 *
 * @param customer - customer object for which to process transactions.
 */
void BankData::process_transactions(Customer& customer) {
    CSE250::dTransactionNode* head = customer._pending_txs;
    customer._pending_txs = nullptr;
    CSE250::dTransactionNode* prev;
    CSE250::dTransactionNode* tail = nullptr;
    while(head != nullptr){
        prev = head->_prev;
        customer._account_balance = customer._account_balance + (head->_tx)._tx_amt;
        if(customer._account_balance < 0){
            customer._overdrawn = true;
        }
        tail = head;
        head = (head->_next);
        delete prev;
        prev = nullptr;
    }
    delete tail;
    tail = nullptr;
}

/**
 * Tell whether or not a customer with the specified ID exists in the stored customer data.
 *
 * @param customer_id -  id of the customer requested.
 * @return  true - if the customer requested has a stored record.
 *         false - otherwise.
 */
bool BankData::customer_exists(const size_t& customer_id) {
    for(auto i : (this->_customer)){
        if((i->_customer_id) == customer_id){
            return true;
        }
    }
    return false;
}

/**
 * Tell whether or not the ID belongs to a valid customer and
 * the timestamp belongs to a valid Transaction under that customer.
 *
 * @param customer_id -  id of the customer requested.
 * @param timestamp - timestamp the transaction was created with.
 * @return  true - if the customer requested has a stored record.
 *         false - otherwise.
 */
bool BankData::transaction_exists(const size_t& customer_id, const size_t& timestamp) {
    for(auto i : (this->_customer)){
        if((i->_customer_id) == customer_id){
            CSE250::dTransactionNode* head = (i->_pending_txs);
            while(head != nullptr){
                if((head->_tx)._timestamp == timestamp){
                    return true;
                }
                head = (head->_next);
            }
            break;
        }
    }
    return false;
}

const Customer& BankData::get_customer_data(const size_t& customer_id) {
    for(auto i : (this->_customer)){
        if((i->_customer_id) == customer_id){
            return *(i);
        }
    }
    Customer* returnVal = new Customer(-1,-1);
    return *returnVal;
}

/**
 * Get access to the transaction data associated with the requested ID and timestamp.
 * You should assume that the ID belongs to a valid customer and the timestamp belongs to a valid Transaction.
 * @param customer_id - id of the customer requested.
 * @param timestamp - timestamp the transaction was created with.
 * @return constant reference to the Transaction object associated with the id and timestamp.
 */
const Transaction& BankData::get_customer_transaction(const size_t& customer_id, const size_t& timestamp) {
    for(auto i : (this->_customer)){
        if((i->_customer_id) == customer_id){
            CSE250::dTransactionNode* head  = (i)->_pending_txs;
            while(head != nullptr){
                if((head->_tx)._timestamp == timestamp){
                    return (head->_tx);
                }
                head = (head->_next);
            }
            break;
        }
    }
    Transaction* returnVal = new Transaction(-1,-1);
    return *returnVal;
}
