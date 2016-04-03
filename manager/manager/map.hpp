//
//  map.hpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 7..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef map_hpp
#define map_hpp

#define MAX_MAP_CNT 1000

#include <string>
#include <iostream>

using namespace std;

struct mymap{
    string key;
    string value;
};

class mymaps {

private:
    struct mymap map[MAX_MAP_CNT];
    int cnt;
public:
    void insert(string key, string value);
    string get(string key);
    void remove(string key);
    mymap getByIndex(int i);
    int getMaxCnt();
};



#endif /* map_hpp */
