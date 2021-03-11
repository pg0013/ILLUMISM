/**
 * @file	AMG_Summer_Co_Production_2020\script\EffectComponent.cpp
 *
 * @brief �C�[�W���O
 *
 * @date 2020-06-28
 * @version 1.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */

#include "EffectComponent.h"
#include "DxLib.h"
#include "easing.h"
using namespace utility;

EffectComponent::EffectComponent(
  bool active,
  int delay, int lifetime, int start_time,
  double value, double start, double stop,
  std::string type):
  _active{active},
  _delay{delay}, _lifetime{lifetime}, _start_time{start_time},
  _value{value}, _start{start}, _stop{stop},
  _easing(Easing::GetFunction(type))
{
}

void EffectComponent::SetParam(bool active, int delay, int lifetime, int start_time,
  double value, double start, double stop, std::string type)
{
  _active = active;
  _delay = delay; _lifetime = lifetime; _start_time = start_time;
  _value = value; _start = start; _stop = stop;
  _easing = Easing::GetFunction(type);
}

void EffectComponent::Update(int current)
{
  if (!_active)
  {
    return;
  }
  // �o�ߎ��ԁ����ݎ����|(�J�n�����{�x������)
  auto elapsed = current - (_start_time + _delay);
  if (elapsed < 0)
  {
    return; // �f�B���C(�x��)��
  }

  if (elapsed < _lifetime)
  {
    _value = _easing(elapsed, _start, _stop - _start, _lifetime);
  }
  else
  {
    _value = _stop;
    _active = false;
  }
}
