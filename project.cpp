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

bool mData=false;
int eRRN=0, noOfEmp=0;

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
                            cout<<"\nSUCCESSFULLY LOGGED-IN"<<endl;
                            break;
                        }else{
                            cout<<"\nTHE ENTERED USERNAME OR PASSWORD IS INCORRECT"<<endl;
                            if(j==2){
                                cout<<"TOO MANY ATTEMPTS";
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
                cout<<"\nMANAGER's DEAILS :"<<endl;
                file.getline(mname,99,'|');
                cout<<"FULL NAME : "<<mname<<endl;
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
                cout<<"EMPLOYEE DETAILS : ";
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

                cout<<"RRN"<<" |"<<"EID"<<"      |"<<"EMPLOYEE NAME"<<endl;
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


//Exexcution starts from here.
int main(){
    bank b;
    fstream file;
    char errn[1000],ps[100];
    int i;
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

    }
    else{
        //...file does not exist
        file.open("minfo.txt",ios::out);
        file.close();
        file.open("eindex.txt",ios::out);
        file.close();
        file.open("erecord.txt",ios::out);
        file.close();
        cout<<"ENTER THE DETAILS FOR THE MANAGER ACCOUNT"<<endl;
        b.manager();
    }
    char choice;
    for(;;){

        cout<<"------BANK OF MIT------"<<endl;
        cout<<"\nSELECT THE LOG-IN TYPE:"<<endl;
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
