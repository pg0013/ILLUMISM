/**
 * @file	AMG_Summer_Co_Production_2020\script\PlayWAVE.cpp.
 *
 * @brief	XAudio2��p���������Đ�
 */

#include"PlayWAVE.h"
#include"../Game.h"
#include<DxLib.h>

namespace sound
{
	IXAudio2* PlayWAVE::m_pXAudio2 = nullptr;
	IXAudio2MasteringVoice* PlayWAVE::m_pMasteringVoice = nullptr;
	HRESULT PlayWAVE::hr;

	PlayWAVE::PlayWAVE() {}
	PlayWAVE::~PlayWAVE() { m_pSourceVoice->DestroyVoice(); }

	void PlayWAVE::Init()
	{
		//COM�̏�����
		//DXLib��COM�̏��������s����̂ŁA������ł͏��������Ȃ�
		//CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		//XAudio2�̍쐬
		UINT32 flags = 0;
		hr = XAudio2Create(&m_pXAudio2, flags);
		if (FAILED(hr))
			CoUninitialize();//�I������

		//MasteringVoice�̍쐬
		hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
		if (FAILED(hr))
		{
			m_pXAudio2->Release();
			m_pXAudio2 = nullptr;
			CoUninitialize();
		}
	}

	void PlayWAVE::Release()
	{
		m_pMasteringVoice->DestroyVoice();
		m_pXAudio2->Release();
		//DXLib��COM�̉���������s����̂ŁA������ł͏��������Ȃ�
		//CoUninitialize();
	}

	void PlayWAVE::Load(const char* _fileName)
	{
		//WAVE�t�@�C���̓ǂݍ���
		m_WaveReader = illumism::ResourceServer::LoadSound(_fileName);

		//SourceVoice�̍쐬
		WAVEFORMATEX wfx = m_WaveReader.Getwfx();
		hr = m_pXAudio2->CreateSourceVoice(&m_pSourceVoice, &wfx, XAUDIO2_VOICE_USEFILTER, 16.0f);
		if (FAILED(hr))
		{
			printfDx("can not create SourceVoice");
			free(m_WaveReader.GetpBuffer());
		}
	}

	void PlayWAVE::SetLoopCount(const int _count)
	{
		m_LoopCount = _count;
	}

	void PlayWAVE::SetVolume(const float _volume)
	{
		m_pSourceVoice->SetVolume(_volume);
	}

	void PlayWAVE::SetVolume_dB(const float _db)
	{
		float volume = XAudio2DecibelsToAmplitudeRatio(_db);
		m_pSourceVoice->SetVolume(volume);
	}

	void PlayWAVE::Pan(const float _targetPan)
	{
		int in_channel, out_channel;
		XAUDIO2_VOICE_DETAILS details;

		//���o�̓`�����l�����̎擾
		m_pSourceVoice->GetVoiceDetails(&details);
		in_channel = details.InputChannels;
		m_pMasteringVoice->GetVoiceDetails(&details);
		out_channel = details.InputChannels;

		//volume��0.0f~1.0f�͈̔͂ł��邽�߁A-90�`90����0~90�x�֐��K�����A�x���烉�W�A���֕ϊ�
		float rad = ((_targetPan + 90.0f) / 2) * (DX_PI_F / 180.0f);

		/*
			��:SetOutputMatrix�̓��o�̓`�����l���ɂ���

			�z��v�f�� = ���̓`�����l���� * �o�̓`�����l����
			���́�Stereo 2ch �o�́�Stereo�̏ꍇ
								<input>	|	�v�f�ԍ�
			<output>		L		 R		|
					L		   1.0   0.0		|	[0]	[1]
					R		   0.0   1.0		|	[2]	[3]
			�̂悤�ɂȂ�B(�s:Output,��:Input)
		*/

		//���m����
		if (in_channel == 1)
		{
			float pan_volumes[2];
			pan_volumes[0] = cosf(rad);			//Input L > Output L
			pan_volumes[1] = sinf(rad);			//Input R > Output R

			m_pSourceVoice->SetOutputMatrix(NULL, in_channel, out_channel, pan_volumes);
		}
		//�X�e���I
		if (in_channel == 2)
		{
			float pan_volumes[4];
			pan_volumes[0] = cosf(rad);			//Input L > Output L
			pan_volumes[1] = 0.0f;					//Input R > Output L(����Ȃ�)
			pan_volumes[2] = 0.0f;					//Input L > Output R(����Ȃ�)
			pan_volumes[3] = sinf(rad);			//Input R > Output R

			m_pSourceVoice->SetOutputMatrix(NULL, in_channel, out_channel, pan_volumes);
		}
	}

