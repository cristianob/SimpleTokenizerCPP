/**
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(default_case3) {
	SimpleTokenizer s("split\nthis\nstring");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(default_case4) {
	SimpleTokenizer s("split\tthis\nstring");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(only_space) {
	SimpleTokenizer s("split this string", " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(other_char) {
	SimpleTokenizer s("split|this|string", "|");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(endl) {
	SimpleTokenizer s("split\nthis\nstring", "\n");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(mix_space_endl) {
	SimpleTokenizer s("split\nthis string", " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split\nthis");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(utf8) {
	SimpleTokenizer s("são dóîs ütf", " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "são");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "dóîs");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "ütf");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(keep_delimiters) {
	SimpleTokenizer s("split this string", " ", true);
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(keep_delimiters2) {
	SimpleTokenizer s("split;this string", " ;", true);
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ";");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(keep_delimiters3) {
	SimpleTokenizer s("split;.this string", " ;.", true);
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ";");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ".");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(keep_delimiters4) {
	SimpleTokenizer s(" split;.this  string", " ;.", true);
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ";");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ".");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(advanced_test) {
	SimpleTokenizer s("	 split;.	this . string ", " \t;.", true);
	s.nextToken();
	BOOST_CHECK(s.getToken() == "\t");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "split");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ";");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ".");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "\t");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "this");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == ".");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "string");
	s.nextToken();
	BOOST_CHECK(s.getToken() == " ");
	BOOST_CHECK(s.nextToken() == false);
}

BOOST_AUTO_TEST_CASE(diferent_delimiters) {
	SimpleTokenizer s("reserved_word this is the value\n");
	s.nextToken();
	BOOST_CHECK(s.getToken() == "reserved_word");
	s.nextToken("\n");
	std::cout << "\"" << s.getToken() << "\"" << std::endl;
	BOOST_CHECK(s.getToken() == "this is the value");
	BOOST_CHECK(s.nextToken() == false);
}
