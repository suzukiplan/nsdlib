/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#include "StdAfx.h"
#include "FileOutput.h"

//==============================================================
//		コンストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
FileOutput::FileOutput(void)
{
//#ifdef	_WIN32
	imbue( std::locale::classic() );
//#endif
}

//==============================================================
//		デストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
FileOutput::~FileOutput(void)
{
}

//--------------------------------
//ファイルを開く　エラー処理付き
//--------------------------------
void	FileOutput::fileopen(const char*	strFileName){

	//File open
	open(strFileName,ios_base::out | ios_base::binary);
	if(good()==false){
		perror(strFileName);
		nsc_exit(EXIT_FAILURE);
	};
};

//--------------------------------
//相対シーク
//--------------------------------
void	FileOutput::StreamPointerAdd(long iSize){
	seekp((long)iSize,ios::cur);
};

//--------------------------------
//絶対シーク
//--------------------------------
void	FileOutput::StreamPointerMove(long iSize){
	seekp((long)iSize,ios::beg);
};

