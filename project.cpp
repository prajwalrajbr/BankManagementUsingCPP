#include<bits/stdc++.h>//It's the header file that includes every header files, i.e., links every header file to our program.
#include <sys/stat.h>//This is required to check if the file exist or not.
#include <termios.h>//This is required to change settings of the terminal.

using namespace std;

//The input password must not show on terminal, so the code implemented is
//From here...............................................................
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo){
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if(echo){
      current.c_lflag |= ECHO; /* set echo mode */
  }else{
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void){
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo){
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(){
  return getch_(0);
}

//To here.................................................................

//Global variables
bool mData=false;
int eRRN=0, noOfEmp=0;
int cRRN=0, noOfCus=0;
int accountNoPrefix = 64213885;
string IFSC = "BMIT0040268"; 

struct emp{
    char rrn[10], name[100], EID[10], email[100], pwd[50], pno[20], addedBy[10], location[100], branchCode[10], buf[300];
};

class bank{
    private:
        char username[20], password[16];
    public:
        inline bool ifFileExist(const string& name);
        string hash(string key);
        bool is_digits(const string &str);

        void manager();
        void employee();
};

//The fastest way to check if the file exists.
inline bool bank::ifFileExist(const string& name){
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}
//A simple multiplicative hash, even though the collision rate is high, it is enough for our simple program.
string bank::hash(string key){
	unsigned int x = 5674356;
	unsigned int hashVariable = 0;
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

bool bank::is_digits(const string &str){
    return str.find_first_not_of("0123456789")==string::npos;
}

void bank::manager(){
    class managers{
        private:
            fstream file;
            int i, j, found;
            char mChoice, buf[1000], ch, pwd,pwd1[14], pwd2[14],id[100],pwde[100],mname[100];
            string name,ID,email,pno,location,branchCode,ps;
            bank b;
            struct emp e[6];
            unsigned int sort[6];
            
        public:
            void managersDashBoard(){
                if(mData){
                    system("clear");
                    file.open("minfo.txt",ios::in);
                    file.getline(mname,99,'|');
                    file.getline(id,99,'|');
                    for(i=0;i<2;i++){
                        file.getline(pwde,99,'|');
                    }
                    file.close();
                    j=0;
                    while(true){
                        cout<<"\nENTER THE MANAGER ID : ";
                        cin>>ID;
                        cout<<"ENTER THE PASSWORD : ";
                        getch();
                        strcpy(pwd1,"");
                        i = 0;
                        while(true){
                            pwd = getch();
                            if (pwd=='\n'){
                                break;
                            }
                            cout<<"*";
                            ps=pwd;
                            strcat(pwd1,ps.c_str());
                            i++;
                        }
                        
                        ps="";
                        for(i=0;i<strlen(pwd1);i++){
                            ps = ps+pwd1[i];
                        }
                        ps=b.hash(ps);
                        if ((strcmp(ps.c_str(),pwde)==0)&&(strcmp(ID.c_str(),id)==0)){
                            break;
                        }else{
                            cout<<"\nTHE ENTERED USERNAME OR PASSWORD IS INCORRECT"<<endl;
                            if(j==2){
                                cout<<"TOO MANY ATTEMPTS\n";
                                exit(1);
                            }
                        }
                        j++;
                    }
                    system("clear");
                    cout<<"WELCOME "<<mname<<endl;
                    
                    while(true){
                        cout<<"\n------BANK OF MIT------"<<endl;
                        cout<<"1: VIEW PROFILE"<<endl;
                        cout<<"2: UPDATE PROFILE"<<endl;
                        cout<<"3: ADD EMPLOYEE"<<endl;
                        cout<<"4: UPDATE EMPLOYEE DATA"<<endl;
                        cout<<"5: VIEW ALL EMPLOYEES"<<endl;
                        cout<<"6: SEARCH EMPLOYEE"<<endl;
                        cout<<"7: REMOVE EMPLOYEE"<<endl;
                        cout<<"8: VIEW TRANSACTIONS"<<endl;
                        cout<<"9: LOG-OUT"<<endl;
                        mChoice = getch();
                        system("clear");

                        switch(mChoice){
                            case '1':
                                managerDataDisplay();
                                cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                                getch();
                                system("clear");
                                break;
                            case '2':
                                managerDataUpdate();
                                break;
                            case '3':
                                employeeDataInput();
                                cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                                getch();
                                system("clear");
                                break;
                            case '4':
                                employeeDataUpdate();
                                cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                                getch();
                                getch();
                                system("clear");
                                break;
                            case '5':
                                viewAllEmployees();
                                cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                                getch();
                                system("clear");
                                break;
                            case '6':
                                employeeDataSearch();
                                cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                                getch();
                                getch();
                                system("clear");
                                break;
                            case '7':
                                removeEmployee();
                                cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                                getch();
                                getch();
                                system("clear");
                                break;
                            case '8':
                                cout<<"NOT IMPLEMENTED";
                                break;
                            default :
                                cout<<"SUCCESSFULLY LOGGED-OUT"<<endl; 
                                return;
                        }
                    }
                }else{
                    managerDataInput();
                    mData = true;
                    managersDashBoard();
                }
            }
            void managerDataInput(){
                strcpy(buf,""); 
                while(true){            
                    cout<<"\nENTER YOUR FULL NAME:"<<endl;
                    getline(cin,name);
                    if(strlen(name.c_str())<1){
                    }else{
                        break;
                    }
                }
                strcat(buf,name.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE 8-DIGIT MANAGER-ID:"<<endl;
                for(;;){
                    cin>>ID;
                    if(b.is_digits(ID)){
                        if(strlen(ID.c_str())==8){
                            break;
                        }else{
                            cout<<"THE ID MUST BE 8 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE ID MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,ID.c_str());
                strcat(buf,"|");

                cout<<"ENTER YOUR EMAIL-ID:"<<endl;
                while(true){
                    cin>>email;
                    for(i=0;i<strlen(email.c_str());i++){
                        if (email[i]=='@'){
                            for(j=i;j<strlen(email.c_str());j++){
                                if (email[j]=='.'){
                                    j=0;
                                    break;
                                }
                            }
                            if (j==0){
                                i=0;
                                break;
                            }
                        }
                    }
                    if (i==0 && j==0){
                        break;
                    }
                    cout<<"ENTER A VALID EMAIL-ID"<<endl;
                }
                strcat(buf,email.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE PASSWORD HAVING 8 TO 14 CHARACTERS:"<<endl;               
                getch();

                startpwd1:
                strcpy(pwd1,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd1;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd1;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd1,ps.c_str());
                    i++;
                }
                cout<<"\nENTER THE PASSWORD AGAIN"<<endl;
                startpwd2:
                strcpy(pwd2,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd2;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd2;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd2,ps.c_str());
                    i++;
                }
                if ((strcmp(pwd1,pwd2))!=0){
                    cout<<"PASSWORDS DOESN'T MATCH, ENTER THE PASSWORDS AGAIN"<<endl;
                    goto startpwd1;
                }
                ps="";
                for(i=0;i<strlen(pwd1);i++){
                    ps = ps+pwd1[i];
                }
                ps = b.hash(ps);
                strcat(buf,ps.c_str());
                strcat(buf,"|");

                cout<<"\nENTER THE 10-DIGIT PHONE NUMBER:"<<endl;
                for(;;){
                    cin>>pno;
                    if(b.is_digits(pno)){
                        if(strlen(pno.c_str())==10){
                            break;
                        }else{
                            cout<<"THE PHONE NUMBER MUST BE 10 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE PHONE NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,pno.c_str());
                strcat(buf,"|");

                getch();
                while(true){
                    cout<<"ENTER THE LOCATION OF THE BANK:"<<endl;
                    getline(cin,location);
                    if(strlen(location.c_str())<1){
                    }else{
                        break;
                    }
                }
                strcat(buf,location.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE 6-DIGIT BRANCH CODE:"<<endl;
                for(;;){
                    cin>>branchCode;
                    if(b.is_digits(branchCode)){
                        if(strlen(branchCode.c_str())==6){
                            break;
                        }else{
                            cout<<"THE BRANCH CODE MUST BE 6 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE BRANCH CODE MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,branchCode.c_str());
                strcat(buf,"\n");
                
                file.open("minfo.txt",ios::out);
                file.write(buf,strlen(buf));
                file.close();
                cout<<"MANAGER ACCOUNT SUCCESSFULLY CREATED..."<<endl;
                
                return;
            }
            void managerDataUpdate(){
                file.open("minfo.txt",ios::in);
                
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                location="";
                for(i=0;i<strlen(mname);i++){
                    location = location+mname[i];
                }
                file.getline(mname,99,'\n');
                branchCode="";
                for(i=0;i<strlen(mname);i++){
                    branchCode = branchCode+mname[i];
                }
                file.close();

                strcpy(buf,"");                
                cout<<"\nENTER THE UPDATED NAME OF THE MANAGER:"<<endl;
                while(true){
                    getline(cin,name);
                    if(strlen(name.c_str())<1){
                        cout<<"\nENTER THE UPDATED NAME OF THE MANAGER:"<<endl;
                    }else{
                        break;
                    }
                }
                strcat(buf,name.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE NEW 8-DIGIT MANAGER-ID:"<<endl;
                for(;;){
                    cin>>ID;
                    if(b.is_digits(ID)){
                        if(strlen(ID.c_str())==8){
                            break;
                        }else{
                            cout<<"THE ID MUST BE 8 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE ID MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,ID.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE NEW EMAIL-ID:"<<endl;
                while(true){
                    cin>>email;
                    for(i=0;i<strlen(email.c_str());i++){
                        if (email[i]=='@'){
                            for(j=i;j<strlen(email.c_str());j++){
                                if (email[j]=='.'){
                                    j=0;
                                    break;
                                }
                            }
                            if (j==0){
                                i=0;
                                break;
                            }
                        }
                    }
                    if (i==0 && j==0){
                        break;
                    }
                    cout<<"ENTER A VALID EMAIL-ID"<<endl;
                }
                strcat(buf,email.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE NEW PASSWORD HAVING 8 TO 14 CHARACTERS:"<<endl;               
                getch();

                startpwd3:
                strcpy(pwd1,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd3;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd3;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd1,ps.c_str());
                    i++;
                }
                cout<<"\nENTER THE PASSWORD AGAIN"<<endl;
                startpwd4:
                strcpy(pwd2,"");
                i = 0;
                while(true){
                    pwd = getch();
                    if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                        if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                        }else{                        
                            cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                            goto startpwd4;
                        }
                    }
                    if (pwd=='\n'){
                        if (i>7 && i<15){
                            break;
                        }else{
                            cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                            goto startpwd4;
                        }
                    }
                    cout<<"*";
                    ps=pwd;
                    strcat(pwd2,ps.c_str());
                    i++;
                }
                if ((strcmp(pwd1,pwd2))!=0){
                    cout<<"PASSWORDS DOESN'T MATCH, ENTER THE PASSWORDS AGAIN"<<endl;
                    goto startpwd3;
                }
                ps="";
                for(i=0;i<strlen(pwd1);i++){
                    ps = ps+pwd1[i];
                }
                ps = b.hash(ps);
                strcat(buf,ps.c_str());
                strcat(buf,"|");

                cout<<"\nENTER THE NEW 10-DIGIT PHONE NUMBER:"<<endl;
                for(;;){
                    cin>>pno;
                    if(b.is_digits(pno)){
                        if(strlen(pno.c_str())==10){
                            break;
                        }else{
                            cout<<"THE PHONE NUMBER MUST BE 10 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE PHONE NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,pno.c_str());
                strcat(buf,"|");

                strcat(buf,location.c_str());
                strcat(buf,"|");

                strcat(buf,branchCode.c_str());
                strcat(buf,"\n");
            
                file.open("minfo.txt",ios::out);
                file.write(buf,strlen(buf));
                file.close();
                system("clear");
                cout<<"MANAGER ACCOUNT SUCCESSFULLY UPDATED..."<<endl;
                cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                getch();
                getch();
                system("clear");
                return;
            }
            void managerDataDisplay(){        
                file.open("minfo.txt",ios::in);
                cout<<"\nMANAGER'S DEAILS :"<<endl;
                file.getline(mname,99,'|');
                cout<<"\nFULL NAME : "<<mname<<endl;
                file.getline(mname,99,'|');
                cout<<"MANAGER-ID : "<<mname<<endl;
                file.getline(mname,99,'|');
                cout<<"EMAIL ADDRESS : "<<mname<<endl;
                file.getline(mname,99,'|');
                file.getline(mname,99,'|');
                cout<<"PHONE NO. : "<<mname<<endl;
                file.getline(mname,99,'|');
                cout<<"LOCATION OF THE BANK : "<<mname<<endl;
                file.getline(mname,99,'\n');
                cout<<"BRANCH CODE : "<<mname<<endl;
                file.close();
                return;
            }
            void employeeDataInput(){
                if(noOfEmp<5){

                    strcpy(buf,to_string(eRRN).c_str());
                    strcat(buf,"|");
                    while(true){            
                        cout<<"\nENTER THE FULL NAME OF THE EMPLOYEE:"<<endl;
                        getline(cin,name);
                        if(strlen(name.c_str())<1){
                        }else{
                            break;
                        }
                    }
                    strcat(buf,name.c_str());
                    strcat(buf,"|");

                    cout<<"ENTER THE 8-DIGIT EMPLOYEE-ID:"<<endl;
                    for(;;){
                        cin>>ID;
                        if(b.is_digits(ID)){
                            if(strlen(ID.c_str())==8){
                                break;
                            }else{
                                cout<<"THE ID MUST BE 8 DIGITS!!!"<<endl;
                            }
                        }else{
                            cout<<"THE ID MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                        }
                    }
                    strcat(buf,ID.c_str());
                    strcat(buf,"|");

                    cout<<"ENTER THE EMPLOYEE'S EMAIL-ID:"<<endl;
                    while(true){
                        cin>>email;
                        for(i=0;i<strlen(email.c_str());i++){
                            if (email[i]=='@'){
                                for(j=i;j<strlen(email.c_str());j++){
                                    if (email[j]=='.'){
                                        j=0;
                                        break;
                                    }
                                }
                                if (j==0){
                                    i=0;
                                    break;
                                }
                            }
                        }
                        if (i==0 && j==0){
                            break;
                        }
                        cout<<"ENTER A VALID EMAIL-ID"<<endl;
                    }
                    strcat(buf,email.c_str());
                    strcat(buf,"|");

                    cout<<"ENTER THE PASSWORD FOR EMPLOYEE HAVING 8 TO 14 CHARACTERS:"<<endl;               
                    getch();

                    startpwd5:
                    strcpy(pwd1,"");
                    i = 0;
                    while(true){
                        pwd = getch();
                        if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                            if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                            }else{
                                cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                                goto startpwd5;
                            }
                        }
                        if (pwd=='\n'){
                            if (i>7 && i<15){
                                break;
                            }else{
                                cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                                goto startpwd5;
                            }
                        }
                        cout<<"*";
                        ps=pwd;
                        strcat(pwd1,ps.c_str());
                        i++;
                    }
                    cout<<"\nENTER THE PASSWORD AGAIN"<<endl;
                    startpwd6:
                    strcpy(pwd2,"");
                    i = 0;
                    while(true){
                        pwd = getch();
                        if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                            if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                            }else{
                                cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                                goto startpwd6;
                            }
                        }
                        if (pwd=='\n'){
                            if (i>7 && i<15){
                                break;
                            }else{
                                cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                                goto startpwd6;
                            }
                        }
                        cout<<"*";
                        ps=pwd;
                        strcat(pwd2,ps.c_str());
                        i++;
                    }
                    if ((strcmp(pwd1,pwd2))!=0){
                        cout<<"PASSWORDS DOESN'T MATCH, ENTER THE PASSWORDS AGAIN"<<endl;
                        goto startpwd5;
                    }
                    ps="";
                    for(i=0;i<strlen(pwd1);i++){
                        ps = ps+pwd1[i];
                    }
                    ps = b.hash(ps);
                    strcat(buf,ps.c_str());
                    strcat(buf,"|");

                    cout<<"\nENTER THE 10-DIGIT PHONE NUMBER OF THE EMPLOYEE:"<<endl;
                    for(;;){
                        cin>>pno;
                        if(b.is_digits(pno)){
                            if(strlen(pno.c_str())==10){
                                break;
                            }else{
                                cout<<"THE PHONE NUMBER MUST BE 10 DIGITS!!!"<<endl;
                            }
                        }else{
                            cout<<"THE PHONE NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                        }
                    }
                    strcat(buf,pno.c_str());
                    strcat(buf,"|");

                    
                    file.open("minfo.txt",ios::in);
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    strcat(buf,mname);
                    strcat(buf,"|");
                    for(i=0;i<3;i++){
                        file.getline(mname,99,'|');
                    }
                    file.getline(mname,99,'|');
                    strcat(buf,mname);
                    strcat(buf,"|");
                    file.getline(mname,99,'\n');
                    strcat(buf,mname);
                    file.close();

                    while(strlen(buf)<200){
                        strcat(buf,"!");
                    }
                    strcat(buf,"\n");

                    file.open("erecord.txt",ios::app);
                    file<<buf;
                    file.close();

                    file.open("eindex.txt",ios::app);
                    file<<eRRN<<"|"<<ID<<"|"<<ps<<"#";
                    file.close();

                    eRRN++;
                    noOfEmp++;
                    system("clear");
                    cout<<"EMPLOYEE ACCOUNT SUCCESSFULLY CREATED..."<<endl;
                    getch();
                }else{
                    cout<<"\nMAXIMUM NUMBER OF EMPLOYEES HAS BEEN CREATED"<<endl;
                    cout<<"REMOVE ANY EMPLOYEE TO ADD THE NEW EMPLOYEE"<<endl;
                }    
                return;
                
            }
            void employeeDataUpdate(){
                found=0;
                cout<<"ENTER THE EMPLOYEE-ID TO BE UPDATED : ";
                cin>>ID; 
                file.open("eindex.txt",ios::in);
                while(!file.eof()){
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    if(strcmp(ID.c_str(),mname)==0){
                        cout<<"EMPLOYEE WITH ID "<<ID<<" FOUND\n"<<endl;
                        found=1;
                        break;
                    }
                    file.getline(mname,99,'#');
                }
                file.close();
                if(found==0){
                    cout<<"EMPLOYEE WITH ID '"<<ID<<"' NOT FOUND"<<endl;
                    return;
                }
                while(true){            
                    cout<<"\nENTER THE UPDATED NAME OF THE EMPLOYEE:"<<endl;
                    getch();
                    getline(cin,name);
                    if(strlen(name.c_str())<1){
                    }else{
                        break;
                    }
                }

                cout<<"ENTER THE EMPLOYEE'S NEW EMAIL-ID:"<<endl;
                while(true){
                    cin>>email;
                    for(i=0;i<strlen(email.c_str());i++){
                        if (email[i]=='@'){
                            for(j=i;j<strlen(email.c_str());j++){
                                if (email[j]=='.'){
                                    j=0;
                                    break;
                                }
                            }
                            if (j==0){
                                i=0;
                                break;
                            }
                        }
                    }
                    if (i==0 && j==0){
                        break;
                    }
                    cout<<"ENTER A VALID EMAIL-ID"<<endl;
                }

                cout<<"ENTER THE NEW PASSWORD FOR EMPLOYEE HAVING 8 TO 14 CHARACTERS:"<<endl;               
                getch();

                startpwd7:
                strcpy(pwd1,"");
                i = 0;
                while(true){
                        pwd = getch();
                        if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                            if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                            }else{
                                cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                                goto startpwd7;
                            }
                        }
                        if (pwd=='\n'){
                            if (i>7 && i<15){
                                break;
                            }else{
                                cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                                goto startpwd7;
                            }
                        }
                        cout<<"*";
                        ps=pwd;
                        strcat(pwd1,ps.c_str());
                        i++;
                }
                cout<<"\nENTER THE PASSWORD AGAIN"<<endl;
                startpwd8:
                strcpy(pwd2,"");
                i = 0;
                while(true){
                        pwd = getch();
                        if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                            if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                            }else{
                                cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                                goto startpwd8;
                            }
                        }
                        if (pwd=='\n'){
                            if (i>7 && i<15){
                                break;
                            }else{
                                cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                                goto startpwd8;
                            }
                        }
                        cout<<"*";
                        ps=pwd;
                        strcat(pwd2,ps.c_str());
                        i++;
                }
                if ((strcmp(pwd1,pwd2))!=0){
                    cout<<"PASSWORDS DOESN'T MATCH, ENTER THE PASSWORDS AGAIN"<<endl;
                    goto startpwd7;
                }
                ps="";
                for(i=0;i<strlen(pwd1);i++){
                    ps = ps+pwd1[i];
                }
                ps = b.hash(ps);

                cout<<"\nENTER THE NEW 10-DIGIT PHONE NUMBER OF THE EMPLOYEE:"<<endl;
                for(;;){
                        cin>>pno;
                        if(b.is_digits(pno)){
                            if(strlen(pno.c_str())==10){
                                break;
                            }else{
                                cout<<"THE PHONE NUMBER MUST BE 10 DIGITS!!!"<<endl;
                            }
                        }else{
                            cout<<"THE PHONE NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                        }
                }

                file.open("eindex.txt",ios::in);
                i=0;
                while(!file.eof()){
                    file.getline(e[i].rrn,99,'|');
                    file.getline(e[i].EID,99,'|');
                    file.getline(e[i].pwd,99,'#');
                    i++;
                }
                file.close();
                file.open("eindex.txt",ios::out);
                for(i=0;i<noOfEmp;i++){
                    if(strcmp(e[i].EID,ID.c_str())==0){
                        file<<e[i].rrn<<"|"<<e[i].EID<<"|"<<ps<<"#";
                    }else{
                        file<<e[i].rrn<<"|"<<e[i].EID<<"|"<<e[i].pwd<<"#";
                    }
                }
                file.close();
                file.open("erecord.txt",ios::in);
                i=0;
                while(!file.eof()){
                    file.getline(e[i].rrn,99,'|');
                    file.getline(e[i].name,99,'|');
                    file.getline(e[i].EID,99,'|');
                    file.getline(e[i].email,99,'|');
                    file.getline(e[i].pwd,99,'|');
                    file.getline(e[i].pno,99,'|');
                    file.getline(e[i].addedBy,99,'|');
                    file.getline(e[i].location,99,'|');
                    file.getline(e[i].branchCode,99,'!');
                    file.getline(e[i].buf,200,'\n');
                    strcat(e[i].buf,"!");
                    i++;
                }
                file.close();
                file.open("erecord.txt",ios::out);                
                for(i=0;i<noOfEmp;i++){
                    if(strcmp(e[i].EID,ID.c_str())==0){
                        strcpy(buf,e[i].rrn);
                        strcat(buf,"|");
                        strcat(buf,name.c_str());
                        strcat(buf,"|");
                        strcat(buf,e[i].EID);
                        strcat(buf,"|");
                        strcat(buf,email.c_str());
                        strcat(buf,"|");
                        strcat(buf,ps.c_str());
                        strcat(buf,"|");
                        strcat(buf,pno.c_str());
                        strcat(buf,"|");
                        strcat(buf,e[i].addedBy);
                        strcat(buf,"|");
                        strcat(buf,e[i].location);
                        strcat(buf,"|");
                        strcat(buf,e[i].branchCode);
                        strcat(buf,"!");
                        while(strlen(buf)<200){
                            strcat(buf,"!");
                        }
                        strcat(buf,"\n");
                        file<<buf;
                        cout<<"EMPLOYEE '"<<e[i].name<<"' WITH EMPOYEE-ID '"<<e[i].EID<<"' SUCCESSFULLY UPDATED"<<endl;
                        
                    }else{
                        file<<e[i].rrn<<"|"<<e[i].name<<"|"<<e[i].EID<<"|"<<e[i].email<<"|"<<e[i].pwd<<"|"<<e[i].pno<<"|"<<e[i].addedBy<<"|"<<e[i].location<<"|"<<e[i].branchCode<<e[i].buf<<"\n";
                    }
                }
                file.close();
                return;

            }
            void employeeDataSearch(){
                found=0;
                cout<<"ENTER THE EMPLOYEE-ID TO BE SEARCHED : ";
                cin>>ID;
                file.open("eindex.txt",ios::in);
                while(!file.eof()){
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    if(strcmp(ID.c_str(),mname)==0){
                        cout<<"EMPLOYEE WITH ID "<<ID<<" FOUND\n"<<endl;
                        found=1;
                        break;
                    }
                    file.getline(mname,99,'#');
                }
                file.close();
                if(found==0){
                    cout<<"EMPLOYEE WITH ID '"<<ID<<"' NOT FOUND"<<endl;
                    return;
                }
                cout<<"EMPLOYEE DETAILS : "<<endl;
                file.open("erecord.txt",ios::in);
                while(!file.eof()){                   
                    file.getline(mname,99,'|');        
                    file.getline(mname,99,'|');
                    file.getline(buf,99,'|');
                    if(strcmp(buf,ID.c_str())==0){
                        cout<<"EMPLOYEE NAME : "<<mname<<endl; 
                        cout<<"EMPLOYEE-ID : "<<buf<<endl;                       
                        file.getline(buf,99,'|');
                        cout<<"EMPLOYEE EMAIL ADDRESS : "<<buf<<endl;                        
                        file.getline(buf,99,'|');                      
                        file.getline(buf,99,'|');
                        cout<<"EMPLOYEE PHONE NO. : "<<buf<<endl;                        
                        file.getline(buf,99,'|');
                        cout<<"ADDED BY MANAGER-ID : "<<buf<<endl;                        
                        file.getline(buf,99,'|');
                        cout<<"LOCATION OF THE BANK : "<<buf<<endl;                        
                        file.getline(buf,99,'!');
                        cout<<"BRANCH CODE : "<<buf<<endl;
                        file.close();
                        return;
                    }
                    file.getline(buf,999,'\n');
                }
                file.close();
                return;
            }
            void removeEmployee(){
                found=0;
                cout<<"ENTER THE EMPLOYEE-ID TO BE REMOVED : ";
                cin>>ID; 
                file.open("eindex.txt",ios::in);
                while(!file.eof()){
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    if(strcmp(ID.c_str(),mname)==0){
                        cout<<"EMPLOYEE WITH ID "<<ID<<" FOUND\n"<<endl;
                        found=1;
                        break;
                    }
                    file.getline(mname,99,'#');
                }
                file.close();
                if(found==0){
                    cout<<"EMPLOYEE WITH ID '"<<ID<<"' NOT FOUND"<<endl;
                    return;
                }
                file.open("eindex.txt",ios::in);
                i=0;
                while(!file.eof()){
                    file.getline(e[i].rrn,99,'|');
                    file.getline(e[i].EID,99,'|');
                    file.getline(e[i].pwd,99,'#');
                    i++;
                }
                file.close();
                file.open("eindex.txt",ios::out);
                for(i=0;i<noOfEmp;i++){
                    if(strcmp(e[i].EID,ID.c_str())==0){
                    }else{
                        file<<e[i].rrn<<"|"<<e[i].EID<<"|"<<e[i].pwd<<"#";
                    }
                }
                file.close();
                file.open("erecord.txt",ios::in);
                i=0;
                while(!file.eof()){
                    file.getline(e[i].rrn,99,'|');
                    file.getline(e[i].name,99,'|');
                    file.getline(e[i].EID,99,'|');
                    file.getline(e[i].email,99,'|');
                    file.getline(e[i].pwd,99,'|');
                    file.getline(e[i].pno,99,'|');
                    file.getline(e[i].addedBy,99,'|');
                    file.getline(e[i].location,99,'|');
                    file.getline(e[i].branchCode,99,'!');
                    file.getline(e[i].buf,200,'\n');
                    strcat(e[i].buf,"!");
                    i++;
                }
                file.close();
                file.open("erecord.txt",ios::out);                
                for(i=0;i<noOfEmp;i++){
                    if(strcmp(e[i].EID,ID.c_str())==0){
                        cout<<"EMPLOYEE '"<<e[i].name<<"' WITH EMPOYEE-ID '"<<e[i].EID<<"' SUCCESSFULLY REMOVED"<<endl;
                        
                    }else{
                        file<<e[i].rrn<<"|"<<e[i].name<<"|"<<e[i].EID<<"|"<<e[i].email<<"|"<<e[i].pwd<<"|"<<e[i].pno<<"|"<<e[i].addedBy<<"|"<<e[i].location<<"|"<<e[i].branchCode<<e[i].buf<<"\n";
                    }
                }
                file.close();
                noOfEmp--;
                return;
            }
            void viewAllEmployees(){
                file.open("eindex.txt",ios::in);                
                i=0;
                while(!file.eof()){
                    file.getline(e[i].rrn,99,'|');
                    file.getline(e[i].EID,99,'|');
                    ps="";
                    for(j=0;j<strlen(e[i].EID);j++){
                        ps+=e[i].EID[j];
                    }
                    stringstream s(ps);
                    s>>sort[i];
                    file.getline(e[i].pwd,99,'#');
                    i++;
                }
                file.close();
                
                //key sorting using bubble sort 
                for(i=0;i<noOfEmp-1;i++){
                    for(j=0;j<noOfEmp-i-1;j++){
                        if(sort[j]>sort[j+1]){
                            sort[j]=sort[j]+sort[j+1];
                            sort[j+1]=sort[j]-sort[j+1];
                            sort[j]=sort[j]-sort[j+1];
                        }

                    }
                }
                
                file.open("eindex.txt",ios::out);  
                for(i=0;i<noOfEmp;i++){
                    for(j=0;j<noOfEmp;j++){
                        if(strcmp(e[j].EID,to_string(sort[i]).c_str())==0){
                            file<<e[j].rrn<<"|"<<e[j].EID<<"|"<<e[j].pwd<<"#";
                        }
                    }
                }
                file.close();
                
                file.open("erecord.txt",ios::in); 
                i=0;
                while(!file.eof()){               
                    file.getline(e[i].rrn,99,'|');
                    file.getline(e[i].name,99,'|');
                    file.getline(e[i].EID,99,'|');                       
                    file.getline(e[i].email,99,'|');                        
                        file.getline(e[i].pwd,99,'|');                      
                        file.getline(e[i].pno,99,'|');                       
                        file.getline(e[i].addedBy,99,'|');                       
                        file.getline(e[i].location,99,'|');                        
                        file.getline(e[i].branchCode,99,'!');                      
                        file.getline(e[i].buf,200,'\n');
                        i++;
                }
                file.close(); 
                cout<<"TOTAL NO. OF EMPLOYEES: "<<noOfEmp<<endl;
                cout<<"\nRRN"<<" |"<<"EID"<<"      |"<<"EMPLOYEE NAME"<<endl;
                for(i=0;i<noOfEmp;i++){
                    for(j=0;j<noOfEmp;j++){
                        if(strcmp(e[j].EID,to_string(sort[i]).c_str())==0){
                            strcpy(buf,"");
                            strcat(buf,e[j].rrn);
                            while(strlen(buf)<4){
                                strcat(buf," ");
                            }
                            strcat(buf,"|");
                            strcat(buf,e[j].EID);
                            while(strlen(buf)<14){
                                strcat(buf," ");
                            }
                            strcat(buf,"|");
                            strcat(buf,e[j].name);
                            strcat(buf,"\n");
                            cout<<buf;
                        }
                    }
                }
                return;
            }
    };
    managers m;
    m.managersDashBoard();
    return;
}

void bank::employee(){
    class employees{
        private:
            fstream file;
            int i, j, found, date, month, year, indexNo=0, k;
            char mChoice, buf[1000], buffer[1000], ch, dob[10], currentLoggedInRRN[10], pwd,pwd1[14], pwd2[14],id[100],pwde[100],mname[100];
            string name,ID,email,pno,location,branchCode,ps,accNo, DOB[3], amt;
            bank b;
            struct emp e[6];
            unsigned int sort[6];
        public:
            void employeeDashBoard(){
                system("clear");
                j=0;
                found=0;
                while(true){
                    cout<<"\nENTER THE EMPLOYEE ID : ";
                    cin>>ID;
                    cout<<"ENTER THE PASSWORD : ";
                    getch();
                    strcpy(pwd1,"");
                    i = 0;
                    while(true){
                        pwd = getch();
                        if (pwd=='\n'){
                            break;
                        }
                        cout<<"*";
                        ps=pwd;
                        strcat(pwd1,ps.c_str());
                        i++;
                    }                        
                    ps="";
                    for(i=0;i<strlen(pwd1);i++){
                        ps = ps+pwd1[i];
                    }
                    ps=b.hash(ps);
                    file.open("eindex.txt",ios::in);
                    while(!file.eof()){                        
                        file.getline(id,99,'|');
                        file.getline(mname,99,'|');
                        file.getline(pwde,99,'#');
                        if ((strcmp(ps.c_str(),pwde)==0)&&(strcmp(ID.c_str(),mname)==0)){
                            strcpy(currentLoggedInRRN,id);
                            found=1;
                            break;
                        }
                    }
                    file.close();
                    if(found == 0){
                        cout<<"\nTHE ENTERED USERNAME OR PASSWORD IS INCORRECT"<<endl;
                        if(j==2){
                            cout<<"TOO MANY ATTEMPTS\n";
                            exit(1);
                        }
                    }else{
                        system("clear");
                        file.open("erecord.txt",ios::in);
                        while(!file.eof()){
                            file.getline(mname,99,'|');
                            if(strcmp(id,mname)==0){
                                file.getline(mname,99,'|');
                                break;
                            }
                            file.getline(buf,300,'\n');
                        }
                        file.close();
                        cout<<"WELCOME "<<mname<<endl;
                        break;
                    }
                    j++;
                }while(true){
                    cout<<"\n------BANK OF MIT------"<<endl;
                    cout<<"1: VIEW PROFILE"<<endl;
                    cout<<"2: UPDATE PROFILE"<<endl;
                    cout<<"3: CREATE CUSTOMER ACCOUNT"<<endl;
                    cout<<"4: UDATE CUSTOMER ACCOUNT"<<endl;
                    cout<<"5: VIEW ALL CUSTOMERS"<<endl;
                    cout<<"6: SEARCH CUSTOMER OR UPDATE BALANCE"<<endl;
                    cout<<"7: REMOVE CUSTOMER"<<endl;
                    cout<<"8: VIEW TRANSACTIONS"<<endl;
                    cout<<"9: LOG-OUT"<<endl;
                    mChoice = getch();
                    system("clear");
                    switch(mChoice){
                        case '1':
                            employeeDataDisplay();
                            cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                            getch();
                            system("clear");
                            break;
                        case '2':
                            employeeDataUpdate();
                            cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                            getch();
                            system("clear");
                            break;
                        case '3':
                            createCustomerAccount();
                            cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                            getch();
                            system("clear");
                            break;
                        case '4':
                            cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                            getch();
                            getch();
                            system("clear");
                            break;
                        case '5':
                            viewAllCustomers();
                            cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                            getch();
                            system("clear");
                            break;
                        case '6':
                            searchCustomerOrUpdateBalance();
                            cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                            getch();
                            getch();
                            system("clear");
                            break;
                        case '7':
                            cout<<"\nPRESS ANY KEY TO RETURN TO MAIN MENU......";
                            getch();
                            getch();
                            system("clear");
                            break;
                        case '8':
                            break;
                        default :
                            cout<<"SUCCESSFULLY LOGGED-OUT"<<endl; 
                            return;
                    }
                }
            }
            void employeeDataDisplay(){                
                cout<<"\nEMPLOYEE'S DEAILS :"<<endl;   
                file.open("erecord.txt",ios::in);
                while(!file.eof()){
                    file.getline(mname,99,'|');
                    if(strcmp(currentLoggedInRRN,mname)==0){
                        file.getline(mname,99,'|');
                        cout<<"\nFULL NAME : "<<mname<<endl;
                        file.getline(mname,99,'|');
                        cout<<"EMPLOYEE-ID : "<<mname<<endl;
                        file.getline(mname,99,'|');
                        cout<<"EMAIL ADDRESS : "<<mname<<endl;
                        file.getline(mname,99,'|');
                        file.getline(mname,99,'|');
                        cout<<"PHONE NO. : "<<mname<<endl;
                        file.getline(mname,99,'|');
                        cout<<"ADDED BY MANAGER-ID : "<<mname<<endl;
                        file.getline(mname,99,'|');
                        cout<<"LOCATION OF THE BANK : "<<mname<<endl;
                        file.getline(mname,99,'!');
                        cout<<"BRANCH CODE : "<<mname<<endl;
                        break;
                    }
                    file.getline(buf,299,'\n');                
                }
                file.close();
                return;
            }
            void employeeDataUpdate(){
                file.open("erecord.txt",ios::in);
                i=0;
                while(!file.eof()){
                    file.getline(e[i].rrn,99,'|');
                    file.getline(e[i].name,99,'|');
                    file.getline(e[i].EID,99,'|');
                    file.getline(e[i].email,99,'|');
                    file.getline(e[i].pwd,99,'|');
                    file.getline(e[i].pno,99,'|');
                    file.getline(e[i].addedBy,99,'|');
                    file.getline(e[i].location,99,'|');
                    file.getline(e[i].branchCode,99,'!');    
                    file.getline(buf,299,'\n');  
                    i++;
                }
                file.close();

                while(true){            
                    cout<<"\nENTER THE UPDATED NAME OF THE EMPLOYEE:"<<endl;
                    getline(cin,name);
                    if(strlen(name.c_str())<1){
                    }else{
                        break;
                    }
                }

                cout<<"ENTER THE UPDATED EMAIL-ID:"<<endl;
                while(true){
                    cin>>email;
                    for(i=0;i<strlen(email.c_str());i++){
                        if (email[i]=='@'){
                            for(j=i;j<strlen(email.c_str());j++){
                                if (email[j]=='.'){
                                    j=0;
                                    break;
                                }
                            }
                            if (j==0){
                                i=0;
                                break;
                            }
                        }
                    }
                    if (i==0 && j==0){
                        break;
                    }
                    cout<<"ENTER A VALID EMAIL-ID"<<endl;
                }

                cout<<"ENTER THE NEW PASSWORD HAVING 8 TO 14 CHARACTERS:"<<endl;               
                getch();

                startpwd7:
                strcpy(pwd1,"");
                i = 0;
                while(true){
                        pwd = getch();
                        if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                            if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                            }else{
                                cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                                goto startpwd7;
                            }
                        }
                        if (pwd=='\n'){
                            if (i>7 && i<15){
                                break;
                            }else{
                                cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                                goto startpwd7;
                            }
                        }
                        cout<<"*";
                        ps=pwd;
                        strcat(pwd1,ps.c_str());
                        i++;
                }
                cout<<"\nENTER THE PASSWORD AGAIN"<<endl;
                startpwd8:
                strcpy(pwd2,"");
                i = 0;
                while(true){
                        pwd = getch();
                        if (pwd==' ' || pwd=='\t' || int(pwd)==127 || int(pwd)==65 || int(pwd)==66 || int(pwd)==67 || int(pwd)==68){
                            if(pwd=='A' ||pwd=='B' ||pwd=='C' ||pwd=='D' ){
                            }else{
                                cout<<"\nSPACES, TABS, BACKSPACESS AND ARROW KEYS ARE NOT ALLOWED, ENTER THE PASSWORD CORRECTLY!!!"<<endl;
                                goto startpwd8;
                            }
                        }
                        if (pwd=='\n'){
                            if (i>7 && i<15){
                                break;
                            }else{
                                cout<<"\nTHE PASSWORD MUST BE 8 TO 14 CHARACTERS!!!"<<endl;
                                goto startpwd8;
                            }
                        }
                        cout<<"*";
                        ps=pwd;
                        strcat(pwd2,ps.c_str());
                        i++;
                }
                if ((strcmp(pwd1,pwd2))!=0){
                    cout<<"PASSWORDS DOESN'T MATCH, ENTER THE PASSWORDS AGAIN"<<endl;
                    goto startpwd7;
                }
                ps="";
                for(i=0;i<strlen(pwd1);i++){
                    ps = ps+pwd1[i];
                }
                ps = b.hash(ps);

                file.open("eindex.txt",ios::out);
                for(i=0;i<noOfEmp;i++){
                    if(strcmp(currentLoggedInRRN,e[i].rrn)==0){
                        file<<e[i].rrn<<"|"<<e[i].EID<<"|"<<ps<<"#";
                        continue;
                    }
                    file<<e[i].rrn<<"|"<<e[i].EID<<"|"<<e[i].pwd<<"#";
                }
                file.close();
                file.open("erecord.txt",ios::out);
                for(i=0;i<noOfEmp;i++){    
                    if(strcmp(currentLoggedInRRN,e[i].rrn)==0){       
                        strcpy(buf,e[i].rrn);
                        strcat(buf,"|");
                        strcat(buf,name.c_str());
                        strcat(buf,"|");
                        strcat(buf,e[i].EID);
                        strcat(buf,"|");
                        strcat(buf,email.c_str());
                        strcat(buf,"|");
                        strcat(buf,ps.c_str());
                        strcat(buf,"|");
                        strcat(buf,e[i].pno);
                        strcat(buf,"|");
                        strcat(buf,e[i].addedBy);
                        strcat(buf,"|");
                        strcat(buf,e[i].location);
                        strcat(buf,"|");
                        strcat(buf,e[i].branchCode);
                        strcat(buf,"!");
                        while(strlen(buf)<200){
                            strcat(buf,"!");
                        }
                        strcat(buf,"\n");
                        file<<buf;    
                        system("clear");
                        cout<<"DETAILS SUCCESSFULLY UPDATED"<<endl;
                        continue;
                    }        
                    strcpy(buf,e[i].rrn);
                    strcat(buf,"|");
                    strcat(buf,e[i].name);
                    strcat(buf,"|");
                    strcat(buf,e[i].EID);
                    strcat(buf,"|");
                    strcat(buf,e[i].email);
                    strcat(buf,"|");
                    strcat(buf,e[i].pwd);
                    strcat(buf,"|");
                    strcat(buf,e[i].pno);
                    strcat(buf,"|");
                    strcat(buf,e[i].addedBy);
                    strcat(buf,"|");
                    strcat(buf,e[i].location);
                    strcat(buf,"|");
                    strcat(buf,e[i].branchCode);
                    strcat(buf,"!");
                    while(strlen(buf)<200){
                        strcat(buf,"!");
                    }
                    strcat(buf,"\n");
                    file<<buf;
                }
                file.close();
                return;
            }
            void createCustomerAccount(){
                strcpy(buf,to_string(cRRN).c_str());
                strcat(buf,"|");
                while(true){            
                    cout<<"\nENTER THE FULL NAME OF THE CUSTOMER:"<<endl;
                    getline(cin,name);
                    if(strlen(name.c_str())<1){
                    }else{
                        break;
                    }
                }
                strcat(buf,name.c_str());
                strcat(buf,"|");

                for(;;){
                    cout<<"SELECT THE ACCOUNT TYPE :"<<endl;
                    cout<<"1. SAVINGS ACCOUNT"<<endl;
                    cout<<"2. CURRENT ACCOUNT"<<endl;
                    cout<<"3. RECURRING DEPOSIT ACCOUNT"<<endl;
                    cout<<"4. FIXED DEPOSIT ACCOUNT"<<endl;
                    cout<<"5. DEMAT ACCOUNT"<<endl;
                    cout<<"6. NRI ACCOUNT"<<endl;
                    ch = getch();
                    if (ch=='1'){
                        cout<<"\nSELECTED : SAVINGS ACCOUNT\n"<<endl;
                        strcat(buf,"SAVINGS ACCOUNT");
                        break;
                    }
                    else if (ch=='2'){
                        cout<<"\nSELECTED : CURRENT ACCOUNT\n"<<endl;
                        strcat(buf,"CURRENT ACCOUNT");
                        break;
                    }
                    else if (ch=='3'){
                        cout<<"\nSELECTED : RECURRING DEPOSIT ACCOUNT\n"<<endl;
                        strcat(buf,"RECURRING DEPOSIT ACCOUNT");
                        break;
                    }
                    else if (ch=='4'){
                        cout<<"\nSELECTED : FIXED DEPOSIT ACCOUNT\n"<<endl;
                        strcat(buf,"FIXED DEPOSIT ACCOUNT");
                        break;
                    }
                    else if (ch=='5'){
                        cout<<"\nSELECTED : DEMAT ACCOUNT\n"<<endl;
                        strcat(buf,"DEMAT ACCOUNT");
                        break;
                    }
                    else if (ch=='6'){
                        cout<<"\nSELECTED : NRI ACCOUNT\n"<<endl;
                        strcat(buf,"NRI ACCOUNT");
                        break;
                    }
                    else {
                        cout<<"SELECT THE CHOICE CORRECTLY"<<endl;
                    }
                }
                strcat(buf,"|");
                
                cout<<"ENTER THE 11-DIGIT CIF NUMBER:"<<endl;
                for(;;){
                    cin>>ID;
                    if(b.is_digits(ID)){
                        if(strlen(ID.c_str())==11){
                            break;
                        }else{
                            cout<<"THE CIF NUMBER MUST BE 11 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE CIF NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,ID.c_str());
                strcat(buf,"|");

                if(cRRN<10){
                    accNo = to_string(accountNoPrefix)+"00"+to_string(cRRN);
                } else if(cRRN<100){
                    accNo = to_string(accountNoPrefix)+"0"+to_string(cRRN);
                }else{
                    accNo = to_string(accountNoPrefix)+to_string(cRRN);
                }
                strcat(buf,accNo.c_str());
                strcat(buf,"|");
   
                getch();
                while(true){
                    cout<<"ENTER THE ADDRESS OF THE CUSTOMER:"<<endl;
                    getline(cin,location);
                    if(strlen(location.c_str())<1){
                    }else{
                        break;
                    }
                }
                strcat(buf,location.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE CUSTOMER'S EMAIL-ID:"<<endl;
                while(true){
                    cin>>email;
                    for(i=0;i<strlen(email.c_str());i++){
                        if (email[i]=='@'){
                            for(j=i;j<strlen(email.c_str());j++){
                                if (email[j]=='.'){
                                    j=0;
                                    break;
                                }
                            }
                            if (j==0){
                                i=0;
                                break;
                            }
                        }
                    }
                    if (i==0 && j==0){
                        break;
                    }
                    cout<<"ENTER A VALID EMAIL-ID"<<endl;
                }
                strcat(buf,email.c_str());
                strcat(buf,"|");
                    
                cout<<"ENTER THE 10-DIGIT PHONE NUMBER OF THE CUSTOMER:"<<endl;
                for(;;){
                    cin>>pno;
                    if(b.is_digits(pno)){
                        if(strlen(pno.c_str())==10){
                            break;
                        }else{
                            cout<<"THE PHONE NUMBER MUST BE 10 DIGITS!!!"<<endl;
                        }
                    }else{
                        cout<<"THE PHONE NUMBER MUST CONTAIN ONLY NUMERICAL DIGITS!!!"<<endl;
                    }
                }
                strcat(buf,pno.c_str());
                strcat(buf,"|");

                cout<<"ENTER THE INITIAL DEPOSIT AMOUNT:"<<endl;
                for(;;){
                    cin>>amt;
                    if(!b.is_digits(amt.c_str())){
                        cout<<"ENTER THE INITIAL DEPOSIT AMOUNT IN DIGITS:"<<endl;
                    }else{
                        break;
                    }
                }
                strcat(buf,amt.c_str());
                strcat(buf,"|");

                ps="";
                for(i=(strlen(ID.c_str())-4);i<strlen(ID.c_str());i++){
                    ps = ps+ID[i];
                }
                ps = b.hash(ps);
                strcat(buf,ps.c_str());
                strcat(buf,"|");

                for(;;){
                    cout<<"ENTER THE DATE OF BIRTH OF THE CUSTOMER IN [DD/MM/YYYY] FORMAT:"<<endl;
                    cin>>dob;
                        DOB[0] = "";
                        DOB[1] = "";
                        DOB[2] = "";
                        j=0;
                    if(strlen(dob)==10){
                        for(i=0;i<10;i++){
                            if(dob[i]=='/'){
                                if(j==2){
                                    break;
                                }
                                j++;
                                continue;
                            }
                            DOB[j]+=dob[i];
                        }
                        date = atoi(DOB[0].c_str());
                        month = atoi(DOB[1].c_str());
                        year = atoi(DOB[2].c_str());
                    }else{
                        continue;
                    }
                    if(year<2020 && year>1900){
                        if((year%4==0)&&(year%10!=0)||(year%400==0)){
                            if(month<13){
                                if(month==2){
                                    if(date<30){
                                        break;
                                    }
                                }else if(month == 1 ||month == 3 ||month == 5 ||month == 7 ||month == 8 ||month == 10 ||month == 12){
                                    if(date<32){
                                        break;
                                    }
                                }else{
                                    if(date<31){
                                        break;
                                    }
                                }
                            }
                        }else{
                            if(month<13){
                                if(month==2){
                                    if(date<29){
                                        break;
                                    }
                                }else if(month == 1 ||month == 3 ||month == 5 ||month == 7 ||month == 8 ||month == 10 ||month == 12){
                                    if(date<32){
                                        break;
                                    }
                                }else{
                                    if(date<31){
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                }
                if(strlen(DOB[0].c_str())==1){
                    strcat(buf,"0");
                }
                strcat(buf,DOB[0].c_str());
                strcat(buf,"/");
                if(strlen(DOB[1].c_str())==1){
                    strcat(buf,"0");
                }
                strcat(buf,DOB[1].c_str());
                strcat(buf,"/");
                strcat(buf,DOB[2].c_str());
                strcat(buf,"|");

                strcat(buf,IFSC.c_str());
                strcat(buf,"|");

                file.open("erecord.txt",ios::in);
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    strcat(buf,mname);
                    strcat(buf,"|");
                    for(i=0;i<4;i++){
                        file.getline(mname,99,'|');
                    }
                    file.getline(mname,99,'|');
                    strcat(buf,mname);
                    strcat(buf,"|");
                    file.getline(mname,99,'!');
                    strcat(buf,mname);
                    strcat(buf,"\n");
                file.close();

                file.open("ahrecord.txt",ios::app);
                if(strlen(buf)<100){
                    file<<"0"<<(strlen(buf)+4)<<"|"<<buf;
                }else{
                    file<<(strlen(buf)+4)<<"|"<<buf;
                }
                file.close();

                if(noOfCus>0){
                    indexNo=0;
                    file.open("ahindex.txt",ios::in);
                    for(j=0;j<noOfCus;j++){
                        for(i=0;i<4;i++){
                            file.getline(id,99,'|');
                        }
                            file.getline(mname,99,'\n');
                    }
                    j=0;
                    stringstream leng(mname);
                    leng>>j;
                    indexNo+=j;
                    file.close();

                    file.open("ahrecord.txt",ios::in);
                    for(j=0;j<noOfCus;j++){
                        file.getline(mname,99,'|');
                        for(i=0;i<14;i++){
                            file.getline(id,99,'|');
                        }
                            file.getline(id,99,'\n');
                    }
                    j=0;
                    stringstream len(mname);
                    len>>j;
                    indexNo+=j;
                    indexNo++;
                    file.close();
                }
                    
                file.open("ahindex.txt",ios::app);
                file<<cRRN<<"|"<<name<<"|"<<accNo<<"|"<<ps<<"|"<<indexNo<<"\n";
                file.close();

                cRRN++;
                noOfCus++;
                system("clear");
                cout<<"CUSTOMER ACCOUNT SUCCESSFULLY CREATED..."<<endl;
                getch();
                return;
            }
            void viewAllCustomers(){   
                cout<<"TOTAL NO. OF CUSTOMERS: "<<noOfCus<<endl;
                cout<<"\nRRN"<<" |"<<"CIF No."<<"    |"<<"CUSTOMER NAME"<<endl;
                file.open("ahrecord.txt",ios::in);
                for (j=0;j<noOfCus;j++){
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    cout<<mname<<"   |";
                    file.getline(id,99,'|');
                    file.getline(mname,99,'|');
                    file.getline(mname,99,'|');
                    cout<<mname<<"|";
                    cout<<id<<endl;
                    file.getline(buf,999,'\n');
                }
                file.close();
            }
            void searchCustomerOrUpdateBalance(){
                cout<<"ENTER THE NAME OF THE CUSTOMER :";
                getline(cin,name);
                found=0;
                file.open("ahindex.txt",ios::in);
                    for(j=0;j<noOfCus;j++){
                        file.getline(mname,99,'|');
                        file.getline(mname,99,'|');
                        if(strcmp(name.c_str(),mname)==0){
                            found++;
                        }
                        file.getline(mname,99,'\n');
                    }
                file.close();

                if(found==0){
                    cout<<"CUSTOMER WITH NAME '"<<name<<"' NOT FOUND"<<endl;
                    return;
                } else if (found==1){
                    cout<<"CUSTOMER DETAILS : "<<endl;
                    file.open("ahrecord.txt",ios::in);
                    while(!file.eof()){                   
                        file.getline(mname,99,'|');  
                        file.getline(buf,99,'|');      
                        file.getline(mname,99,'|');
                        if(strcmp(mname,name.c_str())==0){
                            cout<<"CUSTOMER NAME : "<<mname<<endl; 
                            file.getline(buf,99,'|');
                            cout<<"ACCOUNT TYPE : "<<buf<<endl;
                            file.getline(buf,99,'|');
                            cout<<"CIF NUMBER : "<<buf<<endl;                       
                            file.getline(buf,99,'|');
                            cout<<"ACCOUNT NUMBER : "<<buf<<endl;                        
                            file.getline(buf,999,'|');
                            cout<<"EMPLOYEE ADDRESS : "<<buf<<endl;                      
                            file.getline(buf,99,'|');
                            cout<<"EMPLOYEE EMAIL ADDRESS: "<<buf<<endl;                    
                            file.getline(buf,99,'|');
                            cout<<"EMPLOYEE PHONE NO. : "<<buf<<endl;                        
                            file.getline(mname,99,'|');
                            file.getline(buf,99,'|');
                            file.getline(buf,99,'|');
                            cout<<"DATE OF BIRTH : "<<buf<<endl;
                            file.getline(buf,99,'|');
                            cout<<"IFSC CODE OF THE BANK : "<<buf<<endl;
                            file.getline(buf,99,'|');
                            cout<<"ADDED BY EMPLOYEE-ID : "<<buf<<endl;                        
                            file.getline(buf,99,'|');
                            cout<<"LOCATION OF THE BANK : "<<buf<<endl;                        
                            file.getline(buf,99,'\n');
                            cout<<"BRANCH CODE : "<<buf<<endl;
                            cout<<"\nACCOUNT BALANCE : "<<mname<<endl;
                            file.close();
                            return;
                        }
                        file.getline(buf,999,'\n');
                    }
                    file.close();
                    return;
                } else{
                    cout<<"SELECT THE ACCOUNT NO"<<endl;
                    file.open("ahindex.txt",ios::in);
                    i=0;
                    for(j=0;j<noOfCus;j++){
                        file.getline(mname,99,'|');
                        file.getline(mname,99,'|');
                        if(strcmp(name.c_str(),mname)==0){
                            file.getline(mname,99,'|');
                            i++;
                            cout<<i<<": "<<mname<<endl;
                        }
                        file.getline(mname,99,'\n');
                    }
                    file.close();
                    pwd = getch();
                    dob[0] = pwd;
                    dob[1] = ';';
                    i = atoi(dob);

                    file.open("ahindex.txt",ios::in); 
                    k=0;
                    for(j=0;j<noOfCus;j++){
                        file.getline(mname,99,'|');
                        file.getline(mname,99,'|');
                        if(strcmp(name.c_str(),mname)==0){
                            k++;
                            file.getline(mname,99,'|');
                            if(k==i){
                                strcpy(id,mname);
                                break;
                            }
                        }
                        file.getline(mname,99,'\n');
                    }
                    file.close();
                    
                    cout<<"CUSTOMER DETAILS : "<<endl;
                    file.open("ahrecord.txt",ios::in);
                    while(!file.eof()){                   
                        file.getline(mname,99,'|');  
                        file.getline(mname,99,'|');      
                        file.getline(buf,99,'|');
                        file.getline(buffer,99,'|');
                        file.getline(pwd1,99,'|');
                        file.getline(mname,99,'|');
                        if(strcmp(mname,id)==0){
                            cout<<"CUSTOMER NAME : "<<buf<<endl;
                            cout<<"ACCOUNT TYPE : "<<buffer<<endl;
                            cout<<"CIF NUMBER : "<<pwd1<<endl; 
                            cout<<"ACCOUNT NUMBER : "<<mname<<endl;                        
                            file.getline(buf,999,'|');
                            cout<<"EMPLOYEE ADDRESS : "<<buf<<endl;                      
                            file.getline(buf,99,'|');
                            cout<<"EMPLOYEE EMAIL ADDRESS: "<<buf<<endl;                    
                            file.getline(buf,99,'|');
                            cout<<"EMPLOYEE PHONE NO. : "<<buf<<endl;                       
                            file.getline(mname,99,'|');
                            file.getline(buf,99,'|');
                            file.getline(buf,99,'|');
                            cout<<"DATE OF BIRTH : "<<buf<<endl;
                            file.getline(buf,99,'|');
                            cout<<"IFSC CODE OF THE BANK : "<<buf<<endl;
                            file.getline(buf,99,'|');
                            cout<<"ADDED BY EMPLOYEE-ID : "<<buf<<endl;                        
                            file.getline(buf,99,'|');
                            cout<<"LOCATION OF THE BANK : "<<buf<<endl;                        
                            file.getline(buf,99,'\n');
                            cout<<"BRANCH CODE : "<<buf<<endl;
                            cout<<"\nACCOUNT BALANCE : "<<mname<<endl;
                            file.close();
                            return;
                        }
                        file.getline(buf,999,'\n');
                    }
                    file.close();                    
                }
            }
    };
    employees e;
    e.employeeDashBoard();
    return;
}


//Exexcution starts from here.
int main(){
    bank b;
    fstream file;
    char errn[1000],lengthIndicator[4],ps[100];
    int i, length;
    string s;

    
    system("clear");
    cout<<"WELCOME TO \'BANK OF MIT\'"<<endl;

    if(b.ifFileExist("minfo.txt")){
        //...file exist
        mData = true;
        //...set the employee RRN and no. of employees
        noOfEmp=-1;
        file.open("erecord.txt",ios::in);
        while(!file.eof()){
            file.getline(errn,99,'|');
            s="";
            for(i=0;i<strlen(errn);i++){
                s+=errn[i];
            }
            stringstream rrn(s);
            rrn>>eRRN;
            file.getline(errn,300,'\n');
            noOfEmp++;
        }
        if(noOfEmp!=0){
            eRRN++;
        }
        file.close();
        
        file.open("ahrecord.txt",ios::in);
        while(!file.eof()){
            file.getline(lengthIndicator,99,'|');
            file.getline(errn,99,'|');
            s="";
            for(i=0;i<strlen(errn);i++){
                s+=errn[i];
            }
            stringstream crrn(s);
            crrn>>cRRN;
            file.getline(errn,999,'\n');
            noOfCus++;
        }
        if(noOfCus!=0){
            cRRN++;
            noOfCus--;
        }
        if(noOfCus==0){
            cRRN=0;
        }
        cout<<cRRN<<"|"<<noOfCus;
        file.close();

    }
    else{
        //...file does not exist
        file.open("minfo.txt",ios::out);
        file.close();
        file.open("eindex.txt",ios::out);
        file.close();
        file.open("erecord.txt",ios::out);
        file.close();
        file.open("ahindex.txt",ios::out);
        file.close();
        file.open("ahrecord.txt",ios::out);
        file.close();
        cout<<"ENTER THE DETAILS FOR THE MANAGER ACCOUNT"<<endl;
        b.manager();
    }
    char choice;
    for(;;){

        cout<<"\n------BANK OF MIT------"<<endl;
        cout<<"1: BANK MANAGER LOG-IN"<<endl;
        cout<<"2: EMPLOYEE LOG-IN"<<endl;
        cout<<"3: ACCOUNT HOLDER LOG-IN"<<endl;
        cout<<"4: EXIT"<<endl;       
        choice = getch();
        
        switch (choice){
            case '1':
                b.manager();
                break;
            
            case '2':
                b.employee();
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
