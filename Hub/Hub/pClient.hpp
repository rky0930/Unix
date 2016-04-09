//
//  pClient.hpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 10..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef pClient_hpp
#define pClient_hpp

#include <stdio.h>

class pClient {
    int write();
    int read();
    int dispatch();
    int onMessage();
};

#endif /* pClient_hpp */
