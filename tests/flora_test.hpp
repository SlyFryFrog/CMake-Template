#pragma once

#include <cassert>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define DEFAULT_MSG "No additional message added."

namespace flora_test
{
	struct TestCase
	{
		std::string group;
		std::string name;
		void (*test_function)();
	};

	template <typename T, typename V>
	void assert_fn(const T& condition, const V& message)
	{
		if (!(condition))
		{
			std::ostringstream oss;
			oss << "Assertion failed: " << message;
			throw std::runtime_error(oss.str());
		}
	}

	template <typename T>
	void assert_fn(const T& condition)
	{
		assert_fn(condition, DEFAULT_MSG);
	}

	// Function to get the list of test cases
	std::vector<TestCase>& get_test_cases()
	{
		static std::vector<TestCase> testCases;
		return testCases;
	}

	void run_tests()
	{
		int passed = 0;
		int failed = 0;

		std::cout << "Running Tests...\n";

		// Group tests by group name
		std::string current_group;
		for (const auto& testCase : get_test_cases())
		{
			if (current_group != testCase.group)
			{
				if (!current_group.empty())
				{
					std::cout << "\n"; // Add line between groups
				}
				current_group = testCase.group;
				std::cout << "---- " << current_group << " ----" << std::endl;
			}

			try
			{
				testCase.test_function();
				std::cout << "[PASSED] : " << testCase.name<< std::endl;
				passed++;
			}
			catch (const std::runtime_error& e)
			{
				std::cout << "[FAILED] : " << testCase.name << "\n" << e.what() << std::endl;
				failed++;
			}
		}

		std::cout << "\n--- Test Results ---\n";
		std::cout << "Passed: " << passed << "\n";
		std::cout << "Failed: " << failed << "\n";
	}

	// Function to add a test case with group information
	void add_test(const TestCase& test_case)
	{
		get_test_cases().push_back(test_case);
	}

// Macro to register a test with a group and name
#define FLORA_TEST(group, name)                                                                    \
	void name();                                                                                   \
	struct name##_Register                                                                         \
	{                                                                                              \
		name##_Register()                                                                          \
		{                                                                                          \
			add_test(flora_test::TestCase{#group, #name, &(name)});                                \
		}                                                                                          \
	} name##_instance;                                                                             \
	void name()

// Helper macro for assertions
#define FLORA_ASSERT(condition, ...) flora_test::assert_fn(condition, ##__VA_ARGS__)

#define FLORA_ASSERT_EQ(expected, actual, ...)                                                     \
	flora_test::assert_fn(expected == actual, ##__VA_ARGS__)
} // namespace flora_test
