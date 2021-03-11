/**
 * @file	AMG_Summer_Co_Production_2020\script\MyHighPassFilter.cpp.
 *
 * @brief	�n�C�p�X�t�B���^�[
 * @detail	�Ւf���g���̏�����T���v�����O���g����1/2
 * @remark �Q�l���� https://tsuchidasama.booth.pm/items/1417202
 */

#include"MyHighPassFilter.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"DxLib.h"

namespace sound
{
	XAPO_REGISTRATION_PROPERTIES MyHighPassFilterXAPO::xapoRegProp_ =
	{
		__uuidof(MyHighPassFilterXAPO),//GUID��₢���킹�A���
		L"MyHighPassFilterXAPO",
		L"(c)Yohinori Tsuchida All Right reserved.",
		1,0,//���W���[�o�[�W�����ԍ��A�}�C�i�[�o�[�W�����ԍ�
		XAPOBASE_DEFAULT_FLAG,
		1,1,1,1
	};

	MyHighPassFilterXAPO::MyHighPassFilterXAPO() :CXAPOParametersBase(&xapoRegProp_,
		(BYTE*)Freqency, sizeof(float), FALSE)
	{
		//�G�t�F�N�g�p�����[�^�̏�����
		for (int i = 0; i < EFFECT_PARAMS; i++)
			Freqency[i] = 0.0f;
	}

	HRESULT MyHighPassFilterXAPO::LockForProcess(
		UINT32 InputLockedParameterCount,
		const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pInputLockedParameters,
		UINT32 OutputLockedParameterCount,
		const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pOutputLockedParameters)
	{
		inputFmt_ = *pInputLockedParameters[0].pFormat;
		outputFmt_ = *pOutputLockedParameters[0].pFormat;

		return CXAPOBase::LockForProcess(InputLockedParameterCount, pInputLockedParameters,
			OutputLockedParameterCount, pOutputLockedParameters);
	}

	void MyHighPassFilterXAPO::SetParameters(
		const void* pParameters,
		UINT32 ParameterByteSize)
	{
		if (ParameterByteSize == sizeof(float))//�T�C�Y��v�Ȃ�OK
			CXAPOParametersBase::SetParameters(pParameters, ParameterByteSize);
	}

	void MyHighPassFilterXAPO::Process(
		UINT32 InputProcessParameterCount,
		const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters,
		UINT32 OutputProcessParameterCount,
		XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters,
		BOOL IsEnabled)
	{
		float* in = (float*)pInputProcessParameters[0].pBuffer;
		float* out = (float*)pOutputProcessParameters[0].pBuffer;
		float* freqency = (float*)BeginProcess();

		//���[�p�X�W���̌v�Z
		float a1 = expf(-DX_PI_F * *freqency);			//���̉����c���u�����h��
		float b0 = 1.0f - a1;									//�V�������̃u�����h��

		float Volume = LastVolume;				//�O��̍ŏI�l�����o��

		for (unsigned int i = 0; i < pInputProcessParameters[0].ValidFrameCount * inputFmt_.nChannels; i++)
		{
			Volume = Volume * a1 + *in * b0;
			*out = *in - Volume;
			in++;
			out++;
		}
		LastVolume = Volume;
		EndProcess();
	}
}