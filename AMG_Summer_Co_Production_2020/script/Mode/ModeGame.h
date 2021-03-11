/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeGame.h.
 *
 * @brief	�Q�[�����[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"../Object/BackGround.h"
#include"../Player/Player.h"
#include"../BOSS/BOSS.h"
#include"../Game.h"
#include"../Sound/PlayWAVE.h"
#include"../Server/ObjectServer.h"
#include"../Controller/TouchObjectController.h"
#include"../Controller/CoopMoveController.h"
#include"../Controller/GameUIController.h"
#include"../Controller/SpotlightController.h"
#include"../Object/Camera.h"
#include"../UI/Time_UI.h"
#include"Dxlib.h"

namespace illumism
{
	//<�摜�\���p���W
	namespace
	{
		constexpr int READY_pos_x = 1920 / 2;
		constexpr int READY_pos_y = 1080 / 2;
		constexpr int FIGHT_pos_x = 1920 / 2;
		constexpr int FIGHT_pos_y = 1080 / 2;
		constexpr int FINISH_pos_x = 1920 / 2;
		constexpr int FINISH_pos_y = 1080 / 2;
		constexpr int COUNT_pos_x = 1920 / 2;
		constexpr int COUNT_pos_y = 1080 / 3 + 75;
	}

	/**
	 * @class	ModeGame
	 *
	 * @brief	�C���Q�[��
	 *
	 */
	class ModeGame : public ModeBase
	{
	public:
		/**
		 * @fn	ModeGame::ModeGame(const int _P1charactor, const int _P2charactor);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_P1charactor		�v���C���[1�̃L�����N�^�[���
		 * @param 	_P2charactor		�v���C���[2�̃L�����N�^�[���
		 */
		ModeGame(const int _P1charactor, const int _P2charactor);

		/**
		 * @fn	virtual bool ModeGame::Initialize(Game& _game);
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
		 * @fn	virtual bool ModeGame::Terminate(Game& _game);
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
		 * @fn	virtual bool ModeGame::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeGame::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

		/**
		 * @fn	void ModeGame::SetPlayerPoint(const int _player_num, const int _player_point);
		 *
		 * @brief	�v���C���[�̏����|�C���g���L�^
		 *
		 * @param 	_player_num  	The player number.
		 * @param 	_player_point	The player point.
		 */
		void SetPlayerPoint(const int _player_num, const int _player_point);

		/**
		 * @fn	const int ModeGame::GetPlayerPoint(int _num)
		 *
		 * @brief	Gets player point
		 *
		 * @param 	_num	�v���C���[�ԍ�
		 *
		 * @returns	The player point.
		 */
		const int GetPlayerPoint(int _num) { return m_player_point[_num - 1]; }

		/**
		 * @fn	const int ModeGame::GetPlayerCharactor(int _num)
		 *
		 * @brief	�v���C���[�̃L�����N�^�[��ނ��L�^
		 *
		 * @param 	_num	�v���C���[�ԍ�
		 *
		 * @returns	The player charactor.
		 */
		const int GetPlayerCharactor(int _num) { return m_player_charactor[_num - 1]; }

		/**
		 * @struct	BONUS_PARAM
		 *
		 * @brief	�{�[�i�X���[�h�p�p�����[�^
		 *
		 */
		struct BONUS_PARAM
		{
			int BOSS_DAMAGE;	//!< �{�X�ɗ^�����_���[�W��
			int MAX_COMBO;  //!< �ő�R���{��
			int DEATH_COUNT;	//!< ���S��
		};
		BONUS_PARAM m_bonus_param[2] = { 0,0,0 };

		/**
		 * @fn	void ModeGame::AddPlayerDamage(int _num, int _damage)
		 *
		 * @brief	�{�X�ɗ^�����_���[�W�ʂ��L�^
		 *
		 * @param 	_num   	�v���C���[�ԍ�
		 * @param 	_damage	�_���[�W��
		 */
		void AddPlayerDamage(int _num, int _damage) { m_bonus_param[_num - 1].BOSS_DAMAGE += _damage; }

		/**
		 * @fn	const int ModeGame::GetPlayerDamage(int _num)
		 *
		 * @brief	�{�X�ɗ^�����_���[�W�ʂ��擾
		 *
		 * @param 	_num   	�v���C���[�ԍ�
		 * @returns	�_���[�W��
		 */
		const int GetPlayerDamage(int _num) { return m_bonus_param[_num - 1].BOSS_DAMAGE; }

		/**
		 * @fn	void ModeGame::AddMaxCombo(int _num, int _combo)
		 *
		 * @brief	�ő�R���{�����L�^
		 *
		 * @param 	_num  	�v���C���[�ԍ�
		 * @param 	_combo		�ő�R���{��
		 */
		void AddMaxCombo(int _num, int _combo) { m_bonus_param[_num - 1].MAX_COMBO = _combo; }

		/**
		 * @fn	const int ModeGame::GetMaxCombo(int _num)
		 *
		 * @brief	�ő�R���{�����擾
		 *
		 * @param 	_num	�v���C���[�ԍ�
		 *
		 * @returns	�ő�R���{��
		 */
		const int GetMaxCombo(int _num) { return m_bonus_param[_num - 1].MAX_COMBO; }

		/**
		 * @fn	void ModeGame::AddDeathCount(int _num, int _count)
		 *
		 * @brief	���S�񐔂��L�^
		 *
		 * @param 	_num  	�v���C���[�ԍ�
		 * @param 	_count	���S��
		 */
		void AddDeathCount(int _num, int _count) { m_bonus_param[_num - 1].DEATH_COUNT += _count; }

		/**
		 * @fn	const int ModeGame::GetDeathCount(int _num)
		 *
		 * @brief	���S�񐔂��擾
		 *
		 * @param 	_num	�v���C���[�ԍ�
		 *
		 * @returns	���S��
		 */
		const int GetDeathCount(int _num) { return m_bonus_param[_num - 1].DEATH_COUNT; }

		/**
		 * @fn	const BONUS_PARAM ModeGame::GetBonusParam(int _num)
		 *
		 * @brief	�{�[�i�X�p�����[�^���擾
		 *
		 * @param 	_num	�v���C���[�ԍ�
		 *
		 * @returns	The bonus parameter.
		 */
		const BONUS_PARAM GetBonusParam(int _num) { return m_bonus_param[_num - 1]; }

		Camera m_camera;

		BackGround m_background;

		TouchObjectController m_touch_object_controller;

		SpotlightController m_spotlight_controller;

		CoopMoveController m_coopmove_controller;

		GameUIController m_gameUI_controller;

		Time_UI m_timeUI;

		bool	m_stopObjProcess;   //!< �I�u�W�F�N�g�������X�g�b�v����.

	private:

		/**
		 * @fn	void ModeGame::DrawGameSign(Game& _game);
		 *
		 * @brief	READY?,FIGHT!!,FINISH��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void DrawGameSign(Game& _game);

		/**
		 * @fn	void ModeGame::DrawGameCount(Game& _game);
		 *
		 * @brief	�Q�[���I���܂ł̃J�E���g��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void DrawGameCount(Game& _game);

		/**
		 * @fn	void ModeGame::GenerateGameCount(const char* _filename, const int _count, Game& _game);
		 *
		 * @brief	�Q�[���I���J�E���g�𐶐�
		 *
		 * @param 		  	_filename	�t�@�C����
		 * @param 		  	_count		�Q�[���I�����牽�b�O��
		 * @param [in,out]	_game	 �Q�[���N���X�̎Q��
		 */
		void GenerateGameCount(const char* _filename, const int _count, Game& _game);

		int m_player_point[2] = { 0 };  //!< �v���C���[�����|�C���g
		int m_player_charactor[2] = { 0 };  //!< �L�����N�^�[���
		int m_vignette_graph;   //!< �r�l�b�g�摜�n���h��
	};
}