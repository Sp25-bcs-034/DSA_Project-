#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    string customerId;
    string firstName;
    string lastName;
    string company;
    string city;
    string country;
    string subscriptionDate;
    Node* next;
    Node* prev;
};
Node* head = NULL;
Node* tail = NULL;
void addNode(string customerId, string firstName, string lastName,string company, string city, string country, string subscriptionDate){
   Node* newNode = new Node;
    newNode->customerId     = customerId;
    newNode->firstName      = firstName;
    newNode->lastName       = lastName;
    newNode->company        = company;
    newNode->city           = city;
    newNode->country        = country;
    newNode->subscriptionDate = subscriptionDate;
    newNode->next = NULL;
    newNode->prev = NULL;
    if(head == NULL){
        head = tail = newNode;
        return;
    }
    tail -> next = newNode;
    newNode -> prev = tail;
    tail = newNode;
     
}

void printAll(){
   if(head == NULL){
    cout<<"Linked List is empty"<<endl;
    return;
   }
   Node* temp = head;
   while(temp != NULL){
    cout<< temp -> customerId<<","<<temp->firstName<<","<<temp ->lastName<<","<<temp->city<<","<<temp->company<<","<<temp ->country<<","<<temp ->subscriptionDate<<endl;
    temp = temp -> next;
   }
}
    Node* deleteByCountry(string country){
    Node* temp = head;
    while(temp != NULL){
        if(temp ->country == country){
            Node* del = temp;
            Node* value = temp;
            Node* nextNode = temp->next;
            if(temp -> prev == NULL && temp -> next == NULL){
                head = tail = NULL;
                delete del;
            }
            else if(temp->prev == NULL){
                    head = temp->next;
                    head->prev = NULL;
                    delete del;
            }
            else if(temp -> next == NULL){
                tail = temp -> prev;
                tail -> next = NULL;
                delete del;
            }
            else{
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
            delete del;
        }
        temp = nextNode;
        return value;
        }
        else{
            temp = temp -> next;   
        }
    
    }
}
struct StackNode{
    public:
    Node* data;
    StackNode* next;
    StackNode(){
        data = NULL;
        next = NULL;
    }
};
struct Stack{
    StackNode* top;
    Stack(){
        top = NULL;
    }
    void push(Node* customer){
        StackNode* sn = new StackNode;
        sn -> data = customer;
        sn -> next = top;
        top = sn;
    }
    void pop(){
        if(top == NULL){
            cout<<"Stack is Empty"<<endl;
            return;
        }
        StackNode* temp = top;
        if(top -> next == NULL){
            top = NULL;
            delete temp;
        }
        else{
        top = top -> next;
        delete temp;
        }
    }
    void printing(){
        StackNode* temp = top;
        while(temp != NULL){
            cout<< temp -> data -> customerId<<","<<temp -> data -> firstName<<","<<temp -> data -> lastName<<","<<temp -> data ->city<<","<<temp -> data ->company<<","<<temp -> data -> country<<","<<temp -> data -> subscriptionDate<<endl;
            temp = temp -> next;
        }
    }
};
Stack s1;
void undodeletion(string name){
    Node* value = deleteByCountry(name);
    if(value == NULL){
        cout<<"Nothing is deleted"<<endl;
        return;
    }
    s1.push(value);
    s1.printing();
}
void restore(Node* head){
    if(head == NULL){
        cout<<"ll is empty"<<endl;
        return;
    }
    Node* temp = head;
    while(temp -> next != NULL){
        temp = temp -> next;
    }

}

    void loadFromFile(){
    ifstream fin;
    fin.open("customers-1000.csv");
    if (!fin.is_open()) {
        cout << "Error: Could not open customers-1000.csv\n";
        return;
    }
    string line, word;
    vector<string> lineData;
    int lines = 0;

    while (!fin.eof()) {
        getline(fin, line);
        if (line.empty()) continue;
        stringstream s(line);
        bool inQuotes = false;
        string field = "";
        for (int i = 0; i < (int)line.size(); i++) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                lineData.push_back(field);
                field = "";
            } else {
                field += c;
            }
        }
        lineData.push_back(field);
        if (lines != 0 && lineData.size() >= 11) {
            addNode(lineData[1],lineData[2],lineData[3],lineData[4],lineData[5],lineData[6],lineData[10]);
        }
        lineData.clear();
        lines++;
    }
    fin.close();
    cout << (lines - 1) << " customers loaded from file.\n";
}


int main(){
    loadFromFile();
 deleteByCountry("Macao");
 printAll();
}