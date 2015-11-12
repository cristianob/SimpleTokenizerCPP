#include <iostream>
#include "simple_tokenizer.h"

#define BOOST_TEST_MODULE SimpleTokenizer TestCase
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(default_case) {
	SimpleTokenizer s("split this string");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(default_case2) {
	SimpleTokenizer s("split\nthis string");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(default_case3) {
	SimpleTokenizer s("split\nthis\nstring");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(default_case4) {
	SimpleTokenizer s("split\tthis\nstring");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(only_space) {
	SimpleTokenizer s("split this string", " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(other_char) {
	SimpleTokenizer s("split|this|string", "|");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(endl) {
	SimpleTokenizer s("split\nthis\nstring", "\n");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(mix_space_endl) {
	SimpleTokenizer s("split\nthis string", " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split\nthis");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
}

BOOST_AUTO_TEST_CASE(utf8) {
	SimpleTokenizer s("são dóîs ütf", " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "são");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "dóîs");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "ütf");
}
