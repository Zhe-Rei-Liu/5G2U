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
	ifstream inf1;
	inf1.open("../recording/FMCC_exe.txt");
	ifstream inf2;
	inf2.open("../recording/FMA_exe.txt");
	ofstream outf1;
	outf1.open("FM_CC_PBR.txt");
	ofstream outf2;
	outf2.open("FM_A_PBR.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{		
		outf1 <<"kBps1024"<<endl;
		s.clear();
	}
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{		
		outf2 <<"kBps256"<<endl;
		s.clear();
	}
	
	inf1.close();
	inf2.close();
	outf1.close();
	outf2.close();
	
	return 0;
}
