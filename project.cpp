#include<bits/stdc++.h>//It's the header file that includes every header files, i.e., links every header file to our program.
#include <sys/stat.h>

using namespace std;

class bank{
    private:
        char username[20], password[16];
    public:
	    bank();
        inline bool ifFileExist(const string& name){
            struct stat buffer;   
            return (stat (name.c_str(), &buffer) == 0); 
        }
        ~bank();
};

bank::bank(){
    cout<<"WELCOME TO \'BANK OF MIT\'"<<endl;
}

bank::~bank(){

}

int main(){
    bank b;
    ifstream managerInfo;



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
