#define DBG 1 //0
#if DBG == 1
#include <iostream>
using std::cout;
#endif
//--------------------- Node - Класс элемента двунаправленного списка ----------------------
struct Node {
    double data;
    Node *next;
    Node *previous;
};
//-------------------- Наше пространство имен с нужными функциями --------------------------
namespace TwoLinkedList{
//--------------------- Создание первого элемента списка -----------------------------------
    Node *make_first(double data){
        Node *first = new Node;
        first->data = data;
        first->previous = 0;
        first->next = 0;
        return first;
    }//Node *make_first
//----------------- Добавление элемента в список -------------------------------------------
    void add(Node **l_end,double data){
        Node *new_node = new Node;
        new_node->data = data;new_node->previous = *l_end,new_node->next = 0;
        (*l_end)->next = new_node;
        *l_end = new_node;    
    }//add
//----------------- Поиск элемента в списке по ключу ---------------------------------------
    Node *find(Node *const l_beg,double key){
        Node *curr_node = l_beg;
        while (curr_node){
            if(curr_node->data == key)break;
            curr_node = curr_node->next;
        }//while(есть что перебирать)
        return curr_node;
    }//Node *find
//---------- Удаление элемента по ключу ----------------------------------------------------
    bool remove(Node **l_beg, Node **l_end, double key){
        if(Node *l_key = find(*l_beg,key)){//если ключ который нужен найден
            if (l_key == *l_beg) {//если наш найденный ключ это начало
                *l_beg = (*l_beg)->next;
                (*l_beg)->previous = 0;
            } else if (l_key == *l_end){//если наш ключ в конце
                *l_end = (*l_end)->previous;
                (*l_end)->next = 0;
            } else {//если наш ключ где-то в середине
                (l_key->previous)->next = l_key->next;
                (l_key->next)->previous = l_key->previous;
            }
            delete l_key;//в любом случае мы удалим ключ если его нашли
            return true;//так как успешно удалили возвращаем true
        }
        return false;//если мы не нашли ключ возвращаем false
    }//bool remove
//---------------- Показ элементов списка --------------------------------------------------
#if DBG == 1
    void show(Node *start){
        cout<<"Elements of two linked list:\n";
        while(start){
            cout<<start->data<<" ";
            start = start->next;
        }
        cout<<"\n";
    }//show
#endif
//------------------------ Вставка элемента после заданного ключа --------------------------
    bool insert(Node *const start,Node **end, double key,double new_key){
        Node *tmp_node = find(start,key);
        if(tmp_node){
            if(tmp_node == *end){//если ключ в конце
                add(end,new_key);
                return true;
            } else {//если элемент в середине
                Node *new_node = new Node;
                new_node->data = new_key;
                new_node->next = tmp_node->next;
                new_node->previous = tmp_node;
                tmp_node->next = new_node;
                (new_node->next)->previous = new_node;
                return true;
            }
        }//если  нашли элемент
        return false;
    }//bool insert
//--------- Вставка до ключа ---------------------------------------------------------------
    bool insert_undo(Node**start,double key,double new_key){
        Node *beg = *start;
        Node *tmp_node = find(beg,key);
        if(tmp_node){
            Node *new_node = new Node;
            if(tmp_node == *start) { // если мы попали в начало
                new_node->data = new_key;
                new_node->previous = 0;
                new_node->next = *start;
                (*start)->previous = new_node;
                *start = new_node;
            } else {                 //если элемент в другом месте
                new_node->data = new_key;
                new_node->next = tmp_node;
                new_node->previous = tmp_node->previous;
                (tmp_node->previous)->next = new_node;
                tmp_node->previous = new_node;
            }
            return true;
        }//если нашли элемент
        return false;//если нет то вернем false
    }//bool insert_undo
//----------------- Добавление с сортировкой -----------------------------------------------
    void add_sort(Node **start,Node**end,double data){
        Node *new_node = new Node;
        new_node->data = data;
        Node *tmp_node = *start;
        while (tmp_node){//Перебираем элементы
            if(data < tmp_node->data){
                new_node->next = tmp_node;//вставляем перед текущим элементом
                if(tmp_node == *start){//если текущий элемент это начало то мы вставим новый и сделаем начало из него
                    new_node->previous = 0;
                    *start = new_node;
                } else {//если где-то в середине то свяжем с предыдущим и следующим элементом
                    (tmp_node->previous)->next = new_node;
                    new_node->previous = tmp_node->previous;
                }
                tmp_node->previous = new_node;//связываем ссылку на предыдущий элемент с нашим новым
                return;
            }//if(Нашли куда вставить)
            tmp_node = tmp_node->next;//Не нашли листаем дальше
        }//while(есть что перебирать)
        //Дошли до конца и не получилось никуда вставить
        //Значит вставляем в конец
        new_node->next = 0;
        new_node->previous = *end;
        (*end)->next = new_node;
        *end = new_node;
    }//add_sort
}//namespace TwoLinkedList