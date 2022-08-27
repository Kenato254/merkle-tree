#include <iostream>
#include <vector>
#include <cmath>

#include "../SHA-1/sha1.cpp"
#include "header.h"

using namespace std;

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
    while (cycles >= 0)
    {
        if (index % 2 == 0)
        {
            // computed_root = sha1(hashed_data + merkle_tree.at(cycles).at(index));
        }
        else
        {
            // computed_root = sha1(merkle_tree.at(cycles).at(index) + hashed_data);
        }
        cout << "Cycle: " << cycles << endl;
        cout << "Index " << index << endl;
        cycles--;
        index /= floor(index);
    }
    return root == computed_root;
}
