//ARHAAM KHAN
//162087217

#include <iostream>

//DList
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
public:
	DList() {
		front_ = nullptr;
		back_ = nullptr;
	}
	void push_front(const T& data);
	~DList();

	class const_iterator {
		friend class DList;
	protected:
		const DList* myList_;
		Node* curr_;
		const_iterator(Node* n, const DList* List) {
			curr_ = n;
			myList_ = List;
		}
	public:
		const_iterator() {
			myList_ = nullptr;
			curr_ = nullptr;
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
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				if (myList_)
				{
					curr_ = myList_->back_;
				}
			}
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator old = *this;
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				if (myList_)
				{
					curr_ = myList_->back_;
				}
			}
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
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_)
				{
					this->curr_ = this->myList_->back_;
				}
			}
			return *this;
		}
		iterator operator--(int) {
			iterator old = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_)
				{
					this->curr_ = this->myList_->back_;
				}
			}
			return old;
		}
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}

	};

	const_iterator cbegin() const {
		return const_iterator(front_, this);
	}

	iterator begin() {
		return iterator(front_, this);
	}

	const_iterator cend() const {
		return const_iterator(nullptr, this);
	}
	iterator end() {
		return iterator(nullptr, this);
	}
};


template <typename T>
void DList<T>::push_front(const T& data) {
	Node* nn = new Node(data, front_, nullptr);
	if (front_)//If not empty
	{
		front_->prev_ = nn;
	}
	else//if empty
	{
		back_ = nn;
	}
	front_ = nn;
}


template <typename T>
DList<T>::~DList() {
	//deallocation
	//clean up
	delete front_;
	delete back_;
	front_ = nullptr;
	back_ = nullptr;
}


//Sentinel
template <typename T>
class Sentinel {
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
public:
	Sentinel() {
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator {
		friend class Sentinel;
	protected:
		const Sentinel* myList_;
		Node* curr_;
		const_iterator(Node* n, const Sentinel* theList) {
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
		friend class Sentinel;
		iterator(Node* curr, Sentinel* theList) :const_iterator(curr, theList) {}
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
	const_iterator cbegin() const {
		return const_iterator(front_->next_, this);
	}
	iterator begin() {
		return iterator(front_->next_, this);
	}
	const_iterator cend() const {
		return const_iterator(back_, this);
	}
	iterator end() {
		return iterator(back_, this);
	}
};


template <typename T>
void Sentinel<T>::push_front(const T& data) {
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}


template <typename T>
Sentinel<T>::~Sentinel() {
	//deallocation
	//clean up
	delete front_;
	delete back_;
	front_ = nullptr;
	back_ = nullptr;
}