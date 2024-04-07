/********************************************************************/
/*                                                                  */
/*  A1 Part 2: DList starter file                                   */
/*                                                                  */
/*  Author1 Name: <ARHAAM KHAN>                                       */
/*      - class/function list/main author or main checker           */
/*  Author2 Name: <NEGAR KHALILAZAR>                                       */
/*      - class/function list/main author or main checker           */
/*                                                                  */
/********************************************************************/

#include <utility>

template <typename T>

class DList {
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
	int num_;// keep a track of the number of nodes as seen in lecture slides

public:
	class const_iterator {
		//const iterator as seen in lab4
		friend class DList;
	protected:
		const DList* myList_;
		Node* curr_;
		const_iterator(Node* n, const DList* theList) {
			curr_ = n;
			myList_ = theList;
		}
	public:
		const_iterator() {
			curr_ = nullptr;
			myList_ = nullptr;
		}
		const_iterator& operator++() {
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		const_iterator& operator--() {
			curr_ = curr_->prev_;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator old = *this;
			curr_ = curr_->prev_;
			return old;
		}
		bool operator==(const_iterator rhs) {
			return (this->curr_ == rhs.curr_);
		}
		bool operator!=(const_iterator rhs) {
			return (this->curr_ != rhs.curr_);
		}
		const T& operator*()const {
			return curr_->data_;
		}
	};
	class iterator :public const_iterator {
		//iterator as seen in lab4
		friend class DList;
		iterator(Node* curr, DList* theList) :const_iterator(curr, theList) {}
	public:
		iterator() :const_iterator() {}
		iterator& operator++() {
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator& operator--() {
			this->curr_ = this->curr_->prev_;
			return *this;
		}
		iterator operator--(int) {
			iterator old = *this;
			this->curr_ = this->curr_->prev_;
			return old;
		}
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	DList();
	~DList();
	DList(const DList& rhs);
	DList& operator=(const DList& rhs);
	DList(DList&& rhs)noexcept;
	DList& operator=(DList&& rhs)noexcept;
	iterator insert(iterator it, const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	void sort(iterator first, iterator last);
	bool empty() const;
	int size() const;


	iterator end() {
		//back sentinel
		return iterator(back_, this);
	}
	iterator begin() {
		//first node
		return iterator(front_->next_, this);
	}
	const_iterator cbegin() const {
		//first node
		return const_iterator(front_->next_, this);
	}
	const_iterator cend() const {
		//back sentinel
		return const_iterator(back_, this);
	}

};

template <typename T>
DList<T>::DList() {
	//constructor 
	//make sentinel nodes
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	//intial number of nodes 0
	num_ = 0;
}
template <typename T>
DList<T>::~DList() {
	//deallocate or clean up
	delete front_;
	delete back_;
	front_ = nullptr;
	back_ = nullptr;
	num_ = 0;
}
template <typename T>
DList<T>::DList(const DList& rhs) {
	//simple copy
	this->front_ = nullptr;
	this->back_ = nullptr;
	this->num_ = 0;
	//deallocate first if not empty
	//copy
	*this = rhs;
}
template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs) {
	//if list not empty
	while (num_ != 0)//till all nodes have been deleted
	{//empty the list
		//store node in rm
		//a simple pop  front till all nodes deleted 
		Node* rm = front_->next_;
		front_->next_ = front_->next_->next_;
		delete rm;//delete
		rm = nullptr;
		//reduce number of nodes
		num_--;
	}
	if (this != &rhs)//avoid copying same data
	{
		//contrsuct a sentinel before copying
		front_ = new Node();
		back_ = new Node();
		this->front_->next_ = this->back_;
		this->back_->prev_ = this->front_;
		//deep copy 
		//for (Node* n = rhs.front_->next_; n->next_ != nullptr; n = n->next_)
		for (const_iterator it= rhs.cbegin(); it!= rhs.cend(); ++it)
			this->insert(this->end(), *it);//insert elements from rhs into this in the same order
		//this->num_ = rhs.num_;//copy the number of nodes already happens due to insert incrementing num_
	}
	return *this;
}
template <typename T>
DList<T>::DList(DList&& rhs) noexcept {
	//move
	*this = std::move(rhs);
}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs) noexcept {
	
	if (this != &rhs)
	{
		////deallocate
		this->front_ = nullptr;
		this->back_ = nullptr;
		this->num_ = 0;
		//simple move
		this->front_ = rhs.front_;
		this->back_ = rhs.back_;
		this->num_ = rhs.num_;
		//delete rhs
		rhs.num_ = 0;
		rhs.front_ = nullptr;
		rhs.back_ = nullptr;
	}
	
	return *this;
}


template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it, const T& data) {
	iterator ret;
	//new node would be containaing data
	//new node's next will be the it.curr_ that is the node 'it' points to
	//new nodes's prev will be it.curr_->prev_ that is one before node at 'it'
	Node* current_ = it.curr_;
	Node* nn = new Node(data, current_, current_->prev_);
	//now make the new node be the next_ of the curr_->prev_ (node before node at 'it')
	current_->prev_->next_ = nn;
	//now make the new node the prev_ of the node at 'it'
	current_->prev_ = nn;
	//this completes the insert
	//increase the size
	num_++;
	//return iterator to new node
	ret = iterator(nn, this);

	return ret;
	/* ***NOTE: this above code works in every case;*****
	* if list is empty begin() and end() functions will always given an iterator to the back sentinel
	* as a result in either case we can perform a push back 
	* the above code can be translated to perform a push back
	* for instance:
	* c = begin()/end() i.e., back sentinel
	* c.curr_ is thus front_->next_ or back_ which is simply back_
	* c.curr_->prev_ is always front_ (front sentinel)
	* and the above operations fit that push front and push back implementation 
	* The code below is an alternative way but this above one is much faster
	*/

	//alternative way
	/*if (it==this->end())
	{
	//if end() push back
		Node* nn = new Node(data, back_, back_->prev_);
		back_->prev_->next_ = nn;
		back_->prev_ = nn;
		num_++;
		ret = iterator(nn, this);
	}
	else if(it == this->begin())
	{
	//if begin push front
		Node* nn = new Node(data,front_->next_,front_);
		front_->next_->prev_ = nn;
		front_->next_ = nn;
		num_++;
		ret = iterator(nn, this);
	}
	else
	{*/
	//else find the data element using node traversal and perform the operations to add nodes 
	//the above code is the same but simpler
	/*for (Node* i = front_->next_; i->next_ != nullptr;)
	{
		if (i->data_ == *it)
		{
			Node* nn = new Node(data, i, i->prev_);
			i->prev_->next_ = nn;
			i->prev_ = nn;
			num_++;
			ret = iterator(nn, this);
		}
		i = i->next_;
	}
	return ret;
	}
	*/
	
}

template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data) {
	iterator ret;
	if (num_ != 0)
		//!(empty())
	{
		//node traversal
		for (Node* i = front_->next_; i->next_ != nullptr;)
		{
			//if data matches
			if (i->data_ == data)
			{
				//store iterator
				ret = iterator(i, this);
				//exit loop by making node i as last node
				//after moving to next node i becomes back_ whose next_ = nullptr
				//thus loop ends once data found
				i = back_->prev_;
			}
			else
			{
				//if not found return end()
				ret = this->end();
			}
			i = i->next_;//next node
		}
	}
	else
		//if list empty return end()
		ret = this->end();

	return ret;


}


