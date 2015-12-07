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
	delimiters(DELIMITERS),
	keep_delimiters(false)
{
	this->last_was_delimiter = (delimiters.find_first_of(this->string[this->offset]) == std::string::npos);
}

SimpleTokenizer::SimpleTokenizer(const std::string& s, const std::string& delimiters) :
	string(s), 
	offset(0), 
	delimiters(delimiters),
	keep_delimiters(false)
{
	this->last_was_delimiter = (delimiters.find_first_of(this->string[this->offset]) == std::string::npos);
}

SimpleTokenizer::SimpleTokenizer(const std::string& s, const std::string& delimiters, bool ktokens) :
	string(s), 
	offset(0), 
	delimiters(delimiters),
	keep_delimiters(ktokens)
{
	this->last_was_delimiter = (delimiters.find_first_of(this->string[this->offset]) == std::string::npos);
}

bool SimpleTokenizer::nextToken() 
{
	return this->nextToken(this->delimiters);
}

bool SimpleTokenizer::nextToken(const std::string& delimiters) 
{
	if(this->keep_delimiters)
		return this->nextToken_K(delimiters);
	else
		return this->nextToken_notK(delimiters);
}

bool SimpleTokenizer::nextToken_K(const std::string& delimiters) {
	if(this->offset == this->string.length())
		return false;
		
	// Location of the next delimiter
	size_t j = this->string.find_first_of(delimiters, this->offset);
	
	// If there is no more delimiter, token is what is left
	if (j == std::string::npos) {
		this->token = this->string.substr(this->offset);
		this->offset = this->string.length();
		return true;
	}

	if(this->last_was_delimiter) {
		this->token = this->string.substr(this->offset, j - this->offset);
		this->offset = j;
		this->last_was_delimiter = false;
	} else {
		this->token = this->string.substr(this->offset, 1);
		this->offset++;
		
		this->last_was_delimiter = (delimiters.find_first_of(this->string[this->offset]) == std::string::npos);
	}
    
	return true;
}

bool SimpleTokenizer::nextToken_notK(const std::string& delimiters_a) {
	if(delimiters_a != this->delimiters)
		this->offset++;

	size_t i = this->string.find_first_not_of(delimiters_a, this->offset);   
	if (std::string::npos == i) {
		this->offset = this->string.length();
		return false;
	}

	size_t j = this->string.find_first_of(delimiters_a, i);
	if (std::string::npos == j) {
		this->token = this->string.substr(i);
		this->offset = this->string.length();
		return true;
	}

	this->token = this->string.substr(i, j - i);
	this->offset = j;
    
	return true;
}

const std::string SimpleTokenizer::getToken() const 
{
	return this->token;
}

bool SimpleTokenizer::keepDelimiters(bool k) 
{
	this->keep_delimiters = k;
	return this->keep_delimiters;
}
