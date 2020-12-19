#include "pml_hash.h"
#include <cstdlib>

vector<string> split(const string &str, const string &pattern);

int main() {
     PMLHash hash("/mnt/pmemdir/pmem0");
     size_t num[(HASH_SIZE + 1) * TABLE_SIZE];
     for(size_t i=0; i<(HASH_SIZE + 1) * TABLE_SIZE ; i++){
     	num[i] = rand() % 999 + 1;
     }

     /*
     for (uint64_t i = 1; i <= HASH_SIZE * TABLE_SIZE; i++) {
         //hash.insert( rand()%999 , rand()%999 );
     	hash.insert(num[i-1] , num[i-1]);
     }
     hash.Show_all();*/
     
     /*
     for (uint64_t i = 1; i <= HASH_SIZE; i++) {
         uint64_t val;
         hash.search(i, val);
         cout << "key: " << i << "\nvalue: " << val << endl;
     }*/
     
     for(size_t i=0 ; i<HASH_SIZE+1 ; i++){
     	cout<<"insert" <<i<<"*****************"<<endl;
     	for(size_t j=0; j<TABLE_SIZE ; j++){
     		hash.insert( num[i*HASH_SIZE + j]  , num[i*HASH_SIZE + j] );
     	}
     	hash.Show_all();
     	cout<<endl;
     }

     for(size_t i=0 ; i<HASH_SIZE+1 ; i++){
     	cout<<"remove" <<i<<"*****************"<<endl;
     	for(size_t j=0; j<TABLE_SIZE ; j++){
     		hash.remove( num[i*HASH_SIZE + j] );
     	}
     	hash.Show_all();
     	cout<<endl;
     }
     //cout<<"*****************"<<endl;
     /*
     for (uint64_t i = HASH_SIZE * TABLE_SIZE + 1; 
          i <= (HASH_SIZE + 1) * TABLE_SIZE; i++) {
         //hash.insert(rand()%999 , rand()%999 );
     	hash.insert(num[i-1] , num[i-1]);
     }
     hash.Show_all();

     cout<<"*******************"<<endl;

     for(size_t i=HASH_SIZE*TABLE_SIZE ; i<(HASH_SIZE+1)*TABLE_SIZE ; i++){
     	hash.remove(num[i]);
     }
     hash.Show_all();

     cout<<"******************"<<endl;
     for(size_t i = 0 ; i < HASH_SIZE*TABLE_SIZE ; i++ ){
     	hash.remove(num[i]);
     }
     hash.Show_all();
		*/
    

     /*
     for (uint64_t i = HASH_SIZE * TABLE_SIZE + 1;
          i <= (HASH_SIZE + 1) * TABLE_SIZE; i++) {
         uint64_t val;
         hash.search(i, val);
         cout << "key: " << i << "\nvalue: " << val << endl;
     }*/


     /*
    fstream infile;
	infile.open("/home/chaibli/Database/Datatest/Fist.txt");
	string line;
	vector<string> sdata;
	string operate;
	int count = 0;
	size_t key;
	size_t value;
	int success;
	///////////////////////////////////build the hash table
	
	while(getline(infile , line)){
		sdata = split(line , " ");
		operate = sdata[0];
		key = stol(sdata[1]);

		cout<<operate<<" "<<key<<endl;

		if(operate == "INSERT"){
			success = hash.insert(key , key);
			if(success != 0){
				printf("Insert  fail!\n");
				//break;
			}
		}else if(operate == "READ"){
			success = hash.remove(key);
			if(success != 0){
				printf("Search  fail!\n");
				//break;
			}
		}
		count++;
	}


	cout<<"count="<<count<<endl;
	infile.close();
	*/
	/*
     cout<<"meta:"<<endl;
     cout<<"meta->size = "<<hash.meta->size<<endl;
     cout<<"meta->level = "<<hash.meta->level<<endl;
     cout<<"meta->next = "<<hash.meta->next<<endl;
     cout<<"meta->overflow_num = "<<hash.meta->overflow_num<<endl;
     cout<<"bitmap"<<endl;
     for(int i=0; i<BITMAP; i++){
     	cout<<hash.bitmap[i]<<" ";
     }*/
     return 0;
}

vector<string> split(const string &str, const string &pattern)
{
	vector<string> res;
	if (str == "")
		return res;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + pattern;
	size_t pos = strs.find(pattern);

	while (pos < strs.size())
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(pattern);
	}

	return res;
}
