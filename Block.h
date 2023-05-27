//
// Created by Diego Pacheco Ferrel on 19/05/23.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <ostream>
#include "BankTransfer.h"
#include "sha256.h"
#include "double.h"

using namespace std;

typedef string hash_t;

template <class Data>
class Block{
    bool valid_block;
    int index;
    int nonce;
    std::time_t timestamp;
    DoubleList<Data*> transactions;
    hash_t prev_hash;
    hash_t hash;
    int maxTransactions;

public:
    Block():index(0), nonce(0), timestamp(time(nullptr)), maxTransactions(0){};

    //_prev_hash = "0000000000000000000000000000000000000000000000000000000000000000"

    Block(int _maxTransactions, hash_t _prev_hash){
        index = 1;
        nonce = 0;
        timestamp = std::time(nullptr);
        prev_hash = _prev_hash;
        maxTransactions = _maxTransactions;
        hash = calculateHash();
    }

    ~Block(){
        for (Data* transaction : transactions) {
            delete transaction;
        }
    }

    void add_transaction(Data* _data){
        if(transactions.size() < maxTransactions){
            transactions.push_back(_data);
            hash = calculateHash();
        }
        else
            throw("Block is full");
    }

    ///Hashcash
    void mineBlock(int difficulty) {
        string target(difficulty, '0');
        while (hash.substr(0, difficulty) != target) {
            nonce++;
            hash = calculateHash();
        }
    }

    void set_maxTransaction(int _maxTransactions){
        maxTransactions = _maxTransactions;
    }

    int get_index() const {
        return index;
    }

    int get_transactions_count(){
        return transactions.size();
    }

    int get_nonce() const {
        return nonce;
    }

    time_t get_timestamp() const {
        return timestamp;
    }

    DoubleList<Data*>& get_transactions(){
        return transactions;
    }

    void show_transactions(){
        const DoubleList<Data*>& transactions = get_transactions();
        for (IteratorDouble<Data*> it = transactions.begin(); it != transactions.end(); ++it) {
            cout << **it << endl;
        }
    }

    int get_maxTransactions() const {
        return maxTransactions;
    }

    hash_t get_prevHash() const {
        return prev_hash;
    }

    hash_t get_hash() const {
        return hash;
    }

    bool isValidBlock(int difficulty){
        string target(difficulty, '0');
        if(hash.substr(0, difficulty) == target)
            return true;
        return false;
    }

private:

    hash_t calculateHash() const {
        std::stringstream ss;
        ss << this->index << this->nonce << this->timestamp << this->transactions.list_to_string() << this->prev_hash;
        return sha256(ss.str());
    }

};


#endif //BLOCKCHAIN_BLOCK_H
