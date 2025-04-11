# AVL Multiset

This project implements a multiset using an AVL tree in C++. A multiset is similar to a set, but it allows duplicate elements. The data structure is designed as a self-balancing binary search tree (AVL tree) that maintains order, supports duplicate values, and offers efficient insertion, deletion, and query operations.

## Overview

The code is written as a C++ template class so that the multiset can store elements of any type that supports comparison operations. Internally, each node in the AVL tree keeps track of several key pieces of information:
- **Value (data):** The element stored in the node.
- **Count (quantity):** The number of occurrences of the element (for duplicate values).
- **Height:** The height of the node, used to ensure the AVL tree remains balanced.
- **Subtree Size (pos):** The total number of elements in the subtree, including duplicates. This facilitates order-statistic queries (e.g., finding the k-th smallest element).

## Code Structure

### 1. Node Structure
The `Node` struct is defined within the AVL class and holds:
- **Pointers:** To the left and right children.
- **Height:** The height of the subtree, used for balance calculations.
- **Subtree Size (`pos`):** The cumulative count of elements in the subtree.
- **Quantity:** The frequency of the node’s value.
- **Data:** The actual element of type `TEMPAVL`.

### 2. Tree Balancing & Rotations
- **Height Calculation:**  
  The method `getHeight(Node *v)` returns the height of a node (or -1 for a null pointer). The helper method `countHeight(Node *v)` updates the height based on its children.

- **Subtree Size Calculation:**  
  The method `getPos(Node *v)` recalculates the subtree size (the cumulative count of all nodes, including duplicates).

- **Rotations:**  
  The functions `leftRotate` and `rightRotate` are implemented to maintain balance. After each rotation, the height and subtree sizes are updated.

- **Balancing:**  
  The function `balance(Node *v)` computes the balance factor and performs the appropriate single or double rotations.

### 3. Core Operations

#### Insertion
- **Function:** `insert(TEMPAVL val)`
- **Operation:**  
  - If the element exists, the method increments its quantity.
  - Otherwise, it creates a new node, adjusts heights and positions, and then rebalances the tree.

#### Deletion
There are two deletion methods:
- **By Value:** `remove(TEMPAVL val)` – Deletes all occurrences of the specified element.
- **By Index:** `removeByIndex(size_t idx)` – Deletes one occurrence of the element at the given in-order index (0-indexed).

Both methods update the tree structure, adjust subtree sizes, and ensure the tree remains balanced.

#### Element Search
- **By Value:** `find(TEMPAVL val)` returns `true` if the element is found.
- **By Index:** `findByIndex(size_t idx)` returns the element at the specified in-order index with O(log n) time complexity.

#### Bound Queries
- **Lower Bound:**  
  `lowerBound(TEMPAVL val)` returns the index of the first element that is not less than (`>=`) the given value.
  
- **Upper Bound:**  
  `upperBound(TEMPAVL val)` returns the index of the first element that is greater than (`>`) the given value.

These mimic the behavior of the standard C++ lower/upper bound functions.

#### Inorder Traversal (Sorting)
- **Function:** `sort(std::vector<TEMPAVL>& a)`
- **Operation:**  
  Performs an in-order traversal to fill a vector with all elements in sorted order, accounting for duplicates.

## Usage Example

Below is a brief example of how to integrate and use the AVL multiset in a C++ project:

```cpp
#include <iostream>
#include <vector>
#include "AVL_multiset.hpp" // Ensure the header file is correctly included

int main() {
    // Create an instance of the AVL multiset to store integers
    AVL<int> avlMultiset;
    
    // Insert elements
    avlMultiset.insert(10);
    avlMultiset.insert(5);
    avlMultiset.insert(10); // Duplicate insertion
    avlMultiset.insert(20);

    // Check size (should reflect duplicate insertions)
    std::cout << "Size: " << avlMultiset.size() << std::endl;

    // Search for an element
    if (avlMultiset.find(10)) {
        std::cout << "Element 10 found." << std::endl;
    }
    
    // Retrieve the second smallest element (0-indexed)
    int secondElement = avlMultiset.findByIndex(1);
    std::cout << "Second smallest element: " << secondElement << std::endl;

    // Remove one occurrence of an element by value
    avlMultiset.remove(10);

    // Sort the elements into a vector
    std::vector<int> sortedElements;
    avlMultiset.sort(sortedElements);
    std::cout << "Sorted elements: ";
    for (const auto &elem : sortedElements) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## Conclusion

This AVL multiset implementation provides an efficient and flexible method to store, maintain, and query elements in a multiset. By combining AVL tree balancing with careful bookkeeping of node counts, the structure supports efficient order-statistic queries and duplicate handling. Feel free to extend and adapt this code to suit your project’s needs.
