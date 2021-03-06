#include <gtest/gtest.h>
#include "queue.h"

class queue_utest: public ::testing::Test {
    protected: 
        virtual void SetUp( ) {
            queue_init(&testQueue, 20);
        }

        virtual void TearDown( ) {
        }

    struct testClass{
        void *next;
        int name;
        int id;
    };

    struct Queue testQueue;

    static bool find_name_50(void *element, unsigned short pos, void *arg) {
        if(((struct testClass *)element)->name == *(int *)arg){
            return true;
        }
        return false;
    }
};

TEST_F(queue_utest, queue_init){
    EXPECT_EQ(testQueue.size, 0);
    EXPECT_EQ(testQueue.max_size, 20);
    EXPECT_EQ(testQueue.head, (struct Node *)NULL);
    EXPECT_EQ(testQueue.tail, (struct Node *)NULL);
}

TEST_F(queue_utest, queue_push_success){
    struct testClass testElement_1[20] = {NULL, 100, 1};
    
    struct testClass testElement_2 = {NULL, 50 , 2};

    for(int i = 0; i < 20; i++){
    EXPECT_EQ(queue_push(&testQueue, &testElement_1[i]), QUEUE_SUCCESS);
        EXPECT_EQ(testQueue.max_size, 20);
        EXPECT_EQ(testQueue.size, i + 1);
        EXPECT_EQ(testQueue.head, (struct Node *)&testElement_1[0]);
        EXPECT_EQ(testQueue.tail, (struct Node *)&testElement_1[i]);
    }

    EXPECT_NE(queue_push(&testQueue, &testElement_2), QUEUE_SUCCESS);
}

TEST_F(queue_utest, queue_frond){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_1);

    EXPECT_EQ(((struct testClass *)queue_frond(&testQueue))->name , 50);
    EXPECT_EQ(((struct testClass *)queue_frond(&testQueue))->id , 2);
}

TEST_F(queue_utest, queue_back){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_1);

    EXPECT_EQ(((struct testClass *)queue_back(&testQueue))->name , 100);
    EXPECT_EQ(((struct testClass *)queue_back(&testQueue))->id , 1);
}

TEST_F(queue_utest, queue_pop){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_1);

    EXPECT_NE(queue_frond(&testQueue), (struct Node *)&testElement_1);
    queue_pop(&testQueue);
    EXPECT_EQ(queue_frond(&testQueue), (struct Node *)&testElement_1);
}

TEST_F(queue_utest, queue_find_short_list){
    struct testClass testElement_1 = {NULL, 100, 1};

    queue_push(&testQueue, &testElement_1);

    int a = 100;

    struct testClass *element = (struct testClass *)queue_find(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_1);
}

TEST_F(queue_utest, queue_find){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 50;

    struct testClass *element = (struct testClass *)queue_find(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_2);
}

TEST_F(queue_utest, queue_find_head){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 100;

    struct testClass *element = (struct testClass *)queue_find(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_1);
}

TEST_F(queue_utest, queue_find_body){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 50;

    struct testClass *element = (struct testClass *)queue_find(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_2);
}

TEST_F(queue_utest, queue_find_tail){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 200;

    struct testClass *element = (struct testClass *)queue_find(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_3);
}

TEST_F(queue_utest, queue_pop_element_short_list){
    struct testClass testElement_1 = {NULL, 100, 1};

    queue_push(&testQueue, &testElement_1);

    int a = 100;

    struct testClass *element = (struct testClass *)queue_pop_element(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_1);
    EXPECT_EQ(testQueue.size, 0);
}


TEST_F(queue_utest, queue_pop_element_head){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 100;

    struct testClass *element = (struct testClass *)queue_pop_element(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_1);
    EXPECT_EQ(testQueue.size, 2);
    EXPECT_EQ(testQueue.head, (struct Node *)&testElement_2);
    EXPECT_EQ(testQueue.tail, (struct Node *)&testElement_3);
}

TEST_F(queue_utest, queue_pop_element_body){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 50;

    struct testClass *element = (struct testClass *)queue_pop_element(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_2);
    EXPECT_EQ(testQueue.size, 2);
    EXPECT_EQ(testQueue.head, (struct Node *)&testElement_1);
    EXPECT_EQ(testQueue.tail, (struct Node *)&testElement_3);
}

TEST_F(queue_utest, queue_pop_element_tail){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 200;

    struct testClass *element = (struct testClass *)queue_pop_element(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_3);
    EXPECT_EQ(testQueue.size, 2);
    EXPECT_EQ(testQueue.head, (struct Node *)&testElement_1);
    EXPECT_EQ(testQueue.tail, (struct Node *)&testElement_2);
}

TEST_F(queue_utest, queue_pop_element_full){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    int a = 100;

    struct testClass *element = (struct testClass *)queue_pop_element(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_1);
    EXPECT_EQ(testQueue.size, 2);
    EXPECT_EQ(testQueue.head, (struct Node *)&testElement_2);
    EXPECT_EQ(testQueue.tail, (struct Node *)&testElement_3);


    a = 50;

    element = (struct testClass *)queue_pop_element(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_2);
    EXPECT_EQ(testQueue.size, 1);
    EXPECT_EQ(testQueue.tail, (struct Node *)&testElement_3);

    a = 200;

    element = (struct testClass *)queue_pop_element(&testQueue, find_name_50, &a);

    EXPECT_EQ(element, &testElement_3);
    EXPECT_EQ(testQueue.size, 0);
}

TEST_F(queue_utest, queue_print_debug){
    struct testClass testElement_1 = {NULL, 100, 1};
    struct testClass testElement_2 = {NULL, 50 , 2};
    struct testClass testElement_3 = {NULL, 200 , 3};

    queue_push(&testQueue, &testElement_1);
    queue_push(&testQueue, &testElement_2);
    queue_push(&testQueue, &testElement_3);

    //printQueueAddressChain(&testQueue);
}