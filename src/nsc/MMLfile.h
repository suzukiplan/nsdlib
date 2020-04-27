/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#pragma once

/****************************************************************/
/*																*/
/*			定数定義											*/
/*																*/
/****************************************************************/
struct	Macro_Stack {
				string		name;
	unsigned	int			line;
};

/****************************************************************/
/*																*/
/*			クラス定義											*/
/*																*/
/****************************************************************/
class MMLfile	// :
//	public FileInput
{
//メンバー変数
private:
	vector	<	FileInput*	>		ptcFiles;			//MMLファイル
				FileInput*			nowFile;			//現在のファイル
	unsigned	int					iFiles;				//現在のファイルNo.

	map		< string,		string>	ptcMac;				//Macro文字列の保存
	map		< string,		int>	lv_Mac;				//Macroの階層

	vector	<	Macro_Stack	>		s_macro;			//ネスト中のマクロ名スタック
				Macro_Stack			nowMacro;
				int					p_macro;			//何ネスト目？

				bool				f_macro;			//マクロ処理を終えた時に立つフラグ
				bool				f_2to1;				//マルチバイト文字を変換した？
public:
	map		<unsigned int,	Patch*>	ptcPatch;			//Patch

				int					offset_Ei;			//
				int					offset_Ev;			//
				int					offset_En;			//
				int					offset_Em;			//
				int					iReleaseVolume;		//
				int					iRepeatMode;		//
				int					iTieMode;			//
				int					timebase;			//
				bool				octave_reverse;		//Octave Reverse
				bool				q_reverse;			//q, Q q_reverse
				int					rest;				// r コマンドの挙動
				int					wait;				// w コマンドの挙動
	unsigned	int					QMax;				// qMax
	unsigned	char				priority;

//メンバー関数
public:
	MMLfile(const char*	strFileName);
	~MMLfile(void);

				bool	eof(void);				//現在のファイルのEOFチェック
				bool	eom(void);				//ＭＭＬの終了チェック

				void	include();				//現ポインタにあるファイルを#includeする
	
				void	SetMacro(int i_Lv);
				void	DeleteMacro(int i_Lv);
				void	CallMacro(void);
				int		GetMacroNest(void){return(p_macro);};

				void	SetPatch(void);
				bool	ChkPatch(unsigned int _no);

				int		tellg(void);					//現在のファイルのポインタ取得
				void	StreamPointerMove(long iSize);	//現在のファイルのポインタ移動
				void	Back_one(void);					//1文字戻し
				void	Back(void);						//1文字戻し（全角・半角変換対応）

				char	read_char(void);	//1Byte読み込み
				char	cRead(void);		//1Byte読み込み（全角・半角変換対応）
				char	GetChar(void);		//1Byte読み込み（with EOF & Commend check）
				string	GetString(void);	//""付 文字列 読み込み
				int		GetNum(void);		//()付  数値  読み込み
				int		GetInt(void);		//数値読み込み
				int		GetLength(int DefaultLength);	//音長読み込み（演算付き）
				int		readLength(int DefaultLength);	//音長読み込み

				int		GetCommandID(const Command_Info _command[], unsigned int _size);	//コマンドIDを取得

	unsigned	int		GetLine(void){return(nowFile->GetLine());};
				void	SetLine(unsigned int i){nowFile->SetLine(i);};


	void		Err(const _CHAR msg[]);
	void		Warning(const _CHAR msg[]);
};
