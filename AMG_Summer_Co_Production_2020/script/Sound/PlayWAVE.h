/**
 * @file	AMG_Summer_Co_Production_2020\script\PlayWAVE.h.
 *
 * @brief	XAudio2��p���������Đ�
 * @author	Takuya Fujisawa
 */

#pragma once
#define XAUDIO2_HELPER_FUNCTIONS
#define _USE_MATH_DEFINES
#include<math.h>
#include<cstdlib>
#include<ctime>
#include<thread>
#include<xaudio2.h>
#include"MyFadeXAPO.h"
#include"MyLowPassFilterXAPO.h"
#include"MyHighPassFilter.h"
#include"MyPeakMeterXAPO.h"
#include"../Server/ResourceServer.h"

namespace sound
{

	namespace
	{
		constexpr float PAN_LEFT = -90.0f;
		constexpr float PAN_RIGHT = 90.0f;
		constexpr float PAN_CENTER = 0.0f;
	}

	/**
	 * @class	PlayWAVE
	 *
	 * @brief	wav�t�@�C���̍Đ�
	 *
	 */
	class PlayWAVE
	{
	public:
		PlayWAVE();
		~PlayWAVE();

		/**
		 * @fn	static void PlayWAVE::Init();
		 *
		 * @brief	XAudio2�̏���������
		 *
		 */
		static void Init();

		/**
		 * @fn	static void PlayWAVE::Release();
		 *
		 * @brief	XAudio2�̉������
		 *
		 */
		static void Release();

		/**
		 * @fn	void PlayWAVE::Load(const char* _fileName);
		 *
		 * @brief	wav�t�@�C����ǂݍ��݁A�\�[�X�{�C�X�쐬
		 *
		 * @param 	_fileName	�����t�@�C����
		 */
		void Load(const char* _fileName);

		/**
		 * @fn	void PlayWAVE::SetLoopCount(const int _count);
		 *
		 * @brief	���[�v�񐔂�ݒ�
		 *
		 * @param 	_count	_count�͐܂�Ԃ���
		 * 					ex) _count = 1 �@���@2��Đ�
		 * 					�������[�v�� XAUDIO2_LOOP_INFINITE��ݒ�
		 */
		void SetLoopCount(const int _count);

		/**
		 * @fn	void PlayWAVE::SetVolume(const float _volume);
		 *
		 * @brief	SourceVoice�̉��ʂ�ݒ�
		 *
		 * @param 	_volume	MAX : 1.0f
		 * 									MIN  : 0.0f
		 */
		void SetVolume(const float _volume);

		/**
		 * @fn	void PlayWAVE::SetVolume_dB(const float _db);
		 *
		 * @brief	�f�V�x���l�Ń{�����[����ݒ�
		 *
		 * @param 	_db	�f�V�x��		MAX : 0[dB]
		 * 												MIN  : -40[dB]
		 * 												1/2	: -6[dB]
		 */
		void SetVolume_dB(const float _db);

		/**
		 * @fn	void PlayWAVE::Pan(const float _targetPan);
		 *
		 * @brief	�o�̓`�����l���̉��ʃo�����X�̐ݒ� (-90.0f <= _targetPan <= 90.0f)
		 * 			L�̂݁�PAN_LEFT�@�Z���^�[��PAN_CENTER�@R�̂݁�PAN_RIGHT
		 *
		 * @param 	_targetPan	���ʃo�����X
		 * 										L�̂݁�PAN_LEFT
		 * 										�Z���^�[��PAN_CENTER
		 * 										R�̂݁�PAN_RIGHT
		 *
		 */
		void Pan(const float _targetPan);

		/**
		 * @fn	void PlayWAVE::Pan(const int _pos_x);
		 *
		 * @brief	��ʂ̕��ɑ΂��鍶�E�̉��ʃo�����X�̐ݒ�
		 *
		 * @param 	_pos_x	x���W
		 */
		void Pan(const int _pos_x);

		/**
		 * @fn	void PlayWAVE::Pitch(const float _pitch);
		 *
		 * @brief	�Đ����x��ݒ�
		 *
		 * @param 	_pitch	�Đ����x
		 * 								MAX	:	16.0f
		 * 								MIN	:	0.0f
		 */
		void Pitch(const float _pitch);

		/**
		 * @fn	void PlayWAVE::RandomPitch(const float _pitch_diff);
		 *
		 * @brief	SE�p�����_���s�b�`�ݒ�
		 *
		 * @param 	_pitch_diff	���{�Đ�����}_pitch_diff �͈̗̔͂����ōĐ������.
		 */
		void RandomPitch(const float _pitch_diff);

