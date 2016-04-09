//
//  map.cpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 7..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "map.hpp"

void mymaps::insert(string key, string value) {
    int i;
    for (i=0; i<MAX_MAP_CNT; i++) {
        if(map[i].key=="") {
            map[i].key   = key   ;
            map[i].value = value ;
            break;
        }
        if (i==MAX_MAP_CNT-1) {
            cerr<<"map full!";
        }
    }
    if(i>cnt) cnt= i;
    return;
}


string mymaps::get(string key) {
    string ret_val;
    for(int i=0; i<MAX_MAP_CNT; i++){
        if(map[i].key==key) {
            ret_val = map[i].value;
        }
    }
    return ret_val;
}


void mymaps::remove(string key) {
    string ret_val;
    for(int i=0; i<MAX_MAP_CNT; i++){
        if(map[i].key==key) {
            map[i].key = "";
        }
    }
}

mymap mymaps::getByIndex(int i) {
     return map[i];
}

int mymaps::getMaxCnt() {
    return cnt;
}