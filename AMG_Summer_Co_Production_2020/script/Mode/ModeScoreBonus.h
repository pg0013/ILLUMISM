/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeScoreBonus.h.
 *
 * @brief	�X�R�A�{�[�i�X�\�����[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"ModeGame.h"
#include"../UI/BonusPoint.h"

namespace illumism
{
	namespace   //!<�{�[�i�X�|�C���g�p�萔
	{
		constexpr int BONUS_POINT = 200;
	}

	/**
	 * @class	ModeScoreBonus
	 *
	 * @brief	�X�R�A�{�[�i�X�\�����[�h
	 *
	 */
	class ModeScoreBonus : public ModeBase
	{
	public:

		/**
		 * @fn	ModeScoreBonus::ModeScoreBonus(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor,ModeGame::BONUS_PARAM _player1, ModeGame::BONUS_PARAM _player2);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_point1			�v���C���[�P�����|�C���g
		 * @param 	_point2			�v���C���[�Q�����|�C���g
		 * @param 	_P1charactor	�v���C���[�P�I���L����
		 * @param 	_P2charactor	�v���C���[�Q�I���L����
		 * @param 	_player1		�v���C���[�P�{�[�i�X�p�����[�^
		 * @param 	_player2		�v���C���[2�{�[�i�X�p�����[�^
		 */
		ModeScoreBonus(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor, ModeGame::BONUS_PARAM _player1, ModeGame::BONUS_PARAM _player2);

		/**
		 * @fn	virtual bool ModeScoreBonus::Initialize(Game& _game);
		 *
		 * @brief	����������
		 * @detail	ModeServer�ڑ����Ɉ�x�����Ă΂��
		 *
		 * @param [in,out]	_game	Game�N���X�̎Q��
		 *
		 * @returns	�����������̉�
		 */
		virtual bool Initialize(Game& _game);

		/**
		 * @fn	virtual bool ModeScoreBonus::Terminate(Game& _game);
		 *
		 * @brief	�I������
		 * @detail	ModeServer����폜�����ہA��x�����Ă΂��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�I�����������̉�
		 */
		virtual bool Terminate(Game& _game);

		/**
		 * @fn	virtual bool ModeScoreBonus::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeScoreBonus::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

	private:
		/**
		 * @fn	void ModeScoreBonus::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();
		/**
		 * @fn	void ModeScoreBonus::SetCharaGraph(int _player1, int _player2);
		 *
		 * @brief	�v���C���[���I�������L�����̑ҋ@�A�j���[�V�����ƃA�s�[���A�j���[�V������ݒ�
		 *
		 * @param 	_player1	�v���C���[�P�I���L����
		 * @param 	_player2	�v���C���[�Q�I���L����
		 */
		void SetCharaGraph(int _player1, int _player2);

		/**
		 * @fn	void ModeScoreBonus::DrawBonusSign(Game& _game);
		 *
		 * @brief	�{�[�i�X���摜�ƃ{�[�i�X���Z�G�t�F�N�g���A�w�莞�Ԃɕ\��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void DrawBonusSign(Game& _game);

		/**
		 * @fn	void ModeScoreBonus::DrawCharactor();
		 *
		 * @brief	�L�����N�^�[��`��
		 */
		void DrawCharactor();

		/**
		 * @fn	void ModeScoreBonus::DrawSpotlight();
		 *
		 * @brief	Draw spotlight
		 *
		 */
		void DrawSpotlight();

		/**
		 * @fn	void ModeScoreBonus::AddBonusPoint();
		 *
		 * @brief	�{�[�i�X�p�����[�^��]�����A�X�R�A�{�[�i�X�����Z
		 *
		 */
		void AddBonusPoint();

		/**
		 * @fn	void ModeScoreBonus::PlaySE(const char* _filename, const float _pitch, Game & _game);
		 *
		 * @brief	���ʉ��Đ�
		 *
		 * @param 		   	_filename	�����t�@�C����.
		 * @param 		   	_pitch   	�Đ����x.
		 * @param [in, out]	_game	 	�Q�[���N���X�̎Q��.
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game);

	private:
		int m_player_point[2] = { 0 };  //!< �v���C���[�l���|�C���g
		ModeGame::BONUS_PARAM m_bonus_param[2]; //!< �e�v���C���[�{�[�i�X�p�����[�^


		BonusPoint bonuspoint1; //!< �{�[�i�X�|�C���g�`��N���X
		BonusPoint bonuspoint2;
		BonusPoint bonuspoint3;


		int m_background_graph; //!< �摜�n���h��
		int m_bg_bonus_graph;
		int m_spotlight_graph;
		int m_player_charactor_graph[2] = { 0 };
		int m_charactor1_graph[30] = { 0 };
		int m_charactor2_graph[30] = { 0 };
		int m_appealchara1_graph[40] = { 0 };
		int m_appealchara2_graph[40] = { 0 };
		int m_player_charactor[2] = { 0 };
		int m_bonus_graph[3] = { 0 };
		int m_num_graph[3] = { 0 };
		int m_bonus_point_graph;

		bool  m_boss_bonus, m_combo_bonus, m_death_bonus;//!< �{�[�i�X���Z�������s���t���O
	};
}