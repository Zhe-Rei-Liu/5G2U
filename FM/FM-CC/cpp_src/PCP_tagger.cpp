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

long double CCtime[4557] = {0.0}, Atime[2107] = {0.0}, temp, addmac_time=0.000008964, rmmac_time=0.00000351;
int CCcount ,Acount;


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
	srand(time(NULL));	

	//  計算控制指令總共的執行延遲,並加入文字檔中
	ifstream inf;
	
	int PCP5 = 0, PCP4 = 0;
	
	string s;
	vector<string> v;
	int payload;
	long double x=1,y=1;
	long double max = 1.05, min = 0.95;
	
	
	CCcount = 0;
	inf.open("../recording/ts_5-4_CCserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		CCtime[CCcount] += temp;
		CCcount++;
		s.clear();
	}
	inf.close();
	
	CCcount = 0;
	inf.open("../recording/ts_7-5_CCserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		CCtime[CCcount] += temp;
		CCcount++;
		s.clear();
	}
	CCtime[CCcount] += 0;
	inf.close();
	
	CCcount = 0;
	inf.open("../recording/ts_8-7_CCserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		CCtime[CCcount] += temp;
		CCcount++;
		s.clear();
	}
	CCtime[CCcount] += 0;
	inf.close();
	
	CCcount = 0;
	inf.open("../recording/ts_9-8_CCserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		CCtime[CCcount] += temp;
		CCcount++;
		s.clear();
	}
	CCtime[CCcount] += 0;
	inf.close();
	
	
	//  將執行延遲加入封包的trace file
	ifstream inf1;
	inf1.open("fmccpacket.txt");
	ofstream outf1;
	outf1.open("FM_CC_TSN.txt");	
	
	CCcount = 0;
	
	cout << "# of PCP5 packets (Control Command): " << endl;
	while(getline(inf1, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " ");
		if(v[1]=="192.168.0.101"&&v.size()==8)			
		{		
								
			stringstream ss(v[5].c_str());
			ss>>payload; // 數字字串轉成int
			//payload = payload+8;  // 4bytes CRC + 4 bytes VLAN ID  
			if(payload==66)
			{
				outf1<<fixed<<setprecision(9)<<addmac_time*x+rmmac_time*y<<' '<<payload+8<<" PCP=5 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"ack"<<endl;  // ack僅考慮mac層的延遲
				x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
				y = (max - min) * rand() / (RAND_MAX + 1.0) + min;
				
			}
			else if(payload==74)
			{
				outf1<<fixed<<setprecision(9)<<addmac_time*x+rmmac_time*y<<' '<<payload+8<<" PCP=5 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"opn"<<endl;  // opn僅考慮mac層的延遲
				x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
				y = (max - min) * rand() / (RAND_MAX + 1.0) + min;
				//CCcount++;
			}
			else if(payload==1514)
			{
				outf1<<fixed<<setprecision(9)<<CCtime[CCcount]<<' '<<payload+8<<" PCP=5 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"reassemble"<<endl;
			}
			else
			{
				outf1<<fixed<<setprecision(9)<<addmac_time*x+rmmac_time*y<<' '<<payload+8<<" PCP=5 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"unknown"<<endl;
			}
			
			PCP5++;
			printf("%d\r",PCP5);
		}
		else if(v[1]=="192.168.0.101"&&v[8]=="opcua"&&v.size()==9)			
		{							
			stringstream ss(v[5].c_str());
			ss>>payload; // 數字字串轉成int
			//payload = payload+8;  // 4bytes CRC + 4 bytes VLAN ID  
						
			outf1<<fixed<<setprecision(9)<<CCtime[CCcount]<< ' '<<payload+8<<" PCP=5 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<v[8]<<endl;
			x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
			y = (max - min) * rand() / (RAND_MAX + 1.0) + min;			
			CCcount++;
			PCP5++;
			printf("%d\r",PCP5);
		
		}

		s.clear();
		v.clear();
	}
	inf1.close();
	outf1.close();
	
	printf("%d\n",PCP5);
	cout << "# of PCP4 packets (Warning): " << endl;
	
	Acount = 0;
	inf.open("../recording/ts_5-4_Aserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		Atime[Acount] += temp;
		Acount++;
		s.clear();
	}
	inf.close();
	
	Acount = 0;
	inf.open("../recording/ts_7-5_Aserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		Atime[Acount] += temp;
		Acount++;
		s.clear();
	}
	Atime[Acount] += 0;
	inf.close();
	
	Acount = 0;
	inf.open("../recording/ts_8-7_Aserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		Atime[Acount] += temp;
		Acount++;
		s.clear();
	}
	Atime[Acount] += 0;
	inf.close();
	
	Acount = 0;
	inf.open("../recording/ts_9-8_Aserver.txt");
	while(getline(inf, s))
	{
		temp = stold(s);
		Atime[Acount] += temp;
		Acount++;
		s.clear();
	}
	Atime[Acount] += 0;
	inf.close();
	
	//  將執行延遲加入封包的trace file
	
	ifstream inf2;
	inf2.open("fmapacket.txt");
	ofstream outf2;
	outf2.open("FM_A_TSN.txt");
	
	Acount = 0;
	
	while(getline(inf2, s))  //  將文檔一行一行讀入字串s
	{	
		SplitString(s, v, " ");
		if(v[1]=="192.168.0.101"&&v.size()==8)			
		{							
			stringstream ss(v[5].c_str());
			ss>>payload; // 數字字串轉成int
			//payload = payload+8; // 4bytes CRC + 4 bytes VLAN ID  
			if(payload==66)
			{
				outf2<<fixed<<setprecision(9)<<addmac_time*x+rmmac_time*y<<' '<<payload+8<<" PCP=4 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"ack"<<endl;
				x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
				y = (max - min) * rand() / (RAND_MAX + 1.0) + min;
			}
			else if(payload==74)
			{
				outf2<<fixed<<setprecision(9)<<addmac_time*x+rmmac_time*y<<' '<<payload+8<<" PCP=4 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"opn"<<endl;
				x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
				y = (max - min) * rand() / (RAND_MAX + 1.0) + min;
				//Acount++;
			}
			else if(payload==1514)
			{
				outf2<<fixed<<setprecision(9)<<Atime[Acount]<<' '<<payload+8<<" PCP=4 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"reassemble"<<endl;
			}
			else
			{
				outf2<<fixed<<setprecision(9)<<addmac_time*x+rmmac_time*y<<' '<<payload+8<<" PCP=4 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<"unknown"<<endl;
			}
			PCP4++;
			printf("%d\r",PCP4);
			
		}
		else if(v[1]=="192.168.0.101"&&v[8]=="opcua"&&v.size()==9)			
		{							
			stringstream ss(v[5].c_str());
			ss>>payload; // 數字字串轉成int
			//payload = payload+8;  // 4bytes CRC + 4 bytes VLAN ID  
			outf2<<fixed<<setprecision(9)<<Atime[Acount]<<' '<<payload+8<<" PCP=4 TCP_SEQ="<<v[6]<<" TCP_ACK="<<v[7]<<' '<<v[8]<<endl;
			x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
			y = (max - min) * rand() / (RAND_MAX + 1.0) + min;
			Acount++;
			PCP4++;
			printf("%d\r",PCP4);
		}
		
		s.clear();
		v.clear();
	}

	
	printf("%d\n",PCP4);
	
	inf2.close();
	outf2.close();
	
	return 0;
}
