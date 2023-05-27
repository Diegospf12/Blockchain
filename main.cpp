#include "sha256.h"
#include "BankTransfer.h"
#include "Block.h"
#include "Blockchain.h"
#include "double.h"
#include "B+Tree.h"


using namespace std;

int main() {

    //DoubleList<BankTransfer> list;

    auto transfer1 = new BankTransfer("Alice", "Emma", 50);
    auto transfer2 = new BankTransfer("Bob", "Olivia", 100);
    auto transfer3 = new BankTransfer("Charlie", "Sophia", 200);
    auto transfer4 = new BankTransfer("Diego", "Ava", 500);
    auto transfer5 = new BankTransfer("Daniel", "Liam", 1000);
    auto transfer6 = new BankTransfer("Ethan", "Isabella", 150);
    auto transfer7 = new BankTransfer("Frederick", "Mia", 300);
    auto transfer8 = new BankTransfer("George", "Charlotte", 250);
    auto transfer9 = new BankTransfer("Henry", "Amelia", 400);
    auto transfer10 = new BankTransfer("Isaac", "Harper", 600);
    auto transfer11 = new BankTransfer("John", "Damian", 600000);



    /*Block<BankTransfer> block(10);

    block.add_transaction(transfer1);
    block.add_transaction(transfer2);
    block.add_transaction(transfer3);
    block.add_transaction(transfer4);
    block.add_transaction(transfer5);
    block.add_transaction(transfer6);
    block.add_transaction(transfer7);
    block.add_transaction(transfer8);
    block.add_transaction(transfer9);
    block.add_transaction(transfer10);
    block.mineBlock(4);
    block.show_transactions();
    cout << block.get_hash() << endl;*/

    Blockchain<BankTransfer> chain(4, 10);

    chain.insert_transaction(transfer1);
    chain.insert_transaction(transfer2);
    chain.insert_transaction(transfer3);
    chain.insert_transaction(transfer4);
    chain.insert_transaction(transfer5);
    chain.insert_transaction(transfer6);
    chain.insert_transaction(transfer7);
    chain.insert_transaction(transfer8);
    chain.insert_transaction(transfer9);
    chain.insert_transaction(transfer10);
    chain.insert_transaction(transfer11);

    cout << "Monto máximo: " << chain.max_amount() << endl;
    cout << "Monto mínimo: " << chain.min_amount() << endl;
    cout << "Montos entre 2 y 750: ";
    for(auto elem : chain.range_search(2,750))
        cout << elem << " ";



    /*cout << genesis.get_hash() << endl;
    transfer1.modify_emisor("Eric");
    genesis.modify(transfer1);
    cout << genesis.get_hash() << endl;*/
}

