#include <toUpperFunction.h>
void toUpper(std::string & str){
    for(size_t index = 0;index<str.size();++index){
        str[index]=std::toupper(str[index]);
    }
}