		/**
		 * @fn	void PlayWAVE::Pause();
		 *
		 * @brief	�ꎞ��~
		 *
		 */
		void Pause();

		/**
		 * @fn	void PlayWAVE::Start();
		 *
		 * @brief	�ꎞ��~��̍Đ�
		 * @detail	�ꎞ��~����Fade�ɂ���ĉ��ʂ�0�ɂȂ��Ă��邽�߁AFadein�Ŗ߂�
		 *
		 */
		void ReStart();

		/**
		 * @fn	void PlayWAVE::Fade(const float _targetVolume, const float _targetTime);
		 *
		 * @brief	�t�F�[�h����
		 *
		 * @param 	_targetVolume	�t�F�[�h�C��		:	1.0f
		 * 											�t�F�[�h�A�E�g	:	0.0f
		 * @param 	_targetTime  	�t�F�[�h����
		 */
		void Fade(const float _targetVolume, const float _targetTime);

		/**
		 * @fn	void PlayWAVE::FadeWithEQ(const float _targetVolume, const float _targetTime, const float _freqency, const int _typeEQ);
		 *
		 * @brief	EQ�������Ȃ���t�F�[�h�������s��
		 *
		 * @param 	_targetVolume	�t�F�[�h�C��		:	1.0f
		 * 											�t�F�[�h�A�E�g	:	0.0f
		 * @param 	_targetTime  	�t�F�[�h����
		 * @param 	_freqency			�Ւf���g��
		 * @param 	_typeEQ		 	LPF	:	0
		 * 											HPF	:	1
		 */
		void FadeWithEQ(const float _targetVolume, const float _targetTime, const float _freqency, const int _typeEQ);

		/**
		 * @fn	void PlayWAVE::LowPassFilter(const float _freqency);
		 *
		 * @brief	���[�p�X�t�B���^�[.
		 *
		 * @param 	_freqency	�Ւf���g��
		 */
		void LowPassFilter(const float _freqency);

		/**
		 * @fn	void PlayWAVE::HighPassFilter(const float _freqency);
		 *
		 * @brief	�n�C�p�X�t�B���^�[
		 *
		 * @param 	_freqency	�Ւf���g��
		 */
		void HighPassFilter(const float _freqency);

		/**
		 * @fn	void PlayWAVE::Play();
		 *
		 * @brief	WAVE�t�@�C�����͂��߂���Đ�
		 *
		 */
		void Play();

		/**
		 * @fn	void PlayWAVE::PlayWithLoop(float _loopbegin, float looplength);
		 *
		 * @brief	���[�v�đI
		 *
		 * @param 	_loopbegin	���[�v�J�n�n�_[s]
		 * @param 	looplength		���[�v�p������[s]
		 */
		void PlayWithLoop(float _loopbegin, float looplength);

		/**
		 * @fn	void PlayWAVE::PlayBackGround(PlayWAVE& _pw);
		 *
		 * @brief	�o�b�N�O���E���h�Đ�
		 *
		 * @param [in,out]	PlayWAVE�̎Q��
		 */
		void PlayBackGround(PlayWAVE& _pw);

		/**
		 * @fn	void PlayWAVE::PlayBackGroundWithLoop(PlayWAVE& _pw, float _loopbegin, float looplength);
		 *
		 * @brief	�o�b�N�O���E���h�Ń��[�v�Đ�
		 *
		 * @param [in,out]	PlayWAVE�̎Q��
		 * 	@param 	_loopbegin	���[�v�J�n�n�_[s]
		 * @param 	looplength		���[�v�p������[s]
		 */
		void PlayBackGroundWithLoop(PlayWAVE& _pw, float _loopbegin, float looplength);

		/**
		 * @fn	void PlayWAVE::Destroy();
		 *
		 * @brief	�\�[�X�{�C�X�̔j��
		 *
		 */
		void Destroy();

		/**
		 * @fn	bool PlayWAVE::CheckIsRunning();
		 *
		 * @brief	�Đ������m�F
		 *
		 * @returns	�Đ����̉�
		 */
		bool CheckIsRunning();

	private:
		static IXAudio2* m_pXAudio2;	//!< XAudio2�̍쐬
		static IXAudio2MasteringVoice* m_pMasteringVoice;   //!< MasteringVoice�̍쐬
		static HRESULT hr;
		WAVEReader m_WaveReader;	//!< WAVE�t�@�C���ǂݍ��݃N���X
		IXAudio2SourceVoice* m_pSourceVoice = nullptr;  //!< SourceVoice�̍쐬
		int m_LoopCount = 0;	//!< ���[�v��
	};
}