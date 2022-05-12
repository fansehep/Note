# **AVL树(c++)**
- 1.基于前面二叉搜索树(BST)的学习，我们大概知道了二叉搜索树的初步模型，但是但我们用一个有序的数组插入到二叉搜索树的时候，这个树会退化为单链表，他的搜索的时间复杂度会从O(log2(n)) 变为 O (n) ,这对性能影响很大，那么我们该如何阻止这种事情发生呢?,那肯定是在这种树插入删除节点的时候，让他自己平衡了。我觉得发明这个树得人太厉害了。这两位大神是G. M. Adelson-Velsky和Evgenii Landis，好的，话不多说，上代码。
- 2.是这样的，考虑向一个BST插入一个有序数组，先看图片。
```c++
template<typename type>
struct Node
{
    type m_val;
    Node* left = nullptr;   //左节点
    Node* right = nullptr;  //右节点
    int m_deepth = 0;       //树的深度
    Node(type val)
    {
        this->m_val = val;
    }
    ~Node()
    {
        delete left;
        delete right;
    }
};
```


```c++
  1.插入 8
  	    8
	 /    \
  2.插入 9
        8
     /    \
		   9
  3.插入 10
        8
      /   \
           9
            \
             10
  。。。。。。此处省略N步
```
 - 1.我们直到依次这样插入下去，他就会变成单链表，那么该如何阻止他呢，那肯定想到，如果我的根节点是 9 就很好了，没错！
 - 2.我们需要这里进行一个操作,我们需要进行左旋转,让9成为根节点，
 ```c++
 			    8   root 
		          /   \
      				9 root->right 
      				  \
      				   10
 ```
 ```c++
 ```c++
	 Node<type>* newhead = root->right;
     root->right = newhead->left;
     newhead->left = root;
     /*这里就是左旋操作，先保存根节点的右节点，再让根节点的右节点指向
     原来root->right的那个左节点，这里因为也要考虑 9 这个节点的左节点的
     值，因为我们旋转这颗树的时候，不可能单一旋转某一个节点，因为9
     的左子树都是 >8 && < 9 的，所以需要将 8 的右节点指向 9的左子树。
	*/
	//他就变成了这样
	 		9
	 	  /    \
	 	8       10     
```
 - 1现在已经有了左旋操作，那么你肯定能想到右旋操作，右旋操作呢，与上面同理·
```c++
	   10
      /
	9
   /
 8
 //右旋代码·
 {
	 Node<type>* newhead = root->left;
     root->left = newhead->right;
     newhead->right = root;
 }	
```
- 1.好了，你现在肯定对左旋和右旋有了一些基本的认知了，那么有时候我们会遇到下面这两种特殊情况，该如何处理呢?
```c++
		10             
	  /	
     6
       \
        9
```
- 2.我们发现我们已经不能通过基本的单步左旋和右旋来让他平衡了，那可以看到如果将 9 那个节点放到6的位置，并将9的左节点变为6那不就很完美了，对，没错！！！
```c++
	10
   / 
  9
 /
6
```
```c++
	 9
   /  \
  6    10
```
- 3.那么这两部操作就是先左旋转 6 那个节点 ，再右旋转 10 那个根节点。那么扩展一下，既然有左右旋转，那么肯定有右左旋转。是的，具体自己看哦
# 二 AVL树的具体实现
- 1.由于这是一颗平衡二叉搜索树，所以他肯定有一个根节点，
```c++
template<typename type>
class AVL_Tree
{
private:
    Node<type>* m_root = nullptr;
    int   m_size = 0;
    // !!!!这个函数用于返回当前树的高度,很重要！！！！
    int get_height(Node<type>* root)
    {
        if( root == nullptr )
        {
            return 0;
        }
        else
        {
            return root->m_deepth;
        }
    } 
};
/*看Node的定义，我们可以看到它里面有一个树的高度的定义。这个很关键，
用于判断某一个树是否该左旋还是右旋，因为AVL树的定义就是要求左右子树的
高度差不允许 > 2的。*/
```
- 1.增加一个节点，详解
```c++
    void add(type val)
    {	//这里采用递归的方式，需要将add方法放到public中，_Insert_Node函数放入private中
        _Insert_Node(val,this->m_root);
    }
	Node<type>* _Insert_Node(type val,Node<type>* root)
    {
    	//用于递归并进行判断，如果当前节点为nullptr,那么就直接赋值返回
        if( root == nullptr )
        {
            root = new Node<int>(val);
            root->m_deepth = 1;
            return root;
        }
        if( val < root->m_val )
        {
        	//二分法，如果小于当前节点的值，就去左子树
            root->left = _Insert_Node(val,root->left);
        }
        else if( val > root->m_val )
        {
            root->right = _Insert_Node(val,root->right);
        }
        //注意！！！这个地方很重要，由于上面的函数是由递归查找的，所以其实这里每一个节点的值都会被更新
        //我们会在左右子树的高度值中选取最大的，并且包含自己的,所以需要+1
        root->m_deepth = 1 + max(get_height(root->left),get_height(root->right));
		//左右子树的高度差，！！！！！这里也会不断递归，这个用于判断左右子树是左旋还是右旋。
		int bal = get_height(root->left) - get_height(root->right);
		//当左子树的高度 > 右子树的高度
		if( bal > 1 )
        {	
        	// 将所需要插入的值与他的父亲节点比较，是插入左边还是右边
        	// 1. 插入到左边，所以直接右旋即可
            if( val < root->left->m_val )
            {	//这里的右旋只需要旋转局部的树即可，所以这里其实一共真正只操作了3个节点
                right_Rotation(root);
            }
            else
            {	
                //这边就比较麻烦了，需要先左右旋转。
                // 这里用了一个很巧妙的办法，就是让root->left直接去接受右旋后操作的返回节点，！
                root->left = left_Rotation(root->left);
                // 左旋
                return right_Rotation(root);
            }
        }
		//这里同理，
        else if( bal < -1 )
        {
            if( val > root->right->m_val )
            {
                return left_Rotation(root);
            }
            else
            {
                root->right = right_Rotation(root->right);
                return left_Rotation(root);
            }
        }
        return root;
    }
