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
	double exlatency, e2elatency;
	double LR5 = 0.015*10.0/13.0, LR2 = 0.0225*7.0/17.0;
	ifstream inf1;
	inf1.open("../recording/FMCC_exe.txt");
	ifstream inf2;
	inf2.open("../recording/FMA_exe.txt");
	ofstream outf1;
	outf1.open("FM_CC_priority.txt");
	ofstream outf2;
	outf2.open("FM_A_priority.txt");
	ofstream outf3;
	outf3.open("FM_CC_PBR.txt");
	ofstream outf4;
	outf4.open("FM_A_PBR.txt");
	
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{		
		
		exlatency = atof(s.c_str()); // 數字字串轉成 double
		e2elatency = LR5 - exlatency; 
		if(e2elatency<=0.0015)
		{
			outf1<<"priority = 1"<<endl;
		}
		else if(e2elatency>0.0015 && e2elatency<=0.002)
		{
			outf1<<"priority = 2"<<endl;
		}
		else if(e2elatency>0.002 && e2elatency<=0.003)
		{
			outf1<<"priority = 3"<<endl;
		}
		else if(e2elatency>0.003 && e2elatency<=0.004)
		{
			outf1<<"priority = 4"<<endl;
		}	
		else if(e2elatency>0.004 && e2elatency<=0.006)
		{
			outf1<<"priority = 5"<<endl;
		}
		else if(e2elatency>0.006 && e2elatency<=0.008)
		{
			outf1<<"priority = 6"<<endl;
		}
		else if(e2elatency>0.008 && e2elatency<=0.012)
		{
			outf1<<"priority = 7"<<endl;
		}
		else if(e2elatency>0.012 && e2elatency<=0.016)
		{
			outf1<<"priority = 8"<<endl;
		}
		else if(e2elatency>0.016 && e2elatency<=0.024)
		{
			outf1<<"priority = 9"<<endl;
		}
		else if(e2elatency>0.024 && e2elatency<=0.032)
		{
			outf1<<"priority = 10"<<endl;
		}
		else if(e2elatency>0.032 && e2elatency<=0.046)
		{
			outf1<<"priority = 11"<<endl;
		}
		else if(e2elatency>0.046 && e2elatency<=0.064)
		{
			outf1<<"priority = 12"<<endl;
		}
		else if(e2elatency>0.064 && e2elatency<=0.092)
		{
			outf1<<"priority = 13"<<endl;
		}
		else if(e2elatency>0.092 && e2elatency<=0.128)
		{
			outf1<<"priority = 14"<<endl;
		}
		else if(e2elatency>0.128 && e2elatency<=0.182)
		{
			outf1<<"priority = 15"<<endl;
		}
		else if(e2elatency>0.182)
		{
			outf1<<"priority = 16"<<endl;
		}
		else
		{
			outf1<<"Error"<<endl;
		}
		
		outf3 <<"kBps4096"<<endl;
		
		s.clear();
	}
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{		
		
		exlatency = atof(s.c_str()); // 數字字串轉成 double
		e2elatency = LR2 - exlatency; 
		if(e2elatency<=0.0015)
		{
			outf2<<"priority = 1"<<endl;
		}
		else if(e2elatency>0.0015 && e2elatency<=0.002)
		{
			outf2<<"priority = 2"<<endl;
		}
		else if(e2elatency>0.002 && e2elatency<=0.003)
		{
			outf2<<"priority = 3"<<endl;
		}
		else if(e2elatency>0.003 && e2elatency<=0.004)
		{
			outf2<<"priority = 4"<<endl;
		}	
		else if(e2elatency>0.004 && e2elatency<=0.006)
		{
			outf2<<"priority = 5"<<endl;
		}
		else if(e2elatency>0.006 && e2elatency<=0.008)
		{
			outf2<<"priority = 6"<<endl;
		}
		else if(e2elatency>0.008 && e2elatency<=0.012)
		{
			outf2<<"priority = 7"<<endl;
		}
		else if(e2elatency>0.012 && e2elatency<=0.016)
		{
			outf2<<"priority = 8"<<endl;
		}
		else if(e2elatency>0.016 && e2elatency<=0.024)
		{
			outf2<<"priority = 9"<<endl;
		}
		else if(e2elatency>0.024 && e2elatency<=0.032)
		{
			outf2<<"priority = 10"<<endl;
		}
		else if(e2elatency>0.032 && e2elatency<=0.046)
		{
			outf2<<"priority = 11"<<endl;
		}
		else if(e2elatency>0.046 && e2elatency<=0.064)
		{
			outf2<<"priority = 12"<<endl;
		}
		else if(e2elatency>0.064 && e2elatency<=0.092)
		{
			outf2<<"priority = 13"<<endl;
		}
		else if(e2elatency>0.092 && e2elatency<=0.128)
		{
			outf2<<"priority = 14"<<endl;
		}
		else if(e2elatency>0.128 && e2elatency<=0.182)
		{
			outf2<<"priority = 15"<<endl;
		}
		else if(e2elatency>0.182)
		{
			outf2<<"priority = 16"<<endl;
		}
		else
		{
			outf2<<"Error"<<endl;
		}
		
		outf4 <<"kBps2048"<<endl;
		
		s.clear();
	}
	
	inf1.close();
	inf2.close();
	outf1.close();
	outf2.close();
	outf3.close();
	outf4.close();
	
	return 0;
}
