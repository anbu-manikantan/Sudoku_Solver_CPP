//Naked triplets
#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool findTriplets(multimap < vector<int>, int > m, vector<int> &triplet, int *pos);
bool findTripletsAdv(multimap < int, int > m, vector<int> &triplet, int *pos);

void dispVector(vector<int> v){
	cout << "[";
	
	for(auto vi : v){
		cout << vi << " ";
	}
	cout << "]";
}

vector<int> vMat[9];

int main(){
	
	/*multimap < vector<int>, int > mPos;
	
	vector<int> temp = {1,5,9};
	vector<int> temp2 = {1,6,8,9};
	vector<int> temp3 = {5,6,8,9};
	
	mPos.insert(make_pair(temp,0));
	mPos.insert(make_pair(temp,1));
	mPos.insert(make_pair(temp,6));
	mPos.insert(make_pair(temp2,7));
	mPos.insert(make_pair(temp3,8));
	
	vector<int> trp;
	int opos[3];
	
	findTriplets(mPos, trp, opos);
	cout << "success " ;
	dispVector(trp);
	
	cout << endl << "Position "<< endl;
	cout << opos[0] << " " << opos[1] << " " << opos[2] << endl;
	*/
	
	vMat[0] = {5,6};
	vMat[2] = {1,4,8,9};
	vMat[3] = {4,7};
	vMat[4] = {6,8};
	vMat[5] = {1,6,7};
	vMat[6] = {3,4,7,9};
	vMat[7] = {3,4,5,7,9};
	//vMat[8] = {5,8};
	
	multimap<int, int> mSiz;  // multimap of size and position
	
	for(int i=0; i<9; i++){
		mSiz.insert(make_pair(vMat[i].size(), i));
	}
	
	vector<int> trp;
	int opos[3];
	
	findTripletsAdv(mSiz, trp, opos);
}

bool findTriplets(multimap < vector<int>, int > m, vector<int> &triplet, int *pos){
	for(auto mit=m.begin(); mit != m.end(); mit = m.upper_bound(mit->first) ){
		if(mit->first.size() == 3){
			if(m.count(mit->first) == 3){
				cout << "!!! Naked Triplet found !!!"<< endl;
				dispVector(mit->first);
				triplet = mit->first;
				
				auto eit = m.equal_range(mit->first);
				for(auto it = eit.first; it != eit.second; it++){
					*pos++ = it->second;
				}
			}
		}
	}
}

bool findTripletsAdv(multimap < int, int > m, vector<int> &triplet, int *pos){
	// find number of candidates of size 2
	if(m.count(2) == 3){
		cout << "There are 3 candidates with size 2" << endl;
		// merge all elements
		vector<int> vMrg;
		auto it = m.equal_range(m.find(2));
		for(auto i=it.first; i!=it.second; i++){
			vMrg.insert(vMrg.end(), vMat[i->second].begin(), vMat[i->second].end());
		}
		
		cout << "Merged vector "<<endl;
		dispVector(vMrg);
	}
}
