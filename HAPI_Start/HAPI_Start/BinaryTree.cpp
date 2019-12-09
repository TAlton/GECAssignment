#include "BinaryTree.h"

std::shared_ptr<BinaryTree> BinaryTree::s_pBinaryTree = nullptr;

BinaryTree::BinaryTree() {

	m_nodeRoot = nullptr;

}

BinaryTree::~BinaryTree() {

	DestroyTree();

}

void BinaryTree::DestroyTree(Node* leaf) {

	if (nullptr != leaf) {

		DestroyTree(leaf->m_nodeLeft); //destroys the left side sub tree
		DestroyTree(leaf->m_nodeRight); //destroys the right side sub tree

		delete leaf;

	}

}

void BinaryTree::Insert(int id, Node* leaf) {

	if (id < leaf->m_nID) {

		if (nullptr != leaf->m_nodeLeft) { //if id < left node id add the node to the left

			Insert(id, leaf->m_nodeLeft);

		}
		else {

			leaf->m_nodeLeft = new Node;	//creation of the new node
			leaf->m_nodeLeft->m_nID = id;
			leaf->m_nodeLeft->m_nodeParent = leaf;
			leaf->m_nodeLeft->m_nodeLeft = leaf->m_nodeLeft->m_nodeRight = nullptr;

		}

	}
	else if (id >= leaf->m_nID) {

		if (nullptr != leaf->m_nodeRight) { //if id >= leaf node id add the node to the right

			Insert(id, leaf->m_nodeRight);

		}
		else {

			leaf->m_nodeRight = new Node;	//creation of the new node
			leaf->m_nodeRight->m_nID = id;
			leaf->m_nodeRight->m_nodeParent = leaf;
			leaf->m_nodeRight->m_nodeLeft = leaf->m_nodeRight->m_nodeRight = nullptr;

		}

	}

}

void BinaryTree::Insert(int id) {

	if (nullptr != m_nodeRoot) { //if there is a root then add to root

		Insert(id, m_nodeRoot);

	}
	else {

		m_nodeRoot = new Node; //creation of new root if none exists
		m_nodeRoot->m_nID = id;
		m_nodeRoot->m_nodeLeft = m_nodeRoot->m_nodeRight = nullptr;

	}

}

Node* BinaryTree::Search(int id, Node* leaf) {

	if (leaf != nullptr) {

		if (id == leaf->m_nID) {
			return leaf;
		}

		if (id < leaf->m_nID) {

			return Search(id, leaf->m_nodeLeft);

		}
		else {

			return Search(id, leaf->m_nodeRight);

		}

	}

	return nullptr;

}

Node* BinaryTree::Search(int id) {

	return Search(id, m_nodeRoot);

}

void BinaryTree::DestroyTree() {

	DestroyTree(m_nodeRoot);

}

int BinaryTree::GetTreeSize() const {

	return static_cast<int>(vecnTreeNodes.size());

}

Node* BinaryTree::GetParent(int key) {

	if (key <= vecnTreeNodes.size() && key >= 0) {

		Node* n = Search(key);

		return n->m_nodeParent;
	}

	return nullptr;

}

Node* BinaryTree::GetLeftChild(int key) {

	if (key <= vecnTreeNodes.size() && key >= 0) {

		Node* n = Search(key);

		return n->m_nodeLeft;

	}

	return nullptr;

}

Node* BinaryTree::GetRightChild(int key) {

	if (key <= vecnTreeNodes.size() && key >= 0) {

		Node* n = Search(key);

		return n->m_nodeRight;

	}

	return nullptr;

}

void BinaryTree::CreateTree(unsigned int numNodes) {

	std::default_random_engine rand(static_cast<unsigned int>(unSeed)); //setting up random number gen
	std::uniform_int_distribution<int> distrib(0, numNodes - 1);
	auto genRandNum = std::bind(distrib, rand);

	for (int i{ 0 }; vecnTreeNodes.size() < numNodes; i++) {



		vecnTreeNodes.push_back(genRandNum()); //pushes random nums into vector , sorts these numbers and deletes duplicates
		std::sort(vecnTreeNodes.begin(), vecnTreeNodes.end());

		vecnTreeNodes.erase(
			std::unique(vecnTreeNodes.begin(),
				vecnTreeNodes.end()),
			vecnTreeNodes.end());

	}

	std::shuffle(vecnTreeNodes.begin(), vecnTreeNodes.end(), rand); //shuffles the vector as it will be sorted

	for (auto& x : vecnTreeNodes) {

		this->Insert(x);

	}

}