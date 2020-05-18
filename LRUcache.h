//
// Created by kevin yan on 2020-05-18.
//

#ifndef INTERVIEWALGO_LRUCACHE_H
#define INTERVIEWALGO_LRUCACHE_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

struct DLNode{
    string key;
    int value;
    DLNode *prev,*next;
};

class LRUcache{
private:
    map<string, DLNode*> cache;
    int capacity;//page capacity
    DLNode *head,*tail;//double linked list
    int dln_len;

public:
    LRUcache(int cap):capacity(cap),dln_len(0){
        head=new DLNode();
        tail=new DLNode();
        head->next=tail;
        head->prev=NULL;
        tail->prev=head;
        tail->next=NULL;
    }

    ~LRUcache(){
        //release map's pointer point to memory area
        auto iter=cache.begin();
        while(iter!=cache.end())
        {
            delete iter->second;
            iter->second=NULL;
            cache.erase(iter++);
        }
        delete head;
        delete tail;
    }
    void RemoveDLNode(DLNode *node)
    {
        //remove not release
        DLNode *prev=node->prev;
        DLNode *next=node->next;
        prev->next=next;
        next->prev=prev;
        dln_len--;
    }
    /*
     * always remove weed out page at the end of DLList */
    void SetToHead(DLNode *node)
    {
        DLNode *tem=head->next;
        head->next=node;
        node->prev=head;
        node->next=tem;
        tem->prev=node;
        dln_len++;
    }

    /*
     * insert into cache, if exists, update*/
    int Set(string key,int value)
    {
        auto iter=cache.find(key);
        if(iter!=cache.end())//cache hit
        {
            if(dln_len>=capacity)
                RemoveDLNode(tail->prev);
            SetToHead(iter->second);
            return iter->second->value;
        }else
        {
            //hit failed
            DLNode *node=new DLNode();
            node->key=key;
            node->value=value;
            if(dln_len>=capacity)//if cache full need weed out
            {
                RemoveDLNode(tail->prev);
                SetToHead(node);
            }else
            {
                SetToHead(node);
            }
            cache[key]=node;
            return -1;
        }
    }

    int Get(string key)
    {
        auto iter=cache.find(key);//
        if(iter==cache.end())
            return -1;//find failed
        else {
            DLNode *node = iter->second;
            RemoveDLNode(node);
            SetToHead(node);
            return node->value;
        }
    }

    int GetDLNlsize()
    {
        return dln_len;
    }
    void showcache()
    {
        printf("dln_len:%d\n",dln_len);
        DLNode *tem=head->next;
        while(tem->next)
        {
            cout<<tem->value<<" ";
            tem=tem->next;
        }
        cout<<endl;
    }

};

#endif //INTERVIEWALGO_LRUCACHE_H
