#include <iostream>
#include <String>
using namespace std;


class String
{
private:
    char *s;
    int size;
public:
    String(char *c){
      size = strlen(c);
      s = new char[size+1];
      strcpy(s,c);
    } // constructor
    ~String();      // destructor
    void Stringfunc(char *c);

};

void String::Stringfunc(char *c)
{   String fwef("fwef");
    size = strlen(fwef.s);
    s = fwef.s;
    strcpy(s,c);
}

String::~String()
{
    cout << "delete" << endl;
    delete s;
    s = nil;
}

int main(int argc, char const *argv[]) {
    String teststr = "fwefwe";
    teststr.Stringfunc("frefe");
  return 0;
}
