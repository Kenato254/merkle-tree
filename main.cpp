#include <iostream>
#include <string>
#include <vector>

#include "merkle.h"

using namespace std;

int main()
{
    MerkleTree d1;
    MerkleTree *merkle = &d1;

    vector<string> db{
        // Data Blocks
        "Bob paid $10 to Alice",
        "John got paid $40 by Jane",
        "Jin paid $80 to Yu",
        "Bob paid $5000 to Kassa",
        "Kassa paid $11 to Alice",
        "John got paid $40 by Yu",
        "Lin paid $20 to Yu",
        "Bob paid $25 to John",
        // "Jane paid $5000 to Kassa",
    };

    // Add transactions(data blocks) to the merkle tree
    vector<string>::iterator i;
    for (i = db.begin(); i != db.end(); i++)
    {
        merkle->add_data_block(&(*i));
    }

    merkle->create_merkle_tree();
    merkle->print_merkle_tree();
    cout << endl;
    cout << "Merkle root: " << merkle->root << endl;
    cout << endl;
    cout << "Merkle node: ";
    merkle->print_merkle_child_nodes();
    cout << endl;
    merkle->print_merkle_leaves();

    // vector<string>::iterator j;
    // for (j = merkle->leaves.begin(); j != merkle->leaves.end(); j++)
    // {
    //     cout << *j << " ";
    // }
    // cout << endl;

    // for(int k=1; k < merkle->leaves.size(); k+=2)
    // {
    //     cout << sha1(merkle->leaves.at(k-1)+merkle->leaves.at(k)) << " ";
    // }
    // cout << endl;
    
    // cout << sha1("b9c05e18af644d9165a856b42076bfdfb00fb05aba8f830721e9d638e55fd68191414dfed2cf094e") << endl;
    return 0;
}