#include<string>
#include<iostream>
#include<exception>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    Node* next;
    float daten;

    Node()
    {
        next=nullptr;
    }
    //Node(float daten):daten(daten),next(nullptr) {};

};

class Stack
{
private:
    Node* last;
    int size;
public:
    Stack();
    Stack(float daten);
    ~Stack();
    float Peek();
    bool isEmpty();
    void push(float daten);
    void pop(); //float
    friend ostream& operator<<(ostream& os, const Stack& oStack);
    friend class StringMashine;
};


class StringMashine//Composition
{
private:
    Stack* stack;
    float result;
    void evalied();
    vector<string> expression;

public:
    StringMashine(vector<string> expression):expression(expression) {};
    float getResult()
    {
        int i=0;
        stack=new Stack;
        std::vector<int>::size_type sz = expression.size();
        while(i<sz)
        {
            if(expression[i]=="-" && i>1)
            {
                float a=stack->last->daten;
                float b=stack->last->next->daten;
                stack->pop();
                stack->last->daten=a-b;

            }
            else if(expression[i]=="+" && i>1)
            {
                float a=stack->last->daten;
                float b=stack->last->next->daten;
                stack->pop();
                stack->last->daten=a+b;
            }
            else if(expression[i]=="POP" && i>0)
            {
                stack->pop();
            }
            else if(expression[i]=="DUP" && i>0)
            {
                float a=stack->last->daten;
                stack->push(a);
            }
            else
            {
                float strFloat=stof(expression[i]);
                stack->push(strFloat);
            }
            i++;
        }
        result=stack->Peek();
        return result;
    }
};
/*
    for(int a=0; a<arr.size(); a++)
    {
        cout<<arr[a]<<" ";
    }
    cout<<endl;
*/
Stack::Stack()
{
    last=nullptr;
    size=0;
}


Stack::Stack(float daten)
{
    last->daten=daten;
    last->next=nullptr;
    size++;
}



bool Stack::isEmpty()
{
    if(size==0)
        return true;
    return false;
}

//throw length_error (

float Stack::Peek()
{
    if(isEmpty())
    {
        throw std::out_of_range("The array is empty");
    }
    else
    {
        return last->daten;
        //cout<<last->daten<<" is last daten "<<size<<" total size."<<endl;
    }

}

void Stack::push(float daten)
{
    Node* newNode=new Node;
    newNode->daten=daten;
    if(!isEmpty())
    {
        newNode->next=last;
        last=newNode;
    }
    else
    {
        newNode->next=nullptr;
        last=newNode;
    }
    size++;
}

ostream& operator<<(ostream& os, const Stack& oStack)
{
    if(oStack.size==0)
    {
        os<<"The array is empty"<<endl;
    }
    else
    {
        os<<oStack.size<<" is the size of Stack and "<<oStack.last->daten<<" the Last element, next: "<<oStack.last->next<<" adresi."<<endl;
    }
    return os;
}

void Stack::pop()
{
    if(!isEmpty())
    {
        Node* a=last;
        last=last->next;
        delete a;
        size--;
    }
    else
    {
        cout<<"It is impossible"<<endl;
    }
}

Stack::~Stack()
{
    while(size!=0)
    {
        Node* temp=last;
        last=last->next;
        delete temp;
        size--;
    }
}




// Function to split the string to words in a vector
// separated by the delimiter
vector<string> split(string str, string delimiter)
{
    vector<string> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
            // Find the index of occurrence
            int idx = str.find(delimiter, start);
            if (idx == string::npos)
            {
                break;
            }

            // If found add the substring till that
            // occurrence in the vector
            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        }
        while (true);
        v.push_back(str.substr(start));
    }

    return v;
}


int main()
{
    cout<<"Choice your operations (POP, DUP, +, -, number, break)"<<endl;
    string b;
    getline(cin,b)
    vector<string> arr=split(b," ");
    StringMashine stringMashine(arr);
    float result=stringMashine.getResult();
    cout<<result;
    return 0;
}
