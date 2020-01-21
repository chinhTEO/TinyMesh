#include "utest.h"
#include "nb_test.h"
#include "../src/queue.h"
#include <stdlib.h>

struct test_date {
    int a;
    int b;
    int c;
};

UTEST_F_SETUP(test_date) {
    utest_fixture->a = 2;
    utest_fixture->b = 3;
    queue_init(&nbt_snap_list, 0xffff);
}

UTEST_F_TEARDOWN(test_date) {
    struct nbt_snap *snap;
    while(queue_size(&nbt_snap_list)){
        snap = (struct nbt_snap *)queue_frond(&nbt_snap_list);
        free(snap->key_UUID);
        free(snap->data);
        queue_pop(&nbt_snap_list);
        free(snap);
    }
}

void testFunction() {
    int a =  2;
    int b =  3;
    NBT_SNAP(A_INSIDE_TESTFUNCTION, &a, sizeof(int));
    NBT_SNAP(B_INSIDE_TESTFUNCTION, &b, sizeof(int));
}

UTEST_F(test_date, NBT_BEGIN) {
    NBT_BEGIN();
}

UTEST_F(test_date, NBT_END) {
    NBT_BEGIN();

    testFunction();

    NBT_END();

    EXPECT_EQ((int)queue_size(&nbt_snap_list), 0);
}

UTEST_F(test_date, NBT_CMP) {
    
}

UTEST_F(test_date, NBT_SNAP){
    NBT_BEGIN();

    testFunction();

    EXPECT_EQ((int)queue_size(&nbt_snap_list), 2);

    NBT_END();
}


UTEST_F(test_date, NBT_CMP_TEST){
    NBT_BEGIN();

    testFunction();

    EXPECT_EQ((int)queue_size(&nbt_snap_list), 2);

    EXPECT_EQ((int)NBT_CMP(A_INSIDE_TESTFUNCTION, &(utest_fixture->a)) , true);
    EXPECT_EQ((int)NBT_CMP(B_INSIDE_TESTFUNCTION, &(utest_fixture->b)) , true);

    NBT_END();
}

UTEST_MAIN()