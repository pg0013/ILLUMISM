/**
 * @file	AMG_Summer_Co_Production_2020\script\WAVEReader.cpp.
 *
 * @brief	WAVE�t�@�C���ǂݍ��݃N���X
 */

#include<xaudio2.h>
#include<iostream>
#include<DxLib.h>
#include"WAVEReader.h"

namespace sound
{
	WAVEReader::WAVEReader() {}
	WAVEReader::~WAVEReader() {}

	WAVEReader& WAVEReader::operator=(const WAVEReader& rhs)
	{
		//���ȑ������
		if (this != &rhs)
		{
			this->m_pBuffer = rhs.m_pBuffer;
			this->m_WFX = rhs.m_WFX;
			this->m_data = rhs.m_data;
		}
		return*this;
	}

	void WAVEReader::LoadWAVE(const char* _fileName)
	{
		int filehandle;

		//DX���C�u�����̃A�[�J�C�u�@�\���g�����߁ADX���C�u������fileopen�֐����g��
		filehandle = FileRead_open(_fileName);

		//RIFF�w�b�_�[�̓ǂݍ���
		RiffHeader riff;
		FileRead_read(&riff, sizeof(riff), filehandle);

		//Format�`�����N�̓ǂݍ���
		FmtChunk format;
		FileRead_read(&format, sizeof(format), filehandle);

		//Data�`�����N�̓ǂݍ���
		FileRead_read(&m_data, sizeof(m_data), filehandle);

		//Data�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
		m_pBuffer = (char*)malloc(m_data.chunk_size);
		FileRead_read(m_pBuffer, m_data.chunk_size, filehandle);

		//�g�`�t�H�[�}�b�g�̐ݒ�
		memcpy(&m_WFX, &format.fmt, sizeof(format.fmt));

		//WAVEFORMAT�ɂ͂Ȃ��r�b�g�[�x���v�Z
		m_WFX.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;
	}
}