#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>

#include "../SHA-1/sha1.cpp"
#include "header.h"

using namespace std;

MerkleTree::MerkleTree()
/**
 * @brief Constructor-1 takes no arguments
 */
{
}

bool MerkleTree::is_empty()
/**
 * @brief Checks if merkle tree is empty
 * @return bool
 */

{
    if (this->merkle_tree.size() == 0)
    {
        return false;
    }
    return true;
}

void MerkleTree::add_data_block(string *data_block)
/**
 * @brief Creates a list of data blocks
 * @param data_block a string pointer containing location of data block to be added to the list
 */
{
    if (data_block->length() == 0)
    {
        throw invalid_argument("Null input @data_block");
    }
    else
    {
        this->leaves.push_back(sha1(*data_block)); // Hashing Data Blocks
    }
}

void MerkleTree::create_merkle_tree()
/**
 * @brief Creates a merkle tree from a vector of data blocks
 * @return NULL
 */
{
    // To create a merkle tree, length of leaves should always be 2^n
    bool length_check = (log2(this->leaves.size()) - floor(log2(this->leaves.size()))) > 0;
    if (!length_check)
    {
        this->merkle_tree.push_back(this->leaves); // Add leaves to the tree
        int index = 0;
        int cycles = log2(this->leaves.size());
        while (cycles > index)
        {
            // Create a vector
            vector<string> anynomous;
            for (int i = 1; i < this->merkle_tree.at(index).size(); i += 2)
            {
                // Push nodes to the vector
                anynomous.push_back(sha1(this->merkle_tree.at(index).at(i - 1) + this->merkle_tree.at(index).at(i)));
            }
            // Push vector(child node) to the tree
            this->merkle_tree.push_back(anynomous);
            anynomous.clear(); // Clear vector for reuse;
            index++;
        }
    }
    else
    {
        char buffer[100];
        sprintf(buffer, "Vector with length %ld can not create a binary tree!\n", this->leaves.size());
        throw length_error(buffer);
    }
    this->root = this->merkle_tree.back()[0];
}

void MerkleTree::print_merkle_tree()
/**
 * @brief Print the entire merkle tree from leaves to the root. Time: O(n log n)
 * @return NULL
 */
{
    if (!this->merkle_tree.empty())
    {
        for (vector<string> v1d : this->merkle_tree) // first dimension
        {
            for (string v : v1d) // second dimension
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No element in the tree" << endl;
    }
}

void MerkleTree::print_merkle_leaves()
/**
 * @brief Prints merkle leaves
 * @return NULL
 */

{
    if (this->leaves.size() > 0)
    {
        cout << "Merkle leaves: ";
        for (const string hash_ : this->leaves)
        {
            cout << hash_ << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No element in the tree" << endl;
    }
}

void MerkleTree::print_merkle_child_nodes()
/**
 * @brief Prints merkle nodes. Time: O(n log n)
 * @return NULL
 */

{
    for (int i = this->merkle_tree.size() - 2; i > 0; i--)
    {
        for (int j = 0; j < this->merkle_tree.at(i).size(); j++)
        {
            cout << this->merkle_tree.at(i).at(j) << " ";
        }
        cout << endl;
    }
}
