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

    string r = "56ffcf48b462b48e3002c9feb0fdd8fec377e531";
    string c = "9d718ee01e5e390f729ab893b4aaafc6817e6a79";
    int idx = 6;

    vector<vector<string>> tree = merkle->merkle_tree;

    bool check = verify(tree, r, c, idx);

    // cout << "Verify: " << check << endl;

    cout << "Log2: " << (log2(merkle->merkle_tree.size() + 1) - floor(log2(merkle->merkle_tree.size() + 1)) > 0) << endl;

    return 0;
}