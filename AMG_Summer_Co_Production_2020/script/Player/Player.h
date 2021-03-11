/**
 * @file	AMG_Summer_Co_Production_2020\script\Player.h.
 *
 * @brief	�v���C���[�Ɋւ��鏈��
  * @author	Takuya Fujisawa
 */

#pragma once
#include"../Object/ObjectBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
	 * @class	Player
	 *
	 * @brief	�v���C���[�N���X
	 *
	 */
	class Player :public ObjectBase
	{
	public:

		/**
		 * @fn	Player::Player(const int _num,const int _charatype);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_num	  	�v���C���[�ԍ�
		 * @param 	_charatype	�I���L�����N�^�[
		 */
		Player(const int _num, const int _charatype);
		~Player();

		/**
		 * @fn	virtual OBJECT_TYPE Player::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return m_object_type; }

		/**
		 * @fn	void Player::SetType(OBJECT_TYPE _object_type)
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�ݒ�
		 *
		 * @param 	_object_type	�I�u�W�F�N�g�̎��
		 */
		void SetType(OBJECT_TYPE _object_type) { m_object_type = _object_type; }

		/**
		 * @enum	PLAYER_STATE
		 *
		 * @brief	�v���C���[�̏�ԑJ�ڗp�萔
		 */
		enum PLAYER_STATE
		{
			APPEAR, MOVE, JUMP, SHOOT, ATTACK, FLY, TOUCH, DAMAGE, HIT, APPEAL, SPMOVE, RESPOWN
		};

		/**
		 * @fn	void Player::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void Player::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Player::Draw(Game& _game) override;
		 *
		 * @brief	�v���C���[��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

	private:
		/**
		 * @fn	void Player::Input(Game& _game);
		 *
		 * @brief	�R���g���[���[������͂����m���A��Ԃ�J�ڂ��鏈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Input(Game& _game);

		/**
		 * @fn	void Player::State(Game& _game);
		 *
		 * @brief	��ԑJ�ڂ��s������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void State(Game& _game);

		/**
		 * @fn	void Player::Appear(Game& _game);
		 *
		 * @brief	�v���C���[�o�ꎞ�̏���
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Appear(Game& _game);

		/**
		 * @fn	void Player::Move(Game& _game);
		 *
		 * @brief	�ړ�����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Move(Game& _game);

		/**
		 * @fn	void Player::Jump(Game& _game);
		 *
		 * @brief	�W�����v�����iA�{�^���j
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Jump(Game& _game);

		/**
		 * @fn	void Player::Shoot(Game& _game);
		 *
		 * @brief	�e�ۂ𔭎˂���U������(RT)
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Shoot(Game& _game);

		/**
		 * @fn	void Player::Attack(Game& _game);
		 *
		 * @brief	ATTACK�U�����s�������iB�{�^���j
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��.
		 */
		void Attack(Game& _game);

		/**
		 * @fn	void Player::Fly(Game& _game);
		 *
		 * @brief	��s���[�h�����iLT�j
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Fly(Game& _game);

		/**
		 * @fn	void Player::Touch(Game& _game);
		 *
		 * @brief	�^�b�`�A�N�V�����̏����iX�{�^���j
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Touch(Game& _game);

		/**
		 * @fn	void Player::Appeal(Game& _game);
		 *
		 * @brief	�A�s�[���A�N�V�����̏����iLB�j
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Appeal(Game& _game);

		/**
		 * @fn	void Player::SPMove(Game& _game);
		 *
		 * @brief	�K�E�Z�A�N�V�����̏����iY�{�^���j
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void SPMove(Game& _game);

		/**
		 * @fn	void Player::Hit(Game& _game);
		 *
		 * @brief	���I�u�W�F�N�g�Ƃ̓����蔻�菈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Hit(Game& _game);

		/**
		 * @fn	void Player::Damage(Game& _game);
		 *
		 * @brief	�_���[�W���󂯂��Ƃ��̏���
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game);

		/**
		 * @brief	�_���[�W���󂯂��Ƃ��Ƀv���C���[�������_���[�W���̈ʒu�ɂ���ĕς��鏈��.
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void SetDamagedDirection(Game& _game);
		/**
		 * @fn	void Player::Respawn(Game& _game);
		 *
		 * @brief	HP=0�ɂȂ������̃��X�|�[������
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Respawn(Game& _game);

		/**
		 * @fn	void Player::UpdatePlayerUI(Game& _game);
		 *
		 * @brief	�v���C���[UI�̃p�����[�^���X�V
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void UpdatePlayerUI(Game& _game);

		/**
		 * @fn	void Player::OffScreen();
		 *
		 * @brief	��ʊO�ւ̈ړ��𐧌����鏈��
		 *
		 */
		void OffScreen();

		/**
		 * @fn	void Player::ParamsProcess(Game& _game);
		 *
		 * @brief	�v���C���[�̃p�����[�^�Ɋւ��鏈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void ParamsProcess(Game& _game);

		/**
		 * @fn	void Player::LoadCharaGraph(const int _charatype);
		 *
		 * @brief	�L�����N�^�[�摜�����[�h���鏈��
		 *
		 * @param 	_charatype	�v���C���[�I���L����
		 */
		void LoadCharaGraph(const int _charatype);

		/**
		 * @fn	void Player::PlaySE(const char* _filename, Game& _game);
		 *
		 * @brief	���ʉ��Đ�
		 *
		 * @param 		  	_filename	�����t�@�C����
		 * @param 		  	_pan	 		���E�o�����X�ݒ�Ax���W������
		 * @param [in,out]	_game	 �Q�[���N���X�̎Q��
		 */
		void PlaySE(const char* _filename, Game& _game);

		/**
		 * @fn	void Player::GenerateComboEffect(Game& _game);
		 *
		 * @brief	�R���{���\���G�t�F�N�g�𐶐�
		 *
		 * @param [in,out]	_game	 �Q�[���N���X�̎Q��
		 */
		void GenerateComboEffect(Game& _game);

		/**
		 * @fn	void Player::GenerateFlyParticle(Game& _game);
		 *
		 * @brief	��s���[�h�̃p�[�e�B�N���𐶐�
		 *
		 * @param [in,out]	_game	 �Q�[���N���X�̎Q��
		 */
		void GenerateFlyParticle(Game& _game);

		/**
		 * @fn	void Player::GenerateTouchParticle(Game& _game);
		 *
		 * @brief	�^�b�`�������̃p�[�e�B�N���𐶐�
		 *
		 * @param [in,out]	_game	 �Q�[���N���X�̎Q��
		 */
		void GenerateTouchParticle(Game& _game, ObjectBase* iter);

		/**
		 * @fn	virtual void ObjectBase::SetDirection(Game& _game, int _num, bool _turn_flag)
		 *
		 * @brief	�I�u�W�F�N�g�̕�����ݒ�
		 *
		 * @param [in,out]	_game	  	�Q�[���N���X�̎Q��
		 * @param 		  	_num	  		�v���C���[�ԍ�
		 * @param 		  	_turn_flag		�摜���]�t���O
		 */
		void SetDirection(Game& _game, int _num, bool _turn_flag) override;

		sound::PlayWAVE m_se;  //!< ���ʉ�

	private:
		int PLAYER_NUM; //!< �v���C���[�ԍ�

		OBJECT_TYPE m_object_type;  //!< �I�u�W�F�N�g�̎�ޗp�ϐ�

		int m_player_state; //!< �v���C���[�̏�ԑJ�ڗp�ϐ�

		const int BODY_W = 100; //!< �v���C���[�T�C�Y
		const int BODY_H = 150;

		int m_inertia;  //!< �ړ����̊����p�ϐ�

		ObjectBase* m_Attack;   //!< ATTACK�p�����蔻��

		ObjectBase* m_spmove;   //!< �K�E�Z�I�u�W�F�N�g

		int m_falling_speed;	//!< �󒆂ɂ���Ƃ��̗������x

		int m_bullet_frame_count;   //!<�e�𓙊Ԋu�Ŕ��˂��邽�߂̃t���[���J�E���^

		bool m_attack_flag; //!< ATTACK��SHOOT���������֎~�p�̃t���O

		int m_attacked_point;   //!< ATTACK���ꂽ�瑊��Ƀ|�C���g�����Z

		int m_move_flag;	//!< �ړ��������s���t���O

		int m_pushRT_frame; //!< RT�������ꂽ�Ƃ��̃t���[�����L�^�i�{�^��2�x�����p�j

		int m_pushRT_count; //!< RT���w�莞�ԓ��ɉ����ꂽ�����J�E���g

		bool m_RT_flag;//!<�g���K�[���͌��o�p�t���O
		bool m_oldRT_flag;//!<�g���K�[���͌��o�p�t���O

		// < �A�j���[�V�����̃t���[�����L�^.
		int m_jump_frame;
		int m_attack_frame;
		int m_spmove_frame;
		int m_touch_frame;
		int m_appeal_frame;
		int m_damage_frame;

		bool m_animation_running_flag;  //!< �A�j���[�V���������s���̃t���O
		bool m_appeal_flag; //!< �A�s�[�����ɃA�s�[�������s����Ȃ����߂̃t���O
		bool m_spmove_flag; //!< �K�E�Z���ɃA�s�[�������s����Ȃ����߂̃t���O
		bool m_touch_flag;  //!< �^�b�`���ɑ��A�N�V���������s���ꂽ�����߂̃t���O
		bool m_fly_flag;	//!< ��s���ɑ��A�N�V���������s����Ȃ����߂̃t���O

		int m_fly_time; //!< ��s����
		int m_fly_frame;	//!< FLY�J�n�̃t���[�����L�^
		bool m_fly_trigger_flag;	//!< LT�ptrigger�t���O

		int m_respawn_time; //!< ���X�|�[�����Ԃ̃J�E���^

		int m_isAlive_flag; //!< ���X�|�[�����̓v���C���[��`�悵�Ȃ��t���O

		int m_combo;	//!< �v���C���[�R���{��
		int m_max_combo;	//!< �ő�R���{�L�^�p�ϐ�

		//!<�A�N�V�������Ƃ̉摜�n���h��
		int m_wait_graph[30];
		int m_dash_graph[20];
		int m_shootdash_graph;
		int m_jump_graph[27];
		int m_shoot_graph[5];
		int m_shoot_up_graph[5];
		int m_shoot_upleft_graph[5];
		int m_shoot_downleft_graph[5];
		int m_dashshoot_graph[20];
		int m_dashshoot_up_graph[20];
		int m_dashshoot_upleft_graph[20];
		int m_dashshoot_downleft_graph[20];
		int m_touch_graph[15];
		int m_lightball_graph;
		int m_appeal_graph[40];
		int m_specialmove_graph;
		int m_coopmove_graph;
		int m_damage_graph[15];
		int m_attack_graph[27];
		int m_death_graph[45];
		int m_noname_toucheffect[7] = { 0 };
		int m_return_graph;
	};
}