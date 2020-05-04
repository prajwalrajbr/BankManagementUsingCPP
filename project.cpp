#include<bits/stdc++.h>//It's the header file that includes every header files, i.e., links every header file to our program.
#include <sys/stat.h>//This is required to check if the file exist or not.

using namespace std;

class bank{
    private:
        char username[20], password[16];
    public:
	    bank();
        inline bool ifFileExist(const string& name);
        string hash(string key);
        ~bank();
};

//Constructor
bank::bank(){
    cout<<"WELCOME TO \'BANK OF MIT\'"<<endl;
}

//The fastest way to check if the file exists.
inline bool bank::ifFileExist(const string& name){
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}

//A simple multiplicative hash, even though the collision rate is high, it is enough for our simple program.
string bank::hash(string key){
	unsigned int x = 5674356;
	unsigned int hashVariable;
	for(int i = 0;i < key.length();i++){
		hashVariable = hashVariable ^ ( key[i] );
		hashVariable = hashVariable * x;
	}
    stringstream hexHash;
    hexHash << hex << hashVariable;
    key = hexHash.str();
    transform(key.begin(), key.end(), key.begin(), ::toupper);
	return key;
}

//Destructor
bank::~bank(){

}

//Exexcution starts from here.
int main(){
    bank b;
    fstream managerInfo;

    if(b.ifFileExist("minfo.txt")){
        //...file exist
        cout<<"exist"<<endl;
    }
    else{
        //...file does not exist
        cout<<"not exist"<<endl;
    }
    char choice;
    for(;;){

        cout<<"SELECT THE LOG-IN TYPE:"<<endl;
        cout<<"1: BANK MANAGER LOG-IN"<<endl;
        cout<<"2: EMPLOYEE LOG-IN"<<endl;
        cout<<"3: ACCOUNT HOLDER LOG-IN"<<endl;
        cout<<"4: EXIT"<<endl;       
        cin>>choice;
        
        switch (choice){
            case '1':
                cout<<"1"<<endl;
                break;
            
            case '2':
                cout<<"1"<<endl;
                break;
            
            case '3':
                cout<<"1"<<endl;
                break;
        
            default:
                exit(0);
            
        }

    }
    return 0;
}