template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it) {
	
	if (num_ != 0)//if list not empty
		//!(empty())
	{
		Node* rm;//to delete a node
		Node* ret=nullptr;
		//store node at "it"
		rm = it.curr_;
		//store the iterator to the next node
		ret = it.curr_->next_;
		//make the next_ of the node before rm and the next_ of rm
		rm->prev_->next_ = rm->next_;
		//make the prev_ of the node after rm and the prev_ of rm
		rm->next_->prev_ = rm->prev_;
		//this removes rm from the list
		/*delete it;*/
		delete rm;
		rm = nullptr;
		num_--;//reduce size
		return iterator(ret,this);//return iterator
	}

	/*alternative using node traversal looks a bit slow*/
	//if (num_ != 0)
	//{
	//	Node* temp;
	//	Node* ret = nullptr;
	//	for (Node* i = front_->next_; i->next_ != nullptr; )
	//	{
	//		if (i->data_ == *it)
	//		{
	//			temp = i;
	//			i->prev_->next_ = temp->next_;
	//			i->next_->prev_ = temp->prev_;
	//			/*delete t;*/
	//			temp = nullptr;
	//			ret = i->next_;
	//			num_--;
	//			i = back_->prev_;
	//		}
	//		i = i->next_;//otherwise advance the pointer
	//	}
	//	return iterator(ret, this);//return iterator call the constructor
	//}

}

template <typename T>
void DList<T>::sort(iterator first, iterator last) {
	Node* swap;
	iterator it;
	while (first != last)
	{
		//to understand we used the following 
		/*source: https://www.geeksforgeeks.org/how-to-sort-a-linkedlist-in-java/ */
		it = first;
		++it;
		//it is one after the first
		while (it != last) {
			if (*it < *first) {
				//if data at "it" is less than "first" swap the nodes
				// 
				//first swap their next_
				//the diagram shows the logic
				swap = it.curr_->next_;
				it.curr_->next_ = first.curr_->next_;
				first.curr_->next_ = swap;

				//change the prev_ of their next
				//the diagram shows the logic
				it.curr_->next_->prev_ = it.curr_;
				first.curr_->next_->prev_ = first.curr_;

				//swap their prev_
				//the diagram shows the logic
				swap = it.curr_->prev_;
				it.curr_->prev_ = first.curr_->prev_;
				first.curr_->prev_ = swap;

				//change the next of their prev_
				//the diagram shows the logic
				first.curr_->prev_->next_ = first.curr_;
				it.curr_->prev_->next_ = it.curr_;

				//swap and update the iterators
				//to advance the loop
				iterator temp = first;
				first = it;
				it = temp;
				/* once we swap data is in order while loop reaches last with more swaps
				if *it is smaller than the first; first remains same till end is reached
				Then we increment the  iterator*/
			}
			it++;
			//change it to next one
			//once end reached change first and do the same swap and comparing successive nodes
		}
		//change first next one
		first++;
	}

}

template <typename T>
bool DList<T>::empty() const {
	//if empty number of nodes =0
	return (num_ == 0);
}
template <typename T>
int DList<T>::size() const {
	// size is number of nodes
	return num_;
}