	void PlayWAVE::Pan(const int _PosX)
	{
		int in_channel, out_channel;
		XAUDIO2_VOICE_DETAILS details;

		//���o�̓`�����l�����̎擾
		m_pSourceVoice->GetVoiceDetails(&details);
		in_channel = details.InputChannels;
		m_pMasteringVoice->GetVoiceDetails(&details);
		out_channel = details.InputChannels;

		//volume��0.0f~1.0f�͈̔͂ł��邽�߁A-90�`90����0~90�x�֐��K�����A�x���烉�W�A���֕ϊ�
		float rad = (((float)_PosX / (float)illumism::SCREEN_WIDTH) * 90.0f) * (DX_PI_F / 180.0f);

		/*
			��:SetOutputMatrix�̓��o�̓`�����l���ɂ���

			�z��v�f�� = ���̓`�����l���� * �o�̓`�����l����
			���́�Stereo 2ch �o�́�Stereo�̏ꍇ
								<input>	|	�v�f�ԍ�
			<output>		L		 R		|
					L		   1.0   0.0	|	[0]	[1]
					R		   0.0   1.0	|	[2]	[3]
			�̂悤�ɂȂ�B(�s:Output,��:Input)
		*/

		//���m����
		if (in_channel == 1)
		{
			float pan_volumes[2];
			pan_volumes[0] = cosf(rad);			//Input L > Output L
			pan_volumes[1] = sinf(rad);			//Input R > Output R

			m_pSourceVoice->SetOutputMatrix(NULL, in_channel, out_channel, pan_volumes);
		}
		//�X�e���I
		if (in_channel == 2)
		{
			float pan_volumes[4];
			pan_volumes[0] = cosf(rad);			//Input L > Output L
			pan_volumes[1] = 0.0f;					//Input R > Output L(����Ȃ�)
			pan_volumes[2] = 0.0f;					//Input L > Output R(����Ȃ�)
			pan_volumes[3] = sinf(rad);			//Input R > Output R

			m_pSourceVoice->SetOutputMatrix(NULL, in_channel, out_channel, pan_volumes);
		}

	}

	void PlayWAVE::Pitch(const float _pitch)
	{
		m_pSourceVoice->SetFrequencyRatio(_pitch);
	}

	void PlayWAVE::RandomPitch(float _pitch_diff)
	{
		float random = static_cast<float>(((rand() % 100) - 50) * 0.01 * _pitch_diff);

		m_pSourceVoice->SetFrequencyRatio(1.0f + random);
	}

	void PlayWAVE::Pause()
	{
		Fade(0.0f, 0.0f);
		m_pSourceVoice->DisableEffect(0);
		m_pSourceVoice->Stop(XAUDIO2_PLAY_TAILS);
	}

	void PlayWAVE::ReStart()
	{
		Fade(1.0f, 0.01f);
		m_pSourceVoice->Start();
	}

