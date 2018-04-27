#include <iostream>

#include "gtest/gtest.h"
#include "../include/base/mutex.h"
#include "../include/base/condition.h"
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>

using namespace muduonet;

Mutex mutex;
Condition condition(mutex);
std::vector<int> joblist;
int job = 0;

void* consumethrfun(void*) {
    
    while (1) {
        MutexGuard mg(mutex);
        while (joblist.empty()) {
            condition.wait();
        }
        if (!joblist.empty()) {
            printf("%x: %d\n", (unsigned)pthread_self(), joblist.back());
            joblist.pop_back();
        }
    }

    return (void*)0;
}

void* productthrfun(void*) {
    while (1) { 
        
        {
            MutexGuard mg(mutex);
            joblist.push_back(++job);
            condition.notify();
        }

        usleep(1000);
    }

    return (void*)0;
}

int test() {
    pthread_t c1, c2, c3, c4, p1, p2, p3;
    if (0 != pthread_create(&c1, NULL, consumethrfun, NULL)) {
        printf("create thread error\n");
        return -1;
    }
    printf("c1:%x\n", (unsigned)c1);
    
    if (0 != pthread_create(&c2, NULL, consumethrfun, NULL)) {
        printf("create thread error\n");
        return -1;
    }
    printf("c2:%x\n", (unsigned)c2);
    
    if (0 != pthread_create(&c3, NULL, consumethrfun, NULL)) {
        printf("create thread error\n");
        return -1;
    }
    printf("c3:%x\n", (unsigned)c3);
    
    if (0 != pthread_create(&c4, NULL, consumethrfun, NULL)) {
        printf("create thread error\n");
        return -1;
    }
    printf("c4:%x\n", (unsigned)c4);

    if (0 != pthread_create(&p1, NULL, productthrfun, NULL)) {
        printf("create thread error\n");
        return -1;
    }
    printf("p1:%x\n", (unsigned)p1);
    
    if (0 != pthread_create(&p2, NULL, productthrfun, NULL)) {
        printf("create thread error\n");
        return -1;
    }
    printf("p2:%x\n", (unsigned)p2);

    if (0 != pthread_create(&p3, NULL, productthrfun, NULL)) {
        printf("create thread error\n");
        return -1;
    }
    printf("p3:%x\n", (unsigned)p3);

    int s = 0;
    s |= pthread_join(c1, NULL);
    s |= pthread_join(c2, NULL);
    s |= pthread_join(c3, NULL);
    s |= pthread_join(c4, NULL);
    s |= pthread_join(p1, NULL);
    s |= pthread_join(p2, NULL);
    s |= pthread_join(p3, NULL);

    return s;
}

TEST(MUDUONET, MUTEX_CONDITON) {
    EXPECT_EQ(0, test());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
