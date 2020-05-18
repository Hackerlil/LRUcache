//
// Created by kevin yan on 2020-05-18.
//

#include "LRUcache.h"
int main()
{
    LRUcache *lrc=new LRUcache(3);
    lrc->Set("page1",7);
    lrc->showcache();
    lrc->Set("page2",0);
    lrc->showcache();
    lrc->Set("page3",1);
    lrc->showcache();
    lrc->Set("page4",2);
    lrc->showcache();
    lrc->Get("page2");
    lrc->showcache();
    lrc->Set("page5",3);
    lrc->showcache();
    lrc->Get("page2");
    lrc->showcache();
    lrc->Set("page6",4);
    lrc->showcache();

    return 0;
}
