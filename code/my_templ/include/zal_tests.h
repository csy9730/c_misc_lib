#ifndef _ZAL_TESTS_H_
#define _ZAL_TESTS_H_

// #include "zal_debug.h"

#define ZAL_TEST_EPS (1e-4f)

// FLAG === 0 : means no error
// FLAG === 1 : means error
#define ZAL_ERROR (1)
#define ZAL_CORRECT (0)

#define ZAL_TEST_FILENAME "testMsg.log"     ///< 测试记录
#define ZAL_TEST_DISP(...) ZAL_DEBUG_PRINTF(1, ZAL_TEST_FILENAME, __VA_ARGS__)
#define ZAL_DEBUG_PRINTF(DISPLAY,FILE,...) if (DISPLAY >0)  printf(__VA_ARGS__)

#define  ZAL_TEST_DISP_EX(FLAG)   ZAL_TEST_DISP("%s,%s,%d,%d\n", __FILE__,__FUNCTION__,__LINE__,FLAG);
#define  ZAL_TEST_DISP2(FLAG)  if (FLAG){ ZAL_TEST_DISP("%s,%s,%d,%d\n", __FILE__,__FUNCTION__,__LINE__,FLAG);}


#define ZAL_TEST_TRUE(COND,FLAG) \
        {\
            if (!(COND)){\
                FLAG = ZAL_ERROR;\
            }\
        }while(0)


#define ZAL_TEST_FLOAT_ARRAY_EQUAL(ARR0,ARR2,LEN,FLAG) \
        {\
            int i;\
            double sum =0;\
            for (i=0;i<LEN;i++){\
                sum += (ARR0[i]-ARR2[i])* (ARR0[i]-ARR2[i]);\
            };\
            if (sum < ZAL_TEST_EPS )\
                FLAG |= ZAL_CORRECT;\
            else\
                FLAG = ZAL_ERROR;\
        }while(0)

#define ZAL_TEST_INT_ARRAY_EQUAL(ARR0,ARR2,LEN,FLAG) \
        {\
            int i;\
            for (i=0;i<LEN;i++){\
                if (ARR0[i]!=ARR2[i]){\
                    FLAG = ZAL_ERROR;\
                    break;\
                }\
            };\
        }while(0)

#endif