#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	char value;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

// 创建先序遍历二叉树
TreeNode* createTree() {
	char c;
	scanf(" %c", &c);
	
	if (c == '0') {
		return NULL;
	}
	
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->value = c;
	
	printf("请输入 %c 的左子节点: ", c);
	root->left = createTree();
	
	printf("请输入 %c 的右子节点: ", c);
	root->right = createTree();
	
	return root;
}
TreeNode* createTree1() {
	char c;
	scanf(" %c", &c);
	
	if (c == '0') {
		return NULL;
	}
	
	
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	printf("请输入 %c 的左子节点: ", c);
	root->left = createTree();
	root->value = c;
	printf("请输入 %c 的右子节点: ", c);
	root->right = createTree();
	
	return root;
}
TreeNode* createTree2() {
	char c;
	scanf(" %c", &c);
	
	if (c == '0') {
		return NULL;
	}
	
	
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	printf("请输入 %c 的左子节点: ", c);
	root->left = createTree();
	printf("请输入 %c 的右子节点: ", c);
	root->right = createTree();
	root->value = c;
	
	return root;
}
// 计算节点数目
int countNodes(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	
	return countNodes(root->left) + countNodes(root->right) + 1;
}

// 计算叶子节点数目
int countLeaves(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	
	if (root->left == NULL && root->right == NULL) {
		return 1;
	}
	
	return countLeaves(root->left) + countLeaves(root->right);
}

// 先序遍历
void preOrder(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	
	printf("%c ", root->value);
	preOrder(root->left);
	preOrder(root->right);
}

// 中序遍历
void inOrder(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	
	inOrder(root->left);
	printf("%c ", root->value);
	inOrder(root->right);
}

// 后序遍历
void postOrder(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	
	postOrder(root->left);
	postOrder(root->right);
	printf("%c ", root->value);
}

int main() {
	printf("请输入二叉树先序遍历结果: ");
	TreeNode* root = createTree();
	
	printf("\n先序遍历结果: ");
	preOrder(root);
	
	printf("\n中序遍历结果: ");
	inOrder(root);
	
	printf("\n后序遍历结果: ");
	postOrder(root);
	
	printf("\n节点数目: %d", countNodes(root));
	printf("\n叶子节点数目: %d", countLeaves(root));
	
	return 0;
}
