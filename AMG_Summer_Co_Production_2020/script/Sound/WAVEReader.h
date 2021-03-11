/**
 * @file	AMG_Summer_Co_Production_2020\script\WAVEReader.h.
 *
 * @brief	WAVE�t�@�C���ǂݍ��݃N���X
 * @author	Takuya Fujisawa
 */

#include<xaudio2.h>
#include<iostream>

namespace sound
{
	/**
	 * @class	WAVEReader
	 *
	 * @brief	WAVE�t�@�C���ǂݍ��݃N���X
	 *
	 */
	class WAVEReader
	{
	private:

		/**
		 * @struct	Chunk
		 *
		 * @brief	chunk�f�[�^�̊�{�\��.
		 * @note	chunk���f�[�^�̉�
		 *
		 */
		struct Chunk
		{
			char id[4];					//!< chunk����ID
			int32_t chunk_size;	//!< �`�����N�T�C�Y
		};

		/**
		 * @struct	RiffHeader
		 *
		 * @brief	RIFF�w�b�_�[
		 *
		 */
		struct RiffHeader
		{
			Chunk chunk;	//!< "RIFF"
			char type[4];	//!< "WAVE"
		};

		/**
		 * @struct	FmtChunk
		 *
		 * @brief	fmt�`�����N
		 *
		 */
		struct FmtChunk
		{
			Chunk chunk;
			WAVEFORMAT fmt;
		};

		WAVEFORMATEX m_WFX{};   //!< WAVEFORMATEX�\����

		char* m_pBuffer;	//!< �g�`�f�[�^���̐擪�A�h���X

		Chunk m_data;   //!< �f�[�^�`�����N

	public:
		WAVEReader();
		~WAVEReader();

		WAVEReader& operator=(const WAVEReader& rhs);

		/**
		 * @fn	void WAVEReader::LoadWAVE(const char* _fileName);
		 *
		 * @brief	WAV�t�@�C���̓ǂݍ���
		 *
		 * @param 	_fileName	Filename of the file.
		 */
		void LoadWAVE(const char* _fileName);

		/**
		 * @fn	WAVEFORMATEX WAVEReader::Getwfx()
		 *
		 * @brief	WFX�\���̂�Ԃ�
		 *
		 * @returns	A WAVEFORMATEX.
		 */
		WAVEFORMATEX Getwfx() { return m_WFX; }

		/**
		 * @fn	char* WAVEReader::GetpBuffer()
		 *
		 * @brief	�g�`�f�[�^�̐擪�A�h���X��Ԃ�
		 *
		 * @returns	�g�`�f�[�^�̐擪�A�h���X
		 */
		char* GetpBuffer() { return m_pBuffer; }

		/**
		 * @fn	Chunk WAVEReader::GetDataChunk()
		 *
		 * @brief	�g�`�f�[�^��Ԃ�
		 *
		 * @returns	The data chunk.
		 */
		Chunk GetDataChunk() { return m_data; }
	};
}