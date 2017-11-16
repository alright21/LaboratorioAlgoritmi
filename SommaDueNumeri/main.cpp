#include <iostream>
#include <fstream>


using namespace std;

int main()
{


    int N,M;

    ifstream in ("input.txt");

    in>>N>>M;

    ofstream out("output.txt");

    out << N+M<<endl;




    return 0;
}
