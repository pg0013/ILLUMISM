/**
 * @file	AMG_Summer_Co_Production_2020\script\MyPeakMeterXAPO.cpp.
 *
 * @brief	�S���s�[�N���[�^
 * @remark �Q�l���� https://tsuchidasama.booth.pm/items/1417202 
 */

#include"MyPeakMeterXAPO.h"

namespace sound
{
	XAPO_REGISTRATION_PROPERTIES MyPeakMeterXAPO::xapoRegProp_ =
	{
		__uuidof(MyPeakMeterXAPO),//GUID��₢���킹�A���
		L"MyPeakMeterXAPO",
		L"(c)Yohinori Tsuchida All Right reserved.",
		1,0,//���W���[�o�[�W�����ԍ��A�}�C�i�[�o�[�W�����ԍ�
		XAPOBASE_DEFAULT_FLAG,
		1,1,1,1
	};

	MyPeakMeterXAPO::MyPeakMeterXAPO() :CXAPOParametersBase(&xapoRegProp_,
		(BYTE*)PeakLevels, sizeof(float), TRUE)
	{
		//�G�t�F�N�g�p�����[�^�̏�����
		for (int i = 0; i < EFFECT_PARAMS; i++)
			PeakLevels[i] = 0;
	}

	HRESULT MyPeakMeterXAPO::LockForProcess(
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

	void MyPeakMeterXAPO::SetParameters(
		const void* pParameters,
		UINT32 ParameterByteSize)
	{
		if (ParameterByteSize == sizeof(float))//�T�C�Y��v�Ȃ�OK
			CXAPOParametersBase::SetParameters(pParameters, ParameterByteSize);
	}

	void MyPeakMeterXAPO::Process(
		UINT32 InputProcessParameterCount,
		const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters,
		UINT32 OutputProcessParameterCount,
		XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters,
		BOOL IsEnabled)
	{
		float* in = (float*)pInputProcessParameters[0].pBuffer;
		float* out = (float*)pOutputProcessParameters[0].pBuffer;

		float* param = (float*)BeginProcess();
		for (unsigned int i = 0; i < pInputProcessParameters[0].ValidFrameCount; i++)
		{
			float volume = *in;
			//�}�C�i�X�Ȃ畄�����]
			if (volume < 0.0f)
				volume = -volume;
			/*
			�����ƂȂ��Ă���擪1bit�𔽓]������ꍇ��
			*(UINT32*)&volume &= 0x7fffffff;
			*/

			//�ߋ��ő�Ɣ�r���đ傫����΍����ւ�
			if (volume > MaxVolume)
				MaxVolume = volume;

			//�g�`�͉����������̂܂܃R�s�[����
			*out = *in;
			in++;
			out++;
		}
		//�ߋ��ő�l���p�����[�^�G���A�Ɋi�[����
		*param = MaxVolume;
		EndProcess();
	}
}