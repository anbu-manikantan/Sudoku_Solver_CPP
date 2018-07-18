// Remove naked pair
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void dispVec(vector<int> v){
	cout << "[";
	for(auto vi : v){
		cout << " " << vi;
	}
	cout <<"]";
}

void dispMap(multimap< vector<int>, int > m){
	for(auto mi : m){
		cout << "{ ";
		dispVec(mi.first);
		cout << " , " << mi.second << " }" << endl;
	}
}

void nakedPair(multimap< vector<int>, int > m, vector<int> &npv, int &p1, int &p2){
	for (auto mi : m){
		if(m.count(mi.first) == 2){
			
			npv = mi.first;
			
			pair< multimap< vector<int>, int >::iterator, multimap< vector<int>, int >::iterator > mRan; // matching range
			mRan = m.equal_range(npv);
			for(auto it=mRan.first; it!= mRan.second; it++){
				static int cnt = 0;
				if(cnt == 0){
					p1 = it->second;
					cnt++;
				}
				else
					p2 = it->second;
			}
			//p1 = mRan.first->second;
			//p2 = (mRan.first+1)->second;
			
			cout << "Naked pair is found " << p1 << "," << p2 << endl;
			dispVec(npv);
			return;
		}
	}
	cout << "Naked Pair is not found " << endl;
}

int main(){
	multimap< vector<int>, int > m;
	
	m.insert(make_pair((vector<int>){1,2,4,5},0));
	m.insert(make_pair((vector<int>){1,2,4,5,7},1));
	m.insert(make_pair((vector<int>){2,4},2));
	m.insert(make_pair((vector<int>){5,3},4));
	m.insert(make_pair((vector<int>){2,3},7));
	m.insert(make_pair((vector<int>){2,4},8));
	
	dispMap(m);
	
	
	vector<int> npv;
	int p1,p2;
	nakedPair(m, npv, p1, p2);	
}
