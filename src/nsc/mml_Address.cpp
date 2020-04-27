/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#include "StdAfx.h"
#include "mml_Address.h"

//==============================================================
//		コンストラクタ
//--------------------------------------------------------------
//	●引数
//		unsigned	char 	_code		コード
//		const		char	_strName[]	クラスの名前
//	●返値
//				無し
//==============================================================
mml_Address::mml_Address(unsigned char _code, const _CHAR _strName[]):
	f_id(false),
	MusicEvent(_strName)
{

	iSize = 3;
	code.resize(iSize);
	code[0] = _code;
	code[1] = 0;
	code[2] = 0;
}

//==============================================================
//		コンストラクタ
//--------------------------------------------------------------
//	●引数
//		unsigned	char 	_code		コード
//		unsigned	char 	_data		引数1
//		const		char	_strName[]	クラスの名前
//	●返値
//				無し
//==============================================================
mml_Address::mml_Address(unsigned char _code, unsigned char _data, const _CHAR _strName[]):
	f_id(false),
	MusicEvent(_strName)
{
	iSize = 4;
	code.resize(iSize);
	code[0] = _code;
	code[1] = _data;
	code[2] = 0;
	code[3] = 0;
}

//==============================================================
//		デストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
mml_Address::~mml_Address(void)
{
}

//==============================================================
//		アドレスの設定
//--------------------------------------------------------------
//	●引数
//		unsigned	int		_addr	アドレス
//	●返値
//				無し
//==============================================================
void	mml_Address::set_Address(unsigned int _addr)
{
	switch(iSize){
		case(3):
			code[1] = (unsigned char)((_addr     ) & 0xFF);
			code[2] = (unsigned char)((_addr >> 8) & 0xFF);
			break;
		case(4):
			code[2] = (unsigned char)((_addr     ) & 0xFF);
			code[3] = (unsigned char)((_addr >> 8) & 0xFF);
			break;
		default:
			_CERR << _T("mml_Address::set_Address()関数でエラーが発生しました。") << endl;
			nsc_exit(EXIT_FAILURE);
			break;
	}
	

}

//==============================================================
//		アドレスの取得
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
/*
unsigned	int	mml_Address::get_Address(void)
{
	return((unsigned char)code[1] + ((unsigned char)code[2]<<8) );
}
*/

//==============================================================
//		idの設定
//--------------------------------------------------------------
//	●引数
//		unsigned	int		_id		番号
//	●返値
//				無し
//==============================================================
void	mml_Address::set_id(unsigned int _id)
{
	f_id = true;
	m_id = _id;
}

//==============================================================
//		idの取得
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//		unsigned	int		番号
//==============================================================
unsigned int	mml_Address::get_id(void)
{
	return(m_id);
}
//==============================================================
//		idの取得
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//		unsigned	int		番号
//==============================================================
bool	mml_Address::get_flag(void)
{
	return(f_id);
}

