# include <iostream>
# include <vector>
# include <stack>
# include <map>
# include <string>
# include <cstdlib>
using namespace std;



bool IsDigit(char ch){
    int t = ch-'0';
    if ( t>=0 && t<10 ) return true;
    return false;
}

int main(void){
    map<char,int> dict;
    dict['*']=2;
    dict['/']=2;
    dict['+']=1;
    dict['-']=1;
    dict['(']=3;
    string ori="";
    string op="";
    stack<char> con;  //存符号
    int i=0;
    getline(cin,ori);
    if ( ori=="" ) return 0;
    for (i=0; i<ori.size(); ++i){
        char cur = ori[i];
        if ( ori[i]==32 ) continue;
        //是数字
        if ( cur=='('){
            con.push(cur);
            continue;
        }
        if ( IsDigit(cur) ){
            int j=i;
            while ( IsDigit(ori[j]) ){
                op = op + ori[j++];
            }
            i = j-1;
            op = op + ' ';
        } 
        //是符号
        else{
            if ( con.empty() ){
                con.push(ori[i]);
            } 
            else{
                if ( cur==')' ){
                    while( !con.empty() && con.top()!='(' ){
                        op = op + con.top() + ' ';
                        con.pop();
                    }
                    con.pop();
                }else{
                    if ( dict[cur]<=dict[con.top()] ){
                        while( !con.empty() && dict[cur]<=dict[con.top()] && con.top()!='('  ){
                            op = op + con.top() + ' ';
                            con.pop();
                        }
                        con.push(cur);
                    }else{
                        con.push(cur);
                    }
                }
            }
        }
    }
    while( !con.empty() ){
        op = op + con.top()+' ';
        con.pop();
    }
    cout<<op<<endl;
    //calc
    stack<int> ans;
    for ( int i=0; i<op.size(); i++ ){
        int tmp=0;
        if ( op[i]==' ' ) continue;
        if ( IsDigit(op[i]) ){
            int j=i;
            while( IsDigit(op[j]) ){
                tmp = tmp*10 + (op[j++]-'0');
            }
            i = j;
            ans.push(tmp);
        }
        else{
            int b = ans.top();
            ans.pop();
            int a = ans.top();
            ans.pop();
            switch(op[i]){
                case '+': ans.push((a+b)); break;
                case '*': ans.push((a*b)); break;
                case '/': ans.push((a/b)); break;
                case '-': ans.push((a-b)); break;
                //default : break;
            }
        }
    }
    cout<<ans.top()<<endl;

    return 0;
}