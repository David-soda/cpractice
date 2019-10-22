#include <iostream>
#include <stack>
using namespace std;
#define none '#'        
typedef char TelemType; // 节点数据域类型

// 二叉链表存储 
typedef struct Binode {
	TelemType data;
	struct Binode* left, * right;
}Binode, * Bitree;
// 按先序输入建立二叉树 
int createBiTree(Bitree& T) {
	TelemType ch;
	cin>>ch;
	if (ch == none) T = NULL;
	else {
		T = new Binode;
		T->data = ch;
		createBiTree(T->left);
		createBiTree(T->right);
	}
	return 1;
}
// 按照先序遍历二叉树 
int preOrder(Bitree T) {
	if (T) {
		cout << T->data;
		preOrder(T->left);
		preOrder(T->right);
		return 1;
	}
	else return 0;
}
//中序遍历
int inOrder(Bitree T) {
	if (T) {
		if (T->left) inOrder(T->left);
		cout<<T->data;
		if (T->right) inOrder(T->right);
		return 1;
	}
	else return 0;
}
//后序遍历
int postOrder(Bitree T) {
	if (T) {
		if (T->left) postOrder(T->left);
		if (T->right) postOrder(T->right);
		cout<< T->data;
		return 1;
	}return 0;
}
//非递归中序遍历 
int inOrderTraverse1(Bitree T) {
	stack<Bitree> s;  //存放节点指针
	s.push(T);
	while (!s.empty()) {
		while (s.top()) s.push(s.top()->left);  //向左走到尽头
		s.pop(); //空指针退栈
		if (!s.empty()) {
			Bitree t = s.top();
			s.pop(); // 根节点出栈 
			cout<< t->data;
			s.push(t->right);
		}
	}
	return 1;
}
int inOrderTraverse2(Bitree T) {
	stack<Bitree> s;
	Bitree p = T; //当前遍历节点 
	while (!s.empty() || p) {
		if (p) {
			s.push(p); //根节点进栈
			p = p->left; //遍历左子树 
		}
		else {
			p = s.top();
			s.pop(); //返回上一根节点
			cout<< p->data;
			p = p->right; // 遍历右节点  
		}
	}
	return 1;
}

//非递归前序遍历
int preOrderTraverse1(Bitree T) {
	stack<Bitree> s;
	s.push(T);
	Bitree p;
	while (!s.empty()) {
		while (s.top()) {
			p = s.top();
			cout<< p->data; //先访问根
			s.push(p->left);//向左走到尽头 
		}
		s.pop(); //空指针出栈 
		if (!s.empty()) {
			p = s.top(); //退回上一层的根节点
			s.pop();
			s.push(p->right);
		}
	}
	return 1;
}

int preOrderTraverse2(Bitree T) {
	stack<Bitree> s;
	Bitree p = T; //当前访问节点
	while (!s.empty() || p) {
		if (p) {
			cout<< p->data;
			s.push(p);
			p = p->left; //访问左节点
		}
		else {
			p = s.top(); //返回上一根节点
			s.pop();
			p = p->right;
		}
	}
	return 1;
}
// 非递归先序遍历，按照节点的访问顺序压栈 根-左-右
void preOrderTraverse3(Bitree T) {
	stack<Bitree> s;
	while (T) {
		cout<<T->data;//先访问根
		//先把右子树压栈，
		//把左子树访问之后再访问右子树 
		if (T->right) s.push(T->right);
		T = T->left; //类似递归访问左子树
		if (T == NULL && !s.empty()) { //如果左子树为空，则访问右子树 
			T = s.top();
			s.pop();
		}
	}
}
//非递归后序遍历
/*
* 1.如果是叶子节点，则输出
* 2.如果左子树访问完，且右子树为空，则输出
* 3.如果左右子树访问完，则输出
* 4.否则将右、左子树依次压栈
* 用last表示最后一个访问过的节点
*/
int postOrderTraverse1(Bitree T) {
	stack<Bitree> s;
	Bitree p; //当前访问节点
	Bitree last; //最后一个访问过的节点 
	last = p = T;
	s.push(T);
	while (!s.empty()) {
		p = s.top();
		if ((p->left == NULL && p->right == NULL)
			|| (p->right == NULL && last == p->left)
			|| (last == p->right)) {
			cout<< p->data;
			s.pop();
			last = p;
		}
		else {
			if (p->right) s.push(p->right);
			if (p->left) s.push(p->left);
		}
	}
	return 1;
}
void postOrderTraverse2(Bitree T) {
	stack<Bitree> s;
	Bitree p = T;
	s.push(p); s.push(p);
	while (!s.empty()) {
		p = s.top();  s.pop(); //取栈顶根节点
		if (p == s.top() && !s.empty()) { //表示该节点的孩子结点还为访问 
			if (p->right) {
				s.push(p->right); s.push(p->right);
			}
			if (p->left) {
				s.push(p->left); s.push(p->left);
			}
		}
		else cout<< p->data; //第二次接触，表示孩子结点已经访问完
	}
}
//设置标志位
typedef struct flagNode {
	int flag;  //是不是第一次出现再栈顶 
	Binode* bnode;
}flagNode;
void postOrderTraverse3(Bitree T) {
	stack<flagNode*> s;
	Bitree p = T;
	flagNode* temp;
	while (p || !s.empty()) {
		while (p) { //向左走到尽头 
			flagNode* fnode = new flagNode;
			fnode->bnode = p;
			fnode->flag = 1;
			s.push(fnode);
			p = p->left;
		}
		if (!s.empty()) {
			temp = s.top(); s.pop();
			if (temp->flag) {//第一次
				temp->flag = 0;
				s.push(temp);
				p = temp->bnode->right; //访问右子树 
			}
			else {
				cout<<temp->bnode->data;
				p = NULL; //退回上一层 
			}
		}
	}
}
int main() {
	cout<<"输入二叉链表："
	Bitree T;
	createBiTree(T);
	cout << "先序遍历：";
	preOrder(T);
	cout << "\n后序遍历：";
	postOrder(T);
	cout << "\n中序遍历：";
	inOrder(T);
	cout << endl;
	cout << "\n非递归先序遍历：";
	preOrderTraverse1(T);
	cout << "\n非递归后序遍历：";
	postOrderTraverse1(T);
	cout << "\n非递归中序遍历：";
	inOrderTraverse1(T);

	return 0;
}