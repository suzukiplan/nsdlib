/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#include "StdAfx.h"
#include "FileInput.h"

/****************************************************************/
/*					グローバル変数（クラスだけど・・・）		*/
/****************************************************************/
extern	OPSW*			cOptionSW;	//オプション情報へのポインタ変数

//==============================================================
//		デストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
FileInput::FileInput(void):
	readData(0),
	iLine(1)
{
}

//==============================================================
//		デストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
FileInput::~FileInput(void)
{
}

//--------------------------------
//ファイルを開く　エラー処理付き
//--------------------------------
void	FileInput::fileopen(const char*	_strFileName){

	errno = 0;	//グローバル変数 errno を０に初期化
	clear();	//フラグのクリア

	open(_strFileName,ios_base::in | ios_base::binary);
	if(good()==false){
		perror(_strFileName);
		nsc_exit(EXIT_FAILURE);
	};
	strFilename = _strFileName;
};

//--------------------------------
//ファイルを開く　エラー処理付き
//--------------------------------
void	FileInput::fileopen(const char*	_strFileName,SearchPass* _pass)
{
	bool	success	= false;

	//先ずは、そのまま
	errno = 0;	//グローバル変数 errno を０に初期化
	clear();	//フラグのクリア
	open(_strFileName,ios_base::in | ios_base::binary);
	if(cOptionSW->flag_SearchPass){
		perror(_strFileName);
	}

	if(good()==true){
		success = true;
	} else {

		//検索パス
		int		i		= 0;
		int		iSize	= _pass->count();
		string	name;
		string	workName= string(_strFileName);
		int		loc		= workName.rfind('/');

		//指定のファイルにパスが書かれていたら、消す。
		if(loc != string::npos){
			workName.erase(0, loc);		//ファイル名のみ
		}

		while(i < iSize){

#ifdef _WIN32
			//Windowsの場合は、相対パスも含めて検索する（UNIX系は不可）
			//指定の検索パスを基準とした相対パスも検索する。
			errno = 0;	//グローバル変数 errno を０に初期化
			clear();	//フラグのクリア

			name.assign(_pass->get(i));
			name.append(_strFileName);
			open(name.c_str(),ios_base::in | ios_base::binary);
			if(cOptionSW->flag_SearchPass){
				perror(name.c_str());
			}
			if(good()==true){
				success = true;
				break;
			};
#endif
			//WINDOWS, UNIX系共通
			//検索パス＋ファイル名のみで検索。
			errno = 0;	//グローバル変数 errno を０に初期化
			clear();	//フラグのクリア

			name.assign(_pass->get(i));
			name.append(workName);
			open(name.c_str(),ios_base::in | ios_base::binary);
			if(cOptionSW->flag_SearchPass){
				perror(name.c_str());
			}
			if(good()==true){
				success = true;
				break;
			};

			i++;
		}

	};

	if(success == false){
		_CERR << _T("全ての検索パスで、ファイルが見つかりませんでした。") << endl;
		if(cOptionSW->flag_SearchPass == false){
			perror(_strFileName);
		}
		nsc_exit(EXIT_FAILURE);
	}
}

//--------------------------------
//相対シーク
//--------------------------------
void	FileInput::StreamPointerAdd(long iSize){
	seekg((long)iSize,ios::cur);
};

//--------------------------------
//絶対シーク
//--------------------------------
void	FileInput::StreamPointerMove(long iSize){
		seekg((long)iSize,ios::beg);
};

void	FileInput::Back(void)
{
	StreamPointerAdd(-1);
	if(readData == 0x0A){
		iLine--;
	}

	//更新
	read((char*)&readData, sizeof(unsigned char));
	StreamPointerAdd(-1);
}
//--------------------------------
//1Byte読み込み
//--------------------------------
unsigned	char	FileInput::cRead()
{
	read((char*)&readData, sizeof(unsigned char));
	if(readData == 0x0A){
		iLine++;
	}

	return(readData);
};
//--------------------------------
//サイズ
//--------------------------------
unsigned	int	FileInput::GetSize(){

	unsigned	int	iData;
	unsigned	int	iDataT = tellg();

	seekg(0		,ios::end);
	iData = tellg();
	seekg(iDataT,ios::beg);

	return(iData);
};
