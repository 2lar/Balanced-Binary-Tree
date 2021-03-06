#include <string>

class Node
{
public:
  int   data_{};
  Node *left_  = nullptr;
  Node *right_ = nullptr;

  Node() = default;
  Node(int data, Node *l = nullptr, Node *r = nullptr)
      : data_(data), left_(l), right_(r){}
};

class BinTree{

  Node *root_ = nullptr;
  int   size_ = 0;

  auto prefix(Node *root) -> std::string;
  auto infix(Node *root) -> std::string;
  auto postfix(Node *root) -> std::string;
  auto is_full(Node *root) -> bool;
  auto insert(int d, Node *root) -> void;
  auto size(Node *root) -> int;
  auto del(Node *root) -> void;

public:
  auto size() -> int;
  auto insert(int d) -> void;
  auto righttmost_leaf() -> int;
  auto leftmost_leaf() -> int;

  auto prefix() -> std::string;
  auto postfix() -> std::string;
  auto infix() -> std::string;

  ~BinTree(){
    del(root_);
  }
};

auto
    BinTree::del(Node *root) -> void{
  if (!root)
    return;
  if (root->left_)
    del(root->left_);
  if (root->right_)
    del(root->right_);
  delete root;
}

auto
    BinTree::size() -> int{
  return size(root_);
}

auto
    BinTree::size(Node *root) -> int{
  return root ? size(root->left_) + size(root->right_) + 1 : 0;
}

auto
    BinTree::is_full(Node *root) -> bool{
  return size(root->left_) == size(root->right_);
}

auto
    BinTree::insert(int d) -> void{
  if (root_ == nullptr)
    root_ = new Node{ d };
  else
    insert(d, root_);
}

auto
    BinTree::insert(int d, Node *root) -> void{
  if (root->left_ == nullptr)
    root->left_ = new Node{ d };
  else if (root->right_ == nullptr)
    root->right_ = new Node{ d };
  else if (size(root->left_) != size(root->right_) && is_full(root->left_))
    insert(d, root->right_);
  else
    insert(d, root->left_);
}

auto
    BinTree::righttmost_leaf() -> int{
  auto root = root_;
  while (root->right_)
    root = root->right_;
  return root->data_;
}

auto
    BinTree::leftmost_leaf() -> int{
  auto root = root_;
  while (root->left_)
    root = root->left_;
  return root->data_;
}

auto
    BinTree::prefix() -> std::string{
  return prefix(root_);
}

auto
    BinTree::prefix(Node *root) -> std::string{
  if (root != nullptr)
    return std::to_string(root->data_) + prefix(root->left_) +
           prefix(root->right_);
  return {};
}

auto
    BinTree::infix() -> std::string{
  return infix(root_);
}

auto
    BinTree::infix(Node *root) -> std::string{
  if (root)
    return infix(root->left_) + std::to_string(root->data_) +
           infix(root->right_);
  return {};
}

auto
    BinTree::postfix() -> std::string{
  return postfix(root_);
}

auto
    BinTree::postfix(Node *root) -> std::string{
  if (root)
    return postfix(root->left_) + postfix(root->right_) +
           std::to_string(root->data_);
  return {};
}
