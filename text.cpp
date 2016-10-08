#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
int main(int argc, char const *argv[]) {
    const char * file="file";
    if(open(file, O_RDWR)==-1)
    {
        cout<<"false"<<endl;
    }
    return 0;
}
