/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: <ARHAAM KHAN>                                */
/*      - class/function list/main author or main checker    */
/*  if any, Author2 Name: <NEGAR KHALILAZAR>                                */
/*      - class/function list/main author or main checker    */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table{
public:
    Table(){}
    virtual bool insert(const std::string& key, const TYPE& value)=0;
    virtual bool modify(const std::string& key, const TYPE& value)=0;
    virtual bool remove(const std::string& key)=0;
    virtual bool find(const std::string& key, TYPE& value)=0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

    struct Record{
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data){
            key_=key;
            data_=data;
        }

    };

    Record** records_;   //the table
    int capacity_;       //capacity of the array

    void grow(){
        Record** newarray=new Record*[capacity_*2+1];
        int sz = numRecords();

        for(int i=0;i<sz;i++){
            newarray[i]=records_[i];
        }
        capacity_*=2;
        delete [] records_;
    }
public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const{return numRecords()==0;}
    virtual int numRecords() const;
    virtual int capacity() const {return capacity_;}

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const{
    int rc=0;
    for(int i=0;records_[i]!=nullptr;i++){
        rc++;
    }
    return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
    records_=new Record*[capacity+1];
    capacity_=capacity;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs){
    records_=new Record*[rhs.capacity_+1];
    capacity_=rhs.capacity_;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
    for(int i=0;i<rhs.numRecords();i++){
        insert(rhs.records_[i]->key_,rhs.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs){
    capacity_=rhs.capacity_;
    records_=rhs.records_;
    rhs.records_=nullptr;
    rhs.capacity_=0;
}

template <class TYPE>
bool SimpleTable<TYPE>::insert(const std::string& key, const TYPE& value){
    int idx=-1;
    int sz=numRecords();
    bool rc=false;
    for(int i=0;i<sz;i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1){
        if(sz == capacity_){
            grow();
        }
        records_[numRecords()]=new Record(key,value);
        for (int i=0; i<sz-1; i++) {      
            for (int j=0; j<sz-1-i; j++){   
                if (records_[j+1]->key_ < records_[j]->key_) {    
                    Record* tmp = records_[j];             
                    records_[j] = records_[j+1];        
                    records_[j+1] = tmp;           
                }
            }
        }
        rc=true;
    }

    return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::modify(const std::string& key, const TYPE& value){
    int idx=-1;
    bool rc=false;
    for(int i=0;i<numRecords();i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx!=-1){
        records_[idx]->data_=value;
    }
    return rc;
}


template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key){
    int idx=-1;
    for(int i=0;i<numRecords();i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx!=-1){
        delete records_[idx];
        for(int i=idx;i<numRecords()-1;i++){
            records_[i]=records_[i+1];
        }
        records_[numRecords()-1]=nullptr;
        return true;
    }
    else{
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value){
    int idx=-1;
    int size = numRecords();
    for(int i=0;i<size;i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1){
        return false;
    }
    else{
        value=records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs){
    if(this!=&rhs){
        if(records_){
            while(numRecords() != 0){
                remove(records_[0]->key_);
            }
            delete [] records_;
        }
        records_=new Record*[rhs.capacity_+1];
        capacity_=rhs.capacity_;
        for(int i=0;i<capacity_;i++){
            records_[i]=nullptr;
        }
        for(int i=0;i<rhs.numRecords();i++){
            insert(rhs.records_[i]->key_,rhs.records_[i]->data_);
        }

    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs){
    if(records_){
        while(numRecords() != 0){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
    records_=rhs.records_;
    capacity_=rhs.capacity_;
    rhs.records_=nullptr;
    rhs.capacity_=0;

    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
    if(records_){
        int sz=numRecords();
        for(int i=0;i<sz;i++){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
}

//CHAINING TABLE
template <class TYPE>
class ChainingTable :public Table<TYPE> {
    struct Record {
        TYPE data_;
        std::string key_;
        Record()
        {
            data_ = TYPE();
            key_ = "";
        }
        Record(const std::string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }
        bool operator==(Record rhs)
        {
            return key_ == rhs.key_;
        }

        bool operator!=(Record rhs)
        {
            return key_ != rhs.key_;
        }

        bool operator<(Record rhs)
        {
            return key_ < rhs.key_;
        }
    };


    DList<Record>** records;
    int capacity_;
    int numRecords_;
    double maxLoadFactor_;
    std::hash<std::string> hashFunction;

    void grow()
    {
        DList<Record>** old = new DList<Record> *[capacity_];
        int oldCap = capacity_;
        for (int i = 0; i < oldCap; i++)
            old[i] = nullptr;
        for (int i = 0; i < oldCap; i++)
        {
            if (records[i] != nullptr)
                old[i] = new DList<Record>(*records[i]);
        }
        capacity_ *= 2;
        records = new DList<Record> *[capacity_];
        numRecords_ = 0;
        for (int i = 0; i < capacity_; i++)
            records[i] = nullptr;
        for (int i = 0; i < oldCap; i++)
        {
            if (old[i] != nullptr)
            {
                auto it = old[i]->begin();
                while (it != old[i]->end())
                {
                    Record e = *it;
                    insert(e.key_, e.data_);
                    it++;
                }
            }
        }
    }

public:
    ChainingTable(int capacity, double maxLoadFactor = 1.0);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    double loadFactor() const;
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor) : Table<TYPE>() {
    capacity_ = capacity;
    maxLoadFactor_ = maxLoadFactor;
    records = new DList<Record> *[capacity_];
    for (int i = 0; i < capacity_; i++)
    {
        records[i] = nullptr;
    }
    numRecords_ = 0;

}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) {
    //*this = other;
    capacity_ = other.capacity_;
    hashFunction = other.hashFunction;
    maxLoadFactor_ = other.maxLoadFactor_;
    numRecords_ = other.numRecords_;
    records = new DList<Record> *[capacity_];
    for (size_t i = 0; i < capacity_; i++)
    {
        if (other.records[i] == nullptr)
        {
            records[i] = nullptr;
        }
        else
        {
            records[i] = new DList<Record>;
            records[i] = other.records[i];
        }
    }

}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) {
    capacity_ = other.capacity_;
    hashFunction = other.hashFunction;
    maxLoadFactor_ = other.maxLoadFactor_;
    numRecords_ = other.numRecords_;
    records = new DList<Record> *[capacity_];
    for (int i = 0; i < capacity_; i++)
    {
        records[i] = std::move(other.records[i]);
    }
    for (int i = 0; i < capacity_; i++)
    {
        if (other.records[i] != nullptr)
        {
            other.records[i] = nullptr;
        }
    }
    other.capacity_ = 1;
    other.maxLoadFactor_ = 1.0;
    other.numRecords_ = 0;

}
template <class TYPE>
bool ChainingTable<TYPE>::insert(const std::string& key, const TYPE& value) {

    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    if (records[idx] == nullptr)
    {
        records[idx] = new DList<Record>();
        Record* e = new Record(key, value);
        auto it1 = records[idx]->begin();
        records[idx]->insert(it1, *e);
        numRecords_++;
        if (loadFactor() > maxLoadFactor_)
        {
            grow();
        }
        return true;
    }
    else
    {
        auto it = records[idx]->begin();
        while (it != records[idx]->end())
        {
            Record e = *it;
            if (e.key_ == key)
                return false;
            it++;
        }
        Record* e = new Record(key, value);
        auto it1 = records[idx]->begin();
        records[idx]->insert(it1, *e);
        numRecords_++;
        if (loadFactor() > maxLoadFactor_)
        {
            grow();
        }
        return true;
    }


}

template <class TYPE>
bool ChainingTable<TYPE>::modify(const std::string& key, const TYPE& value) {

    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    if (records[idx] == nullptr)
    {
        return false;
    }
    else
    {
        auto it = records[idx]->begin();
        while (it != records[idx]->end())
        {
            Record e = *it;
            if (e.key_ == key)
            {
                e.data_ = value;
                auto itr = records[idx]->erase(it);
                records[idx]->insert(itr, e);
                return true;
            }
            it++;
        }
        return false;
    }


}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key) {
    bool removed = false;
    const size_t hash = hashFunction(key);
    const size_t idx = hash % capacity_;
    if (records[idx] == nullptr)
        return false;

    auto it = records[idx]->begin();
    Record e;
    while (it != records[idx]->end())
    {
        e = *it;
        if (e.key_ == key)
        {
            records[idx]->erase(it);
            removed = true;
            break;
        }
        it++;
    }
    return removed;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    if (records[idx] == nullptr)
        return false;

    auto it = records[idx]->begin();
    while (it != records[idx]->end())
    {
        Record e = *it;
        if (e.key_ == key)
        {
            value = e.data_;
            return true;
        }
        it++;
    }
    return false;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) {
    if (this != &other)
    {
        capacity_ = other.capacity_;
        hashFunction = other.hashFunction;
        maxLoadFactor_ = other.maxLoadFactor_;
        numRecords_ = 0;
        records = new DList<Record> *[capacity_];
        for (int i = 0; i < capacity_; i++)
            records[i] = nullptr;
        for (int i = 0; i < other.capacity_; i++)
        {
            if (other.records[i] != nullptr)
            {
                auto it = other.records[i]->begin();
                while (it != other.records[i]->end())
                {
                    Record e = *it;
                    insert(e.key_, e.data_);
                    it++;
                }
            }
        }
    }
    
    return *this;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) {
    for (size_t i = 0; i < capacity_; i++)
    {
        delete records[i];
    }
    delete[] records;
    capacity_ = other.capacity_;
    hashFunction = other.hashFunction;
    maxLoadFactor_ = other.maxLoadFactor_;
    numRecords_ = other.numRecords_;
    records = new DList<Record> *[capacity_];
    for (int i = 0; i < capacity_; i++)
    {
        records[i] = std::move(other.records[i]);
    }
    for (int i = 0; i < capacity_; i++)
    {
        if (other.records[i] != nullptr)
        {
            other.records[i] = nullptr;
        }
    }
    other.capacity_ = 1;
    other.maxLoadFactor_ = 1.0;
    other.numRecords_ = 0;
    return *this;
}

template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {
    delete[] records;
}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
    return numRecords_ == 0;;
}

template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
    return numRecords_;
}
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
    return capacity_;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const {
    return (double)numRecords_ / (double)capacity_;
}


//LP TABLE
template <class TYPE>
class LPTable :public Table<TYPE> {
    struct Record
    {
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data)
        {
            key_ = key;
            data_ = data;
        }
    };

    Record** records;
    double loadFactor_;
    int capacity_;
    int numRecords_;//capacity of the array

    void grow() {
        int oldcap = capacity_;
        Record** oldrecs = new Record * [capacity_ + 1];
        for (int i = 0; i < oldcap; i++)
        {
            oldrecs[i] = records[i];
            records[i] = nullptr;
        }
        delete[] records;
        this->numRecords_ = 0;
        capacity_ *= 2;
        records = new Record * [capacity_ + 1];
        for (int i = 0; i < capacity_; i++)
        {
            records[i] = nullptr;
        }
        for (int i = 0; i < oldcap; i++)
        {
            if (oldrecs[i] != nullptr)
            {
                insert(oldrecs[i]->key_, oldrecs[i]->data_);
                delete oldrecs[i];
            }
        }
        delete[] oldrecs;
    }

    std::hash<std::string> hashFunction;


public:
    LPTable(int capacity, double maxLoadFactor = 0.7);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    double loadFactor() const;
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual int probe(const std::string& key) const;
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity, double maxLoadFactor) : Table<TYPE>() {
    capacity_ = capacity;
    loadFactor_ = maxLoadFactor;
    records = new Record * [capacity];
    for (int i = 0; i < capacity_; i++) {
        records[i] = nullptr;
    }
    numRecords_ = 0;
}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other) {
    capacity_ = other.capacity_;
    hashFunction = other.hashFunction;
    loadFactor_ = other.loadFactor_;
    numRecords_ = other.numRecords_;
    records = new Record * [capacity_];
    for (int i = 0; i < capacity_; i++)
    {
        if (other.records[i] == nullptr)
        {
            records[i] = nullptr;
        }
        else
        {
            records[i] = other.records[i];
        }
    }
}

template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {
    capacity_ = other.capacity_;
    hashFunction = other.hashFunction;
    loadFactor_ = other.loadFactor_;
    numRecords_ = other.numRecords_;
    records = new Record * [capacity_];
    for (int i = 0; i < capacity_; i++)
    {
        if (other.records[i] == nullptr)
        {
            records[i] = nullptr;
        }
        else
        {
            records[i] = other.records[i];
        }
    }
    other.capacity_ = 1;
    other.loadFactor_ = 0.7;
    other.numRecords_ = 0;
    for (int i = 0; i < capacity_; i++)
    {
        other.records[i] = nullptr;
    }
    other.records = nullptr;
}


template <class TYPE>
bool LPTable<TYPE>::insert(const std::string& key, const TYPE& value) {
    bool inserted = false;
    size_t hashval = hashFunction(key);
    size_t idx = hashval % capacity_;
    size_t i = 0;
    if (probe(key) == -1)
    {
        while ((records[(idx + i) % capacity_] != nullptr))
        {
            i++;
        }
        records[(idx + i) % capacity_] = new Record(key, value);
        numRecords_++;
        inserted = true;
    }
    else
    {
        inserted = false;
    }
    if (numRecords_ > (loadFactor_ * capacity_))
    {
        grow();
    }
    return inserted;
}

template <class TYPE>
int LPTable<TYPE>::probe(const std::string& key) const
{
    bool found = false;
    size_t hashval = hashFunction(key);
    size_t idx = hashval % capacity_;
    int i = 0;
    bool stop = false;
    if (numRecords_ > 0) {
        while (!found && i < capacity_ && !stop)
        {
            if (records[(idx + i) % capacity_] != nullptr)
            {
                if (records[(idx + i) % capacity_]->key_ != key)
                {
                    i++;
                }
                else
                {
                    found = true;
                }
            }
            else
            {
                stop = true;
            }
        }
        if (found)
        {
            return (idx + i % capacity_);
        }
    }
    return -1;
}

template <class TYPE>
bool LPTable<TYPE>::modify(const std::string& key, const TYPE& value) {
    int index = probe(key);
    if (index != -1)
    {
        records[index % capacity_]->data_ = value;
        return true;
    }
    return false;
}

template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key) {

    int i = 1;
    int index = probe(key);

    if (index != -1)
    {
        delete records[index % capacity_];
        records[index % capacity_] = nullptr;
        numRecords_--;
        while (records[(index + i) % capacity_] != nullptr && i < capacity_)
        {
            std::string temp_key = records[(index + i) % capacity_]->key_;
            TYPE temp_data = records[(index + i) % capacity_]->data_;
            numRecords_--;
            records[(index + i) % capacity_] = nullptr;
            insert(temp_key, temp_data);
            i++;
        }
        return true;
    }

    return false;
}

template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value) {
    int index = probe(key);

    if (index != -1)
    {
        value = records[index % capacity_]->data_;
        return true;
    }
    return false;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) {

    if (this != &other)
    {
        for (int i = 0; i < capacity_; i++)
        {
            delete records[i];
        }
        delete[] records;
        capacity_ = other.capacity_;
        hashFunction = other.hashFunction;
        loadFactor_ = other.loadFactor_;
        numRecords_ = other.numRecords_;
        records = new Record * [capacity_];
        for (int i = 0; i < capacity_; i++)
        {
            if (other.records[i] == nullptr)
            {
                records[i] = nullptr;
            }
            else
            {
                records[i] = new Record(other.records[i]->key_, other.records[i]->data_);
            }
        }
    }
    return *this;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
    if (this != &other)
    {
        for (int i = 0; i < capacity_; i++)
        {
            delete records[i];
        }
        delete[] records;
        capacity_ = other.capacity_;
        hashFunction = other.hashFunction;
        loadFactor_ = other.loadFactor_;
        numRecords_ = other.numRecords_;
        records = new Record * [capacity_];
        for (int i = 0; i < capacity_; i++)
        {
            if (other.records[i] == nullptr)
            {
                records[i] = nullptr;
            }
            else
            {
                records[i] = new Record(other.records[i]->key_, other.records[i]->data_);
            }
        }

        other.capacity_ = 1;
        other.loadFactor_ = 0.7;
        other.numRecords_ = 0;
        for (size_t i = 0; i < capacity_; i++)
        {
            other.records[i] = nullptr;
        }
        other.records = nullptr;
    }
    return *this;
}

template <class TYPE>
LPTable<TYPE>::~LPTable() {
    delete[] records;
}

template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
    return this->numRecords_ == 0;
}

template <class TYPE>
int LPTable<TYPE>::numRecords() const {
    return this->numRecords_;
}
template <class TYPE>
int LPTable<TYPE>::capacity() const {
    return this->capacity_;
}
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
    return numRecords_ / capacity_;
}
