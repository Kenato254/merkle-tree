#ifndef MERKLE_H
#define MERKLE_H

#include <string>
#include <vector>

using namespace std;

class MerkleTree
{
public:
    // Constructors
    MerkleTree();

    // A 2d vector consisting of nodes of merkle tree
    vector <vector<string>> merkle_tree;
    // A vector consisting of hash values of data blocks
    vector <string> leaves;
    // A Merkle root
    string root;

    // Methods
    bool is_empty();
    string *hashed_data(string s1, string s2);
    void print_merkle_tree();
    void create_merkle_tree();
    void print_merkle_leaves();
    void print_merkle_child_nodes();
    void add_data_block(string *blocks);
};
#endif