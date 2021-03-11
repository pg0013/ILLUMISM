/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeOverlay.cpp.
 *
 * @brief	��ʑJ�ڃ��[�h
 * 				�L���v�`�����t�F�[�h�����w�肵�ĉ�ʑJ�ڂ��s��
 * 				�L���v�`���ł́A�\����ʂ̏ォ��I�[�o�[���C�\��
 * 				�t�F�[�h�ł́A��ʂ��Ó]������
 */

#include "ModeOverlay.h"
#include "DxLib.h"
#include"../Server/ResourceServer.h"
#include"../Game.h"
using namespace illumism;

bool ModeOverlay::Initialize(Game& _game)
{
	if (!ModeBase::Initialize(_game)) { return false; }

	return true;
}

bool ModeOverlay::Terminate(Game& _game)
{
	ModeBase::Terminate(_game);

	DeleteGraph(m_graph);

	return true;
}

void	ModeOverlay::Capture(int fadecnt)
{
	m_count = fadecnt;
	m_all = fadecnt;

	 //��ʃT�C�Y�Ɠ����X�N���[���̍쐬
	m_graph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	 //��ʂɕ\������Ă���摜�̎�荞��
	GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_graph);
}

void ModeOverlay::Fade(int fadecount, int fadetype)
{
	m_count = fadecount;
	m_all = fadecount;
	m_fade_type = fadetype;

	//��ʃT�C�Y�Ɠ����X�N���[���̍쐬
	m_graph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	//���摜�̕s�����x�𒲐߂��ĈÓ]���s�����@�͂��܂������Ȃ������̂ŁA
	//��ʊO����`�悳��Ă��Ȃ��������X�N���[���Ƃ��Đ؂���A�Ó]�p�摜�Ƃ��Ďg�p���Ă���B
	GetDrawScreenGraph(2*SCREEN_WIDTH, 2*SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, m_graph);
}

bool ModeOverlay::Process(Game& _game)
{
	ModeBase::Process(_game);

	m_count--;

	if (m_count <= 0)
		_game.m_modeserver->Del(this);

	return true;
}

bool ModeOverlay::Draw(Game& _game)
{
	ModeBase::Draw(_game);

	// ���l���v�Z
	int alpha;

	if (m_fade_type == FADE_IN)
		alpha = 255 * m_count / m_all;
	if(m_fade_type == FADE_OUT)
		alpha = 255- 255 * m_count / m_all;

	// ��ɉ�ʂ�킹��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);		// �������`��w��
	DrawGraph(0, 0, m_graph, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��

	return true;
}