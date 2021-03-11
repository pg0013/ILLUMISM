/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeBase.h.
 *
 * @brief	モードの基底クラス
 */

#pragma once
#include	<string>

namespace illumism
{
	//<二重インクルード防止
	class ModeServer;
	class Game;

	/**
	 * @class	ModeBase
	 *
	 * @brief	モードの基底クラス
	 *
	 */
	class	ModeBase
	{
	public:
		ModeBase();
		virtual ~ModeBase();

		/**
		 * @fn	virtual bool ModeBase::Initialize(Game& g);
		 *
		 * @brief	ModeServerに接続時、Process()の前に一度だけ呼ばれる
		 *
		 * @param [in,out]	g	A Game to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool	Initialize(Game& g);

		/**
		 * @fn	virtual bool ModeBase::Terminate(Game& g);
		 *
		 * @brief	ModeServerから削除される際、一度だけ呼ばれる
		 *
		 * @param [in,out]	g	A Game to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool	Terminate(Game& g);

		/**
		 * @fn	virtual bool ModeBase::Process(Game& g);
		 *
		 * @brief	毎フレーム呼ばれる。処理部を記述
		 *
		 * @param [in,out]	g	A Game to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool	Process(Game& g);

		/**
		 * @fn	virtual bool ModeBase::Draw(Game& g);
		 *
		 * @brief	毎フレーム呼ばれる。描画部を記述
		 *
		 * @param [in,out]	g	A Game to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool	Draw(Game& g);


	public:
		/**
		 * @fn	int ModeBase::GetModeCount()
		 *
		 * @brief	このモードが始まってからのカウンタ
		 *
		 * @returns	The mode count.
		 */
		int	 GetModeCount() { return _cntMode; }

		/**
		 * @fn	unsigned long ModeBase::GetModeTm()
		 *
		 * @brief	このモードが始まってからの時間ms
		 *
		 * @returns	The mode time.
		 */
		unsigned long GetModeTm() { return _tmMode; }

		/**
		 * @fn	unsigned long ModeBase::GetStepTm()
		 *
		 * @brief	前フレームからの経過時間ms
		 *
		 * @returns	The step time.
		 */
		unsigned long GetStepTm() { return _tmStep; }

		/**
		 * @fn	void ModeBase::SetCallPerFrame(int frame)
		 *
		 * @brief	何フレームに1回Process()を呼ぶか(def:1)
		 *
		 * @param 	frame	The frame.
		 */
		void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }

		/**
		 * @fn	void ModeBase::SetCallOfCount(int count)
		 *
		 * @brief	1回の呼び出しに何回Process()を呼ぶか(def:1)
		 *
		 * @param 	count	Number of.
		 */
		void SetCallOfCount(int count) { _callOfCount = count; }

		int GetCallPerFrame() { return _callPerFrame; }
		int GetCallOfCount() { return _callOfCount; }


	private:
		friend	ModeServer; //!< ModeServer用

		std::string		_szName;
		int				_uid;
		int				_layer;

		/**
		 * @fn	void ModeBase::StepTime(unsigned long tmNow);
		 *
		 * @brief	時間経過させる
		 *
		 * @param 	tmNow	The time now.
		 */
		void StepTime(unsigned long tmNow);

		/**
		 * @fn	void ModeBase::StepCount();
		 *
		 * @brief	カウントを進める
		 *
		 */
		void StepCount();

		///!< モード内処理用
		int		_cntMode;   //!< 本モードに入ってからのカウンタ, 0スタート
		unsigned long	_tmMode;	//!< 本モードに入ってからの時間。ms
		unsigned long	_tmStep;	//!< 前フレームからの経過時間。ms
		unsigned long	_tmModeBase;	//!< このモードが始まった時間。ms
		unsigned long	_tmPauseBase;   //!< ポーズ中のベース時間。ms
		unsigned long	_tmPauseStep;   //!< ポーズ中の積算時間。ms 動作中、この値を _tmMode に用いる
		unsigned long	_tmOldFrame;	//!< 前フレームの時間。ms

		//!< CallPerFrame / CallOfCount用.
		int		_callPerFrame, _callPerFrame_cnt;
		int		_callOfCount;
	};
}