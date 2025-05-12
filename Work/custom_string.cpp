#include <iostream>
using namespace std;

class CustomString {
    private:
        char* str;
        size_t size;
    public:
        CustomString(const char* s) {
            size = strlen(s);
            str = new char[size +1];
            strcpy(str, s);
            str[size] = '\0';
        }
        ~CustomString() {
            delete[] str;
        }
        CustomString(const CustomString& ori) {
            size = ori.size;
            str = new char[size + 1];
            strcpy(str, ori.str);
        }
        CustomString& operator=(const CustomString& other) {
            if (this == &other) {
                return *this;
            }
            delete[] str;
            size = other.size;
            str = new char[size + 1];
            strcpy(str, other.str);
            return *this;
        }
        
}