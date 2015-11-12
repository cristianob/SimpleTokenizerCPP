#pragma once
#include <string>

class SimpleTokenizer 
{
    public:
        static const std::string DELIMITERS;
        
        SimpleTokenizer(const std::string& str);
        SimpleTokenizer(const std::string& str, const std::string& delimiters);
        
        bool nextToken();
        bool nextToken(const std::string& delimiters);
        
        const std::string getToken() const;
        void reset();
    
    protected:
        size_t offset;
        const std::string string;
        std::string token;
        std::string delimiters;
};
