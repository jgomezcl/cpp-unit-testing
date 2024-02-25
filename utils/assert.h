/**
 * @file assert.h
 *
 * @brief Assert macro to be used as a replacement in unit tests without
 *  blocking execution
 */

#ifndef ASSERT_H
#define ASSERT_H

#include <stdexcept>

/**
 * Macro to be used as a replacement for ASSERT() in unit tests.
 *
 * @note Will throw a std::runtime_exception
 * @note Use EXPECT_THROW( ... , std::runtime_error) in the unit test for
 * assertions expected to fail
 */
#define ASSERT(expr)    do                                                      \
                        {                                                       \
                            if(!(expr))                                         \
                            {                                                   \
                                throw std::runtime_error("Assertion failed");   \
                            }                                                   \
                        }                                                       \
                        while(0)

#endif /* ASSERT_H */
