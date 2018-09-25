#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1
#include "HuffmanTree.h"
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include<algorithm>
struct CharInFo
{
	unsigned char _ch;//字符这里用unsigned char 中文会溢出
	long long _count;//字符出现的次数
	string _code;//Huffman编码
	bool operator < (const CharInFo&info)
	{
		return _count < info._count;
	} 
	CharInFo operator + (const CharInFo&info)
	{
		CharInFo ret;
		ret._count = _count + info._count;
		return ret;
	}
	bool operator != (const CharInFo&info)
	{
		return _count != info._count;
	}
	CharInFo(long long count = 0) 
		: _ch(0)  
		,_count(count)  
		, _code("")  
	{}  
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInFo> Node;
public:
	struct ConfigInfo
	{
		unsigned char _ch;
		long long _count;
	};

	FileCompress()
	{
		//构造函数，初始化数组
		for(int i = 0; i< 256 ; ++i)
		{
			_infos[i]._ch = i;//初始化，0~255
			//_infos[i]._count = 0;//开始的时候次数都为0
		}
	}
	bool Compress(const char*filename)
	{
		assert(filename);
		//1.统计字符出现的次数
		FILE *fout = fopen(filename,"rb");//打开文件读,以二进制读
		assert(fout);
		unsigned char ch = fgetc(fout);//文件中读取的读字符
		long long charcount = 0;
		while(ch != EOF)
		{
			if(feof(fout))
			{
				break;
			}
			_infos[ch]._count++;//这个字符对应的次数
			ch = fgetc(fout);
			charcount++;
		}

		//2.构建Huffman树
		CharInFo invalid;
		invalid._count = 0;
		HuffmanTree<CharInFo> tree(_infos,256,invalid);
		Node* root = tree.GetRoot();

		//3.生成Huffman编码
		string code;//huffmancode
		GenerateHuffmanCode(root,code);
		//完成后charinfo中的_code中存的就是Huffmancode

		//4.压缩
		string compressFile = filename;
		compressFile += ".huffman";//生成压缩文件
		FILE*fin = fopen(compressFile.c_str(),"wb");//打开压缩文件写
		assert(fin);
		fseek(fout,0,SEEK_SET);//把文件指针指向源文件头
		//向压缩文件里写入Huffman编码
		unsigned char ch1 = fgetc(fout);//读源文件内容
		//这里用unsigned 因为char是到0~255 而中文是负数，就写不进去
		char value = 0;
		int pos = 0;
		while(ch1!=EOF)
		{
			if (feof(fout))  
				break;  
			string& code = _infos[ch1]._code;//每个字符的Huffman编码  
			for (size_t i = 0; i < code.size(); i++)  
			{  
				value <<= 1;
				/*先左移一位，如果code为1就进行下面的代码，把第一位变为1，为0就不处理
				循环进行，就会把哪一位为1就把那一位置为1*/
				if (code[i] == '1')  //得到二进制的1  
				{  
					value |= 1;  
				}  
				if (++pos == 8)   //满8位写入文件  
				{  
					fputc(value,fin);//把value写进去,里面存的八个位，就是Huffmancode
					value = 0; //重置，循环写 
					pos = 0;  
				}  
			}  
			ch1 = fgetc(fout);  
		}
		//到这里文件读完了
		if(pos)//最后一个编码不足8个位
		{
			value = value<<(8-pos);//左移，把那些没用的位去掉
			fputc(value,fin);
		}

		//5.写配置信息，字符和字符出现的次数都写进去

		string ConfigFilename = filename;  
		ConfigFilename += ".config";  
		FILE* fConfig = fopen(ConfigFilename.c_str(), "wb");  
		assert(fConfig);  
		char countStr[168];  //字符出现的次数  
		/*先把所有字符出现的总次数写进配置文件，为防止超过int范围，
		charcount使用的是long long 所以要分两步写入 所以为什么存了一个0，
		因为如果超过long long的话转换高位可以计算出正确的次数*/

		//itoa(charcount >> 32, countStr, 10);
		//配置文件中的0  
		//把字符转换为10进制数，因为文件中存的都是字符串，转换高位  
		//fputs(countStr, fConfig);  //0写入  
		//fputc('\n', fConfig); 
		//itoa(charcount&0Xffffffff, countStr, 10);//转换低位 

		itoa(charcount, countStr, 10);   
		fputs(countStr, fConfig);  //把总次数写入  
		fputc('\n', fConfig); //换行 
		for (int i = 0; i < 256; i++)  
		{  
			string put;  
			if (_infos[i]!=invalid)  
			{  
				fputc(_infos[i]._ch,fConfig);
				//必须先把ch放进去，如果把ch作为string的字符最后转换为C的字符，会导致'\0'没有处理  
				put.push_back(',');  
				itoa(_infos[i]._count, countStr, 10);  
				put += countStr;  
				fputs(put.c_str(), fConfig);  
				fputc('\n', fConfig);  
			}  
		}  


		fclose(fin);
		fclose(fout);
		fclose(fConfig);
		return true;
	}
	bool UnCompress(const char* filename)
	{
		//1.读取配置文件   
		string ConfigFilename = filename;  
		int count = ConfigFilename.rfind('.');  
		ConfigFilename = ConfigFilename.substr(0, count);  
		string UnCompressname = ConfigFilename + ".unpress";   
		FILE* fUnCompress = fopen(UnCompressname.c_str(), "wb"); //创建解压缩文件  
		ConfigFilename += ".config";  
		FILE* fconfig = fopen(ConfigFilename.c_str(),"rb");
		assert(fconfig);
		assert(fUnCompress);
		FILE* fpress = fopen(filename,"rb");//打开压缩好的文件
		assert(fpress);

		long long charCount = 0;//找出字符出现的次数
		
		string line;
		_ReadLine(fconfig,line);//每次读配置文件中的一行
		charCount = atoi(line.c_str());
		line.clear();
		while(_ReadLine(fconfig,line))//文件结束会返回0
		{
			if(!line.empty())
			{
				unsigned char ch = line[0];//字符在前，读到
				string tmp = line.substr(2);//把前两个字符剪切掉
				//字符串的剪切，读出次数，在文件中都是以字符串的形式存在
				_infos[(unsigned char)ch]._count = atoi(tmp.c_str());  
				line.clear();
			}
			else//空行
			{
				line += '\n';
			}
		}
		//再次构建huffma树
		CharInFo invalid;
		invalid._count = 0;
		HuffmanTree<CharInFo> tree(_infos,256,invalid);
		Node* root = tree.GetRoot();
		Node* cur = root;
		char ch = fgetc(fpress);//读压缩文件
		int pos = 8;
		while(1)
		{
			--pos;
			if((ch>>pos)&1)//为1往右走
			{
				cur = cur->_right;
			}
			else//为0往左走
			{
				cur = cur->_left;
			}
			if(cur->_left==NULL&&cur->_right==NULL)//左右都为空，叶子，读出来
			{
				fputc(cur->_w._ch,fUnCompress);//读到解压缩的文件中
				cur = root;//再次从根节点遍历
				charCount--;//字符总数减减
			}
			if(pos == 0)//一个字节读完，重置，读下一个字节
			{
				ch = fgetc(fpress);
				pos = 8;//重置
			}
			if(charCount == 0)//当字符总数为0 则停止读
			{
				break;
			}
		}
		fclose(fconfig);
		fclose(fUnCompress);
		fclose(fpress);
		return true;
	}


protected:
	bool _ReadLine(FILE*filename,string&line)
	{
		assert(filename);
		if(feof(filename))//判断是否否读到文件末尾
		{
			return false;
		}
		unsigned char ch = fgetc(filename); //一个字符一个字符的读

		while(ch != '\n') //字符\n
		{
			line += ch;
			ch = fgetc(filename);
			if(feof(filename))
			{
				return false;
			}
		}
		return true;
	}
	void GenerateHuffmanCode(Node*cur,string code)
	{
		if(cur==NULL)
			return;
		if(cur->_left == NULL && cur->_right == NULL)
		{
			_infos[(unsigned char)cur->_w._ch]._code = code;
			return;
		}
		GenerateHuffmanCode(cur->_left,code + '0');//左边为0，右边为1
		GenerateHuffmanCode(cur->_right,code + '1');
	}
protected:
	CharInFo _infos[256];
};
void TestCompress()  
{  
	FileCompress hft;  
	int begin = GetTickCount();  
	hft.Compress("hc.txt");  
	//hft.Compress("1.jpg");  
	//hft.Compress("2.pdf");  
	//hft.Compress("4.mp3");
	//hft.Compress("5.docx");
	int end = GetTickCount();  
	cout << end-begin << endl;  
}  

void TestUnCompress()  
{  
	FileCompress hf;  
	int begin = GetTickCount();  
	hf.UnCompress("hc.txt.huffman");  
	//hf.UnCompress("1.jpg.huffman");  
	//hf.UnCompress("2.pdf.huffman");  //PDF压缩后解压出来都是乱码
	//hf.UnCompress("4.mp3.huffman");  
	//hf.UnCompress("5.docx.huffman");
	int end = GetTickCount();  
	cout << end - begin << endl;  
}  
