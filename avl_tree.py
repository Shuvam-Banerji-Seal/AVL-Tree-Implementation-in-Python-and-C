class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1  # Initialize height to 1

class AVLTree:
    def __init__(self):
        self.root = None

    def get_height(self, node):
        if node is None:
            return 0
        return node.height

    def get_balance(self, node):
        if node is None:
            return 0
        return self.get_height(node.left) - self.get_height(node.right)

    def right_rotate(self, y):
        x = y.left
        T2 = x.right

        # Perform rotation
        x.right = y
        y.left = T2

        # Update heights
        y.height = max(self.get_height(y.left), self.get_height(y.right)) + 1
        x.height = max(self.get_height(x.left), self.get_height(x.right)) + 1

        return x

    def left_rotate(self, x):
        y = x.right
        T2 = y.left

        # Perform rotation
        y.left = x
        x.right = T2

        # Update heights
        x.height = max(self.get_height(x.left), self.get_height(x.right)) + 1
        y.height = max(self.get_height(y.left), self.get_height(y.right)) + 1

        return y

    def update_height_and_balance(self, node):
        if node is not None:
            node.height = max(self.get_height(node.left), self.get_height(node.right)) + 1

    def insert(self, data):
        self.root = self._insert(data, self.root)
        print("Inserted:", data)
        self.print_bfs_with_bf()

    def _insert(self, data, root):
        if root is None:
            return Node(data)
        elif data < root.data:
            root.left = self._insert(data, root.left)
        else:
            root.right = self._insert(data, root.right)

        self.update_height_and_balance(root)

        balance = self.get_balance(root)

        if balance > 1 and data < root.left.data:
            return self.right_rotate(root)

        if balance < -1 and data > root.right.data:
            return self.left_rotate(root)

        if balance > 1 and data > root.left.data:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        if balance < -1 and data < root.right.data:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root

    def find_min_node(self, root):
        current = root
        while current.left is not None:
            current = current.left
        return current

    def delete(self, data):
        self.root = self._delete(data, self.root)
        print("Deleted:", data)
        self.print_bfs_with_bf()

    def _delete(self, data, root):
        if root is None:
            return root

        if data < root.data:
            root.left = self._delete(data, root.left)
        elif data > root.data:
            root.right = self._delete(data, root.right)
        else:
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left
            else:
                temp = self.find_min_node(root.right)
                root.data = temp.data
                root.right = self._delete(temp.data, root.right)

        self.update_height_and_balance(root)

        balance = self.get_balance(root)

        if balance > 1 and self.get_balance(root.left) >= 0:
            return self.right_rotate(root)

        if balance < -1 and self.get_balance(root.right) <= 0:
            return self.left_rotate(root)

        if balance > 1 and self.get_balance(root.left) < 0:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        if balance < -1 and self.get_balance(root.right) > 0:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root

    def print_bfs_with_bf(self):
        """Prints the tree in a breadth-first manner, showing balance factors."""
        queue = []
        if self.root is not None:
            queue.append(self.root)

        while len(queue) > 0:
            current_level = []
            next_level = []
            for node in queue:
                left_height = self.get_height(node.left)
                right_height = self.get_height(node.right)
                balance_factor = left_height - right_height
                current_level.append(f"{node.data}({balance_factor})")
                if node.left is not None:
                    next_level.append(node.left)
                if node.right is not None:
                    next_level.append(node.right)
            print(" ".join(current_level))
            queue = next_level


# Initialize the tree
tree = AVLTree()

# Menu-based system
while True:
    print("\nAVL Tree Operations:")
    print("1. Insert")
    print("2. Delete")
    print("3. Print Tree with Balance Factors")
    print("4. Exit")

    choice = input("Enter your choice: ")

    if choice == '1':
        data = int(input("Enter a value to insert: "))
        tree.insert(data)
    elif choice == '2':
        data = int(input("Enter a value to delete: "))
        tree.delete(data)
    elif choice == '3':
        print("AVL Tree with Balance Factors:")
        tree.print_bfs_with_bf()
    elif choice == '4':
        print("Exiting...")
        break
    else:
        print("Invalid choice. Please try again.")
