#include <iostream>
#include <fstream>


using namespace std;


void schifo(){

	ifstream in1("output.txt");
	ofstream out1("real.txt");

	while (!in1.eof()) {

		int a,b,c;

		in1>>a>>b>>c;
		out1 << "g.addEdge("<<a<<","<<b<<","<<c<<");"<<endl;
		 //g.addEdge(0, 1, 4);
		
	   
	}

}
int main(){

	ifstream in("input5.txt");
	ofstream out("output.txt");

	int N;
	int M;
	in>>N>>M;

	while (!in.eof()) {

		int a,b,c,d,e,f;

		in>>a>>b>>c>>d>>e>>f;
		out << a<<" "<<b<<" "<<c<<"\n";

		schifo();
	   
	}



}

