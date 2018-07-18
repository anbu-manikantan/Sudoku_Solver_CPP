// Omission
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;


vector<int> m_mPosMat[9][9] = {
								{ {7,6}, {1,6,7}, {}, {1,6,9}, {1,8,9}, {2,6}, {}, {2,8}, {}			},
								{ {7,8}, {}, {1,5}, {}, {}, {5,7}, {1,9}, {}, {1,7,9}			},
								{ {}, {1,6,7}, {}, {1,5,6}, {1,5,8}, {2,5,6}, {2,7,8}, {2,3,8}, {2,3,7}			},
								{ {}, {}, {}, {}, {}, {}, {}, {}, {}			},
								{ {}, {}, {}, {}, {}, {}, {}, {}, {}			},
								{ {}, {}, {}, {}, {}, {}, {}, {}, {}			},
								{ {}, {}, {}, {}, {}, {}, {}, {}, {}			},
								{ {}, {}, {}, {}, {}, {}, {}, {}, {}			},
								{ {}, {}, {}, {}, {}, {}, {}, {}, {}			},
								};

void Omission();

int main(){
	cout << "Testing Omission " << endl;
	
	Omission();
}

void Omission(){
	cout << endl << "!!! Omission started !!!" << endl;
	cout << "===> Rows and Blocks <====" << endl;
	
	for(int r=0; r<9; r++){
		multimap<int, int> mValPos;		// multimap of value and position
		
		for(int c=0; c<9; c++){
			if(m_mPosMat[r][c].empty()) continue;		// skip the empty vector
			for(auto v : m_mPosMat[r][c]){
				mValPos.insert(make_pair(v, c));
			}
		}
		
		// Check if any value is apear in a block range
		for(int v=1; v <= 9; v++){
			if((mValPos.count(v) == 2) || (mValPos.count(v) == 3)){
				int pos[3];
				int i=0;
				auto it = mValPos.equal_range(v);
				for(auto itv=it.first; itv != it.second; itv++){
					pos[i++] = itv->second;
				}
				
				if( ((mValPos.count(v)==2) && (pos[0]/3) == (pos[1]/3)) || 
				    ((mValPos.count(v)==3) && ( (pos[0]/3) == (pos[1]/3) && (pos[0]/3) == (pos[2]/3)) ) ){
					cout << " Found elements in  row " << r << " with value " << v << " in " << pos[0] << " and " << pos[1];
					if(mValPos.count(v)==3) cout << " and " << pos[2];
					cout << endl;
					
					// Remove the elements for the block
					for(int br=r/3; br<(r/3)+3; br++){
						if(br == r) continue;		// skip the row where omission is found
						for(int bc=(pos[0]/3)*3; bc<(pos[0]/3)*3 + 3; bc++){
							if(m_mPosMat[br][bc].empty()) continue;		// skip the empty vector
							auto itr = find(m_mPosMat[br][bc].begin(), m_mPosMat[br][bc].end(), v);
							if(itr != m_mPosMat[br][bc].end()){
								m_mPosMat[br][bc].erase(itr);
								cout << "Removing " << v << " from [" << br << "," << bc << "]" << endl;
								if(m_mPosMat[br][bc].size() == 1){
									cout << "Candiate found for [" << br << "," << bc << "] with value " <<  m_mPosMat[br][bc][0] << endl;
								}
							}
						}
					}
				}
			}
		}
	}
}
