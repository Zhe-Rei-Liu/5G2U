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
	inf.open("/home/j/Desktop/FM-A/bin/exetime_recording/ts_exetime_server.txt");
	ofstream outf1;
	outf1.open("/home/j/Desktop/recording/ts_5-4_Aserver.txt");
	ofstream outf2;
	outf2.open("/home/j/Desktop/recording/ts_6-5_Aserver.txt");
	ofstream outf3;
	outf3.open("/home/j/Desktop/recording/ts_8-7_Aserver.txt");
	ofstream outf4;
	outf4.open("/home/j/Desktop/recording/ts_9-8_Aserver.txt");
	
	while(getline(inf, s))  //  將文檔一行一行讀入字串s
	{	
		if(s[0]=='4')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中
			
				
			stringstream ss(v[3].c_str());
			ss>>vpre_1; // 數字字串轉成double
			//cout<<fixed<<setprecision(9)<<vnow<<'\t';
			//outf<<fixed<<setprecision(9)<<vnow<<'\t';
			
		}
		
		if(s[0]=='5')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中

			stringstream ss(v[3].c_str());
			ss>>vnow_1;
			//cout<<fixed<<setprecision(9)<<vnow<<'\n'<<endl;
				//outf<<fixed<<setprecision(9)<<vnow<<'\n';

			
			vdiff_1 = vnow_1 - vpre_1;
			outf1<<fixed<<setprecision(9)<<vdiff_1<<'\n';
			
		}
		
		if(s[0]=='6')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中

			stringstream ss(v[3].c_str());
			ss>>vnow_2;
			//cout<<fixed<<setprecision(9)<<vnow<<'\n'<<endl;
				//outf<<fixed<<setprecision(9)<<vnow<<'\n';			
			vdiff_2 = vnow_2 - vnow_1;
			outf2<<fixed<<setprecision(9)<<vdiff_2<<'\n';
			
		}
		
		if(s[0]=='7')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中
			
				
			stringstream ss(v[3].c_str());
			ss>>vpre_3; // 數字字串轉成double
			//cout<<fixed<<setprecision(9)<<vnow<<'\t';
			//outf<<fixed<<setprecision(9)<<vnow<<'\t';
			
		}
		
		if(s[0]=='8')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中

			stringstream ss(v[3].c_str());
			ss>>vnow_3;
			//cout<<fixed<<setprecision(9)<<vnow<<'\n'<<endl;
				//outf<<fixed<<setprecision(9)<<vnow<<'\n';

			
			vdiff_3 = vnow_3 - vpre_3;
			outf3<<fixed<<setprecision(9)<<vdiff_3<<'\n';
		}
		
		if(s[0]=='9')			
		{
			SplitString(s, v, " ");   //文檔中讀到" ",則將字串存入vector v中

			stringstream ss(v[3].c_str());
			ss>>vnow_4;
			//cout<<fixed<<setprecision(9)<<vnow<<'\n'<<endl;
				//outf<<fixed<<setprecision(9)<<vnow<<'\n';

			
			vdiff_4 = vnow_4 - vnow_3;
			outf4<<fixed<<setprecision(9)<<vdiff_4<<'\n';
			
		}
		
		s.clear();
		v.clear();
	}
	
	inf.close();
	outf1.close();
	outf2.close();
	outf3.close();
	outf4.close();
	
	return 0;
}
