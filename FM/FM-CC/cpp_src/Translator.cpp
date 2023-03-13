#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	srand(911);
	string s;
	vector<string> v;
	int PCP5 = 0, PCP4 = 0;
	int payload;
	double sent_time;
	ifstream inf1;
	inf1.open("FM_CC_TSN.txt");
	ifstream inf2;
	inf2.open("FM_A_TSN.txt");
	ofstream outf1;
	outf1.open("FM_CC_5G.txt");
	ofstream outf2;
	outf2.open("FM_A_5G.txt");
	
	double x = (double) rand() / (RAND_MAX + 1.0);
	x = x*0.00004;  // 加入5G MAC header所需的時間(4-40 us)
	
	cout << "Start 5G/TSN Translation for PCP5 (Control Command)" <<endl;
	usleep(3000000);
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " ");
		if(v[2]=="PCP=5"&&v.size()==6)			
		{		
								
			stringstream ss(v[1].c_str());
			ss>>payload; // 數字字串轉成int
			stringstream sst(v[0].c_str());
			sst>>sent_time;
			
			if(payload<256)
			{
				if(payload==74)
				{
					outf1<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000101 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
				}
				else if(payload==82)
				{
					outf1<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000101 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
				}
				else
				{
					outf1<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000101 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
				}
				
			}
			else
			{
				outf1<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+3<<' '<<v[2]<<" (R=0 F=1 LCID=000101 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
			}
		}
		/*else if(v[2]=="PCP=5"&&v.size()==6)			
		{							
			stringstream ss(v[1].c_str());
			ss>>payload; // 數字字串轉成int
			stringstream sst(v[0].c_str());
			sst>>sent_time;
			
			if(payload<256)
			{
				outf1<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000101 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
			}
			else
			{
				outf1<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+3<<' '<<v[2]<<" (R=0 F=1 LCID=000101 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
			}
			
		}*/
		PCP5++;
		
		cout << "[" << PCP5 << "]" << "Adding 5G header time:" << x << endl;
		  
		x = (double) rand() / (RAND_MAX + 1.0);
		x = x*0.00004;  // 加入5G MAC header所需的時間(4-40 us)

		s.clear();
		v.clear();
	}
	
	cout << "Start 5G/TSN Translation for PCP4 (Warning)" <<endl;
	usleep(3000000);
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " ");
		if(v[2]=="PCP=4"&&v.size()==6)			
		{		
								
			stringstream ss(v[1].c_str());
			ss>>payload; // 數字字串轉成int
			stringstream sst(v[0].c_str());
			sst>>sent_time;
			
			if(payload<256)
			{
				if(payload==74)
				{
					outf2<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000100 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
				}
				else if(payload==82)
				{
					outf2<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000100 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
				}
				else
				{
					outf2<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000100 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
				}
				
			}
			else
			{
				outf2<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+3<<' '<<v[2]<<" (R=0 F=1 LCID=000100 L="<<payload<<") "<<v[3]<<' '<<v[4]<<' '<<v[5]<<endl;
			}
			
		}
		/*else if(v[2]=="PCP=2"&&v.size()==6)			
		{							
			stringstream ss(v[1].c_str());
			ss>>payload; // 數字字串轉成int
			stringstream sst(v[0].c_str());
			sst>>sent_time;
			
			if(payload<256)
			{
				outf2<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+2<<' '<<v[2]<<" (R=0 F=0 LCID=000010 L="<<payload<<") TCP_SEQ="<<v[3]<<" TCP_ACK="<<v[4]<<' '<<v[5]<<endl;
			}
			else
			{
				outf2<<fixed<<setprecision(9)<<sent_time+x<<' '<<payload+3<<' '<<v[2]<<" (R=0 F=1 LCID=000010 L="<<payload<<") TCP_SEQ="<<v[3]<<" TCP_ACK="<<v[4]<<' '<<v[5]<<endl;
			}
			
		}*/
		PCP4++;
		
		cout << "[" << PCP4 << "]" << "Adding 5G header time:" << x << endl;
		
		x = (double) rand() / (RAND_MAX + 1.0);
		x = x*0.00004;  // 加入5G MAC header所需的時間(4-40 us)
		
		s.clear();
		v.clear();
	}
	
	inf1.close();
	inf2.close();
	outf1.close();
	outf2.close();

	
	return 0;
}
