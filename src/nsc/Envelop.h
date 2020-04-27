/*******************************************************************************

			NES Sound Driver & Library	(NSD.lib)	MML Compiler

	Copyright (c) 2012 A.Watanabe (S.W.), All rights reserved.
	 For conditions of distribution and use, see copyright notice in "nsc.cpp".

*******************************************************************************/

#pragma once
#include "MusicItem.h"

/****************************************************************/
/*																*/
/*			クラス定義											*/
/*																*/
/****************************************************************/
class Envelop :
	public MusicItem
{
//メンバー変数
private:
	unsigned	int		m_id;				//エンベロープ番号
				int		Loop_Normal;		//ループ位置（発音中）
				int		Loop_Release;		//ループ位置（リリース中）
				bool	Release;			//リリースパターンがあるかどうか
				int		ptEnvelop;			//処理ポインタ

//static	const	Command_Info	Command[];	//コマンドの情報

//メンバー関数
public:
				Envelop(MMLfile* MML, unsigned int _id, const _CHAR _strName[] = _T("Envelope"));
				~Envelop(void);
		void	SetLoop(MMLfile* MML, int LoopPoint);
		void	setHold(int length);
		int		sweep(MMLfile* MML);
		void	getAsm(MusicFile* MUS);
};