	void PlayWAVE::Fade(const float _targetVolume, const float _targetTime)
	{
		//Fade�t�B���^�[�̐錾
		IUnknown* pXAPO;
		pXAPO = (IXAPO*)new MyFadeXAPO();

		//EFFECT_DESCRIPTOR�\���̂̐錾
		XAUDIO2_EFFECT_DESCRIPTOR descriptor;
		descriptor.InitialState = TRUE;
		descriptor.OutputChannels = 2;
		descriptor.pEffect = pXAPO;

		//EFFECT_CHAIN�\���̂̐錾
		XAUDIO2_EFFECT_CHAIN chain;
		chain.EffectCount = 1;
		chain.pEffectDescriptors = &descriptor;

		//MyFadeXAPO��pSourceVoice�ɑ}��
		m_pSourceVoice->SetEffectChain(&chain);
		//��d�Ǘ��ɂȂ�Ȃ��悤�ɔj��
		pXAPO->Release();

		MyFadeXAPO::MyFadeParam fade_params;
		fade_params.TargetVolume = _targetVolume;
		fade_params.TargetTime = _targetTime;

		m_pSourceVoice->SetEffectParameters(0, &fade_params, sizeof(fade_params));
	}

	void PlayWAVE::FadeWithEQ(const float _targetVolume, const float _targetTime, const float _freqency, const int _typeEQ)
	{
		//Fade�t�B���^�[�̐錾
		IUnknown* FadeXAPO;
		FadeXAPO = (IXAPO*)new MyFadeXAPO();

		//EFFECT_DESCRIPTOR�\���̂̐錾
		XAUDIO2_EFFECT_DESCRIPTOR descriptor[2];
		descriptor[0].InitialState = TRUE;
		descriptor[0].OutputChannels = 2;
		descriptor[0].pEffect = FadeXAPO;

		//0 : LowPassFilter   1 : HighPassFilter
		IUnknown* EQXAPO;
		if (_typeEQ == 1)
		{
			EQXAPO = (IXAPO*)new MyHighPassFilterXAPO();

			descriptor[1].InitialState = true;
			descriptor[1].OutputChannels = 2;
			descriptor[1].pEffect = EQXAPO;
		}
		else
		{
			EQXAPO = (IXAPO*)new MyLowPassFilterXAPO();

			descriptor[1].InitialState = true;
			descriptor[1].OutputChannels = 2;
			descriptor[1].pEffect = EQXAPO;
		}

		//EFFECT_CHAIN�\���̂̐錾
		XAUDIO2_EFFECT_CHAIN chain;
		chain.EffectCount = 2;
		chain.pEffectDescriptors = descriptor;

		//��d�Ǘ��ɂȂ�Ȃ��悤�ɔj��
		FadeXAPO->Release();
		EQXAPO->Release();

		MyFadeXAPO::MyFadeParam fade_params;
		fade_params.TargetVolume = _targetVolume;
		fade_params.TargetTime = _targetTime;
		m_pSourceVoice->SetEffectParameters(0, &fade_params, sizeof(fade_params));

		WAVEFORMATEX wfx = m_WaveReader.Getwfx();
		float freq = 2.0f * sinf(DX_PI_F * _freqency / wfx.nSamplesPerSec);
		m_pSourceVoice->SetEffectParameters(1, &freq, sizeof(freq));
	}

	void PlayWAVE::LowPassFilter(const float _freqency)
	{
		WAVEFORMATEX wfx = m_WaveReader.Getwfx();

		XAUDIO2_FILTER_PARAMETERS FilterParams;
		FilterParams.Type = XAUDIO2_FILTER_TYPE::LowPassFilter;
		float freq = 2.0f * sinf(DX_PI_F * _freqency / wfx.nSamplesPerSec);
		if (freq > XAUDIO2_MAX_FILTER_FREQUENCY)
			freq = XAUDIO2_MAX_FILTER_FREQUENCY;
		FilterParams.Frequency = freq;
		FilterParams.OneOverQ = 1.4142f;

		m_pSourceVoice->SetFilterParameters(&FilterParams);

		//TODO : �m�C�Y���o��
		//IUnknown* pXAPO;
		//pXAPO = (IXAPO*)new MyLowPassFilterXAPO();

		//XAUDIO2_EFFECT_DESCRIPTOR descriptor;
		//descriptor.InitialState = true;
		//descriptor.OutputChannels = 2;
		//descriptor.pEffect = pXAPO;

		//XAUDIO2_EFFECT_CHAIN chain;
		//chain.EffectCount = 1;
		//chain.pEffectDescriptors = &descriptor;

		//m_pSourceVoice->SetEffectChain(&chain);
		//pXAPO->Release();

		//m_pSourceVoice->SetEffectParameters(0, &freq, sizeof(freq));
	}

