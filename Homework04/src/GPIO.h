#ifndef GPIO_h
#define GPIO_h

#include <string>

using namespace std;

namespace ECE {

class GPIO {
protected:
    string readPinFile(string filename);
    void writePinFile(string filename, string value);

    string m_pinDir;
};

}; /* namespcae ECE */

#endif /* GPIO_h */
