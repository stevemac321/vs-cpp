#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdio>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";

void enable_virtual_terminal_processing() {
#ifdef _WIN32
    // Get the console handle
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }

    // Get the current console mode
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return;
    }

    // Enable the virtual terminal processing mode
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}


//////////////////////////////////////////////////////////////////////
    // Global variables
int test_count = 0;
int test_passed = 0;
int test_failed = 0;
std::vector<std::string> failed_tests;
std::chrono::steady_clock::time_point start_time;
std::chrono::steady_clock::time_point end_time;
// Macro to start a test suite
#define TEST_BEGIN(name) \
    std::cout << "[ RUN      ] " << name << std::endl; \
    start_time = std::chrono::steady_clock::now();

// Macro to end a test suite
#define TEST_END(name) \
    end_time = std::chrono::steady_clock::now(); \
    std::cout << "[       OK ] " << name << " (" << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " ms)" << std::endl; \
    test_passed++; \
    test_count++;

// ASSERT_EQ macro
#define ASSERT_EQ(val1, val2) \
    if ((val1) == (val2)) { \
        std::cout << GREEN << "ASSERT_EQ passed: " << #val1 << " == " << #val2 << RESET << std::endl; \
    } else { \
        std::cout << RED << "ASSERT_EQ failed: " << #val1 << " != " << #val2 << RESET << std::endl; \
    }

// ASSERT_ITER_EQ macro
#define ASSERT_ITER_EQ(iter1_begin, iter1_end, iter2_begin, iter2_end) \
    if (std::equal((iter1_begin), (iter1_end), (iter2_begin), (iter2_end))) { \
        std::cout << GREEN << "ASSERT_ITER_EQ passed: ranges are equal." << RESET << std::endl; \
    } else { \
        std::cout << RED << "ASSERT_ITER_EQ failed: ranges are not equal." << RESET << std::endl; \
    }

// ASSERT_STREQ macro for const char* and std::string
#define ASSERT_STREQ(str1, str2) \
    if (std::strcmp((str1), (str2)) == 0) { \
        std::cout << GREEN << "ASSERT_STREQ passed: " << #str1 << " == " << #str2 << RESET << std::endl; \
    } else { \
        std::cout << RED << "ASSERT_STREQ failed: " << #str1 << " != " << #str2 << RESET << std::endl; \
        test_failed++; \
        test_count++; \
        failed_tests.push_back(__FUNCTION__); \
        return; \
    }

// ASSERT_STR_EQ macro for std::string
#define ASSERT_STR_EQ(str1, str2) \
    if ((str1) == (str2)) { \
        std::cout << GREEN << "ASSERT_STR_EQ passed: " << #str1 << " == " << #str2 << RESET << std::endl; \
    } else { \
        std::cout << RED << "ASSERT_STR_EQ failed: " << #str1 << " != " << #str2 << RESET << std::endl; \
        test_failed++; \
        test_count++; \
        failed_tests.push_back(__FUNCTION__); \
        return; \
    }

// Function to print summary
void print_summary() {
    std::cout << GREEN << "[==========] " << test_count << " tests from " << test_count - test_failed
        << " test suites ran." << RESET << std::endl;
    std::cout << GREEN << "[  PASSED  ] " << test_passed << " tests." << RESET << std::endl;
    if (test_failed > 0) {
        std::cout << RED << "[  FAILED  ] " << test_failed << " tests, listed below:" << RESET << std::endl;
        for (const auto& test : failed_tests) {
            std::cout << RED << "[  FAILED  ] " << test << RESET << std::endl;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
// helper functions
template <typename T, const size_t N> constexpr size_t __countof(T(&)[N])
{
    return N;
}

template <typename T, const size_t N> void print_array(T(&a)[N])
{
    for (int i = 0; i < N; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}
// Specialization for std::array<char, N>
template <const size_t N>
void print_array(std::array<char, N>& a)
{
    for (int i = 0; i < N; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}