```
- 提示:代码设计很巧妙，建议大家多模拟几遍，去感受这个魅力。
 - 2.删除一个节点
 ```c++
 	bool erase(type val)  //public方法
    {
        if( _Delete_Node_(val,this->m_root) )
        {
            return true;
        }
        return false;
    }
	 Node<type>* _Delete_Node_(type val,Node<type>* root) //private方法
    {
    	//这里同样也是用的递归二分法实现的
        if( root == nullptr )
        {
        	//当前节点为空时，直接返回空
            return nullptr;
        }
        if( val < root->m_val )
        {
            return _Delete_Node_(val,root->left);
        }
        else if( val > root->m_val )
        {
            return _Delete_Node_(val,root->right);
        }
        //找到节点了！
        else
        {
        	//当所需删除元素右子树为空时
            Node<type>* p = root->right;
            if( root->right == nullptr )
            {
            	//这里直接接上即可
                Node<type>* l = root->left;
                delete(root);
                root = l;
            }
	       else if( root->left == nullptr )
            {
                delete(root);
                root = p;
            }
            //左右子节点都不为空
            else
            {
            	// !!!!这个设计也很巧妙，这里呢由于所需删除的节点的左右子树都不为空
            	// 他先用一个指针扫到根节点(所需删除节点）的右子树的最左边
                while( p->left != nullptr )
                {
                    p = p->left;
                }
                root->m_val = p->m_val;	//直接赋值，完全符合，
                 //所以呢，我们就需要找到这个元素，在根节点的右子树了，不得不佩服这个设计
                root->right = _Delete_Node_(val,root->right);
            }
        }
        // 删除叶子节点，直接返回
        if( root == nullptr )
        {
            return root;
        }
        //删除完节点可能会导致一些节点的左右树的高度失衡，这个函数本来会自己递归，
        //根节点的高度的重新赋值
        root->m_deepth = 1 + max(get_height(root->left)，get_height(root->right));
        //考虑当前节点的失衡情况
        int bal = get_height(root->left) - get_height(root->right);
		//左子树的高度大于右子树的高度
        if( bal > 1)
        {
            if( get_height(root->left) >= get_height(root->right) )
            {
                return right_Rotation(root); //直接右旋即可
            }
            //左子树的高度 < 右子树的高度
            else
            {
            	//这里同插入节点那个操作有点像，可以类比一下,这里需要左右旋转一下
                root->left = left_Rotation(root->left)；
                return right_Rotation(root);
            }
        }
        else if( bal < -1 )
        {
            if( get_height(root->right) >= get_height(root->left) )
            {
                return left_Rotation(root);
             }
            else
            {   
                root->right = right_Rotation(root->right);
                return left_Rotation(root);
            } 
        }
        return root;
    }
```
- 3.查找一个节点
```c++
Node<type>* _Find_(type val ,Node<type> root)	//private方法
{ 
	//一个递归即可
	if( root == nullptr )
	{
		return nullptr;
	}
	if( val == root->m_val )
	{
		return root;
	}
	else if( val > root->m_val )
	{
		return _Find_(val, root->right);
	}
	else if( val < root->m_val )
	{
		return _Find_(val, root->left);
	}
}
```
 - 4.析构函数我就不写了，可以直接用我上一篇二叉搜索树的析构函数。
- # 总结
- **AVL树是一种平衡二叉搜索树，左右树的高度 <= 1，他这种自我平衡的实现还是很厉害的，大家可以多模拟多模拟，这里真的很敬佩那两个发明这种树得人。**


