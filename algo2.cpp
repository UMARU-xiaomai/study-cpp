#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

int main() {
string s = "Golden Global View,disk * desk";
const string d = " ,*";
char *p;

p = strtok(s, d);
while(p) {
printf("%s\n", p);
p = strtok(NULL, d);
}
return 0;
}