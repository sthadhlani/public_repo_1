#include <iostream>
using namespace std;
class foo{
	private:
		int x;
	public:
		foo(){
			x = 2;
		}
		foo(int i){
			x = i;
		}
		void* get(){
			return (void *)this;
		}
		string operator <<(){
			string
		}
};

int main(int arc, char *argv[]){
	int a = 0;
	foo f = foo(1);
	foo *p = new foo(1);
	cout<<&a<<endl;
	cout<<f.get()<<endl;
	cout<<p->get()<<endl;
	return 0;
}
