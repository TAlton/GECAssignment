#pragma once

class Node {

public:

	int m_nID{ 0 };

	Node();
	~Node();

	Node* m_nodeParent{ nullptr };
	Node* m_nodeLeft{ nullptr };
	Node* m_nodeRight{ nullptr };

	const int GetID() const { return this->m_nID; }
	Node& GetParent() const { return *this->m_nodeParent; }
	Node& GetLeft() const { return *this->m_nodeLeft; }
	Node& GetRight() const { return *this->m_nodeRight; }

};

