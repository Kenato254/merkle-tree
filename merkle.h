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
                // Push node to the vector
                anynomous.push_back(sha1(this->merkle_tree.at(index).at(i - 1) + this->merkle_tree.at(index).at(i)));
            }
            this->merkle_tree.push_back(anynomous);
            anynomous.clear();
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
 * @brief Print the entire merkle tree from leaves to the root
 * @return NULL
 */
{
    if (!this->merkle_tree.empty())
    {
        for (vector<string> v1d : this->merkle_tree)
        {
            for (string v : v1d)
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

bool verify(vector<vector<string>> merkle_tree, string root, string data, int index)
/**
 * @brief function verifies existence of data in the merkle tree
 * @param merkle_branch an array of leaves and nodes needed to computer the merkle tree
 * @param root hash the root of the merkle tree
 * @param data to authenticate
 * @param index of data in the leaves/block
 */
{
    string hashed_data = sha1(data);
    string computed_root;
    // Computer merkle tree
    // for (int i = 0, j = 0; i < merkle_tree.size(); i++)
    // {
    //     if (index % 2 == 0)
    //     {
    //         computed_root = sha1(hashed_data + merkle_tree.at(j).at(i));
    //         j++;
    //     } else {
    //         computed_root = sha1(merkle_tree.at(j).at(i) + hashed_data);
    //         j++;
    //     }
    // }
    int cycles = log2(merkle_tree.size()); // Number of loops
    while (cycles > 0)
    {
        if (index % 2 == 0)
        {
            // computed_root = sha1(hashed_data + merkle_tree.at(cycles).at(i));
        } else {
            // computed_root = sha1(merkle_tree.at(cycles).at(i) + hashed_data);
        }
        cycles--;
    }
    return root == computed_root;
}
