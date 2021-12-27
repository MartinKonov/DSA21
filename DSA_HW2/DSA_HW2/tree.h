#pragma once
#include<stdexcept>
#include "employee.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>


class Tree {

	int size;
	size_t level = 0;

	std::vector<Employee*> allEmployees;

public:
	
	Tree();
	~Tree();

	bool find(const string person, const Employee* first)const;

	bool insert(Employee* person, Employee* boss, Employee* first, bool lvl_change);

	int count_employees(const string name_of_person, const Employee* first)const;

	int getSize()const;

	string name_of_boss(const string name_of_person, const Employee* first)const;

	size_t getSize() { return this->size; }

	void count_descendants(const Employee* person, int &counter)const;

	void count_overloaded(int n, const Employee* first, int& count)const ;

	bool fire(string name_of_person, Employee* first);

	size_t height(const Employee* first)const;

	unsigned long paycheck(const Employee* person, const Employee* first)const;

	void fillPairs(const Employee* first, vector<string>* pairs)const;

	bool InTree(string el)const;

	bool InQueue(std::queue<const Employee*> q, Employee* el)const;

	void sortPairs(vector<string>* pairs)const;

	string printTree(const Employee* first)const;

	//---------------------------

	Employee* curEmployee(string name, Employee* first);

	const Employee* curEmployee(string name, const Employee* first)const;

	bool isEmployee(const Employee* person, const Employee* boss)const;

	void merge(const Tree* other, const Employee* other_first ,const Employee* first, Tree& merged, Employee* merged_first, bool& exit_rec)const;

	void fillRestOfOther(Tree& merged, Employee* merged_first, const Employee* first)const;
};

//#pragma once
//
//#ifndef __TREE_HEADER_INCLUDED_
//#define __TREE_HEADER_INCLUDED_
//
//#include <iostream>
//#include <queue>
//
//namespace fmi {
//    namespace sdp {
//
//        template <class DataType>
//        class Tree
//        {
//        public:
//            Tree() : root(nullptr), size(0) {};
//
//            ~Tree() { clear(root); }
//
//            Tree(const Tree& tree)
//                : root(copy(tree.root))
//                , size(tree.size) {};
//
//            Tree(Tree&& tree)
//                : Tree()
//            {
//                std::swap(root, tree.root);
//                std::swap(size, tree.size);
//            };
//
//            Tree& operator=(const Tree& tree)
//            {
//                if (&tree != this) {
//                    clear(root);
//                    root = copy(tree.root);
//                    size = tree.size;
//                }
//                return *this;
//            }
//
//            Tree& operator=(Tree&& rhs)
//            {
//                if (this != &rhs) {
//                    std::swap(root, rhs.root);
//                    std::swap(size, rhs.size);
//                }
//                return *this;
//            }
//
//            bool find(const DataType& key) const { return find(root, key); }
//            bool insert(const DataType& key, int path[])
//            {
//                if (insert(root, key, path)) {
//                    ++size;
//                    return true;
//                }
//                return false;
//            }
//            bool remove(const DataType& key) { return remove(root, key); }
//
//            size_t getSize() const { return size; }
//            size_t getHeight() const { return height(root); }
//
//            template <class Function>
//            void map(const Function& fun) { map(fun, root); }
//
//            void print() {
//                map([](const DataType& x) {std::cout << x << ' '; });
//                std::cout << '\n';
//            }
//
//            void printByLevels() const { printByLevels(root); }
//        private:
//            struct node
//            {
//                DataType data;
//                node* child, * brother;
//
//                node(const DataType& data, node* child = nullptr, node* brother = nullptr)
//                    : data(data)
//                    , child(child)
//                    , brother(brother)
//                {}
//            } *root;
//
//            size_t size;
//
//        private:
//
//            void clear(node* root)
//            {
//                if (root) {
//                    clear(root->child);
//                    clear(root->brother);
//                    delete root;
//                }
//            }
//
//            node* copy(node* root)
//            {
//                return root ?
//                    new node(root->data, copy(root->child), copy(root->brother)) :
//                    root;
//            }
//
//            bool find(const node* root, const DataType& key) const
//            {
//                if (!root) return false;
//                if (root->data == key) return true;
//                return find(root->brother, key) || find(root->child, key);
//            }
//
//            size_t height(const node* root) const
//            {
//                if (!root) return 0;
//                return std::max(1 + height(root->child), height(root->brother));
//            }
//
//            template <class Function>
//            void map(const Function& fun, node* root) {
//                if (root) {
//                    fun(root->data);
//                    map(fun, root->brother);
//                    map(fun, root->child);
//                }
//            }
//
//            bool remove(node*& root, const DataType& key) {
//                if (!root) return false;
 //
//                if (root->data == key) {
//                    node* toDelete = root;
//                    if (!root->child) {
//                        root = root->brother;
//                    }
//                    else if (root->brother) {
//                        node* it = root->child;
//                        while (it->brother) it = it->brother;
//                        it->brother = root->brother->child;
//                        root->brother->child = root->child;
//                        root = root->brother;
//                    }
//                    else {
//                        root = root->child;
//                    }
//                    --size;
//                    delete toDelete;
//                    return true;
//                }
//                else {
//                    return remove(root->brother, key) || remove(root->child, key);
//                }
//            }
//
//            bool insert(node*& root, const DataType& key, const int* path)
//            {
// //               ������ ���� ���� �� ������
//                if (path[0] < 0) {
//                    root = new node(key, nullptr, root);
//                    return true;
//                }
//
////                 ���� ��������� -> ������ ���?
//                if (!root) return false;
//
// //                ������ ������ � ������������ �� ������
//                if (path[0] == 0) {
//                    return insert(root->child, key, path + 1);
//                }
//
// //                ������ �������� ��������� � ����������
//                node* it = root;
//                int pos = path[0];
//                while (it->brother && pos > 0) {
//                    it = it->brother;
//                    --pos;
//			          }
//                return it->brother ? insert(it->brother->child, key, path + 1) : false;
//            }
//
//            void printByLevels(const node* root) const
//            {
//                if (!root) return;
//                std::queue<const node*> front;
//                front.push(root);
//                front.push(nullptr);
//                for (;;) {
//                    const node* current = front.front();
//                    front.pop();
//                    if (!current) {
//                        std::cout << '\n';
//                        if (front.empty()) return;
//                        front.push(nullptr);
//                    }
//                    else {
//                        std::cout << current->data << ' ';
//                        for (const node* it = current->child; it; it = it->brother) {
//                            front.push(it);
//                        }
//                    }
//                }
//            }
//        };
//
//    } //namespace sdp
//} //namespace fmi
//
//#endif //__TREE_HEADER_INCLUDED_