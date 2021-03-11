/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeBase.h.
 *
 * @brief	���[�h�̊��N���X
 */

#pragma once
#include	<string>

namespace illumism
{
	//<��d�C���N���[�h�h�~
	class ModeServer;
	class Game;

	/**
	 * @class	ModeBase
	 *
	 * @brief	���[�h�̊��N���X
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
		 * @brief	ModeServer�ɐڑ����AProcess()�̑O�Ɉ�x�����Ă΂��
		 *
		 * @param [in,out]	g	A Game to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool	Initialize(Game& g);

		/**
		 * @fn	virtual bool ModeBase::Terminate(Game& g);
		 *
		 * @brief	ModeServer����폜�����ہA��x�����Ă΂��
		 *
		 * @param [in,out]	g	A Game to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool	Terminate(Game& g);

		/**
		 * @fn	virtual bool ModeBase::Process(Game& g);
		 *
		 * @brief	���t���[���Ă΂��B���������L�q
		 *
		 * @param [in,out]	g	A Game to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		virtual bool	Process(Game& g);

		/**
		 * @fn	virtual bool ModeBase::Draw(Game& g);
		 *
		 * @brief	���t���[���Ă΂��B�`�敔���L�q
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
		 * @brief	���̃��[�h���n�܂��Ă���̃J�E���^
		 *
		 * @returns	The mode count.
		 */
		int	 GetModeCount() { return _cntMode; }

		/**
		 * @fn	unsigned long ModeBase::GetModeTm()
		 *
		 * @brief	���̃��[�h���n�܂��Ă���̎���ms
		 *
		 * @returns	The mode time.
		 */
		unsigned long GetModeTm() { return _tmMode; }

		/**
		 * @fn	unsigned long ModeBase::GetStepTm()
		 *
		 * @brief	�O�t���[������̌o�ߎ���ms
		 *
		 * @returns	The step time.
		 */
		unsigned long GetStepTm() { return _tmStep; }

		/**
		 * @fn	void ModeBase::SetCallPerFrame(int frame)
		 *
		 * @brief	���t���[����1��Process()���ĂԂ�(def:1)
		 *
		 * @param 	frame	The frame.
		 */
		void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }

		/**
		 * @fn	void ModeBase::SetCallOfCount(int count)
		 *
		 * @brief	1��̌Ăяo���ɉ���Process()���ĂԂ�(def:1)
		 *
		 * @param 	count	Number of.
		 */
		void SetCallOfCount(int count) { _callOfCount = count; }

		int GetCallPerFrame() { return _callPerFrame; }
		int GetCallOfCount() { return _callOfCount; }


	private:
		friend	ModeServer; //!< ModeServer�p

		std::string		_szName;
		int				_uid;
		int				_layer;

		/**
		 * @fn	void ModeBase::StepTime(unsigned long tmNow);
		 *
		 * @brief	���Ԍo�߂�����
		 *
		 * @param 	tmNow	The time now.
		 */
		void StepTime(unsigned long tmNow);

		/**
		 * @fn	void ModeBase::StepCount();
		 *
		 * @brief	�J�E���g��i�߂�
		 *
		 */
		void StepCount();

		///!< ���[�h�������p
		int		_cntMode;   //!< �{���[�h�ɓ����Ă���̃J�E���^, 0�X�^�[�g
		unsigned long	_tmMode;	//!< �{���[�h�ɓ����Ă���̎��ԁBms
		unsigned long	_tmStep;	//!< �O�t���[������̌o�ߎ��ԁBms
		unsigned long	_tmModeBase;	//!< ���̃��[�h���n�܂������ԁBms
		unsigned long	_tmPauseBase;   //!< �|�[�Y���̃x�[�X���ԁBms
		unsigned long	_tmPauseStep;   //!< �|�[�Y���̐ώZ���ԁBms ���쒆�A���̒l�� _tmMode �ɗp����
		unsigned long	_tmOldFrame;	//!< �O�t���[���̎��ԁBms

		//!< CallPerFrame / CallOfCount�p.
		int		_callPerFrame, _callPerFrame_cnt;
		int		_callOfCount;
	};
}