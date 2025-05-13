#include <bits/stdc++.h>
using namespace std;
class Solution {
    public:
        string res;
        string reverseParentheses(string s) {
            rec(s,0,s.size()-1,1);
            return res;
        }
        void rec(string& s,int from,int to,int direction)
        {
            for(int i=from;i!=to;i+=direction)
            {
                if(s[i]=='('||s[i]==')')
                {
                    int f = i;
                    //find pair
                    int n=1;    
                    while(n>0)
                    {
                        i+=direction;
                        if(s[i]=='(')
                            n+=direction;
                        else if(s[i]==')')
                            n-=direction;
                    }
                    rec(s,i-direction,f,-direction);
                }else
                {
                    res.push_back(s[i]);
                    cout<<s[i]<<endl;

                
                }
            }
     
        }
    };
int main()
{
    cout<<Solution().reverseParentheses(string(("u(love)i")))<<endl;
}