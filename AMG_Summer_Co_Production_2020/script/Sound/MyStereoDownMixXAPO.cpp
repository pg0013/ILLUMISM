/**
 * @file	AMG_Summer_Co_Production_2020\script\MyStereoDownMixXAPO.cpp.
 *
 * @brief	�X�e���I�_�E���~�b�N�X
 * @remark �Q�l���� https://tsuchidasama.booth.pm/items/1417202
 */

#include"MyStereoDownMixXAPO.h"

namespace sound
{
	XAPO_REGISTRATION_PROPERTIES MyStereoDownMixXAPO::xapoRegProp_ =
	{
		__uuidof(MyStereoDownMixXAPO),//GUID��₢���킹�A���
		L"MyFadeXAPO",
		L"(c)Yohinori Tsuchida All Right reserved.",
		1,0,//���W���[�o�[�W�����ԍ��A�}�C�i�[�o�[�W�����ԍ�
		XAPOBASE_DEFAULT_FLAG,
		1,1,1,1
	};

	MyStereoDownMixXAPO::MyStereoDownMixXAPO() :CXAPOBase(&xapoRegProp_)
	{
	}

	HRESULT MyStereoDownMixXAPO::LockForProcess(
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

	void MyStereoDownMixXAPO::Process(
		UINT32 InputProcessParameterCount,
		const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters,
		UINT32 OutputProcessParameterCount,
		XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters,
		BOOL IsEnabled)
	{
		//6ch��2ch�ϊ��e�[�u��
		static const float L_Mix[6] = { 0.9f,0.1f,0.6f,0.4f,0.9f,0.0f };
		static const float R_Mix[6] = { 0.1f,0.9f,0.6f,0.4f,0.0f,0.9f };

		float* in = (float*)pInputProcessParameters[0].pBuffer;
		float* out = (float*)pOutputProcessParameters[0].pBuffer;

		//�o�͐揉���ʒu���Z�b�g
		float* pLeft = out;
		float* pRight = out + 1;

		//�T���v��������
		for (unsigned int i = 0; i < pInputProcessParameters[0].ValidFrameCount; i++)
		{
			*pLeft = 0.0f;
			*pRight = 0.0f;

			//LR�Ƀ`�����l�������񂵂č�������
			for (int ch = 0; ch < inputFmt_.nChannels; ch++)
			{
				//�X�e���I�����͂��ꂽ�Ƃ��p
				if (inputFmt_.nChannels != 6)
				{
					*out = *in;
					in++;
					out++;
					break;
				}

				*pLeft += *in * L_Mix[ch];
				*pRight += *in * R_Mix[ch];
				in++;
			}
			pLeft += 2;
			pRight += 2;
		}
	}
}