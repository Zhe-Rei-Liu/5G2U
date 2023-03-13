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
	long double vnow_1=0, vpre_1=0, vnow_2=0, vpre_2=0,  vnow_3=0, vpre_3=0, vnow_4=0, vpre_4=0, vdiff_1=0, vdiff_2=0, vdiff_3=0, vdiff_4=0;
	ifstream inf;
	inf.open("/home/j/Desktop/FM-M/bin/exetime_recording/ts_exetime_sub.txt");
	ofstream outf1;
	outf1.open("/home/j/Desktop/recording/ts_5-4_Msub.txt");
	ofstream outf2;
	outf2.open("/home/j/Desktop/recording/ts_6-5_Msub.txt");
	
	while(getline(inf, s))  //  將文檔一行一行讀入字串s
	{	
		if(s[0]=='4')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中
			
				
			stringstream ss(v[3].c_str());
			ss>>vpre_1; // 數字字串轉成double
			
		}
		
		if(s[0]=='5')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中

			stringstream ss(v[3].c_str());
			ss>>vnow_1;

			
			vdiff_1 = vnow_1 - vpre_1;
			outf1<<fixed<<setprecision(9)<<vdiff_1<<'\n';
			
		}
		
		if(s[0]=='6')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中

			stringstream ss(v[3].c_str());
			ss>>vnow_2;
		
			vdiff_2 = vnow_2 - vnow_1;
			outf2<<fixed<<setprecision(9)<<vdiff_2<<'\n';
			
		}
		
		
		
		s.clear();
		v.clear();
	}
	
	inf.close();
	outf1.close();
	outf2.close();
	
	return 0;
}
