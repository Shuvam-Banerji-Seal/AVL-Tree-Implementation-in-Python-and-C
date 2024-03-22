## Algorithms Used in AVL Tree Implementation

### 1. Python Implementation:

#### Node Class:
- **Attributes:**
  - `data`: Stores the value of the node.
  - `left`: Points to the left child node.
  - `right`: Points to the right child node.
  - `height`: Represents the height of the node in the tree.

#### AVLTree Class:
- **Methods:**
  - `insert(data)`: Inserts a new node with the given data into the AVL tree.
    - Uses `_insert(data, root)` as a helper function to recursively insert the node while maintaining the AVL property.
    - After insertion, updates the height and checks for imbalance to perform rotations if necessary.
  - `delete(data)`: Deletes the node with the given data from the AVL tree.
    - Uses `_delete(data, root)` as a helper function to recursively delete the node while maintaining the AVL property.
    - After deletion, updates the height and checks for imbalance to perform rotations if necessary.
  - `print_bfs_with_bf()`: Prints the tree in breadth-first order along with the balance factors.
    - Utilizes a breadth-first traversal to print the tree level by level, calculating and displaying the balance factors for each node.

#### Rotations:
- **Right Rotation (`right_rotate(y)`):**
  - Takes a node `y` as input and performs a right rotation around it.
  - Adjusts pointers and updates heights accordingly.
- **Left Rotation (`left_rotate(x)`):**
  - Takes a node `x` as input and performs a left rotation around it.
  - Adjusts pointers and updates heights accordingly.

#### Balancing:
- Balancing operations are performed after every insertion and deletion to ensure that the AVL tree maintains its balance property.
- The `get_balance(node)` function calculates the balance factor of a given node by subtracting the height of its right subtree from the height of its left subtree.
- Based on the balance factor, appropriate rotations are performed to rebalance the tree.

### 2. C Implementation:

#### Node Structure:
- **Members:**
  - `data`: Stores the value of the node.
  - `left`: Points to the left child node.
  - `right`: Points to the right child node.
  - `height`: Represents the height of the node in the tree.

#### Function Prototypes:
- Functions for AVL tree operations are defined with appropriate parameters and return types.

#### Insertion and Deletion:
- `insert(struct Node* root, int data)`: Inserts a new node with the given data into the AVL tree.
  - Uses recursion to find the appropriate position for insertion while maintaining the AVL property.
  - After insertion, updates the height and checks for imbalance to perform rotations if necessary.
- `deleteNode(struct Node* root, int data)`: Deletes the node with the given data from the AVL tree.
  - Uses recursion to find and delete the node while maintaining the AVL property.
  - After deletion, updates the height and checks for imbalance to perform rotations if necessary.

#### Printing:
- `printBFSWithBF(struct Node* root)`: Prints the tree in breadth-first order along with the balance factors.
  - Utilizes a breadth-first traversal to print the tree level by level, calculating and displaying the balance factors for each node.

#### Rotations and Balancing:
- Similar to the Python implementation, rotations and balancing operations are performed to ensure that the AVL tree remains balanced after insertions and deletions.


## Usage

1. Clone the repository:
   ```
   git clone https://github.com/your-username/avl-tree-python-c.git
   ```

2. Navigate to the repository directory:
   ```
   cd avl-tree-python-c
   ```

3. Compile and run the C implementation:
   ```
   gcc avl_tree.c -o avl_tree
   ./avl_tree
   ```

4. Run the Python implementation:
   ```
   python avl_tree.py
   ```

   
### Conclusion:
Both implementations follow the same principles of AVL trees, employing rotations and balancing techniques to maintain balance and ensure efficient search, insertion, and deletion operations. The Python implementation leverages object-oriented programming while the C implementation focuses on pointers and dynamic memory allocation.



## Contribution

Contributions are welcome! Feel free to submit pull requests or open issues for any improvements or bug fixes.
