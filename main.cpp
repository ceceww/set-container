#include <iostream>
#include <string>
#include <exception>

#include "Set.h"

// This is a file that will help you test your implementation.
// There is no need to submit this file and you can edit
// and change it as you wish.

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;


int main() {
	
	Set<int> set;
	Set<string> str_set;
	
	try{
		
		set.readFromFile("set_file");
		cout << set; 

		set.insert(12);
		
		cout<<"Container"<<endl;
		cout<<set;
		
		std::vector<int> closest = set.findClosest(5,4);

		cout<<"findClosest(5,4)"<<endl;
		for(int i=0; i < closest.size(); ++i){
			cout<<closest[i]<<" ";
		}
		cout<<endl;

		closest = set.findClosest(8,3);

		cout<<"findClosest(8,3)"<<endl;
		for(int i=0; i < closest.size(); ++i){
			cout<<closest[i]<<" ";
		}
		cout<<endl;

		closest = set.findClosest(12,3);

		cout<<"findClosest(12,3)"<<endl;
		for(int i=0; i < closest.size(); ++i){
			cout<<closest[i]<<" ";
		}
		cout<<endl;

		
		std::vector<int> range = set.getRange(4,9);
		cout<<"getRange(4,9)"<<endl;
		for(int i=0; i < range.size(); ++i){
			cout<<range[i]<<" ";
		}
		cout<<endl;

		range = set.getRange(4,8);
		cout<<"getRange(4,8)"<<endl;
		for(int i=0; i < range.size(); ++i){
			cout<<range[i]<<" ";
		}
		cout<<endl;

		cout<<"getRange(7,2)"<<endl;
		range = set.getRange(7,2);
		for(int i=0; i < range.size(); ++i){
			cout<<range[i]<<" ";
		}
		cout<<endl;
		
		cout<<"getRange(11,13)"<<endl;
		range = set.getRange(11,13);
		for(int i=0; i < range.size(); ++i){
			cout<<range[i]<<" ";
		}
		cout<<endl;
		
	}
	catch (std::exception e){
		cerr<< e.what()<<": could not populate container"<<endl; 
	}

	return 0;
}

