//
// Created by Diego Pacheco Ferrel on 20/05/23.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <iostream>
#include <utility>
#include "vector"
#include "Block.h"
#include "BankTransfer.h"
#include "heap.h"
#include "B+Tree.h"
#include "avl.h"

typedef float amount_t;

template <class Data, class TK=int, class TV=float>
class Blockchain{
    int size;
    int difficulty;
    int max_blockTransactions;
    Block<Data>* genesis;
    DoubleList<Block<Data>*> chain;

    //Indices
    Heap<amount_t> amounts_maxheap;
    Heap<amount_t> amounts_minheap;
    BPlusTree<amount_t> amounts;

public:
    Blockchain():amounts_maxheap(10), amounts_minheap(10, Heap<amount_t>::MIN_HEAP), amounts(3){
        max_blockTransactions = 10;
        size = 1;
        difficulty = 0;
        genesis = new Block<Data>(10, "0000000000000000000000000000000000000000000000000000000000000000");
        chain.push_back(genesis);
    }

    Blockchain(int _difficulty, int _maxTransactions): amounts_maxheap(_maxTransactions), amounts_minheap(_maxTransactions, Heap<amount_t>::MIN_HEAP),
                                                       amounts(3){
        max_blockTransactions = _maxTransactions;
        size = 1;
        difficulty = _difficulty;
        genesis = new Block<Data>(_maxTransactions, "0000000000000000000000000000000000000000000000000000000000000000");
        chain.push_back(genesis);
    }

    ~Blockchain(){
        for (auto blockPtr : chain) {
            delete blockPtr;
        }
    }

    void insert_transaction(Data* transaction){
        if(chain.back()->get_transactions_count() < max_blockTransactions){
            chain.back()->add_transaction(transaction);
        }
        else{
            auto newBlock = new Block<Data>(max_blockTransactions, chain.back()->get_hash());
            newBlock->add_transaction(transaction);
            chain.push_back(newBlock);
            size += 1;
        }
        amounts_maxheap.push(transaction->get_monto());
        amounts_minheap.push(transaction->get_monto());
        amounts.insert(transaction->get_monto());
    }

    int chain_size(){
        return size;
    }

    TV max_amount(){
        TV max = amounts_maxheap.top();
        return max;
    }

    TV min_amount(){
        TV min = amounts_minheap.top();
        return min;
    }

    vector<TV> range_search(TK begin, TK end){
        return amounts.range_search(begin,end);
    }

};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
