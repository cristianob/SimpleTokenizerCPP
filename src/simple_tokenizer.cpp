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

#include "simple_tokenizer.h"

const std::string SimpleTokenizer::DELIMITERS(" \t\n\r");

SimpleTokenizer::SimpleTokenizer(const std::string& s) :
	string(s), 
	offset(0), 
	delimiters(DELIMITERS) 
{}

SimpleTokenizer::SimpleTokenizer(const std::string& s, const std::string& delimiters) :
	string(s), 
	offset(0), 
	delimiters(delimiters) 
{}

bool SimpleTokenizer::nextToken() {
	return this->nextToken(this->delimiters);
}

bool SimpleTokenizer::nextToken(const std::string& delimiters) 
{
	size_t i = this->string.find_first_not_of(delimiters, this->offset);
    
	if (std::string::npos == i) {
		this->offset = this->string.length();
		return false;
	}

	size_t j = this->string.find_first_of(delimiters, i);
	if (std::string::npos == j) {
		this->token = this->string.substr(i);
		this->offset = this->string.length();
		return true;
	}

	this->token = this->string.substr(i, j - i);
	this->offset = j;
    
	return true;
}

const std::string SimpleTokenizer::getToken() const {
	return this->token;
}

