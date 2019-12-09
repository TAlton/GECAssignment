#pragma once

#include <random>
#include <future>
#include <set>
#include <stdexcept>

#include "Node.h"

class BinaryTree {

public:

	static std::shared_ptr<BinaryTree>& GetInstance() {

		if (!s_pBinaryTree)
			s_pBinaryTree.reset(new BinaryTree());
		return s_pBinaryTree;

	}

	~BinaryTree();

	void Insert(int id);
	void CreateTree(unsigned int numNodes);
	void DestroyTree();

	Node* GetTree() const { return this->m_nodeRoot; }
	int GetTreeSize() const;
	Node* GetParent(int key);
	Node* GetLeftChild(int key);
	Node* GetRightChild(int key);
	Node* Search(int id);

	std::vector<int> vecnTreeNodes;

protected:
private:

	BinaryTree();

	static std::shared_ptr<BinaryTree> s_pBinaryTree;

	Node* m_nodeRoot;
	std::chrono::milliseconds::rep unSeed = std::chrono::system_clock::now().time_since_epoch().count();

	void Insert(int id, Node* leaf);
	void DestroyTree(Node* leaf);
	Node* Search(int id, Node* leaf);

};

#define BINARYTREE BinaryTree::GetInstance()