	void PlayWAVE::HighPassFilter(const float _freqency)
	{
		IUnknown* pXAPO;
		pXAPO = (IXAPO*)new MyHighPassFilterXAPO();

		XAUDIO2_EFFECT_DESCRIPTOR descriptor;
		descriptor.InitialState = true;
		descriptor.OutputChannels = 2;
		descriptor.pEffect = pXAPO;

		XAUDIO2_EFFECT_CHAIN chain;
		chain.EffectCount = 1;
		chain.pEffectDescriptors = &descriptor;

		m_pSourceVoice->SetEffectChain(&chain);
		pXAPO->Release();

		WAVEFORMATEX wfx = m_WaveReader.Getwfx();
		float freq = 2.0f * sinf(DX_PI_F * _freqency / wfx.nSamplesPerSec);
		m_pSourceVoice->SetEffectParameters(0, &freq, sizeof(freq));
	}

	void PlayWAVE::Play()
	{
		//XAudio2_BUFFER�\���̂̍쐬
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.pAudioData = (BYTE*)m_WaveReader.GetpBuffer();
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = m_WaveReader.GetDataChunk().chunk_size;
		buffer.PlayBegin = 0;
		buffer.LoopCount = m_LoopCount;

		//�g�`�f�[�^�̏����Z�b�g
		if (FAILED(hr = m_pSourceVoice->SubmitSourceBuffer(&buffer)))
		{
			printfDx("can not submitting source buffer");
			m_pSourceVoice->DestroyVoice();
		}

		if (SUCCEEDED(hr = m_pSourceVoice->Start()))
		{
		}
	}

	void PlayWAVE::PlayWithLoop(float _loopbegin, float _looplength)
	{
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.pAudioData = (BYTE*)m_WaveReader.GetpBuffer();
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = m_WaveReader.GetDataChunk().chunk_size;
		buffer.PlayBegin = 0;
		buffer.LoopCount = m_LoopCount;
		buffer.LoopBegin = static_cast<int>(_loopbegin * m_WaveReader.Getwfx().nSamplesPerSec);
		buffer.LoopLength = static_cast<int>(_looplength * m_WaveReader.Getwfx().nSamplesPerSec);

		//�g�`�f�[�^�̏����Z�b�g
		if (FAILED(hr = m_pSourceVoice->SubmitSourceBuffer(&buffer)))
		{
			printfDx("can not submitting source buffer");
			m_pSourceVoice->DestroyVoice();
		}

		if (SUCCEEDED(hr = m_pSourceVoice->Start()))
		{
		}
	}

	bool PlayWAVE::CheckIsRunning()
	{
		XAUDIO2_VOICE_STATE state;
		m_pSourceVoice->GetState(&state);
		if (state.BuffersQueued > 0)
			return true;
		else
			return false;
	}

	void PlayWAVE::Destroy()
	{
		if (CheckIsRunning() == true)
			Pause();
	}

	void PlayWAVE::PlayBackGround(PlayWAVE& _pw)
	{
		std::thread th(&PlayWAVE::Play, &_pw);
		th.detach();
	}

	void PlayWAVE::PlayBackGroundWithLoop(PlayWAVE& _pw, float _loopbegin, float _looplength)
	{
		std::thread th(&PlayWAVE::PlayWithLoop, &_pw, _loopbegin, _looplength);
		th.detach();
	}
}