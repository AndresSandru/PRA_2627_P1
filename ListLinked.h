
#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 
        Node<T>* first;
		int n;
		Node<T>* getNode(int pos) const{
		Node<T>* current=first;
		for(int i=0; i<pos; i++){
			current=current->next;

		}
		return current;
		}
    public:

		ListLinked(){
			n=0;
			first(nullptr);
		}
		~ListLinked() override{
			while(first!=nullptr){
			Node<T>*aux=first->next;
			delete first;
			first=aux;
			}
		}

    void insert(int pos, T e) override {
        if (pos<0 || pos>n) {
            throw std::out_of_range("Fuera del rango");
        }
        if (pos==0){
            first=new Node<T>(e, first);
        }else{
            Node<T>* prev=getNode(pos-1);
            prev->next=new Node<T>(e, prev->next);
        }
        n++;
   }

    void append(T e) override{
        insert(n, e);
    }

    void prepend(T e) override{
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos<0||pos>=n) {
            throw std::out_of_range("Fuera del rango");
        }
        T val;
        if (pos == 0) {
            Node<T>* aux = first;
            val = aux->data;
            first = first->next;
            delete aux;
        } else {
            Node<T>* prev = getNode(pos - 1);
            Node<T>* target = prev->next;
            val = target->data;
            prev->next = target->next;
            delete target;
        }
        n--;
        return val;
    }

    T get(int pos) override {
        if (pos<0 || pos>=n) {
            throw std::out_of_range("Fuera del rango");
        }
        return getNode(pos)->data;
    }

    int search(T e) override{
        Node<T>* current=first;
        int i=0;
        while (current!=nullptr) {
            if (current->data==e) {
                return i;
            }
            current=current->next;
            i++;
        }
        return -1;
    }

    bool empty()override{
        return n==0;
    }

    int size() override{
        return n;
    }

    T operator[](int pos){
        if (pos<0 || pos>=n){
            throw std::out_of_range("Fuera del rango");
        }
        return get(pos);
    }

    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
        out<<"[";
        Node<T>* current=list.first;
        while(current!=nullptr){
            out<<current->data;
            if (current->next!=nullptr){
                out<<",";
            }
            current=current->next;
        }
        out<<"]";
        return out;
    }

};

