#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>

using namespace std;

void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);           // 回傳顯示字串"c"的索引值
    pos1 = 0;
    while(string::npos != pos2)  // 當讀入的字串中有包含字串"c"的索引值,則執行下列迴圈
     {
        v.push_back(s.substr(pos1, pos2-pos1));  // 將讀入的字串從[0]到"c"的索引值,引入vector中
         
        pos1 = pos2 + c.size();  // pos1設為讀入v的字串後的索引值
        pos2 = s.find(c, pos1);  // 接著搜尋下一個包含字串"c"的索引值
    }
    if(pos1 != s.length())   // 當完整讀完的字串後的索引值!=輸入字串長度
        v.push_back(s.substr(pos1));   // 則將剩下的輸入字串接在vector後面
}

int main ()
{
	string s;
	vector<string> v;
	int max = 900;
	int couter_1 = 0, couter_2 = 0, couter_3 = 0;
	int temp = 1;
	
	ifstream inf1;
	inf1.open("../recording/WCCC_exe.txt");
	ifstream inf2;
	inf2.open("../recording/WCA_exe.txt");
	ifstream inf3;
	inf3.open("../recording/WCM_exe.txt");
	ofstream outf1;
	outf1.open("WC_CC_PBR.txt");
	ofstream outf2;
	outf2.open("WC_A_PBR.txt");
	ofstream outf3;
	outf3.open("WC_M_PBR.txt");
	
	
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{		
		outf1<<"kBps1024"<<endl;
		s.clear();
	}
	
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{		
		outf2<<"kBps256"<<endl;
		s.clear();
	}
	
	for(int i = 0; i < 300; i++)
	{
		outf3<<"kBps256"<<endl;
	}	
	
	for(int i = 300; i < 345; i++)
	{
		int j = 0;
		
		while(j < 50)
			{
				outf3<<"kBps8192"<<endl;
				j++;
			}
	}	
	
	for(int i = 345; i < 500; i++)
	{
		outf3<<"kBps256"<<endl;
	}
	
	for(int i = 500; i < 545; i++)
	{
		int j = 0;
		while(j < 59)
			{
				outf3<<"kBps8192"<<endl;
				j++;
			}	
	}
	
	for(int i = 545; i < 700; i++)
	{
		outf3<<"kBps256"<<endl;
	}
	
	for(int i = 700; i < 745; i++)
	{
		int j = 0;
		while(j < 68)
			{
				outf3<<"kBps16384"<<endl;
				j++;
			}	
	}
	
	for(int i = 745; i < 900; i++)
	{
		outf3<<"kBps256"<<endl;
	}
	
	inf1.close();
	inf2.close();
	inf3.close();
	outf1.close();
	outf2.close();
	outf3.close();
	
	return 0;
}
