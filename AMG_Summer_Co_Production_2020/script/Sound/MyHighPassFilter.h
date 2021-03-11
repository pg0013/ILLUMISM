/**
 * @file	AMG_Summer_Co_Production_2020\script\MyHighPassFilter.h.
 *
 * @brief	�n�C�p�X�t�B���^�[
 * @detail	�Ւf���g���̏�����T���v�����O���g����1/2
 * @remark �Q�l���� https://tsuchidasama.booth.pm/items/1417202
 */

#include"xapobase.h"
#pragma comment(lib,"xapobase.lib")
namespace sound
{
#define EFFECT_PARAMS 3

	/**
	 * @class	MyHighPassFilterXAPO :public CXAPOParametersBase
	 *
	 * @brief	�n�C�p�X�t�B���^�[��XAPOFX
	 * @detail	�Ւf���g���̏�����T���v�����O���g����1/2
	 *
	 */
	class __declspec(uuid("{5D22ECC9-4095-4694-82A8-BB5237CB348A}"))
		MyHighPassFilterXAPO :public CXAPOParametersBase
	{
	public:
		MyHighPassFilterXAPO();
		~MyHighPassFilterXAPO() {};

		/**
		 * @fn	STDMETHOD(LockForProcess) ( UINT32 InputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pInputLockedParameters, UINT32 OutputLockedParameterCount, const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pOutputLockedParameters);
		 *
		 * @brief	�ǂ��������f�[�^�������Ă����̂��̏�񂪓n�����
		 * 	@detail	�ŏ��̈�x�����Ă΂�,�t�H�[�}�b�g���i�[����
		 *
		 * @param 	InputLockedParameterCount		��2�����̗v�f���A�ʏ�͂P
		 * @param	pInputLockedParameters			Process�ő����Ă���f�[�^�̃t�H�[�}�b�g�\����
		 * @param	OutputLockedParameterCount	��4�����̗v�f���A�ʏ��1
		 * @param	pOutputLockedParameters			�o�͂���f�[�^�̃t�H�[�}�b�g�\���́A���̃t�H�[�}�b�g�ŏo�͂��Ȃ��Ă͂Ȃ�Ȃ�
		 */
		STDMETHOD(LockForProcess)(
			UINT32 InputLockedParameterCount,
			const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pInputLockedParameters,
			UINT32 OutputLockedParameterCount,
			const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pOutputLockedParameters);

		/**
		 * @fn	STDMETHOD_(void, SetParameters) ( const void* pParameters, UINT32 ParameterByteSize);
		 *
		 * @brief	�G�t�F�N�g�p�����[�^��ݒ�
		 *
		 * @param 	pParameters				�����Ă����p�����[�^�̐擪�A�h���X
		 * @param 	ParameterByteSize	�����Ă����p�����[�^�̃f�[�^�T�C�Y
		 */
		STDMETHOD_(void, SetParameters) (
			const void* pParameters,
			UINT32 ParameterByteSize);

		/**
		 * @fn	STDMETHOD_(void, Process) ( UINT32 InputProcessParameterCount, const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters, UINT32 OutputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters, BOOL IsEnabled );
		 *
		 * @brief	�G�t�F�N�g�̐M���������s��
		 * @detail	1�b�Ԃ�100��Ă΂��
		 *
		 * @param 	InputProcessParameterCount		��2�����̗v�f��
		 * @param 	pInputProcessParameters			�����Ă�����H�O�̔g�`�f�[�^�ƁA�t�����̓��͍\����
		 * @param	OutputProcessParameterCount	��4�����̗v�f��
		 * @param	pOutputProcessParameters			�o�͂���g�`�ƕt�����̑����\����
		 * @param	IsEnabled									�L�������t���O
		 */
		STDMETHOD_(void, Process)(
			UINT32 InputProcessParameterCount,
			const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters,
			UINT32 OutputProcessParameterCount,
			XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters,
			BOOL IsEnabled
			);

	private:
		static XAPO_REGISTRATION_PROPERTIES xapoRegProp_;    //!< XAPO�̃v���p�e�B

		WAVEFORMATEX inputFmt_; //!< ���̓t�H�[�}�b�g�̋L���ꏊ
		WAVEFORMATEX outputFmt_;	//!< �o�̓t�H�[�}�b�g�̋L���ꏊ

		float LastVolume = 0.0f;	//!< �Ō�̉��Z�{�����[��

		float Freqency[EFFECT_PARAMS];  //!< �J�b�g�I�t���g��
	};
}