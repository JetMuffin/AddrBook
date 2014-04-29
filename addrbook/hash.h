#ifndef HASH_H
#define HASH_H
#include <iostream>
#include  <fstream>
using namespace std;

class HashElem
{
private:
    string Num;
    string Name;
    string Addr;
public:
    HashElem(string Num,string Name,string Addr)
    {
        this->Num = Num;
        this->Name = Name;
        this->Addr = Addr;
    }

    string getNum()
    {
        return Num;
    }

    string getName()
    {
        return Name;
    }

    string getAddr(){
        return Addr;
    }
};



class HashTable
{
private:
    int cnt;
    int size;
public:

    HashElem **table;

    int getSize(){
        return size;
    }

    HashTable(int max)
    {
        size = max;
        table = new HashElem *[this->getSize()];
        for (int i = 0; i < this->getSize(); i++)
        {
            table[i] = NULL;
        }
    }

    int getCnt()
    {
        return this->cnt;
    }

    int GetKey(string num){
        int key=0,len = num.length();
        for(int i=0;i<len;i++){
            key+=num[i];
        }
        key %= this->getSize();
        return key;
    }

    int Search (string num)
        {
            int key=GetKey(num);
            int di = 1;
            while (di < this->getSize()/2)
            {
                if(table[key]==NULL)
                    return -1;
                else if (table[key]->getNum()==num)
                    return key;
                else if (di > 0)
                {
                    key = key + (di*di);
                    di = -di;
                    if (key < 0) key = this->getSize() + key;
                    key %= this->getSize();
                 }
                else
                {
                    key = key - (di*di);
                    if (key < 0) key = this->getSize() + key;
                    di = -di;
                    key %= this->getSize();
                    di ++;
                }
            }
            return -1;
      }


    void Insert(string Name,string Num,string Addr)
    {
        int odd=1,r=1;
        int key = GetKey(Num);
        //若是有冲突，用二次探测再散列法解决冲突
        while (table[key] != NULL)
        {
            if(odd)
            {
                key=(key+r*r)%this->getSize();
                odd=0;
            }
            else
            {
                key=(key-r*r)%this->getSize();
                odd=1;
                r++;
            }
        }
        table[key] = new HashElem(Num,Name,Addr);
        cnt ++;
    }

    void Destroy()
    {
        for (int i = 0; i < this->getSize(); i++)
        {
            table[i] = NULL;
        }
        cnt = 0;
    }
};


#endif // HASH_H
