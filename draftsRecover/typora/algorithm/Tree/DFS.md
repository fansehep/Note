### DFS

- 深度优先算法 Depth-First-Search

  ```c++
  int maxDepth(TreeNode* root)
  {
    if(root == nullptr)
    {
        return 0;
    }
    else
    {
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return max(left, right) + 1;
    }
  }