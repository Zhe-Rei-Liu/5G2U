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

double vpre=0.0;

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
	double vnow=0.0;
	double CCsize=0.0, Asize=0.0, Msize=0.0;
	ifstream inf1;
	inf1.open("WC_CC_5G.txt");
	ifstream inf2;
	inf2.open("WC_A_5G.txt");
	ifstream inf3;
	inf3.open("WC_M_5G.txt");

	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中
		stringstream ss(v[1].c_str());
		
		ss>>vnow; // 數字字串轉成double
		
		CCsize = CCsize + vnow;
		
		s.clear();
		v.clear();
	}
	
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中
		stringstream ss(v[1].c_str());
		
		ss>>vnow; // 數字字串轉成double
		
		Asize = Asize + vnow;		

		s.clear();
		v.clear();
	}
	
	while(getline(inf3, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中
		stringstream ss(v[1].c_str());
		
		ss>>vnow; // 數字字串轉成double
		
		Msize = Msize + vnow;
		
		s.clear();
		v.clear();
	}
	
	inf1.close();
	inf2.close();
	inf3.close();
	
	printf(" Control Command Bit Rate = %lf \n",CCsize*8.0/90.0);
	printf(" Alarming Bit Rate = %lf \n",Asize*8.0/90.0);
	//printf(" S.D Uploading Bit Rate = %lf \n",Msize*8.0/90.0);
	return 0;
}
