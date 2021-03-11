/**
 * @file	AMG_Summer_Co_Production_2020\script\MyFadeXAPO.cpp.
 *
 * @brief	�T���v���P�ʂ̃t�F�[�h
 * @remark �Q�l���� https://tsuchidasama.booth.pm/items/1417202
 */

#include"MyFadeXAPO.h"

namespace sound
{
	XAPO_REGISTRATION_PROPERTIES MyFadeXAPO::xapoRegProp_ =
	{
		__uuidof(MyFadeXAPO),//GUID��₢���킹�A���
		L"MyFadeXAPO",
		L"(c)Yohinori Tsuchida All Right reserved.",
		1,0,//���W���[�o�[�W�����ԍ��A�}�C�i�[�o�[�W�����ԍ�
		XAPOBASE_DEFAULT_FLAG,
		1,1,1,1
	};

	MyFadeXAPO::MyFadeXAPO() :CXAPOParametersBase(&xapoRegProp_,
		(BYTE*)FadeParams, sizeof(MyFadeParam), FALSE)
	{
	}

	HRESULT MyFadeXAPO::LockForProcess(
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

	void MyFadeXAPO::SetParameters(
		const void* pParameters,
		UINT32 ParameterByteSize)
	{
		MyFadeParam* param = (MyFadeParam*)pParameters;

		//�w�莞�Ԃ�0�Ȃ瑦���s
		if (param->TargetTime == 0)
		{
			NowVolume = param->TargetVolume;
			SlopeVolume = 0.0f;
		}
		else
		{
			SlopeVolume = param->TargetVolume - NowVolume;
			SlopeVolume /= inputFmt_.nSamplesPerSec * inputFmt_.nChannels * param->TargetTime;//���Ԃ��T���v�����ɕϊ�
		}

		CXAPOParametersBase::SetParameters(pParameters, ParameterByteSize);
	}

	void MyFadeXAPO::GetParameters(
		void* pParameters,
		UINT32 ParameterByteSize)
	{
		*(bool*)pParameters = FadeFlag;
	}

	void MyFadeXAPO::Process(
		UINT32 InputProcessParameterCount,
		const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters,
		UINT32 OutputProcessParameterCount,
		XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters,
		BOOL IsEnabled)
	{
		float* in = (float*)pInputProcessParameters[0].pBuffer;		//���̓f�[�^�̐擪�A�h���X
		float* out = (float*)pOutputProcessParameters[0].pBuffer;	//�o�̓f�[�^�̐擪�A�h���X

		MyFadeParam* param = (MyFadeParam*)BeginProcess();
		for (unsigned int i = 0; i < pInputProcessParameters[0].ValidFrameCount * inputFmt_.nChannels; i++)
		{
			float volume = *in;

			//���̔g�`�Ƀ{�����[������Z������Avolume�ɂ�Slope������
			volume *= NowVolume;
			NowVolume += SlopeVolume;
			FadeFlag = false;
			//�ڕW�܂œ��B������I���i�����I�_�̌덷�̂��ߐ��m�ɂ��j

			//�t�F�[�h�A�E�g
			if (SlopeVolume < 0.0f)
			{
				//�t�F�[�h�A�E�g�̃{�����[���ɓ��B
				if (NowVolume <= param->TargetVolume)
				{
					NowVolume = param->TargetVolume;
					SlopeVolume = 0.0f;
					FadeFlag = true;
				}
			}
			//�t�F�[�h�C��
			else if (SlopeVolume > 0.0f)
			{
				//�t�F�[�h�C���̃{�����[���ɓ��B
				if (NowVolume >= param->TargetVolume)
				{
					NowVolume = param->TargetVolume;
					SlopeVolume = 0.0f;
					FadeFlag = true;
				}
			}
			//�o�̓f�[�^����������
			*out = volume;
			in++;
			out++;

		}
		EndProcess();
	}
}