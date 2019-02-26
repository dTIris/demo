/*
 * author:iris
 * date:2019/02/20
 * desc:输入输出操作
 */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string first_name, last_name;
	cout << "Please enter your first name: ";
	cin >> first_name;
	cout << "Please enter your last name: ";
	cin >> last_name;
	cout << "Hello " << first_name + ' ' + last_name  << endl;
	return 0;
}

