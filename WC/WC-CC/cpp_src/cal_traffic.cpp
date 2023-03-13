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

int payload[91] = {0};
//double exetime2_1[10000] = {0.0};
//double exetime3_2[10000] = {0.0};

double temp_time;

string input;


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
	double vtime;
	int temp;
	int pos;
	
	int couter_1 = 0, couter_2 = 0, couter_3 = 0, couter_4 = 0, couter_5 = 0;
	int max = 900;
	int mcount = 0;
	int stage1 = 0, stage2 = 0, stage3 = 0, stage4 = 0, stage5 = 0;
	
	again:printf("Type the traffic scenario (basic or demo or thesis):");
	
	cin >> input;
	
	if(input != "demo" && input != "thesis" && input != "basic")
	{
		printf("Wrong scenario you type, try again.\n");
		goto again;
	}
	
	ifstream inf;
	inf.open("wcccpacket.txt");
	// 將trace file中的封包紀錄檔進行payload加總
	while(getline(inf, s)) 
	{		
		SplitString(s, v, " ");  
		
		stringstream ss1(v[0].c_str());

		ss1>>vtime; // 數字字串轉成double
		
		stringstream ss2(v[5].c_str());
		
		ss2>>temp;
		
		for(double i = 0.0; i < vtime; i++)
		{
			if (vtime - i < 1.0)
			{
				payload[(int)i] = payload[(int)i] + temp*8;
				break;
			}
		}
		
		s.clear();
		v.clear();
	}
	inf.close();
	
	inf.open("wcapacket.txt");
	// 將trace file中的封包紀錄檔進行payload加總
	while(getline(inf, s)) 
	{		
		SplitString(s, v, " ");  
		
		stringstream ss1(v[0].c_str());

		ss1>>vtime; // 數字字串轉成double
		
		stringstream ss2(v[5].c_str());
		
		ss2>>temp;
		
		for(double i = 0.0; i < vtime; i++)
		{
			if (vtime - i < 1.0)
			{
				payload[(int)i] = payload[(int)i] + temp*8;
				break;
			}
		}
		
		s.clear();
		v.clear();
	}
	inf.close();
		
	if(input == "demo" || input == "thesis" )
	{
		inf.open("wcmpacket_demo.txt");
	}
	else if(input == "basic" )
	{
		inf.open("wcmpacket.txt");
	}	
	// 將trace file中的封包紀錄檔進行payload加總
	while(getline(inf, s)) 
	{		
		SplitString(s, v, " ");  
		
		stringstream ss1(v[0].c_str());

		ss1>>vtime; // 數字字串轉成double
		
		stringstream ss2(v[3].c_str());
		
		ss2>>temp;
		
		for(double i = 0.0; i < vtime; i++)
		{
			if (vtime - i < 1.0)
			{
				payload[(int)i] = payload[(int)i] + temp*8;
				break;
			}
		}
		
		s.clear();
		v.clear();
	}
	inf.close();

	ofstream outf;
	outf.open("ana_traffic_WC.txt");
	int i = 0;
	while(i < 91)
	{
		outf<<payload[i]<<endl;
		i++;
	}
	outf.close();
	
	return 0;
}
