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
	long double vnow=0, vdiff=0, vsum=0;
	ifstream inf;
	inf.open("wcccpacket.txt");
	ofstream outf1;
	outf1.open("CCinterval.txt");
	while(getline(inf, s))  //  將文檔一行一行讀入字串s
	{	
		if(s[0]=='o')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中
			
				
			stringstream ss(v[1].c_str());

			ss>>vnow; // 數字字串轉成double
			vdiff = vnow - vsum;
			vsum = vsum + vdiff;
			if(vdiff>0.02)
			{	
				cout<<vdiff<<'\n'; 
			}
			outf1<<fixed<<setprecision(9)<<vdiff<<'\n';
			
			//cout<<fixed<<setprecision(9)<<vnow<<'\t';
			//outf<<fixed<<setprecision(9)<<vnow<<'\t';
			
		}

		s.clear();
		v.clear();
	}
	inf.close();
	outf1.close();
	return 0;
}
