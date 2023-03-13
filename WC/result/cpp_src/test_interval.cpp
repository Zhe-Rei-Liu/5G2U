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
	long double CC_1[5000], CC_2[5000], A_1[2500], A_2[2500], M_1[1000], M_2[1000];
	long double temp, CCpre, Apre, CCnow, Anow;
	int CC_count = 0, A_count = 0, M_count1 = 0;
	ifstream inf1;
	inf1.open("beforeWGCL_WCCC_5G.txt");
	ofstream outf1;
	outf1.open("CC_trans_interval.txt");
	
	CCpre = 0;
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opn" || v[10] == "opcua")
		{
			CCnow = stold(v[1]);
			temp = CCnow - CCpre;
			outf1 << '[' << CC_count << ']' << ' ' <<  temp <<endl;
			CCpre = CCnow;
			CC_count++;
		}	
		s.clear();
		v.clear();
	}
	
	
	inf1.close();
	outf1.close();

	ifstream inf2;
	inf2.open("beforeWGCL_WCA_5G.txt");
	ofstream outf2;
	outf2.open("A_trans_interval.txt");
	
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " "); 
		if(v[10] == "opn" || v[10] == "opcua")
		{
			Anow = stold(v[1]);
			temp = Anow - Apre;
			outf2 << '[' << A_count << ']' << ' ' <<  temp <<endl;
			Apre = Anow;
			A_count++;
		}	
		s.clear();
		v.clear();
	}
	inf2.close();
	outf2.close();
	
	return 0;
}
