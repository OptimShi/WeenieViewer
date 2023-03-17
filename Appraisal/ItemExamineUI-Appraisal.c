
//----- (004ADAE0) --------------------------------------------------------
void __thiscall gmExaminationUI::SetAppraiseInfo(gmExaminationUI *this, unsigned int _objid, AppraisalProfile *_prof)
{
  unsigned int v3; // ebx@1
  gmExaminationUI *v4; // edi@1
  unsigned int v5; // eax@2
  ClientUISystem *v6; // eax@5
  ExamineSubUI *v7; // esi@9
  AC1Legacy::PSRefBuffer<char> *v8; // ebp@11
  HashBaseData<unsigned long> *v9; // ebp@15
  int v10; // ST08_4@18
  const char *v11; // ST04_4@18
  AC1Legacy::PSRefBuffer<char> *v12; // esi@23
  bool is_new; // [sp+13h] [bp-45h]@15
  AC1Legacy::PStringBase<char> gearPlatingName; // [sp+14h] [bp-44h]@16
  AC1Legacy::PStringBase<char> sStatVal; // [sp+18h] [bp-40h]@7
  unsigned int iStatVal; // [sp+1Ch] [bp-3Ch]@7
  CreatureAppraisalProfile cprof; // [sp+20h] [bp-38h]@6
  char _objida; // [sp+5Ch] [bp+4h]@4

  v3 = _objid;
  v4 = this;
  if ( _objid )
  {
    v5 = this->awaiting_appraisal_ID;
    if ( _objid == v5 || _objid == this->current_appraisal_ID )
    {
      _objida = 0;
      if ( v3 == v5 )
      {
        this->awaiting_appraisal_ID = 0;
        v6 = ClientUISystem::GetUISystem();
        ClientUISystem::DecrementBusyCount(v6);
        v4->current_appraisal_ID = v3;
        _objida = 1;
      }
      CreatureAppraisalProfile::CreatureAppraisalProfile(&cprof);
      if ( AppraisalProfile::InqCreature(_prof, &cprof) )
      {
        sStatVal.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
        InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
        iStatVal = 0;
        if ( AppraisalProfile::InqString(_prof, 5u, &sStatVal)
          || AppraisalProfile::InqInt(_prof, 0x105u, (int *)&iStatVal) )
          v7 = (ExamineSubUI *)&v4->m_charUI->vfptr;
        else
          v7 = (ExamineSubUI *)&v4->m_creatureUI->vfptr;
        v8 = sStatVal.m_buffer;
        if ( !InterlockedDecrement((volatile LONG *)&sStatVal.m_buffer->m_cRef) && v8 )
          v8->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v8, 1u);
      }
      else
      {
        v7 = (ExamineSubUI *)&v4->m_itemUI->vfptr;
      }
      is_new = v3 != v7->cur_objid;
      v9 = ClientObjMaintSystem::GetWeenieObject(v3);
      if ( v9 )
      {
        gearPlatingName.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
        InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
        if ( AppraisalProfile::InqString(_prof, 0x34u, &gearPlatingName) )
        {
          gmExaminationUI::SetTitleText(v4, gearPlatingName.m_buffer->m_data, v9[20].id);
        }
        else
        {
          v10 = v9[20].id;
          v11 = ACCWeenieObject::GetObjectName((ACCWeenieObject *)v9, NAME_APPROPRIATE, 0);
          gmExaminationUI::SetTitleText(v4, v11, v10);
        }
        v7->vfptr->Init(v7, v3, (ACCWeenieObject *)v9);
        v7->vfptr->SetAppraiseInfo(v7, _prof, is_new);
        if ( v4->m_activeUI != v7 )
          gmExaminationUI::SetActiveExamineUI(v4, v7);
        if ( _objida )
          v4->vfptr[2].__vecDelDtor((IInputActionCallback *)v4, 1u);
        v12 = gearPlatingName.m_buffer;
        if ( !InterlockedDecrement((volatile LONG *)&gearPlatingName.m_buffer->m_cRef) )
        {
          if ( v12 )
            v12->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v12, 1u);
        }
      }
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004ADCA0) --------------------------------------------------------
void __thiscall ItemExamineUI::AddItemInfo(ItemExamineUI *this, const char *ability_txt, int font, int surpressDoubleSpacing)
{
  ItemExamineUI *v4; // edi@1
  UIElement_Text *v5; // eax@1
  int v6; // esi@6
  PStringBase<unsigned short> *v7; // eax@9
  int v8; // esi@9

  v4 = this;
  v5 = this->m_itemDisplayText;
  if ( v5 )
  {
    if ( v5->m_glyphList.m_glyphList._num_elements > 1 )
    {
      if ( surpressDoubleSpacing )
        PStringBase<unsigned short>::PStringBase<unsigned short>(
          (PStringBase<unsigned short> *)&surpressDoubleSpacing,
          L"\n");
      else
        PStringBase<unsigned short>::PStringBase<unsigned short>(
          (PStringBase<unsigned short> *)&surpressDoubleSpacing,
          L"\n\n");
      UIElement_Text::AppendText(v4->m_itemDisplayText, (PStringBase<unsigned short> *)&surpressDoubleSpacing);
      v6 = surpressDoubleSpacing - 20;
      if ( !InterlockedDecrement((volatile LONG *)(surpressDoubleSpacing - 20 + 4)) )
      {
        if ( v6 )
          (**(void (__thiscall ***)(_DWORD, _DWORD))v6)(v6, 1);
      }
    }
    PStringBase<unsigned short>::PStringBase<unsigned short>(
      (PStringBase<unsigned short> *)&surpressDoubleSpacing,
      0,
      ability_txt);
    UIElement_Text::AppendTextWithFont(v4->m_itemDisplayText, v7, 0, font);
    v8 = surpressDoubleSpacing - 20;
    if ( !InterlockedDecrement((volatile LONG *)(surpressDoubleSpacing - 20 + 4)) )
    {
      if ( v8 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v8)(v8, 1);
    }
  }
}

//----- (004ADD60) --------------------------------------------------------
void __thiscall ItemExamineUI::SetValueText(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // ebx@1
  AC1Legacy::PStringBase<unsigned short> *v3; // eax@5
  AC1Legacy::PSRefBuffer<char> *v4; // esi@5
  AppraisalProfile *v5; // edi@8
  PStringBase<unsigned short> *v6; // eax@8
  char *v7; // esi@8
  char *v8; // esi@14
  int iValue; // [sp+8h] [bp-8h]@2
  AC1Legacy::PStringBase<char> result; // [sp+Ch] [bp-4h]@5

  v2 = this;
  if ( this->m_itemValueText )
  {
    if ( AppraisalProfile::InqInt(_prof, 0x13u, &iValue) )
    {
      _prof = (AppraisalProfile *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( !AC1Legacy::PStringBase<char>::convert((AC1Legacy::PStringBase<char> *)&_prof, iValue, 1) )
        AC1Legacy::PStringBase<char>::set((AC1Legacy::PStringBase<char> *)&_prof, "???");
      v3 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::operator+(
                                                       &result,
                                                       "Value: ",
                                                       (AC1Legacy::PStringBase<char> *)&_prof);
      AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&_prof, v3);
      v4 = result.m_buffer;
      if ( !InterlockedDecrement((volatile LONG *)&result.m_buffer->m_cRef) && v4 )
        v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
      v5 = _prof;
      PStringBase<unsigned short>::PStringBase<unsigned short>(
        (PStringBase<unsigned short> *)&_prof,
        0,
        (const char *)&_prof->armor_profile);
      UIElement_Text::SetText(v2->m_itemValueText, v6);
      v7 = (char *)&_prof[-1].base_armor_wrist;
      if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v7 )
        (**(void (__thiscall ***)(char *, signed int))v7)(v7, 1);
      if ( !InterlockedDecrement(&v5->success_flag) )
      {
        if ( v5 )
          v5->vfptr->__vecDelDtor((PackObj *)v5, 1u);
      }
    }
    else
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&_prof, L"Value: ???");
      UIElement_Text::SetText(v2->m_itemValueText, (PStringBase<unsigned short> *)&_prof);
      v8 = (char *)&_prof[-1].base_armor_wrist;
      if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v8 )
        (**(void (__thiscall ***)(char *, signed int))v8)(v8, 1);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004ADEA0) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowValueInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  int v2; // esi@1
  ItemExamineUI *v3; // ebx@1
  volatile LONG *v4; // edi@1
  int v5; // ebx@2
  AC1Legacy::PStringBase<char> *v6; // eax@9
  AppraisalProfile *v7; // esi@9
  AC1Legacy::PSRefBuffer<char> *v8; // esi@12
  AC1Legacy::PSRefBuffer<char> *v9; // edi@12
  ItemExamineUI *v10; // ecx@20
  const char *v11; // [sp-Ch] [bp-2Ch]@20
  AC1Legacy::PStringBase<char> sDisplayStr; // [sp+10h] [bp-10h]@1
  int iValue; // [sp+14h] [bp-Ch]@1
  AC1Legacy::PStringBase<char> result; // [sp+18h] [bp-8h]@9
  ItemExamineUI *v15; // [sp+1Ch] [bp-4h]@1

  v2 = AC1Legacy::PStringBase<char>::s_NullBuffer;
  v3 = this;
  v4 = (volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4);
  v15 = this;
  sDisplayStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( AppraisalProfile::InqInt(_prof, 0x13u, &iValue) )
  {
    v5 = iValue;
    if ( v2 != AC1Legacy::PStringBase<char>::s_NullBuffer )
    {
      if ( !InterlockedDecrement(v4) && v2 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v2)(v2, 1);
      sDisplayStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    }
    AC1Legacy::PStringBase<char>::append_int32(&sDisplayStr, v5);
    if ( !AC1Legacy::PStringBase<char>::InsertCommas(&sDisplayStr) )
      AC1Legacy::PStringBase<char>::set(&sDisplayStr, "???");
    AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&_prof, "Value: ");
    AC1Legacy::PStringBase<char>::operator+(v6, &result, &sDisplayStr);
    v7 = _prof;
    if ( !InterlockedDecrement(&_prof->success_flag) && v7 )
      v7->vfptr->__vecDelDtor((PackObj *)v7, 1u);
    v8 = sDisplayStr.m_buffer;
    v9 = result.m_buffer;
    if ( sDisplayStr.m_buffer != result.m_buffer )
    {
      if ( !InterlockedDecrement((volatile LONG *)&sDisplayStr.m_buffer->m_cRef) && v8 )
        v8->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v8, 1u);
      v8 = v9;
      InterlockedIncrement((volatile LONG *)&v9->m_cRef);
    }
    if ( !InterlockedDecrement((volatile LONG *)&v9->m_cRef) && v9 )
      v9->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v9, 1u);
    v10 = v15;
    v11 = v8->m_data;
  }
  else
  {
    AC1Legacy::PStringBase<char>::set(&sDisplayStr, "Value: ???");
    v8 = sDisplayStr.m_buffer;
    v11 = sDisplayStr.m_buffer->m_data;
    v10 = v3;
  }
  ItemExamineUI::AddItemInfo(v10, v11, 0, 1);
  if ( !InterlockedDecrement((volatile LONG *)&v8->m_cRef) )
  {
    if ( v8 )
      v8->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v8, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004AE010) --------------------------------------------------------
void __thiscall ItemExamineUI::SetBurdenText(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // ebp@1
  AC1Legacy::PStringBase<unsigned short> *v3; // eax@5
  AC1Legacy::PSRefBuffer<char> *v4; // esi@5
  AC1Legacy::PSRefBuffer<char> *v5; // esi@8
  AppraisalProfile *v6; // edi@11
  PStringBase<unsigned short> *v7; // eax@11
  char *v8; // esi@11
  char *v9; // esi@17
  AC1Legacy::PStringBase<char> rhs; // [sp+8h] [bp-Ch]@5
  int iValue; // [sp+Ch] [bp-8h]@2
  AC1Legacy::PStringBase<char> result; // [sp+10h] [bp-4h]@5

  v2 = this;
  if ( this->m_itemBurdenText )
  {
    if ( AppraisalProfile::InqInt(_prof, 5u, &iValue) )
    {
      _prof = (AppraisalProfile *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( !AC1Legacy::PStringBase<char>::convert((AC1Legacy::PStringBase<char> *)&_prof, iValue, 1) )
        AC1Legacy::PStringBase<char>::set((AC1Legacy::PStringBase<char> *)&_prof, "???");
      AC1Legacy::PStringBase<char>::PStringBase<char>(&rhs, " Burden Units");
      v3 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                       (AC1Legacy::PStringBase<char> *)&_prof,
                                                       &result,
                                                       &rhs);
      AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&_prof, v3);
      v4 = result.m_buffer;
      if ( !InterlockedDecrement((volatile LONG *)&result.m_buffer->m_cRef) && v4 )
        v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
      v5 = rhs.m_buffer;
      if ( !InterlockedDecrement((volatile LONG *)&rhs.m_buffer->m_cRef) && v5 )
        v5->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v5, 1u);
      v6 = _prof;
      PStringBase<unsigned short>::PStringBase<unsigned short>(
        (PStringBase<unsigned short> *)&_prof,
        0,
        (const char *)&_prof->armor_profile);
      UIElement_Text::SetText(v2->m_itemBurdenText, v7);
      v8 = (char *)&_prof[-1].base_armor_wrist;
      if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v8 )
        (**(void (__thiscall ***)(char *, signed int))v8)(v8, 1);
      if ( !InterlockedDecrement(&v6->success_flag) )
      {
        if ( v6 )
          v6->vfptr->__vecDelDtor((PackObj *)v6, 1u);
      }
    }
    else
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&_prof, L"Unknown Burden");
      UIElement_Text::SetText(v2->m_itemBurdenText, (PStringBase<unsigned short> *)&_prof);
      v9 = (char *)&_prof[-1].base_armor_wrist;
      if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v9 )
        (**(void (__thiscall ***)(char *, signed int))v9)(v9, 1);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004AE180) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowBurdenInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  int v2; // esi@1
  ItemExamineUI *v3; // ebx@1
  volatile LONG *v4; // edi@1
  int v5; // ebx@2
  AC1Legacy::PStringBase<char> *v6; // eax@9
  AppraisalProfile *v7; // esi@9
  AC1Legacy::PSRefBuffer<char> *v8; // esi@12
  AC1Legacy::PSRefBuffer<char> *v9; // edi@12
  ItemExamineUI *v10; // ecx@20
  const char *v11; // [sp-Ch] [bp-2Ch]@20
  AC1Legacy::PStringBase<char> sDisplayStr; // [sp+10h] [bp-10h]@1
  int iValue; // [sp+14h] [bp-Ch]@1
  AC1Legacy::PStringBase<char> result; // [sp+18h] [bp-8h]@9
  ItemExamineUI *v15; // [sp+1Ch] [bp-4h]@1

  v2 = AC1Legacy::PStringBase<char>::s_NullBuffer;
  v3 = this;
  v4 = (volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4);
  v15 = this;
  sDisplayStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( AppraisalProfile::InqInt(_prof, 5u, &iValue) )
  {
    v5 = iValue;
    if ( v2 != AC1Legacy::PStringBase<char>::s_NullBuffer )
    {
      if ( !InterlockedDecrement(v4) && v2 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v2)(v2, 1);
      sDisplayStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    }
    AC1Legacy::PStringBase<char>::append_int32(&sDisplayStr, v5);
    if ( !AC1Legacy::PStringBase<char>::InsertCommas(&sDisplayStr) )
      AC1Legacy::PStringBase<char>::set(&sDisplayStr, "???");
    AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&_prof, "Burden: ");
    AC1Legacy::PStringBase<char>::operator+(v6, &result, &sDisplayStr);
    v7 = _prof;
    if ( !InterlockedDecrement(&_prof->success_flag) && v7 )
      v7->vfptr->__vecDelDtor((PackObj *)v7, 1u);
    v8 = sDisplayStr.m_buffer;
    v9 = result.m_buffer;
    if ( sDisplayStr.m_buffer != result.m_buffer )
    {
      if ( !InterlockedDecrement((volatile LONG *)&sDisplayStr.m_buffer->m_cRef) && v8 )
        v8->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v8, 1u);
      v8 = v9;
      InterlockedIncrement((volatile LONG *)&v9->m_cRef);
    }
    if ( !InterlockedDecrement((volatile LONG *)&v9->m_cRef) && v9 )
      v9->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v9, 1u);
    v10 = v15;
    v11 = v8->m_data;
  }
  else
  {
    AC1Legacy::PStringBase<char>::set(&sDisplayStr, "Burden: Unknown");
    v8 = sDisplayStr.m_buffer;
    v11 = sDisplayStr.m_buffer->m_data;
    v10 = v3;
  }
  ItemExamineUI::AddItemInfo(v10, v11, 0, 1);
  if ( !InterlockedDecrement((volatile LONG *)&v8->m_cRef) )
  {
    if ( v8 )
      v8->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v8, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004AE2F0) --------------------------------------------------------
void __thiscall ItemExamineUI::SetInscription(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  ACCWeenieObject *v3; // ecx@1
  char v4; // bl@1
  bool v5; // al@5
  PlayerDesc *v6; // ebx@5
  bool v7; // bl@10
  PStringBase<unsigned short> *v8; // eax@11
  PStringBase<unsigned short> *v9; // eax@11
  InterfacePtr<Interface> *v10; // eax@11
  char v11; // al@13
  PlayerDesc *v12; // ebx@13
  PStringBase<unsigned short> *v13; // eax@16
  char *v14; // edi@19
  int v15; // [sp+0h] [bp-24h]@0
  bool v16; // [sp+13h] [bp-11h]@5
  InterfacePtr<PlayerDesc> spPD; // [sp+14h] [bp-10h]@5
  InterfacePtr<Interface> result; // [sp+1Ch] [bp-8h]@11

  v2 = this;
  ((void (__stdcall *)(signed int))this->m_itemInscriptionText->vfptr[13].__vecDelDtor)(268435536);
  UIElement_Text::ClearAllText(v2->m_itemInscriptionText);
  AC1Legacy::PStringBase<char>::set(&v2->m_old_inscription, &name);
  UIElement_Text::ClearAllText(v2->m_itemInscriptionSignatureText);
  AC1Legacy::PStringBase<char>::set(&v2->m_scribe_name, &name);
  AC1Legacy::PStringBase<char>::set(&v2->m_scribe_account, &name);
  v3 = v2->cur_weenobj;
  v4 = (v3->pwd._bitfield >> 1) & 1;
  if ( ((int (*)(void))v3->vfptr[29].__vecDelDtor)() )
    v4 = AppraisalProfile::IsHookedItemInscribable(_prof) != 0;
  if ( !v4 )
  {
    ((void (__stdcall *)(_DWORD, int))v2->m_itemInscriptionText->vfptr[2].__vecDelDtor)(0, v15);
    ((void (__cdecl *)(signed int))v2->m_itemInscriptionSignatureText->vfptr[2].__vecDelDtor)(0);
    goto LABEL_24;
  }
  if ( !AppraisalProfile::InqString(_prof, 8u, &v2->m_scribe_name) )
    goto LABEL_27;
  AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&spPD, &name);
  v5 = AC1Legacy::PStringBase<char>::operator!=(&v2->m_scribe_name, (AC1Legacy::PStringBase<char> *)&spPD);
  v6 = spPD.m_pInterface;
  v16 = v5;
  if ( !InterlockedDecrement((volatile LONG *)&spPD.m_pInterface->m_dataCategory) && v6 )
    ((void (__thiscall *)(PlayerDesc *, signed int))v6->vfptr->IUnknown_QueryInterface)(v6, 1);
  if ( !v16 )
  {
LABEL_27:
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&_prof, L"<Inscribe here>");
    UIElement_Text::SetText(v2->m_itemInscriptionText, (PStringBase<unsigned short> *)&_prof);
    v14 = (char *)&_prof[-1].base_armor_wrist;
    if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v14 )
      (**(void (__thiscall ***)(char *, signed int))v14)(v14, 1);
    goto LABEL_22;
  }
  if ( !AppraisalProfile::InqString(_prof, 7u, &v2->m_old_inscription) )
    goto LABEL_22;
  AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&spPD, &name);
  v7 = AC1Legacy::PStringBase<char>::operator!=(&v2->m_old_inscription, (AC1Legacy::PStringBase<char> *)&spPD);
  CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&spPD);
  if ( !v7 )
    goto LABEL_22;
  ((void (__stdcall *)(signed int))v2->m_itemInscriptionText->vfptr[13].__vecDelDtor)(1);
  PStringBase<unsigned short>::PStringBase<unsigned short>(
    (PStringBase<unsigned short> *)&spPD,
    0,
    v2->m_old_inscription.m_buffer->m_data);
  UIElement_Text::SetText(v2->m_itemInscriptionText, v8);
  PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&spPD);
  PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&spPD, L"--");
  UIElement_Text::SetText(v2->m_itemInscriptionSignatureText, (PStringBase<unsigned short> *)&spPD);
  PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&spPD);
  PStringBase<unsigned short>::PStringBase<unsigned short>(
    (PStringBase<unsigned short> *)&spPD,
    0,
    v2->m_scribe_name.m_buffer->m_data);
  UIElement_Text::AppendText(v2->m_itemInscriptionSignatureText, v9);
  PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&spPD);
  v10 = GetClassObject(&result, &PlayerDesc_ClassType_7);
  InterfacePtr<PlayerDesc>::InterfacePtr<PlayerDesc>(&spPD, v10);
  if ( (_DWORD)result.m_pInterface )
    ((void (*)(void))result.m_pInterface->vfptr->Release)();
  v11 = InterfacePtr<PlayerDesc>::IsValid(&spPD);
  v12 = spPD.m_pInterface;
  if ( v11
    && PlayerDesc::PlayerIsPSR(spPD.m_pInterface)
    && AppraisalProfile::InqString(_prof, 0x17u, &v2->m_scribe_account) )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&_prof, L" <");
    UIElement_Text::AppendText(v2->m_itemInscriptionSignatureText, (PStringBase<unsigned short> *)&_prof);
    PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&_prof);
    PStringBase<unsigned short>::PStringBase<unsigned short>(
      (PStringBase<unsigned short> *)&_prof,
      0,
      v2->m_scribe_account.m_buffer->m_data);
    UIElement_Text::AppendText(v2->m_itemInscriptionSignatureText, v13);
    PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&_prof);
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&_prof, L">");
    UIElement_Text::AppendText(v2->m_itemInscriptionSignatureText, (PStringBase<unsigned short> *)&_prof);
    PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&_prof);
  }
  if ( !v12 )
  {
LABEL_22:
    ((void (__stdcall *)(signed int, int))v2->m_itemInscriptionText->vfptr[2].__vecDelDtor)(1, v15);
    ((void (__cdecl *)(signed int))v2->m_itemInscriptionSignatureText->vfptr[2].__vecDelDtor)(1);
    goto LABEL_24;
  }
  v12->vfptr->Release((Interface *)v12);
  ((void (__stdcall *)(signed int))v2->m_itemInscriptionText->vfptr[2].__vecDelDtor)(1);
  ((void (__cdecl *)(signed int))v2->m_itemInscriptionSignatureText->vfptr[2].__vecDelDtor)(1);
LABEL_24:
  ItemExamineUI::SetInscriptionEditableState(v2);
}

//----- (004AE620) --------------------------------------------------------
void __thiscall ItemExamineUI::HandleInscriptionLosingFocus(ItemExamineUI *this)
{
  ItemExamineUI *v1; // edi@1
  PStringBase<unsigned short> *v2; // eax@2
  PSRefBufferCharData<char> *v3; // esi@2
  int v4; // esi@2
  char *v5; // esi@5
  bool v6; // al@9
  PSRefBufferCharData<unsigned short> *v7; // esi@9
  bool v8; // bl@9
  char v9; // bl@13
  PSRefBufferCharData<char> *v10; // esi@15
  bool v11; // al@21
  PSRefBufferCharData<char> *v12; // esi@21
  bool v13; // bl@21
  char *v14; // esi@25
  unsigned int v15; // eax@30
  char *v16; // ST08_4@32
  AC1Legacy::PSRefBuffer<char> *v17; // esi@33
  AC1Legacy::PSRefBuffer<char> *v18; // eax@33
  AC1Legacy::PSRefBuffer<char> *v19; // eax@37
  AC1Legacy::PSRefBuffer<char> *v20; // esi@38
  AC1Legacy::PStringBase<char> new_inscription; // [sp+14h] [bp-Ch]@2
  PStringBase<unsigned short> result; // [sp+18h] [bp-8h]@2
  PStringBase<char> v23; // [sp+1Ch] [bp-4h]@2

  v1 = this;
  if ( this->cur_objid )
  {
    v2 = UIElement_Text::GetText(this->m_itemInscriptionText, &result);
    PStringBase<unsigned short>::to_spstring(v2, &v23, 0);
    v3 = v23.m_charbuffer;
    AC1Legacy::PStringBase<char>::PStringBase<char>(&new_inscription, v23.m_charbuffer->m_data);
    v4 = (int)&v3[-2].m_data[12];
    if ( !InterlockedDecrement((volatile LONG *)(v4 + 4)) && v4 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v4)(v4, 1);
    v5 = (char *)&result.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&result.m_charbuffer[-1].m_data[8]) && v5 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v5)(v5, 1);
    AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&v23, &name);
    if ( !AC1Legacy::PStringBase<char>::operator==(&new_inscription, (AC1Legacy::PStringBase<char> *)&v23) )
      goto LABEL_43;
    AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&result, &name);
    v6 = AC1Legacy::PStringBase<char>::operator==(&v1->m_scribe_name, (AC1Legacy::PStringBase<char> *)&result);
    v7 = result.m_charbuffer;
    v8 = v6;
    if ( !InterlockedDecrement((volatile LONG *)&result.m_charbuffer->m_data[2]) && v7 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))&v7->m_data[0])(v7, 1);
    if ( v8 )
      v9 = 0;
    else
LABEL_43:
      v9 = 1;
    v10 = v23.m_charbuffer;
    if ( !InterlockedDecrement((volatile LONG *)&v23.m_charbuffer->m_data[4]) && v10 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))&v10->m_data[0])(v10, 1);
    if ( v9 && AC1Legacy::PStringBase<char>::operator!=(&new_inscription, &v1->m_old_inscription) )
      CM_Writing::Event_SetInscription(v1->cur_objid, &new_inscription);
    AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&v23, &name);
    v11 = AC1Legacy::PStringBase<char>::operator==(&new_inscription, (AC1Legacy::PStringBase<char> *)&v23);
    v12 = v23.m_charbuffer;
    v13 = v11;
    if ( !InterlockedDecrement((volatile LONG *)&v23.m_charbuffer->m_data[4]) && v12 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))&v12->m_data[0])(v12, 1);
    if ( v13 )
    {
      ((void (__stdcall *)(signed int))v1->m_itemInscriptionText->vfptr[13].__vecDelDtor)(268435536);
      PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&v23, L"<Inscribe here>");
      UIElement_Text::SetText(v1->m_itemInscriptionText, (PStringBase<unsigned short> *)&v23);
      v14 = &v23.m_charbuffer[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v23.m_charbuffer[-1]) && v14 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v14)(v14, 1);
      UIElement_Text::ClearAllText(v1->m_itemInscriptionSignatureText);
      AC1Legacy::PStringBase<char>::set(&v1->m_scribe_name, &name);
      AC1Legacy::PStringBase<char>::set(&v1->m_scribe_account, &name);
    }
    else
    {
      if ( SmartBox::smartbox )
        v15 = SmartBox::smartbox->player_id;
      else
        v15 = 0;
      v16 = ACCWeenieObject::GetObjectName((ACCWeenieObject *)v15, 0, 0);
      AC1Legacy::PStringBase<char>::set(&v1->m_scribe_name, v16);
    }
    v17 = v1->m_old_inscription.m_buffer;
    v18 = new_inscription.m_buffer;
    if ( v17 != new_inscription.m_buffer )
    {
      if ( !InterlockedDecrement((volatile LONG *)&v17->m_cRef) && v17 )
        v17->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v17, 1u);
      v19 = new_inscription.m_buffer;
      v1->m_old_inscription.m_buffer = new_inscription.m_buffer;
      InterlockedIncrement((volatile LONG *)&v19->m_cRef);
      v18 = new_inscription.m_buffer;
    }
    v20 = v18;
    if ( !InterlockedDecrement((volatile LONG *)&v18->m_cRef) )
    {
      if ( v20 )
        v20->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v20, 1u);
    }
  }
}

//----- (004AE880) --------------------------------------------------------
int __thiscall ItemExamineUI::Appraisal_ShowSet(ItemExamineUI *this, AppraisalProfile *_prof)
{
  PSRefBufferCharData<char> *v2; // ebp@2
  bool v3; // bl@5
  char *v4; // esi@5
  const unsigned __int16 *v5; // eax@9
  char *v6; // esi@9
  PSRefBufferCharData<char> *v7; // ebp@12
  char *v8; // esi@12
  char *v10; // esi@132
  int setBonus; // [sp+10h] [bp-10h]@1
  PStringBase<char> rhs; // [sp+14h] [bp-Ch]@5
  PStringBase<char> set_string; // [sp+18h] [bp-8h]@2
  ItemExamineUI *v14; // [sp+1Ch] [bp-4h]@1

  v14 = this;
  setBonus = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x109u, &setBonus) )
  {
    v2 = PStringBase<char>::s_NullBuffer.m_charbuffer;
    set_string.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    _prof = (AppraisalProfile *)PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    switch ( setBonus )
    {
      case 4:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Carraida's Benediction");
        goto LABEL_4;
      case 5:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Noble Relic");
        goto LABEL_4;
      case 6:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Ancient Relic");
        goto LABEL_4;
      case 7:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Alduressa Relic");
        goto LABEL_4;
      case 8:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Shou-jen");
        goto LABEL_4;
      case 9:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Empyrean Rings");
        goto LABEL_4;
      case 10:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Arm, Mind, Heart");
        goto LABEL_4;
      case 11:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Coat of Perfect Light");
        goto LABEL_4;
      case 12:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Leggings of Perfect Light");
        goto LABEL_4;
      case 13:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Soldier's");
        goto LABEL_4;
      case 14:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Adept's");
        goto LABEL_4;
      case 15:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Archer's");
        goto LABEL_4;
      case 16:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Defender's");
        goto LABEL_4;
      case 17:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Tinker's");
        goto LABEL_4;
      case 18:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Crafter's");
        goto LABEL_4;
      case 19:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Hearty");
        goto LABEL_4;
      case 20:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Dexterous");
        goto LABEL_4;
      case 21:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Wise");
        goto LABEL_4;
      case 22:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Swift");
        goto LABEL_4;
      case 23:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Hardened");
        goto LABEL_4;
      case 24:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Reinforced");
        goto LABEL_4;
      case 25:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Interlocking");
        goto LABEL_4;
      case 26:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Flame Proof");
        goto LABEL_4;
      case 27:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Acid Proof");
        goto LABEL_4;
      case 28:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Cold Proof");
        goto LABEL_4;
      case 29:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Lightning Proof");
        goto LABEL_4;
      case 30:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Dedication");
        goto LABEL_4;
      case 31:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Gladiatorial Clothing");
        goto LABEL_4;
      case 32:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Ceremonial Clothing");
        goto LABEL_4;
      case 33:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Protective Clothing");
        goto LABEL_4;
      case 35:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Sigil of Defense");
        goto LABEL_4;
      case 36:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Sigil of Destruction");
        goto LABEL_4;
      case 37:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Sigil of Fury");
        goto LABEL_4;
      case 38:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Sigil of Growth");
        goto LABEL_4;
      case 39:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Sigil of Vigor");
        goto LABEL_4;
      case 40:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Heroic Protector");
        goto LABEL_4;
      case 41:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Heroic Destroyer");
        goto LABEL_4;
      case 49:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Alchemy");
        goto LABEL_4;
      case 50:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Arcane Lore");
        goto LABEL_4;
      case 51:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Armor Tinkering");
        goto LABEL_4;
      case 83:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Assess Creature");
        goto LABEL_4;
      case 52:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Assess Person");
        goto LABEL_4;
      case 55:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Cooking");
        goto LABEL_4;
      case 56:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Creature Enchantment");
        goto LABEL_4;
      case 58:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Finesse Weapons");
        goto LABEL_4;
      case 59:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Deception");
        goto LABEL_4;
      case 84:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Dirty Fighting");
        goto LABEL_4;
      case 85:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Dual Wield");
        goto LABEL_4;
      case 60:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Fletching");
        goto LABEL_4;
      case 61:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Healing");
        goto LABEL_4;
      case 62:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Item Enchantment");
        goto LABEL_4;
      case 63:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Item Tinkering");
        goto LABEL_4;
      case 64:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Leadership");
        goto LABEL_4;
      case 65:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Life Magic");
        goto LABEL_4;
      case 66:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Loyalty");
        goto LABEL_4;
      case 68:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Magic Defense");
        goto LABEL_4;
      case 69:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Magic Item Tinkering");
        goto LABEL_4;
      case 70:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Mana Conversion");
        goto LABEL_4;
      case 71:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Melee Defense");
        goto LABEL_4;
      case 72:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Missile Defense");
        goto LABEL_4;
      case 86:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Recklessness");
        goto LABEL_4;
      case 73:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Salvaging");
        goto LABEL_4;
      case 87:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Shield");
        goto LABEL_4;
      case 88:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Sneak Attack");
        goto LABEL_4;
      case 76:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Heavy Weapons");
        goto LABEL_4;
      case 54:
      case 57:
      case 77:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Missile Weapons");
        goto LABEL_4;
      case 78:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Two Handed Combat");
        goto LABEL_4;
      case 53:
      case 67:
      case 74:
      case 75:
      case 79:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Light Weapons");
        goto LABEL_4;
      case 80:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Void Magic");
        goto LABEL_4;
      case 81:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of War Magic");
        goto LABEL_4;
      case 82:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Weapon Tinkering");
        goto LABEL_4;
      case 89:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Shou-jen Shozoku");
        goto LABEL_4;
      case 90:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Weave of Summoning");
        goto LABEL_4;
      case 91:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Shrouded Soul");
        goto LABEL_4;
      case 92:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Darkened Mind");
        goto LABEL_4;
      case 93:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Clouded Spirit");
        goto LABEL_4;
      case 94:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Stinging Shrouded Soul");
        goto LABEL_4;
      case 95:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Sparking Shrouded Soul");
        goto LABEL_4;
      case 96:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Smoldering Shrouded Soul");
        goto LABEL_4;
      case 97:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Shivering Shrouded Soul");
        goto LABEL_4;
      case 98:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Stinging Darkened Mind");
        goto LABEL_4;
      case 99:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Sparking Darkened Mind");
        goto LABEL_4;
      case 100:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Smoldering Darkened Mind");
        goto LABEL_4;
      case 101:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Shivering Darkened Mind");
        goto LABEL_4;
      case 102:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Stinging Clouded Spirit");
        goto LABEL_4;
      case 103:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Sparking Clouded Spirit");
        goto LABEL_4;
      case 104:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Smoldering Clouded Spirit");
        goto LABEL_4;
      case 105:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Minor Shivering Clouded Spirit");
        goto LABEL_4;
      case 106:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Stinging Shrouded Soul");
        goto LABEL_4;
      case 107:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Sparking Shrouded Soul");
        goto LABEL_4;
      case 108:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Smoldering Shrouded Soul");
        goto LABEL_4;
      case 109:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Shivering Shrouded Soul");
        goto LABEL_4;
      case 110:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Stinging Darkened Mind");
        goto LABEL_4;
      case 111:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Sparking Darkened Mind");
        goto LABEL_4;
      case 112:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Smoldering Darkened Mind");
        goto LABEL_4;
      case 113:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Shivering Darkened Mind");
        goto LABEL_4;
      case 114:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Stinging Clouded Spirit");
        goto LABEL_4;
      case 115:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Sparking Clouded Spirit");
        goto LABEL_4;
      case 116:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Smoldering Clouded Spirit");
        goto LABEL_4;
      case 117:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Major Shivering Clouded Spirit");
        goto LABEL_4;
      case 118:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Stinging Shrouded Soul");
        goto LABEL_4;
      case 119:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Sparking Shrouded Soul");
        goto LABEL_4;
      case 120:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Smoldering Shrouded Soul");
        goto LABEL_4;
      case 121:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Shivering Shrouded Soul");
        goto LABEL_4;
      case 122:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Stinging Darkened Mind");
        goto LABEL_4;
      case 123:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Sparking Darkened Mind");
        goto LABEL_4;
      case 124:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Smoldering Darkened Mind");
        goto LABEL_4;
      case 125:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Shivering Darkened Mind");
        goto LABEL_4;
      case 126:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Stinging Clouded Spirit");
        goto LABEL_4;
      case 127:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Sparking Clouded Spirit");
        goto LABEL_4;
      case 128:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Smoldering Clouded Spirit");
        goto LABEL_4;
      case 129:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Blackfire Shivering Clouded Spirit");
        goto LABEL_4;
      case 130:
        PStringBase<char>::set((PStringBase<char> *)&_prof, "Shimmering Shadows");
LABEL_4:
        if ( setBonus <= 0 )
          goto LABEL_132;
        PStringBase<char>::PStringBase<char>(&rhs, &name);
        v3 = PStringBase<char>::operator!=((PStringBase<char> *)&_prof, &rhs);
        v4 = &rhs.m_charbuffer[-2].m_data[12];
        if ( !InterlockedDecrement((volatile LONG *)&rhs.m_charbuffer[-1]) && v4 )
          (**(void (__thiscall ***)(char *, signed int))v4)(v4, 1);
        if ( !v3 )
          goto LABEL_132;
        v5 = (const unsigned __int16 *)operator+(&rhs, "Set: ", (PStringBase<char> *)&_prof);
        PStringBase<unsigned short>::operator=((PStringBase<unsigned short> *)&set_string, v5);
        v6 = &rhs.m_charbuffer[-2].m_data[12];
        if ( !InterlockedDecrement((volatile LONG *)&rhs.m_charbuffer[-1]) && v6 )
          (**(void (__thiscall ***)(char *, signed int))v6)(v6, 1);
        v7 = set_string.m_charbuffer;
        ItemExamineUI::AddItemInfo(v14, set_string.m_charbuffer->m_data, 0, 1);
        v8 = (char *)&_prof[-1].base_armor_wrist;
        if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v8 )
          (**(void (__thiscall ***)(char *, signed int))v8)(v8, 1);
        if ( !InterlockedDecrement((volatile LONG *)&v7[-1]) && v7 != (PSRefBufferCharData<char> *)20 )
          (**(void (__thiscall ***)(char *, signed int))&v7[-2].m_data[12])(&v7[-2].m_data[12], 1);
        return 1;
      default:
        setBonus = 0;
LABEL_132:
        v10 = (char *)&_prof[-1].base_armor_wrist;
        if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v10 )
          (**(void (__thiscall ***)(char *, signed int))v10)(v10, 1);
        if ( !InterlockedDecrement((volatile LONG *)&v2[-1]) && v2 != (PSRefBufferCharData<char> *)20 )
          (**(void (__thiscall ***)(char *, signed int))&v2[-2].m_data[12])(&v2[-2].m_data[12], 1);
        break;
    }
  }
  return 0;
}

//----- (004AF080) --------------------------------------------------------
int __thiscall ItemExamineUI::Appraisal_ShowRatings(ItemExamineUI *this, AppraisalProfile *_prof)
{
  AppraisalProfile *v2; // esi@1
  signed int v3; // esi@1
  PSRefBufferCharData<char> *v4; // eax@2
  int v5; // ecx@2
  int v6; // edi@4
  PSRefBufferCharData<char> *v7; // ecx@9
  int v8; // eax@9
  int v9; // esi@11
  PSRefBufferCharData<char> *v10; // eax@14
  int v11; // ecx@14
  int v12; // edi@16
  PSRefBufferCharData<char> *v13; // ecx@21
  int v14; // eax@21
  int v15; // esi@23
  PSRefBufferCharData<char> *v16; // eax@26
  int v17; // ecx@26
  int v18; // edi@28
  PSRefBufferCharData<char> *v19; // ecx@33
  int v20; // eax@33
  int v21; // esi@35
  PSRefBufferCharData<char> *v22; // eax@38
  int v23; // ecx@38
  int v24; // edi@40
  PSRefBufferCharData<char> *v25; // ecx@45
  int v26; // eax@45
  int v27; // esi@47
  PSRefBufferCharData<char> *v28; // eax@50
  int v29; // ecx@50
  int v30; // edi@52
  PSRefBufferCharData<char> *v31; // ecx@57
  int v32; // eax@57
  int v33; // esi@59
  PSRefBufferCharData<char> *v34; // eax@62
  int v35; // ecx@62
  int v36; // edi@64
  PSRefBufferCharData<char> *v37; // ecx@69
  int v38; // eax@69
  int v39; // esi@71
  PSRefBufferCharData<char> *v40; // eax@74
  int v41; // ecx@74
  int v42; // edi@76
  PSRefBufferCharData<char> *v43; // ecx@81
  int v44; // eax@81
  int v45; // esi@83
  PSRefBufferCharData<char> *v46; // eax@86
  int v47; // ecx@86
  int v48; // edi@88
  PSRefBufferCharData<char> *v49; // ecx@93
  int v50; // eax@93
  int v51; // esi@95
  PSRefBufferCharData<char> *v52; // eax@98
  int v53; // ecx@98
  int v54; // edi@100
  PStringBase<char> *v55; // eax@104
  char *v56; // edi@104
  char *v57; // edi@107
  char *v58; // edi@110
  PSRefBufferCharData<char> *v59; // edi@113
  int v60; // edi@113
  char *v61; // edi@117
  char *v62; // esi@122
  int v63; // eax@125
  char *v64; // esi@126
  int gear_max_health; // [sp+50h] [bp-3Ch]@1
  int damage_rating; // [sp+54h] [bp-38h]@1
  PStringBase<char> vitality_info; // [sp+58h] [bp-34h]@2
  int damage_resist_rating; // [sp+5Ch] [bp-30h]@1
  int crit_rating; // [sp+60h] [bp-2Ch]@1
  int crit_damage_rating; // [sp+64h] [bp-28h]@1
  int crit_resist_rating; // [sp+68h] [bp-24h]@1
  int crit_damage_resist_rating; // [sp+6Ch] [bp-20h]@1
  int healing_boost_rating; // [sp+70h] [bp-1Ch]@1
  int nether_resist_rating; // [sp+74h] [bp-18h]@1
  int life_resist_rating; // [sp+78h] [bp-14h]@1
  ItemExamineUI *v76; // [sp+7Ch] [bp-10h]@1
  PStringBase<char> result; // [sp+80h] [bp-Ch]@9
  PStringBase<char> v78; // [sp+84h] [bp-8h]@104
  PStringBase<char> info_string; // [sp+88h] [bp-4h]@107

  v2 = _prof;
  v76 = this;
  damage_rating = 0;
  damage_resist_rating = 0;
  crit_rating = 0;
  crit_damage_rating = 0;
  crit_resist_rating = 0;
  crit_damage_resist_rating = 0;
  healing_boost_rating = 0;
  nether_resist_rating = 0;
  life_resist_rating = 0;
  gear_max_health = 0;
  AppraisalProfile::InqInt(_prof, 0x172u, &damage_rating);
  AppraisalProfile::InqInt(v2, 0x173u, &damage_resist_rating);
  AppraisalProfile::InqInt(v2, 0x174u, &crit_rating);
  AppraisalProfile::InqInt(v2, 0x176u, &crit_damage_rating);
  AppraisalProfile::InqInt(v2, 0x175u, &crit_resist_rating);
  AppraisalProfile::InqInt(v2, 0x177u, &crit_damage_resist_rating);
  AppraisalProfile::InqInt(v2, 0x178u, &healing_boost_rating);
  AppraisalProfile::InqInt(v2, 0x17Au, &life_resist_rating);
  AppraisalProfile::InqInt(v2, 0x179u, &nether_resist_rating);
  AppraisalProfile::InqInt(v2, 0x17Bu, &gear_max_health);
  _prof = (AppraisalProfile *)PStringBase<char>::s_NullBuffer.m_charbuffer;
  InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
  v3 = 0;
  if ( damage_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    PStringBase<char>::sprintf(&vitality_info, "Dam %d", damage_rating);
    v4 = vitality_info.m_charbuffer;
    v5 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v5 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v5 - 1);
      v4 = vitality_info.m_charbuffer;
    }
    v6 = (int)&v4[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v4[-1]) && v6 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v6)(v6, 1);
  }
  if ( damage_resist_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v7 = result.m_charbuffer;
      v8 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v8 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v8 - 1);
        v7 = result.m_charbuffer;
      }
      v9 = (int)&v7[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v7[-1]) && v9 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v9)(v9, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Dam Resist %d", damage_resist_rating);
    v10 = vitality_info.m_charbuffer;
    v11 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v11 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v11 - 1);
      v10 = vitality_info.m_charbuffer;
    }
    v12 = (int)&v10[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v10[-1]) && v12 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v12)(v12, 1);
  }
  if ( crit_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v13 = result.m_charbuffer;
      v14 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v14 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v14 - 1);
        v13 = result.m_charbuffer;
      }
      v15 = (int)&v13[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v13[-1]) && v15 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v15)(v15, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Crit %d", crit_rating);
    v16 = vitality_info.m_charbuffer;
    v17 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v17 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v17 - 1);
      v16 = vitality_info.m_charbuffer;
    }
    v18 = (int)&v16[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v16[-1]) && v18 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v18)(v18, 1);
  }
  if ( crit_damage_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v19 = result.m_charbuffer;
      v20 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v20 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v20 - 1);
        v19 = result.m_charbuffer;
      }
      v21 = (int)&v19[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v19[-1]) && v21 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v21)(v21, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Crit Dam %d", crit_damage_rating);
    v22 = vitality_info.m_charbuffer;
    v23 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v23 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v23 - 1);
      v22 = vitality_info.m_charbuffer;
    }
    v24 = (int)&v22[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v22[-1]) && v24 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v24)(v24, 1);
  }
  if ( crit_resist_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v25 = result.m_charbuffer;
      v26 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v26 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v26 - 1);
        v25 = result.m_charbuffer;
      }
      v27 = (int)&v25[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v25[-1]) && v27 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v27)(v27, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Crit Resist %d", crit_resist_rating);
    v28 = vitality_info.m_charbuffer;
    v29 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v29 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v29 - 1);
      v28 = vitality_info.m_charbuffer;
    }
    v30 = (int)&v28[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v28[-1]) && v30 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v30)(v30, 1);
  }
  if ( crit_damage_resist_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v31 = result.m_charbuffer;
      v32 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v32 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v32 - 1);
        v31 = result.m_charbuffer;
      }
      v33 = (int)&v31[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v31[-1]) && v33 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v33)(v33, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Crit Dam Resist %d", crit_damage_resist_rating);
    v34 = vitality_info.m_charbuffer;
    v35 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v35 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v35 - 1);
      v34 = vitality_info.m_charbuffer;
    }
    v36 = (int)&v34[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v34[-1]) && v36 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v36)(v36, 1);
  }
  if ( healing_boost_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v37 = result.m_charbuffer;
      v38 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v38 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v38 - 1);
        v37 = result.m_charbuffer;
      }
      v39 = (int)&v37[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v37[-1]) && v39 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v39)(v39, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Heal Boost %d", healing_boost_rating);
    v40 = vitality_info.m_charbuffer;
    v41 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v41 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v41 - 1);
      v40 = vitality_info.m_charbuffer;
    }
    v42 = (int)&v40[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v40[-1]) && v42 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v42)(v42, 1);
  }
  if ( nether_resist_rating > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v43 = result.m_charbuffer;
      v44 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v44 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v44 - 1);
        v43 = result.m_charbuffer;
      }
      v45 = (int)&v43[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v43[-1]) && v45 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v45)(v45, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Nether Resist %d", nether_resist_rating);
    v46 = vitality_info.m_charbuffer;
    v47 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v47 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v47 - 1);
      v46 = vitality_info.m_charbuffer;
    }
    v48 = (int)&v46[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v46[-1]) && v48 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v48)(v48, 1);
  }
  if ( life_resist_rating <= 0 )
  {
    if ( !v3 )
      goto LABEL_116;
  }
  else
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( v3 )
    {
      PStringBase<char>::PStringBase<char>(&result, ", ");
      v49 = result.m_charbuffer;
      v50 = *(_DWORD *)&result.m_charbuffer[-1].m_data[12];
      if ( v50 != 1 )
      {
        PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, result.m_charbuffer->m_data, v50 - 1);
        v49 = result.m_charbuffer;
      }
      v51 = (int)&v49[-2].m_data[12];
      if ( !InterlockedDecrement((volatile LONG *)&v49[-1]) && v51 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v51)(v51, 1);
    }
    PStringBase<char>::sprintf(&vitality_info, "Life Resist %d", life_resist_rating);
    v52 = vitality_info.m_charbuffer;
    v53 = *(_DWORD *)&vitality_info.m_charbuffer[-1].m_data[12];
    if ( v53 != 1 )
    {
      PStringBase<char>::append_n_chars((PStringBase<char> *)&_prof, vitality_info.m_charbuffer->m_data, v53 - 1);
      v52 = vitality_info.m_charbuffer;
    }
    v54 = (int)&v52[-2].m_data[12];
    v3 = 1;
    if ( !InterlockedDecrement((volatile LONG *)&v52[-1]) && v54 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v54)(v54, 1);
  }
  PStringBase<char>::PStringBase<char>(&vitality_info, ".");
  PStringBase<char>::PStringBase<char>(&v78, "Ratings: ");
  PStringBase<char>::operator+(v55, &result, (PStringBase<char> *)&_prof);
  v56 = &v78.m_charbuffer[-2].m_data[12];
  if ( !InterlockedDecrement((volatile LONG *)&v78.m_charbuffer[-1]) && v56 )
    (**(void (__thiscall ***)(char *, signed int))v56)(v56, 1);
  PStringBase<char>::operator+(&result, &info_string, &vitality_info);
  v57 = &result.m_charbuffer[-2].m_data[12];
  if ( !InterlockedDecrement((volatile LONG *)&result.m_charbuffer[-1]) && v57 )
    (**(void (__thiscall ***)(char *, signed int))v57)(v57, 1);
  v58 = &vitality_info.m_charbuffer[-2].m_data[12];
  if ( !InterlockedDecrement((volatile LONG *)&vitality_info.m_charbuffer[-1]) && v58 )
    (**(void (__thiscall ***)(char *, signed int))v58)(v58, 1);
  v59 = info_string.m_charbuffer;
  ItemExamineUI::AddItemInfo(v76, info_string.m_charbuffer->m_data, 0, 1);
  v60 = (int)&v59[-2].m_data[12];
  if ( !InterlockedDecrement((volatile LONG *)(v60 + 4)) && v60 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v60)(v60, 1);
LABEL_116:
  if ( gear_max_health > 0 )
  {
    vitality_info.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    PStringBase<char>::sprintf(&vitality_info, "This item adds %d Vitality.", gear_max_health);
    ItemExamineUI::AddItemInfo(v76, vitality_info.m_charbuffer->m_data, 0, 1);
    v61 = &vitality_info.m_charbuffer[-2].m_data[12];
    if ( !InterlockedDecrement((volatile LONG *)&vitality_info.m_charbuffer[-1]) )
    {
      if ( v61 )
        (**(void (__thiscall ***)(char *, signed int))v61)(v61, 1);
    }
  }
  if ( v3 || gear_max_health > 0 )
  {
    ItemExamineUI::AddItemInfo(v76, &name, 0, 1);
    v64 = (char *)&_prof[-1].base_armor_wrist;
    if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) && v64 )
      (**(void (__thiscall ***)(char *, signed int))v64)(v64, 1);
    v63 = 1;
  }
  else
  {
    v62 = (char *)&_prof[-1].base_armor_wrist;
    if ( !InterlockedDecrement(&_prof[-1].base_armor_hand) )
    {
      if ( v62 )
        (**(void (__thiscall ***)(char *, signed int))v62)(v62, 1);
    }
    v63 = 0;
  }
  return v63;
}

//----- (004AF930) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowUsage(ItemExamineUI *this, unsigned int lm, AppraisalProfile *_prof)
{
  ItemExamineUI *v3; // esi@1
  AC1Legacy::PSRefBuffer<char> *v4; // esi@3
  AC1Legacy::PStringBase<char> strUsage; // [sp+0h] [bp-4h]@1

  strUsage.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  v3 = this;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( AppraisalProfile::InqString(_prof, 0xEu, &strUsage) )
    ItemExamineUI::AddItemInfo(v3, strUsage.m_buffer->m_data, 0, 0);
  v4 = strUsage.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&strUsage.m_buffer->m_cRef) )
  {
    if ( v4 )
      v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004AF9A0) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowWieldRequirements(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // ebx@1
  AC1Legacy::PStringBase<char> *v3; // eax@3
  AC1Legacy::PSRefBuffer<char> *v4; // esi@3
  AC1Legacy::PSRefBuffer<char> *v5; // esi@6
  AC1Legacy::PSRefBuffer<char> *v6; // esi@9
  unsigned int v7; // esi@14
  AC1Legacy::PSRefBuffer<char> *v8; // esi@16
  AC1Legacy::PSRefBuffer<char> *v9; // esi@21
  AC1Legacy::PSRefBuffer<char> *v10; // esi@24
  int v11; // eax@32
  AC1Legacy::PSRefBuffer<char> *v12; // esi@43
  int v13; // eax@47
  int v14; // eax@59
  int v15; // eax@71
  char *v16; // [sp-8h] [bp-82Ch]@35
  char *v17; // [sp-8h] [bp-82Ch]@50
  char *v18; // [sp-8h] [bp-82Ch]@62
  char *v19; // [sp-8h] [bp-82Ch]@74
  const char *v20; // [sp+0h] [bp-824h]@35
  const char *v21; // [sp+0h] [bp-824h]@50
  const char *v22; // [sp+0h] [bp-824h]@62
  const char *v23; // [sp+0h] [bp-824h]@74
  char *v24; // [sp+4h] [bp-820h]@35
  char *v25; // [sp+4h] [bp-820h]@50
  char *v26; // [sp+4h] [bp-820h]@62
  char *v27; // [sp+4h] [bp-820h]@74
  AC1Legacy::PStringBase<char> strSkill; // [sp+18h] [bp-80Ch]@3
  int iDiff; // [sp+1Ch] [bp-808h]@29
  unsigned int iReq; // [sp+20h] [bp-804h]@27
  int iSkill; // [sp+24h] [bp-800h]@28
  unsigned int iAcctReqs; // [sp+28h] [bp-7FCh]@12
  AC1Legacy::PStringBase<char> heritage_specific_msg; // [sp+2Ch] [bp-7F8h]@3
  unsigned int heritage_specific; // [sp+30h] [bp-7F4h]@19
  int has_allowed_wielder; // [sp+34h] [bp-7F0h]@1
  AC1Legacy::PStringBase<char> v36; // [sp+38h] [bp-7ECh]@3
  char numtxt[2024]; // [sp+3Ch] [bp-7E8h]@31

  v2 = this;
  has_allowed_wielder = 0;
  if ( AppraisalProfile::InqBool(_prof, 0x55u, &has_allowed_wielder) && has_allowed_wielder == 1 )
  {
    AC1Legacy::PStringBase<char>::PStringBase<char>(&strSkill, "the original owner");
    AppraisalProfile::InqString(_prof, 0x19u, &strSkill);
    AC1Legacy::PStringBase<char>::PStringBase<char>(&v36, "Wield requires ");
    AC1Legacy::PStringBase<char>::operator+(v3, &heritage_specific_msg, &strSkill);
    v4 = v36.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&v36.m_buffer->m_cRef) && v4 )
      v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
    v5 = heritage_specific_msg.m_buffer;
    ItemExamineUI::AddItemInfo(v2, heritage_specific_msg.m_buffer->m_data, 0, 1);
    if ( !InterlockedDecrement((volatile LONG *)&v5->m_cRef) && v5 )
      v5->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v5, 1u);
    v6 = strSkill.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&strSkill.m_buffer->m_cRef) && v6 )
      v6->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v6, 1u);
  }
  iAcctReqs = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x1Au, (int *)&iAcctReqs) && iAcctReqs )
  {
    strSkill.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    v7 = iAcctReqs;
    AC1Legacy::PStringBase<char>::set(&strSkill, &name);
    if ( v7 == 1 )
      AC1Legacy::PStringBase<char>::set(&strSkill, "Use requires Throne of Destiny.");
    v8 = strSkill.m_buffer;
    ItemExamineUI::AddItemInfo(v2, strSkill.m_buffer->m_data, 0, 1);
    if ( !InterlockedDecrement((volatile LONG *)&v8->m_cRef) && v8 )
      v8->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v8, 1u);
  }
  heritage_specific = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x144u, (int *)&heritage_specific) )
  {
    strSkill.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( AppraisalSystem::InqHeritageGroupDisplayName(heritage_specific, &strSkill) )
    {
      AC1Legacy::operator+(&heritage_specific_msg, "Wield requires ", &strSkill);
      v9 = heritage_specific_msg.m_buffer;
      ItemExamineUI::AddItemInfo(v2, heritage_specific_msg.m_buffer->m_data, 0, 1);
      if ( !InterlockedDecrement((volatile LONG *)&v9->m_cRef) )
      {
        if ( v9 )
          v9->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v9, 1u);
      }
    }
    v10 = strSkill.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&strSkill.m_buffer->m_cRef) && v10 )
      v10->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v10, 1u);
  }
  if ( AppraisalProfile::InqInt(_prof, 0x9Eu, (int *)&iReq)
    && AppraisalProfile::InqInt(_prof, 0x9Fu, &iSkill)
    && AppraisalProfile::InqInt(_prof, 0xA0u, &iDiff) )
  {
    strSkill.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    ItemExamineUI::GetAppraisalStringFromRequirements(iReq, iSkill, iDiff, &strSkill);
    switch ( iReq )
    {
      case 1u:
      case 2u:
      case 3u:
      case 4u:
      case 5u:
      case 6u:
      case 7u:
      case 9u:
      case 0xAu:
        __snprintf(numtxt, 0x7E8u, "Wield requires %s %d", strSkill.m_buffer->m_data, iDiff);
        goto LABEL_38;
      case 8u:
        v11 = (int)"specialized";
        if ( iDiff != 3 )
          v11 = (int)"trained";
        __snprintf(numtxt, 0x7E8u, "Wield requires %s %s", v11, strSkill.m_buffer->m_data);
        goto LABEL_38;
      case 0xBu:
        v24 = strSkill.m_buffer->m_data;
        v20 = "Wield requires %s type";
        v16 = numtxt;
        goto LABEL_37;
      case 0xCu:
        v24 = strSkill.m_buffer->m_data;
        v20 = "Wield requires %s race";
        v16 = numtxt;
LABEL_37:
        __snprintf(v16, 0x7E8u, v20, v24);
LABEL_38:
        ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&strSkill);
        goto LABEL_39;
      default:
        v12 = strSkill.m_buffer;
        if ( !InterlockedDecrement((volatile LONG *)&strSkill.m_buffer->m_cRef) && v12 )
          v12->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v12, 1u);
        break;
    }
  }
  else
  {
LABEL_39:
    if ( AppraisalProfile::InqInt(_prof, 0x10Eu, (int *)&iReq)
      && AppraisalProfile::InqInt(_prof, 0x10Fu, &iSkill)
      && AppraisalProfile::InqInt(_prof, 0x110u, &iDiff) )
    {
      strSkill.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      ItemExamineUI::GetAppraisalStringFromRequirements(iReq, iSkill, iDiff, &strSkill);
      switch ( iReq )
      {
        case 1u:
        case 2u:
        case 3u:
        case 4u:
        case 5u:
        case 6u:
        case 7u:
        case 9u:
        case 0xAu:
          __snprintf(numtxt, 0x7E8u, "Wield requires %s %d", strSkill.m_buffer->m_data, iDiff);
          goto LABEL_53;
        case 8u:
          v13 = (int)"specialized";
          if ( iDiff != 3 )
            v13 = (int)"trained";
          __snprintf(numtxt, 0x7E8u, "Wield requires %s %s", v13, strSkill.m_buffer->m_data);
          goto LABEL_53;
        case 0xBu:
          v25 = strSkill.m_buffer->m_data;
          v21 = "Wield requires %s type";
          v17 = numtxt;
          break;
        case 0xCu:
          v25 = strSkill.m_buffer->m_data;
          v21 = "Wield requires %s race";
          v17 = numtxt;
          break;
        default:
          goto LABEL_78;
      }
      __snprintf(v17, 0x7E8u, v21, v25);
LABEL_53:
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&strSkill);
    }
    if ( AppraisalProfile::InqInt(_prof, 0x111u, (int *)&iReq)
      && AppraisalProfile::InqInt(_prof, 0x112u, &iSkill)
      && AppraisalProfile::InqInt(_prof, 0x113u, &iDiff) )
    {
      strSkill.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      ItemExamineUI::GetAppraisalStringFromRequirements(iReq, iSkill, iDiff, &strSkill);
      switch ( iReq )
      {
        case 1u:
        case 2u:
        case 3u:
        case 4u:
        case 5u:
        case 6u:
        case 7u:
        case 9u:
        case 0xAu:
          __snprintf(numtxt, 0x7E8u, "Wield requires %s %d", strSkill.m_buffer->m_data, iDiff);
          goto LABEL_65;
        case 8u:
          v14 = (int)"specialized";
          if ( iDiff != 3 )
            v14 = (int)"trained";
          __snprintf(numtxt, 0x7E8u, "Wield requires %s %s", v14, strSkill.m_buffer->m_data);
          goto LABEL_65;
        case 0xBu:
          v26 = strSkill.m_buffer->m_data;
          v22 = "Wield requires %s type";
          v18 = numtxt;
          break;
        case 0xCu:
          v26 = strSkill.m_buffer->m_data;
          v22 = "Wield requires %s race";
          v18 = numtxt;
          break;
        default:
          goto LABEL_78;
      }
      __snprintf(v18, 0x7E8u, v22, v26);
LABEL_65:
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&strSkill);
    }
    if ( AppraisalProfile::InqInt(_prof, 0x114u, (int *)&iReq)
      && AppraisalProfile::InqInt(_prof, 0x115u, &iSkill)
      && AppraisalProfile::InqInt(_prof, 0x116u, &iDiff) )
    {
      strSkill.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      ItemExamineUI::GetAppraisalStringFromRequirements(iReq, iSkill, iDiff, &strSkill);
      switch ( iReq )
      {
        case 1u:
        case 2u:
        case 3u:
        case 4u:
        case 5u:
        case 6u:
        case 7u:
        case 9u:
        case 0xAu:
          __snprintf(numtxt, 0x7E8u, "Wield requires %s %d", strSkill.m_buffer->m_data, iDiff);
          goto LABEL_77;
        case 8u:
          v15 = (int)"Specialized";
          if ( iDiff != 3 )
            v15 = (int)"Trained";
          __snprintf(numtxt, 0x7E8u, "Wield requires %s %s", v15, strSkill.m_buffer->m_data);
          goto LABEL_77;
        case 0xBu:
          v27 = strSkill.m_buffer->m_data;
          v23 = "Wield requires %s type";
          v19 = numtxt;
          goto LABEL_76;
        case 0xCu:
          v27 = strSkill.m_buffer->m_data;
          v23 = "Wield requires %s race";
          v19 = numtxt;
LABEL_76:
          __snprintf(v19, 0x7E8u, v23, v27);
LABEL_77:
          ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
          break;
        default:
          break;
      }
LABEL_78:
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&strSkill);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B0140) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowSpecialProperties(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // ebx@1
  int v3; // esi@2
  volatile LONG *v4; // edi@2
  int v5; // ebp@2
  AC1Legacy::PStringBase<char> *v6; // eax@9
  AC1Legacy::PSRefBuffer<char> *v7; // esi@9
  AC1Legacy::PStringBase<char> *v8; // eax@12
  AC1Legacy::PSRefBuffer<char> *v9; // esi@12
  LONG (__stdcall *v10)(volatile LONG *); // ebp@12
  AC1Legacy::PSRefBuffer<char> **v11; // edi@12
  int v12; // edi@17
  AC1Legacy::PSRefBuffer<char> *v13; // edi@20
  AC1Legacy::PSRefBuffer<char> *v14; // edi@23
  int v15; // eax@31
  UIElement_Text *v16; // eax@33
  char *v17; // esi@35
  InterfaceSystem *v18; // eax@40
  AC1Legacy::PSRefBuffer<char> *v19; // esi@40
  int v20; // edi@42
  AC1Legacy::PSRefBuffer<char> *v21; // esi@44
  AC1Legacy::PSRefBuffer<char> *v22; // esi@52
  AC1Legacy::PStringBase<unsigned short> *v23; // eax@61
  int v24; // esi@61
  AC1Legacy::PSRefBuffer<char> *v25; // esi@64
  AC1Legacy::PSRefBuffer<char> *v26; // esi@68
  int v27; // ebx@74
  AC1Legacy::PSRefBuffer<char> *v28; // esi@123
  LONG (__stdcall *v29)(volatile LONG *); // ebp@123
  AppraisalProfile *v30; // esi@127
  AC1Legacy::PSRefBuffer<char> *v31; // esi@130
  AC1Legacy::PSRefBuffer<char> *v32; // esi@145
  AC1Legacy::PStringBase<char> *v33; // eax@158
  AC1Legacy::PSRefBuffer<char> **v34; // esi@158
  int v35; // esi@162
  AC1Legacy::PSRefBuffer<char> *v36; // esi@165
  ItemExamineUI *v37; // esi@168
  signed int v38; // edi@168
  char *v39; // esi@177
  char *v40; // esi@180
  AC1Legacy::PSRefBuffer<char> *v41; // esi@183
  int time_4; // [sp+10h] [bp-88Ch]@40
  AC1Legacy::PStringBase<char> strProperties; // [sp+28h] [bp-874h]@1
  AC1Legacy::PStringBase<char> resModStr; // [sp+2Ch] [bp-870h]@9
  AC1Legacy::PStringBase<char> strBonded; // [sp+30h] [bp-86Ch]@2
  int v46; // [sp+34h] [bp-868h]@40
  int imbuedCheck; // [sp+38h] [bp-864h]@74
  int shared_cooldown_id; // [sp+3Ch] [bp-860h]@12
  PStringBase<unsigned short> sTextStr; // [sp+40h] [bp-85Ch]@30
  PStringBase<unsigned short> sTimeStr; // [sp+44h] [bp-858h]@30
  AC1Legacy::PStringBase<char> v51; // [sp+48h] [bp-854h]@9
  AC1Legacy::PStringBase<char> result; // [sp+4Ch] [bp-850h]@9
  int cleaving; // [sp+50h] [bp-84Ch]@51
  ItemExamineUI *v54; // [sp+54h] [bp-848h]@1
  int bAutowieldLeft; // [sp+58h] [bp-844h]@172
  int bDyable; // [sp+5Ch] [bp-840h]@154
  unsigned int creatureType; // [sp+60h] [bp-83Ch]@57
  int bIvoryable; // [sp+64h] [bp-838h]@151
  int damageType; // [sp+68h] [bp-834h]@143
  int iUnique; // [sp+6Ch] [bp-830h]@1
  int retained; // [sp+70h] [bp-82Ch]@134
  int bonded; // [sp+74h] [bp-828h]@127
  int magic_resist; // [sp+78h] [bp-824h]@117
  int attuned; // [sp+7Ch] [bp-820h]@120
  double infoAddedToPanel; // [sp+80h] [bp-81Ch]@1
  int v66; // [sp+88h] [bp-814h]@39
  int attacktype; // [sp+8Ch] [bp-810h]@71
  long double fResMod; // [sp+90h] [bp-80Ch]@143
  long double fCrit; // [sp+98h] [bp-804h]@137
  IDClass<_tagDataID,32,0> spellDID; // [sp+A0h] [bp-7FCh]@149
  long double iCooldown; // [sp+A4h] [bp-7F8h]@30
  long double absorb_magic; // [sp+ACh] [bp-7F0h]@115
  char tmp_txt[2024]; // [sp+B4h] [bp-7E8h]@145

  v2 = this;
  v54 = this;
  ItemExamineUI::AddItemInfo(this, &name, 0, 1);
  strProperties.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  LODWORD(infoAddedToPanel) = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x117u, &iUnique) )
  {
    v3 = AC1Legacy::PStringBase<char>::s_NullBuffer;
    v4 = (volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4);
    strBonded.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    v5 = iUnique;
    if ( v3 != AC1Legacy::PStringBase<char>::s_NullBuffer )
    {
      if ( !InterlockedDecrement(v4) && v3 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v3)(v3, 1);
      strBonded.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    }
    AC1Legacy::PStringBase<char>::append_int32(&strBonded, v5);
    if ( !AC1Legacy::PStringBase<char>::InsertCommas(&strBonded) )
      AC1Legacy::PStringBase<char>::set(&strBonded, "???");
    AC1Legacy::PStringBase<char>::PStringBase<char>(&resModStr, " of these items.");
    AC1Legacy::PStringBase<char>::PStringBase<char>(&v51, "You can only carry ");
    AC1Legacy::PStringBase<char>::operator+(v6, &result, &strBonded);
    v7 = v51.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&v51.m_buffer->m_cRef) && v7 )
      v7->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v7, 1u);
    v8 = AC1Legacy::PStringBase<char>::operator+(
           &result,
           (AC1Legacy::PStringBase<char> *)&shared_cooldown_id,
           &resModStr);
    v9 = strBonded.m_buffer;
    v10 = InterlockedDecrement;
    v11 = (AC1Legacy::PSRefBuffer<char> **)v8;
    if ( strBonded.m_buffer != v8->m_buffer )
    {
      if ( !InterlockedDecrement((volatile LONG *)&strBonded.m_buffer->m_cRef) && v9 )
        v9->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v9, 1u);
      v9 = *v11;
      InterlockedIncrement((volatile LONG *)&(*v11)->m_cRef);
    }
    v12 = shared_cooldown_id;
    if ( !InterlockedDecrement((volatile LONG *)(shared_cooldown_id + 4)) && v12 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v12)(v12, 1);
    v13 = result.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&result.m_buffer->m_cRef) && v13 )
      v13->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v13, 1u);
    v14 = resModStr.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&resModStr.m_buffer->m_cRef) && v14 )
      v14->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v14, 1u);
    ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
    ItemExamineUI::AddItemInfo(v2, v9->m_data, 0, 1);
    if ( !InterlockedDecrement((volatile LONG *)&v9->m_cRef) && v9 )
      v9->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v9, 1u);
  }
  else
  {
    v10 = InterlockedDecrement;
  }
  sTimeStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
  sTextStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
  if ( AppraisalProfile::InqFloat(_prof, 0xA7u, &iCooldown) )
  {
    shared_cooldown_id = (unsigned __int64)iCooldown;
    ClientUISystem::DeltaTimeToString((double)shared_cooldown_id, &sTimeStr);
    PStringBase<unsigned short>::sprintf(&sTextStr, L"Cooldown When Used: ");
    v15 = *(_DWORD *)&sTimeStr.m_charbuffer[-1].m_data[14];
    if ( v15 != 1 )
      PStringBase<unsigned short>::append_n_chars(&sTextStr, sTimeStr.m_charbuffer->m_data, v15 - 1);
    v16 = v2->m_itemDisplayText;
    if ( v16 )
    {
      if ( v16->m_glyphList.m_glyphList._num_elements > 1 )
      {
        PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&resModStr, L"\n");
        UIElement_Text::AppendText(v2->m_itemDisplayText, (PStringBase<unsigned short> *)&resModStr);
        v17 = (char *)&resModStr.m_buffer[-1].m_cRef;
        if ( !v10((volatile LONG *)&resModStr.m_buffer[-1].m_cRef + 1) )
        {
          if ( v17 )
            (**(void (__thiscall ***)(char *, signed int))v17)(v17, 1);
        }
      }
      UIElement_Text::AppendTextWithFont(v2->m_itemDisplayText, &sTextStr, 0, 0);
    }
    HIDWORD(infoAddedToPanel) = 0;
    v66 = 0;
    if ( AppraisalProfile::InqInt(_prof, 0x118u, &shared_cooldown_id) )
    {
      resModStr.m_buffer = 0;
      v18 = InterfaceSystem::GetInstance();
      InterfaceSystem::GetClass(v18, (TResult *)&v51, &PlayerDesc_ClassType_7, (Interface **)&resModStr);
      v19 = resModStr.m_buffer;
      time_4 = (int)resModStr.m_buffer;
      strBonded.m_buffer = 0;
      v46 = 0;
      if ( resModStr.m_buffer )
        ((void (__thiscall *)(AC1Legacy::PSRefBuffer<char> *))resModStr.m_buffer->vfptr[4].__vecDelDtor)(resModStr.m_buffer);
      v20 = *(_DWORD *)InterfacePtr<PlayerDesc>::_QueryInterface(&strBonded, (int)&result, time_4, 0);
      if ( v19 )
        ((void (__thiscall *)(AC1Legacy::PSRefBuffer<char> *))v19->vfptr[5].__vecDelDtor)(v19);
      v21 = strBonded.m_buffer;
      if ( strBonded.m_buffer
        && v20 >= 0
        && CACQualities::HasEnchantmentRegistry((CACQualities *)strBonded.m_buffer)
        && CEnchantmentRegistry::OnCooldown(
             (CEnchantmentRegistry *)v21[4].m_hash,
             shared_cooldown_id + 0x8000,
             (double *)((char *)&infoAddedToPanel + 4)) )
      {
        PStringBase<unsigned short>::clear(&sTimeStr);
        v51.m_buffer = (AC1Legacy::PSRefBuffer<char> *)(unsigned __int64)*(double *)((char *)&infoAddedToPanel + 4);
        ClientUISystem::DeltaTimeToString((double)(signed int)v51.m_buffer, &sTimeStr);
        PStringBase<unsigned short>::sprintf(&sTextStr, L"Cooldown Remaining: ");
        PStringBase<unsigned short>::operator+=(&sTextStr, &sTimeStr);
        ItemExamineUI::AddItemInfo(v2, &sTextStr, 0, 1);
      }
      ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
      if ( v21 )
        ((void (__thiscall *)(AC1Legacy::PSRefBuffer<char> *))v21->vfptr[5].__vecDelDtor)(v21);
    }
  }
  cleaving = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x124u, &cleaving) )
  {
    v22 = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    resModStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( cleaving > 1 )
    {
      AC1Legacy::PStringBase<char>::sprintf(&resModStr, "Cleave: %d enemies in front arc.", cleaving);
      v22 = resModStr.m_buffer;
      ItemExamineUI::AddItemInfo(v2, resModStr.m_buffer->m_data, 0, 1);
      ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
    }
    if ( !v10((volatile LONG *)&v22->m_cRef) && v22 )
      v22->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v22, 1u);
  }
  if ( AppraisalProfile::InqInt(_prof, 0xA6u, (int *)&creatureType) )
  {
    strBonded.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( AppraisalSystem::InqCreatureDisplayName(creatureType, &strBonded) )
    {
      if ( creatureType == 31 )
      {
        AC1Legacy::PStringBase<char>::set(&strBonded, "Bael'Zharon's Hate");
      }
      else
      {
        AC1Legacy::PStringBase<char>::PStringBase<char>(&resModStr, " slayer");
        v23 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                          &strBonded,
                                                          (AC1Legacy::PStringBase<char> *)&shared_cooldown_id,
                                                          &resModStr);
        AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&strBonded, v23);
        v24 = shared_cooldown_id;
        if ( !v10((volatile LONG *)(shared_cooldown_id + 4)) && v24 )
          (**(void (__thiscall ***)(_DWORD, _DWORD))v24)(v24, 1);
        v25 = resModStr.m_buffer;
        if ( !v10((volatile LONG *)&resModStr.m_buffer->m_cRef) && v25 )
          v25->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v25, 1u);
      }
      AppendHelper(&strProperties, strBonded.m_buffer->m_data);
    }
    v26 = strBonded.m_buffer;
    if ( !v10((volatile LONG *)&strBonded.m_buffer->m_cRef) && v26 )
      v26->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v26, 1u);
  }
  if ( AppraisalProfile::InqInt(_prof, 0x2Fu, &attacktype) && attacktype & 0x79E0 )
    AppendHelper(&strProperties, "Multi-Strike");
  v27 = 0;
  imbuedCheck = 0;
  if ( AppraisalProfile::InqInt(_prof, 0xB3u, &imbuedCheck) )
    v27 = imbuedCheck;
  if ( AppraisalProfile::InqInt(_prof, 0x12Fu, &imbuedCheck) )
    v27 |= imbuedCheck;
  if ( AppraisalProfile::InqInt(_prof, 0x130u, &imbuedCheck) )
    v27 |= imbuedCheck;
  if ( AppraisalProfile::InqInt(_prof, 0x131u, &imbuedCheck) )
    v27 |= imbuedCheck;
  if ( AppraisalProfile::InqInt(_prof, 0x132u, &imbuedCheck) )
    v27 |= imbuedCheck;
  if ( v27 )
  {
    if ( v27 & 1 )
      AppendHelper(&strProperties, "Critical Strike");
    if ( v27 & 2 )
      AppendHelper(&strProperties, "Crippling Blow");
    if ( v27 & 4 )
      AppendHelper(&strProperties, "Armor Rending");
    if ( v27 & 8 )
      AppendHelper(&strProperties, "Slash Rending");
    if ( v27 & 0x10 )
      AppendHelper(&strProperties, "Pierce Rending");
    if ( v27 & 0x20 )
      AppendHelper(&strProperties, "Bludgeon Rending");
    if ( v27 & 0x40 )
      AppendHelper(&strProperties, "Acid Rending");
    if ( BYTE1(v27) & 0x40 )
      AppendHelper(&strProperties, "Nether Rending");
    if ( (char)v27 < 0 )
      AppendHelper(&strProperties, "Cold Rending");
    if ( BYTE1(v27) & 1 )
      AppendHelper(&strProperties, "Lightning Rending");
    if ( BYTE1(v27) & 2 )
      AppendHelper(&strProperties, "Fire Rending");
    if ( BYTE1(v27) & 4 )
      AppendHelper(&strProperties, "+1 Melee Defense");
    if ( BYTE1(v27) & 8 )
      AppendHelper(&strProperties, "+1 Missile Defense");
    if ( BYTE1(v27) & 0x10 )
      AppendHelper(&strProperties, "+1 Magic Defense");
    if ( v27 < 0 )
      AppendHelper(&strProperties, "Phantasmal");
  }
  if ( AppraisalProfile::InqFloat(_prof, 0x9Fu, &absorb_magic) )
    AppendHelper(&strProperties, "Magic Absorbing");
  if ( AppraisalProfile::InqInt(_prof, 0x24u, &magic_resist) && magic_resist >= 9999 )
    AppendHelper(&strProperties, "Unenchantable");
  if ( AppraisalProfile::InqInt(_prof, 0x72u, &attuned) )
  {
    strBonded.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( AppraisalSystem::AttunedStatusToString((AttunedStatusEnum)attuned, &strBonded) )
      AppendHelper(&strProperties, strBonded.m_buffer->m_data);
    v28 = strBonded.m_buffer;
    v29 = InterlockedDecrement;
    if ( !InterlockedDecrement((volatile LONG *)&strBonded.m_buffer->m_cRef) && v28 )
      v28->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v28, 1u);
  }
  else
  {
    v29 = InterlockedDecrement;
  }
  v30 = _prof;
  if ( AppraisalProfile::InqInt(_prof, 0x21u, &bonded) )
  {
    strBonded.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( AppraisalSystem::BondedStatusToString((BondedStatusEnum)bonded, &strBonded) )
      AppendHelper(&strProperties, strBonded.m_buffer->m_data);
    v31 = strBonded.m_buffer;
    if ( !v29((volatile LONG *)&strBonded.m_buffer->m_cRef) && v31 )
      v31->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v31, 1u);
    v30 = _prof;
  }
  if ( AppraisalProfile::InqBool(v30, 0x5Bu, &retained) && retained == 1 )
    AppendHelper(&strProperties, "Retained");
  if ( AppraisalProfile::InqFloat(v30, 0x88u, &fCrit) )
    AppendHelper(&strProperties, "Crushing Blow");
  if ( AppraisalProfile::InqFloat(v30, 0x93u, &fCrit) )
    AppendHelper(&strProperties, "Biting Strike");
  if ( AppraisalProfile::InqFloat(v30, 0x9Bu, &fCrit) )
    AppendHelper(&strProperties, "Armor Cleaving");
  fResMod = 1.0;
  damageType = 0;
  if ( AppraisalProfile::InqFloat(v30, 0x9Du, &fResMod) && AppraisalProfile::InqInt(v30, 0x107u, &damageType) )
  {
    AppraisalSystem::DamageTypeToString((DAMAGE_TYPE)damageType, tmp_txt, 0x7E8u);
    resModStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    AC1Legacy::PStringBase<char>::sprintf(&resModStr, "Resistance Cleaving: %s", tmp_txt);
    v32 = resModStr.m_buffer;
    AppendHelper(&strProperties, resModStr.m_buffer->m_data);
    if ( !v29((volatile LONG *)&v32->m_cRef) && v32 )
      v32->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v32, 1u);
    v30 = _prof;
  }
  if ( AppraisalProfile::InqDataID(v30, 0x37u, &spellDID) )
    AppendHelper(&strProperties, "Cast on Strike");
  bIvoryable = 0;
  if ( AppraisalProfile::InqBool(v30, 0x63u, &bIvoryable) && bIvoryable == 1 )
    AppendHelper(&strProperties, "Ivoryable");
  bDyable = 0;
  if ( AppraisalProfile::InqBool(v30, 0x64u, &bDyable) && bDyable == 1 )
    AppendHelper(&strProperties, "Dyeable");
  if ( strProperties.m_buffer->m_len == 1 )
  {
    v38 = LODWORD(infoAddedToPanel);
    v37 = v54;
  }
  else
  {
    AC1Legacy::PStringBase<char>::PStringBase<char>(&v51, "Properties: ");
    v34 = (AC1Legacy::PSRefBuffer<char> **)AC1Legacy::PStringBase<char>::operator+(
                                             v33,
                                             (AC1Legacy::PStringBase<char> *)&shared_cooldown_id,
                                             &strProperties);
    if ( strProperties.m_buffer != *v34 )
    {
      if ( !v29((volatile LONG *)&strProperties.m_buffer->m_cRef) )
        ((void (__stdcall *)(signed int))strProperties.m_buffer->vfptr->__vecDelDtor)(1);
      strProperties.m_buffer = *v34;
      InterlockedIncrement((volatile LONG *)&strProperties.m_buffer->m_cRef);
    }
    v35 = shared_cooldown_id;
    if ( !v29((volatile LONG *)(shared_cooldown_id + 4)) && v35 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v35)(v35, 1);
    v36 = v51.m_buffer;
    if ( !v29((volatile LONG *)&v51.m_buffer->m_cRef) && v36 )
      v36->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v36, 1u);
    v37 = v54;
    ItemExamineUI::AddItemInfo(v54, strProperties.m_buffer->m_data, 0, 1);
    v38 = 1;
  }
  if ( v27 )
  {
    ItemExamineUI::AddItemInfo(v37, "This item cannot be further imbued.", 0, 1);
    v38 = 1;
  }
  bAutowieldLeft = 0;
  if ( AppraisalProfile::InqBool(_prof, 0x82u, &bAutowieldLeft) && bAutowieldLeft == 1 )
  {
    ItemExamineUI::AddItemInfo(v37, "This item is tethered to the left side.", 0, 1);
LABEL_176:
    ItemExamineUI::AddItemInfo(v37, &name, 0, 1);
    goto LABEL_177;
  }
  if ( v38 )
    goto LABEL_176;
LABEL_177:
  v39 = (char *)&sTextStr.m_charbuffer[-1].m_data[6];
  if ( !v29((volatile LONG *)&sTextStr.m_charbuffer[-1].m_data[8]) && v39 )
    (**(void (__thiscall ***)(char *, signed int))v39)(v39, 1);
  v40 = (char *)&sTimeStr.m_charbuffer[-1].m_data[6];
  if ( !v29((volatile LONG *)&sTimeStr.m_charbuffer[-1].m_data[8]) && v40 )
    (**(void (__thiscall ***)(char *, signed int))v40)(v40, 1);
  v41 = strProperties.m_buffer;
  if ( !v29((volatile LONG *)&strProperties.m_buffer->m_cRef) )
  {
    if ( v41 )
      v41->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v41, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B0DA0) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowCraftsman(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // edi@1
  AC1Legacy::PSRefBuffer<char> *v3; // esi@7
  int has_allowed_iid; // [sp+8h] [bp-7F0h]@1
  AC1Legacy::PStringBase<char> strCraftsman; // [sp+Ch] [bp-7ECh]@5
  char numtxt[2024]; // [sp+10h] [bp-7E8h]@6

  v2 = this;
  has_allowed_iid = 0;
  if ( (!AppraisalProfile::InqBool(_prof, 0x55u, &has_allowed_iid) || !has_allowed_iid)
    && (!AppraisalProfile::InqBool(_prof, 0x5Eu, &has_allowed_iid) || !has_allowed_iid) )
  {
    strCraftsman.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( AppraisalProfile::InqString(_prof, 0x19u, &strCraftsman) )
    {
      __snprintf(numtxt, 0x7E8u, "Created by %s.", strCraftsman.m_buffer->m_data);
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    }
    v3 = strCraftsman.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&strCraftsman.m_buffer->m_cRef) )
    {
      if ( v3 )
        v3->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v3, 1u);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B0E70) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowTinkeringInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // ebp@1
  char *v3; // eax@2
  double v4; // st7@11
  AC1Legacy::PSRefBuffer<char> *v5; // esi@13
  AC1Legacy::PSRefBuffer<char> *v6; // esi@17
  AC1Legacy::PSRefBuffer<char> *v7; // esi@20
  AC1Legacy::PStringBase<char> strWorkmanship; // [sp+1Ch] [bp-804h]@11
  int iWorkmanship; // [sp+20h] [bp-800h]@9
  AC1Legacy::PStringBase<char> strTinkerer; // [sp+24h] [bp-7FCh]@5
  AC1Legacy::PStringBase<char> strImbuer; // [sp+28h] [bp-7F8h]@7
  float fAvg; // [sp+2Ch] [bp-7F4h]@11
  int iNumItems; // [sp+30h] [bp-7F0h]@10
  int cTinkers; // [sp+34h] [bp-7ECh]@1
  char numtxt[2024]; // [sp+38h] [bp-7E8h]@4

  v2 = this;
  if ( AppraisalProfile::InqInt(_prof, 0xABu, &cTinkers) )
  {
    v3 = "s";
    if ( cTinkers <= 1 )
      v3 = &name;
    __snprintf(numtxt, 0x7E8u, "This item has been tinkered %d time%s.", cTinkers, v3);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
  }
  strTinkerer.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( AppraisalProfile::InqString(_prof, 0x27u, &strTinkerer) )
  {
    __snprintf(numtxt, 0x7E8u, "Last tinkered by %s.", strTinkerer.m_buffer->m_data);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
  }
  strImbuer.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( AppraisalProfile::InqString(_prof, 0x28u, &strImbuer) )
  {
    __snprintf(numtxt, 0x7E8u, "Imbued by %s.", strImbuer.m_buffer->m_data);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
  }
  if ( AppraisalProfile::InqInt(_prof, 0x69u, &iWorkmanship) )
  {
    if ( AppraisalProfile::InqInt(_prof, 0xAAu, &iNumItems) )
    {
      v4 = (double)iWorkmanship / (double)iNumItems;
      fAvg = v4;
      iWorkmanship = (unsigned __int64)(v4 + 0.5);
      strWorkmanship.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      AppraisalSystem::InqWorkmanshipAdjective(iWorkmanship, &strWorkmanship, 0);
      __snprintf(
        numtxt,
        0x7E8u,
        "Workmanship: %s (%0.2f)\n\nSalvaged from %d items.",
        strWorkmanship.m_buffer->m_data,
        fAvg,
        iNumItems);
    }
    else
    {
      strWorkmanship.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      AppraisalSystem::InqWorkmanshipAdjective(iWorkmanship, &strWorkmanship, 0);
      __snprintf(numtxt, 0x7E8u, "Workmanship: %s (%d)", strWorkmanship.m_buffer->m_data, iWorkmanship);
    }
    v5 = strWorkmanship.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&strWorkmanship.m_buffer->m_cRef) && v5 )
      v5->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v5, 1u);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
  }
  ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
  v6 = strImbuer.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&strImbuer.m_buffer->m_cRef) && v6 )
    v6->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v6, 1u);
  v7 = strTinkerer.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&strTinkerer.m_buffer->m_cRef) )
  {
    if ( v7 )
      v7->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v7, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B10E0) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowWeaponAndArmorData(ItemExamineUI *this, unsigned int lm, AppraisalProfile *_prof)
{
  ItemExamineUI *v3; // esi@1
  ACCWeenieObject *v4; // ecx@1
  HashBaseData<unsigned long>Vtbl *v5; // edx@1
  InterfacePtr<Interface> *v6; // eax@11
  CACQualities *v7; // edi@13
  AC1Legacy::PSRefBuffer<char> *v8; // eax@13
  unsigned int v9; // ebx@21
  int v10; // edi@23
  int v11; // ecx@44
  double v12; // st7@49
  AppraisalProfile *v13; // edi@54
  AC1Legacy::PSRefBuffer<char> *v14; // edi@65
  char *v15; // eax@71
  AC1Legacy::PStringBase<char> *v16; // eax@86
  AC1Legacy::PSRefBuffer<char> *v17; // ecx@88
  int v18; // edx@88
  int v19; // ecx@89
  char *v20; // eax@91
  int v21; // edi@99
  long double v22; // st7@101
  AC1Legacy::PSRefBuffer<char> *v23; // esi@127
  char *v24; // [sp-18h] [bp-10ECh]@8
  char *v25; // [sp-18h] [bp-10ECh]@73
  char *v26; // [sp-18h] [bp-10ECh]@82
  char *v27; // [sp-18h] [bp-10ECh]@93
  char *v28; // [sp-18h] [bp-10ECh]@105
  int v29; // [sp-14h] [bp-10E8h]@8
  int v30; // [sp-14h] [bp-10E8h]@73
  int v31; // [sp-14h] [bp-10E8h]@82
  int v32; // [sp-14h] [bp-10E8h]@105
  const char *v33; // [sp-10h] [bp-10E4h]@113
  AC1Legacy::PStringBase<char> rhs[2]; // [sp+4h] [bp-10D0h]@13
  AC1Legacy::PStringBase<char> ps[2]; // [sp+Ch] [bp-10C8h]@1
  int v36; // [sp+14h] [bp-10C0h]@88
  int retval; // [sp+18h] [bp-10BCh]@5
  int raised; // [sp+1Ch] [bp-10B8h]@6
  unsigned int v39; // [sp+20h] [bp-10B4h]@1
  InterfacePtr<PlayerDesc> v40; // [sp+24h] [bp-10B0h]@11
  int v41; // [sp+2Ch] [bp-10A8h]@42
  __int16 v42; // [sp+30h] [bp-10A4h]@43
  char v43; // [sp+32h] [bp-10A2h]@43
  WeaponProfile wap; // [sp+34h] [bp-10A0h]@20
  InterfacePtr<Interface> result; // [sp+7Ch] [bp-1058h]@11
  char ability_txt; // [sp+84h] [bp-1050h]@50
  char Dest; // [sp+104h] [bp-FD0h]@6
  char buf; // [sp+8ECh] [bp-7E8h]@47

  ps[0].m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  v3 = this;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  v4 = v3->cur_weenobj;
  v5 = v4->vfptr;
  v39 = v4->pwd._ammoType;
  if ( ((int (*)(void))v5[29].__vecDelDtor)() )
    v39 = AppraisalProfile::GetHookedItemAmmoType(_prof);
  if ( lm & 0x3F00000 )
  {
    if ( lm & 0x200000 )
    {
      retval = -1;
      if ( AppraisalProfile::InqInt(_prof, 0x1Cu, &retval) )
      {
        _sprintf(&Dest, "Base Shield Level: %d", retval);
        raised = 0;
        if ( AppraisalProfile::InqIntEnchantmentMod(_prof, 0x1Cu, &raised) )
        {
          if ( raised )
          {
            v29 = v3->mod_high_font;
            v24 = &Dest;
          }
          else
          {
            v29 = v3->mod_low_font;
            v24 = &Dest;
          }
        }
        else
        {
          v29 = 0;
          v24 = &Dest;
        }
        ItemExamineUI::AddItemInfo(v3, v24, v29, 1);
        v6 = GetClassObject(&result, &PlayerDesc_ClassType_7);
        InterfacePtr<PlayerDesc>::InterfacePtr<PlayerDesc>(&v40, v6);
        if ( (_DWORD)result.m_pInterface )
          ((void (*)(void))result.m_pInterface->vfptr->Release)();
        v7 = (CACQualities *)v40.m_pInterface;
        ps[1].m_buffer = 0;
        rhs[0].m_buffer = 0;
        CACQualities::InqSkill((CACQualities *)&v40.m_pInterface->vfptr, 0x30u, (int *)&ps[1], 0);
        CACQualities::InqSkillAdvancementClass(v7, 0x30u, (SKILL_ADVANCEMENT_CLASS *)rhs);
        v8 = ps[1].m_buffer;
        if ( (signed int)rhs[0].m_buffer < 3 )
        {
          v8 = (AC1Legacy::PSRefBuffer<char> *)((signed int)ps[1].m_buffer / 2);
          ps[1].m_buffer = (signed int)ps[1].m_buffer / 2;
        }
        if ( (signed int)v8 > retval )
        {
          v8 = (AC1Legacy::PSRefBuffer<char> *)retval;
          ps[1].m_buffer = (AC1Legacy::PSRefBuffer<char> *)retval;
        }
        _sprintf(&Dest, "Effective Shield Level : %d (with Shield skill)", v8);
        ItemExamineUI::AddItemInfo(v3, &Dest, 0, 1);
        if ( v7 )
          v7->vfptr->Release((Interface *)v7);
      }
      else
      {
        ItemExamineUI::AddItemInfo(v3, "Shield Level: Unknown", 0, 1);
      }
    }
    WeaponProfile::WeaponProfile(&wap);
    if ( !AppraisalProfile::InqWeapon(_prof, &wap) )
    {
LABEL_109:
      if ( lm & 0x400000 )
      {
        if ( v39 == 1 )
        {
          v33 = "Uses arrows as ammunition.";
        }
        else if ( v39 == 2 )
        {
          v33 = "Uses quarrels as ammunition.";
        }
        else
        {
          if ( v39 != 4 )
            goto LABEL_127;
          v33 = "Uses atlatl darts as ammunition.";
        }
      }
      else
      {
        if ( !((unsigned int)"activation type (%s) with '%s' because of its toggle type (%s)" & lm) )
          goto LABEL_127;
        if ( v39 == 1 )
        {
          v33 = "Used as ammunition by bows.";
        }
        else if ( v39 == 2 )
        {
          v33 = "Used as ammunition by crossbows.";
        }
        else
        {
          if ( v39 != 4 )
            goto LABEL_127;
          v33 = "Used as ammunition by atlatls.";
        }
      }
      goto LABEL_126;
    }
    v9 = lm & 0x400000;
    v10 = lm & 0x400000 && v39;
    raised = v10;
    AC1Legacy::PStringBase<char>::set(ps, "Skill: ");
    if ( AppraisalSystem::SkillToString(wap.weapon_skill, ps) )
    {
      if ( AppraisalProfile::InqInt(_prof, 0x161u, (int *)&ps[1]) )
      {
        switch ( ps[1].m_buffer )
        {
          case 1u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Unarmed Weapon)");
            goto LABEL_38;
          case 2u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Sword)");
            AC1Legacy::PStringBase<char>::operator+=(ps, rhs);
            goto LABEL_39;
          case 3u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Axe)");
            AC1Legacy::PStringBase<char>::operator+=(ps, rhs);
            goto LABEL_39;
          case 4u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Mace)");
            goto LABEL_38;
          case 5u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Spear)");
            AC1Legacy::PStringBase<char>::operator+=(ps, rhs);
            goto LABEL_39;
          case 6u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Dagger)");
            AC1Legacy::PStringBase<char>::operator+=(ps, rhs);
            goto LABEL_39;
          case 7u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Staff)");
            goto LABEL_38;
          case 8u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Bow)");
            AC1Legacy::PStringBase<char>::operator+=(ps, rhs);
            goto LABEL_39;
          case 9u:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Crossbow)");
            AC1Legacy::PStringBase<char>::operator+=(ps, rhs);
            goto LABEL_39;
          case 0xAu:
            AC1Legacy::PStringBase<char>::PStringBase<char>(rhs, " (Thrown)");
LABEL_38:
            AC1Legacy::PStringBase<char>::operator+=(ps, rhs);
LABEL_39:
            CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)rhs);
            break;
          default:
            break;
        }
      }
      ItemExamineUI::AddItemInfo(v3, ps[0].m_buffer->m_data, 0, 1);
    }
    if ( v10 )
    {
      v40.m_pInterface = *(PlayerDesc **)"Damage Bonus: ";
      v40.m_trStatus.m_val = 1109419367;
      v41 = 1937075823;
      v42 = 8250;
      v43 = 0;
    }
    else
    {
      v40.m_pInterface = *(PlayerDesc **)"Damage: ";
      v40.m_trStatus.m_val = 540697959;
      LOBYTE(v41) = 0;
    }
    v11 = wap.weapon_damage;
    if ( wap.weapon_damage <= -1 )
    {
      _sprintf(&ability_txt, "%s%s", &v40, "Unknown");
      ItemExamineUI::AddItemInfo(v3, &ability_txt, 0, 1);
      v13 = _prof;
    }
    else
    {
      Dest = 0;
      if ( !v10 )
      {
        _sprintf(&Dest, ", unknown type");
        if ( wap.damage_type )
        {
          AppraisalSystem::DamageTypeToString(wap.damage_type, &buf, 0x7E8u);
          _sprintf(&Dest, ", %s", &buf);
        }
        v11 = wap.weapon_damage;
      }
      v12 = (double)wap.weapon_damage;
      *(double *)&rhs[0].m_buffer = (1.0 - wap.damage_variance) * v12;
      if ( v12 - *(double *)&rhs[0].m_buffer > 0.00019999999 )
      {
        if ( *(double *)&rhs[0].m_buffer >= 10.0 )
          _sprintf(&ability_txt, "%s%.4g - %d%s", &v40, rhs[0].m_buffer, rhs[1].m_buffer, v11, &Dest);
        else
          _sprintf(&ability_txt, "%s%.3g - %d%s", &v40, rhs[0].m_buffer, rhs[1].m_buffer, v11, &Dest);
      }
      else
      {
        _sprintf(&ability_txt, "%s%d%s", &v40, v11, &Dest);
      }
      v13 = _prof;
      ps[1].m_buffer = 0;
      if ( AppraisalProfile::InqIntEnchantmentMod(_prof, 0x2Cu, (int *)&ps[1]) )
      {
        if ( ps[1].m_buffer )
          ItemExamineUI::AddItemInfo(v3, &ability_txt, v3->mod_high_font, 1);
        else
          ItemExamineUI::AddItemInfo(v3, &ability_txt, v3->mod_low_font, 1);
      }
      else if ( AppraisalProfile::InqFloatEnchantmentMod(_prof, 0x16u, (int *)&ps[1]) )
      {
        if ( ps[1].m_buffer )
          ItemExamineUI::AddItemInfo(v3, &ability_txt, v3->mod_high_font, 1);
        else
          ItemExamineUI::AddItemInfo(v3, &ability_txt, v3->mod_low_font, 1);
      }
      else
      {
        ItemExamineUI::AddItemInfo(v3, &ability_txt, 0, 1);
      }
    }
    retval = 0;
    AppraisalProfile::InqInt(v13, 0xCCu, &retval);
    if ( retval > 0 )
    {
      AppraisalSystem::DamageTypeToString(wap.damage_type, &buf, 0x7E8u);
      rhs[0].m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      AC1Legacy::PStringBase<char>::sprintf(rhs, "Elemental Damage Bonus: %d, %s.", retval, &buf);
      v14 = rhs[0].m_buffer;
      ItemExamineUI::AddItemInfo(v3, rhs[0].m_buffer->m_data, 0, 1);
      if ( !InterlockedDecrement((volatile LONG *)&v14->m_cRef) )
      {
        if ( v14 )
          v14->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v14, 1u);
      }
    }
    if ( v9 && v39 )
    {
      if ( _prof->success_flag )
      {
        v15 = ModifierToString(wap.damage_mod);
        _sprintf(&ability_txt, "Damage Modifier: %s.", v15);
        rhs[0].m_buffer = 0;
        if ( AppraisalProfile::InqFloatEnchantmentMod(_prof, 0x3Fu, (int *)rhs) )
        {
          if ( rhs[0].m_buffer )
          {
            v30 = v3->mod_high_font;
            v25 = &ability_txt;
          }
          else
          {
            v30 = v3->mod_low_font;
            v25 = &ability_txt;
          }
        }
        else
        {
          v30 = 0;
          v25 = &ability_txt;
        }
      }
      else
      {
        v30 = 0;
        v25 = "Damage Modifier: Unknown";
      }
      ItemExamineUI::AddItemInfo(v3, v25, v30, 1);
    }
    if ( lm & 0x2500000 )
    {
      if ( wap.weapon_time <= -1 )
      {
        ItemExamineUI::AddItemInfo(v3, "Speed:  Unknown", 0, 1);
        if ( v9 )
        {
          v27 = "Range:  Unknown";
LABEL_96:
          ItemExamineUI::AddItemInfo(v3, v27, 0, 1);
          goto LABEL_97;
        }
      }
      else
      {
        AC1Legacy::PStringBase<char>::set(ps, "Speed: ");
        AppraisalSystem::WeaponTimeToString(wap.weapon_time, ps);
        _sprintf(&ability_txt, "%s (%d)", ps[0].m_buffer->m_data, wap.weapon_time);
        rhs[0].m_buffer = 0;
        if ( AppraisalProfile::InqIntEnchantmentMod(_prof, 0x31u, (int *)rhs) )
        {
          if ( rhs[0].m_buffer )
          {
            v31 = v3->mod_high_font;
            v26 = &ability_txt;
          }
          else
          {
            v31 = v3->mod_low_font;
            v26 = &ability_txt;
          }
        }
        else
        {
          v31 = 0;
          v26 = &ability_txt;
        }
        ItemExamineUI::AddItemInfo(v3, v26, v31, 1);
        if ( v9 )
        {
          *(double *)&ps[1].m_buffer = pow(wap.max_velocity, 2.0) * 0.1020408163265306 * 1.094;
          v16 = (AC1Legacy::PStringBase<char> *)&MISSILE_RANGE_CAP;
          if ( *(double *)&ps[1].m_buffer <= 85.0 )
            v16 = &ps[1];
          v17 = v16->m_buffer;
          v18 = (int)v16[1].m_buffer;
          ps[1].m_buffer = v16->m_buffer;
          v36 = v18;
          if ( *(double *)&ps[1].m_buffer >= 10.0 )
            v19 = (unsigned __int64)*(double *)&ps[1].m_buffer
                - (signed int)(unsigned __int64)*(double *)&ps[1].m_buffer % 5;
          else
            v19 = (unsigned __int64)_ceil(COERCE_DOUBLE(__PAIR__(v18, (unsigned int)v17)));
          v20 = " (based on STRENGTH 100)";
          if ( !wap.max_velocity_estimated )
            v20 = &name;
          _sprintf(&ability_txt, "Range: %d yds.%s", v19, v20);
          v27 = &ability_txt;
          goto LABEL_96;
        }
      }
    }
LABEL_97:
    if ( wap.weapon_offense != 1.0 && !raised )
    {
      v21 = (int)"+";
      if ( wap.weapon_offense < 1.0 )
        v21 = (int)"-";
      v22 = 1.0 - wap.weapon_offense;
      if ( 1.0 - wap.weapon_offense < 0.0 )
        v22 = -v22;
      _sprintf(&ability_txt, "Bonus to Attack Skill: %s%d%%.", v21, (unsigned __int64)(v22 * 100.0 + 0.5));
      rhs[0].m_buffer = 0;
      if ( AppraisalProfile::InqFloatEnchantmentMod(_prof, 0x3Eu, (int *)rhs) )
      {
        if ( rhs[0].m_buffer )
        {
          v32 = v3->mod_high_font;
          v28 = &ability_txt;
        }
        else
        {
          v32 = v3->mod_low_font;
          v28 = &ability_txt;
        }
      }
      else
      {
        v32 = 0;
        v28 = &ability_txt;
      }
      ItemExamineUI::AddItemInfo(v3, v28, v32, 1);
    }
    goto LABEL_109;
  }
  if ( lm & 0x8007FFF && AppraisalSystem::ClothingPriorityToString(v3->cur_weenobj->pwd._priority, ps) )
  {
    v33 = ps[0].m_buffer->m_data;
LABEL_126:
    ItemExamineUI::AddItemInfo(v3, v33, 0, 1);
  }
LABEL_127:
  v23 = ps[0].m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&ps[0].m_buffer->m_cRef) )
  {
    if ( v23 )
      v23->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v23, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B1B10) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowCasterData(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  char *v3; // eax@2
  AC1Legacy::PSRefBuffer<char> *v4; // ebx@8
  int v5; // edi@8
  char *v6; // eax@10
  char *v7; // eax@10
  int v8; // eax@12
  int v9; // eax@15
  AC1Legacy::PSRefBuffer<char> *v10; // edi@28
  char *v11; // [sp-Ch] [bp-8B4h]@4
  int v12; // [sp-8h] [bp-8B0h]@4
  int v13; // [sp-8h] [bp-8B0h]@18
  int bEnch; // [sp+10h] [bp-898h]@2
  AC1Legacy::PStringBase<char> eleDamageModInfo; // [sp+14h] [bp-894h]@8
  int raised; // [sp+18h] [bp-890h]@10
  AC1Legacy::PStringBase<char> eleDamageModTextPvM; // [sp+1Ch] [bp-88Ch]@8
  long double eleDamageModPvM; // [sp+20h] [bp-888h]@8
  DAMAGE_TYPE damageType; // [sp+2Ch] [bp-87Ch]@9
  long double rManaCModifier; // [sp+30h] [bp-878h]@1
  long double eleDamageModPvP; // [sp+38h] [bp-870h]@10
  char szBuff[128]; // [sp+40h] [bp-868h]@2
  char tmp_txt[2024]; // [sp+C0h] [bp-7E8h]@10

  v2 = this;
  if ( AppraisalProfile::InqFloat(_prof, 0x90u, &rManaCModifier) )
  {
    rManaCModifier = rManaCModifier + 1.0;
    v3 = ModifierToString(rManaCModifier);
    _sprintf(szBuff, "Bonus to Mana Conversion: %s.", v3);
    bEnch = 0;
    if ( AppraisalProfile::InqFloatEnchantmentMod(_prof, 0x90u, &bEnch) )
    {
      if ( bEnch )
      {
        v12 = v2->mod_high_font;
        v11 = szBuff;
      }
      else
      {
        v12 = v2->mod_low_font;
        v11 = szBuff;
      }
    }
    else
    {
      v12 = 0;
      v11 = szBuff;
    }
    ItemExamineUI::AddItemInfo(v2, v11, v12, 0);
  }
  eleDamageModInfo.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  v4 = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  eleDamageModTextPvM.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  v5 = AC1Legacy::PStringBase<char>::s_NullBuffer;
  bEnch = AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  eleDamageModPvM = 1.0;
  if ( AppraisalProfile::InqFloat(_prof, 0x98u, &eleDamageModPvM) )
  {
    damageType = 0;
    if ( AppraisalProfile::InqInt(_prof, 0x2Du, (int *)&damageType) )
    {
      AppraisalSystem::DamageTypeToString(damageType, tmp_txt, 0x7E8u);
      AC1Legacy::PStringBase<char>::sprintf(&eleDamageModInfo, "Damage bonus for %s spells:", tmp_txt);
      eleDamageModPvP = CombatSystem::GetElementalModPKModifier(eleDamageModPvM);
      v6 = SmallModifierToString(eleDamageModPvM);
      AC1Legacy::PStringBase<char>::sprintf(&eleDamageModTextPvM, " vs. Monsters: %s.", v6);
      v7 = SmallModifierToString(eleDamageModPvP);
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&bEnch, " vs. Players: %s.", v7);
      raised = 0;
      if ( AppraisalProfile::InqFloatEnchantmentMod(_prof, 0x98u, &raised) )
      {
        if ( raised )
          v8 = v2->mod_high_font;
        else
          v8 = v2->mod_low_font;
        ItemExamineUI::AddItemInfo(v2, eleDamageModInfo.m_buffer->m_data, v8, 0);
        if ( raised )
          v9 = v2->mod_high_font;
        else
          v9 = v2->mod_low_font;
        v4 = eleDamageModTextPvM.m_buffer;
        ItemExamineUI::AddItemInfo(v2, eleDamageModTextPvM.m_buffer->m_data, v9, 1);
        if ( raised )
          v13 = v2->mod_high_font;
        else
          v13 = v2->mod_low_font;
      }
      else
      {
        ItemExamineUI::AddItemInfo(v2, eleDamageModInfo.m_buffer->m_data, 0, 0);
        v4 = eleDamageModTextPvM.m_buffer;
        ItemExamineUI::AddItemInfo(v2, eleDamageModTextPvM.m_buffer->m_data, 0, 1);
        v13 = 0;
      }
      v5 = bEnch;
      ItemExamineUI::AddItemInfo(v2, (const char *)(bEnch + 20), v13, 1);
    }
  }
  if ( !InterlockedDecrement((volatile LONG *)(v5 + 4)) && v5 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v5)(v5, 1);
  if ( !InterlockedDecrement((volatile LONG *)&v4->m_cRef) && v4 )
    v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
  v10 = eleDamageModInfo.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&eleDamageModInfo.m_buffer->m_cRef) )
  {
    if ( v10 )
      v10->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v10, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B1DF0) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowDefenseModData(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  char *v3; // eax@3
  char *v4; // eax@11
  char *v5; // eax@14
  char *v6; // [sp-Ch] [bp-ACh]@5
  int v7; // [sp-8h] [bp-A8h]@5
  long double rDefenseModifier; // [sp+10h] [bp-90h]@1
  int bEnch; // [sp+1Ch] [bp-84h]@3
  char szBuff[128]; // [sp+20h] [bp-80h]@3

  v2 = this;
  if ( AppraisalProfile::InqFloat(_prof, 0x1Du, &rDefenseModifier) && rDefenseModifier != 1.0 )
  {
    v3 = SmallModifierToString(rDefenseModifier);
    _sprintf(szBuff, "Bonus to Melee Defense: %s.", v3);
    bEnch = 0;
    if ( AppraisalProfile::InqFloatEnchantmentMod(_prof, 0x1Du, &bEnch) )
    {
      if ( bEnch )
      {
        v7 = v2->mod_high_font;
        v6 = szBuff;
      }
      else
      {
        v7 = v2->mod_low_font;
        v6 = szBuff;
      }
    }
    else
    {
      v7 = 0;
      v6 = szBuff;
    }
    ItemExamineUI::AddItemInfo(v2, v6, v7, 1);
  }
  if ( AppraisalProfile::InqFloat(_prof, 0x95u, &rDefenseModifier) && rDefenseModifier != 1.0 )
  {
    v4 = SmallModifierToString(rDefenseModifier);
    _sprintf(szBuff, "Bonus to Missile Defense: %s.", v4);
    ItemExamineUI::AddItemInfo(v2, szBuff, 0, 1);
  }
  if ( AppraisalProfile::InqFloat(_prof, 0x96u, &rDefenseModifier) )
  {
    if ( rDefenseModifier != 1.0 )
    {
      v5 = SmallModifierToString(rDefenseModifier);
      _sprintf(szBuff, "Bonus to Magic Defense: %s.", v5);
      ItemExamineUI::AddItemInfo(v2, szBuff, 0, 1);
    }
  }
}

//----- (004B1F60) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowArmorMods(ItemExamineUI *this, AppraisalProfile *_prof)
{
  AppraisalProfile *v2; // ebp@1
  ItemExamineUI *v3; // esi@1
  int v4; // ebx@4
  AC1Legacy::PSRefBuffer<char> *v5; // edi@4
  unsigned int v6; // eax@4
  AppraisalProfile *v7; // esi@70
  const char *v8; // [sp-14h] [bp-4Ch]@11
  const char *v9; // [sp-14h] [bp-4Ch]@17
  const char *v10; // [sp-14h] [bp-4Ch]@24
  const char *v11; // [sp-14h] [bp-4Ch]@31
  const char *v12; // [sp-14h] [bp-4Ch]@38
  const char *v13; // [sp-14h] [bp-4Ch]@45
  const char *v14; // [sp-14h] [bp-4Ch]@52
  const char *v15; // [sp-14h] [bp-4Ch]@59
  const char *v16; // [sp-14h] [bp-4Ch]@66
  int v17; // [sp-10h] [bp-48h]@11
  int v18; // [sp-10h] [bp-48h]@17
  int v19; // [sp-10h] [bp-48h]@24
  int v20; // [sp-10h] [bp-48h]@31
  int v21; // [sp-10h] [bp-48h]@38
  int v22; // [sp-10h] [bp-48h]@45
  int v23; // [sp-10h] [bp-48h]@52
  int v24; // [sp-10h] [bp-48h]@59
  int v25; // [sp-10h] [bp-48h]@66
  int bEnch; // [sp+8h] [bp-30h]@4
  int armor_lvl; // [sp+Ch] [bp-2Ch]@1
  AC1Legacy::PStringBase<char> v28; // [sp+10h] [bp-28h]@4
  ArmorProfile aap; // [sp+14h] [bp-24h]@1

  v2 = _prof;
  v3 = this;
  aap.vfptr = (PackObjVtbl *)&ArmorProfile::`vftable`;
  LODWORD(aap.mod_vs_slash) = 1065353216;
  LODWORD(aap.mod_vs_pierce) = 1065353216;
  LODWORD(aap.mod_vs_bludgeon) = 1065353216;
  LODWORD(aap.mod_vs_cold) = 1065353216;
  LODWORD(aap.mod_vs_fire) = 1065353216;
  LODWORD(aap.mod_vs_acid) = 1065353216;
  LODWORD(aap.mod_vs_electric) = 1065353216;
  LODWORD(aap.mod_vs_nether) = 1065353216;
  armor_lvl = -1;
  if ( AppraisalProfile::InqArmor(_prof, &aap) && AppraisalProfile::InqInt(v2, 0x1Cu, &armor_lvl) && armor_lvl > 0 )
  {
    _prof = (AppraisalProfile *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    bEnch = 0;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    AC1Legacy::PStringBase<char>::set((AC1Legacy::PStringBase<char> *)&_prof, "\nArmor Level: ");
    v4 = armor_lvl;
    v28.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    AC1Legacy::PStringBase<char>::operator=(&v28, v4);
    v5 = v28.m_buffer;
    v6 = v28.m_buffer->m_len;
    if ( v6 != 1 && v28.m_buffer != (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer )
      AC1Legacy::PStringBase<char>::append_n_chars((AC1Legacy::PStringBase<char> *)&_prof, v28.m_buffer->m_data, v6 - 1);
    if ( !InterlockedDecrement((volatile LONG *)&v5->m_cRef) )
      v5->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v5, 1u);
    if ( AppraisalProfile::InqIntEnchantmentMod(v2, 0x1Cu, &bEnch) )
    {
      if ( bEnch )
      {
        v17 = v3->mod_high_font;
        v8 = (const char *)&_prof->armor_profile;
      }
      else
      {
        v17 = v3->mod_low_font;
        v8 = (const char *)&_prof->armor_profile;
      }
    }
    else
    {
      v17 = 0;
      v8 = (const char *)&_prof->armor_profile;
    }
    ItemExamineUI::AddItemInfo(v3, v8, v17, 1);
    if ( AppraisalSystem::DamageResistanceToString(
           SLASH_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_slash,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0xDu, &bEnch) )
      {
        if ( bEnch )
        {
          v18 = v3->mod_high_font;
          v9 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v18 = v3->mod_low_font;
          v9 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v18 = 0;
        v9 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v9, v18, 1);
    }
    if ( AppraisalSystem::DamageResistanceToString(
           PIERCE_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_pierce,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0xEu, &bEnch) )
      {
        if ( bEnch )
        {
          v19 = v3->mod_high_font;
          v10 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v19 = v3->mod_low_font;
          v10 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v19 = 0;
        v10 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v10, v19, 1);
    }
    if ( AppraisalSystem::DamageResistanceToString(
           BLUDGEON_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_bludgeon,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0xFu, &bEnch) )
      {
        if ( bEnch )
        {
          v20 = v3->mod_high_font;
          v11 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v20 = v3->mod_low_font;
          v11 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v20 = 0;
        v11 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v11, v20, 1);
    }
    if ( AppraisalSystem::DamageResistanceToString(
           FIRE_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_fire,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0x11u, &bEnch) )
      {
        if ( bEnch )
        {
          v21 = v3->mod_high_font;
          v12 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v21 = v3->mod_low_font;
          v12 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v21 = 0;
        v12 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v12, v21, 1);
    }
    if ( AppraisalSystem::DamageResistanceToString(
           COLD_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_cold,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0x10u, &bEnch) )
      {
        if ( bEnch )
        {
          v22 = v3->mod_high_font;
          v13 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v22 = v3->mod_low_font;
          v13 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v22 = 0;
        v13 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v13, v22, 1);
    }
    if ( AppraisalSystem::DamageResistanceToString(
           ACID_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_acid,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0x12u, &bEnch) )
      {
        if ( bEnch )
        {
          v23 = v3->mod_high_font;
          v14 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v23 = v3->mod_low_font;
          v14 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v23 = 0;
        v14 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v14, v23, 1);
    }
    if ( AppraisalSystem::DamageResistanceToString(
           ELECTRIC_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_electric,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0x13u, &bEnch) )
      {
        if ( bEnch )
        {
          v24 = v3->mod_high_font;
          v15 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v24 = v3->mod_low_font;
          v15 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v24 = 0;
        v15 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v15, v24, 1);
    }
    if ( AppraisalSystem::DamageResistanceToString(
           NETHER_DAMAGE_TYPE,
           armor_lvl,
           aap.mod_vs_nether,
           (AC1Legacy::PStringBase<char> *)&_prof) )
    {
      if ( AppraisalProfile::InqFloatEnchantmentMod(v2, 0xA5u, &bEnch) )
      {
        if ( bEnch )
        {
          v25 = v3->mod_high_font;
          v16 = (const char *)&_prof->armor_profile;
        }
        else
        {
          v25 = v3->mod_low_font;
          v16 = (const char *)&_prof->armor_profile;
        }
      }
      else
      {
        v25 = 0;
        v16 = (const char *)&_prof->armor_profile;
      }
      ItemExamineUI::AddItemInfo(v3, v16, v25, 1);
    }
    v7 = _prof;
    if ( !InterlockedDecrement(&_prof->success_flag) )
    {
      if ( v7 )
        v7->vfptr->__vecDelDtor((PackObj *)v7, 1u);
    }
  }
}
// 7AF2FC: using guessed type int (__thiscall *ArmorProfile::`vftable')(void *, char);
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B2480) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowBoostValue(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // ebx@1
  ACCWeenieObject *v3; // ecx@1
  const char *v4; // [sp-Ch] [bp-800h]@13
  int v5; // [sp-8h] [bp-7FCh]@13
  int iBoostAmount; // [sp+4h] [bp-7F0h]@4
  int iAttribEffected; // [sp+8h] [bp-7ECh]@4
  char numtxt[2024]; // [sp+Ch] [bp-7E8h]@10

  v2 = this;
  v3 = this->cur_weenobj;
  if ( !(BYTE2(v3->pwd._bitfield) & 1)
    && (!((int (*)(void))v3->vfptr[29].__vecDelDtor)() || !AppraisalProfile::IsHookedItemHealer(_prof)) )
  {
    iBoostAmount = 0;
    iAttribEffected = 0;
    if ( AppraisalProfile::InqInt(_prof, 0x5Au, &iBoostAmount) )
    {
      if ( AppraisalProfile::InqInt(_prof, 0x59u, &iAttribEffected) )
      {
        if ( iAttribEffected == 2 )
        {
          if ( iBoostAmount < 0 )
          {
            v5 = -iBoostAmount;
            v4 = "Depletes %d Health when used.";
            goto LABEL_18;
          }
          _sprintf(numtxt, "Restores %d Health when used.", iBoostAmount);
        }
        else
        {
          if ( iAttribEffected != 4 )
          {
            if ( iAttribEffected == 6 )
            {
              if ( iBoostAmount < 0 )
                _sprintf(numtxt, "Depletes %d Mana when used.", -iBoostAmount);
              else
                _sprintf(numtxt, "Restores %d Mana when used.", iBoostAmount);
            }
            goto LABEL_19;
          }
          if ( iBoostAmount >= 0 )
          {
            v5 = iBoostAmount;
            v4 = "Restores %d Stamina when consumed.";
LABEL_18:
            _sprintf(numtxt, v4, v5);
            goto LABEL_19;
          }
          _sprintf(numtxt, "Depletes %d Stamina when consumed.", -iBoostAmount);
        }
LABEL_19:
        ItemExamineUI::AddItemInfo(v2, numtxt, 0, 0);
        return;
      }
    }
  }
}

//----- (004B25A0) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowHealKitValues(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  ACCWeenieObject *v3; // ecx@1
  int iBoostAmount; // [sp+8h] [bp-7F4h]@4
  long double rHealKitMod; // [sp+Ch] [bp-7F0h]@6
  char numtxt[2024]; // [sp+14h] [bp-7E8h]@5

  v2 = this;
  v3 = this->cur_weenobj;
  if ( BYTE2(v3->pwd._bitfield) & 1
    || ((int (*)(void))v3->vfptr[29].__vecDelDtor)() && AppraisalProfile::IsHookedItemHealer(_prof) )
  {
    iBoostAmount = 0;
    if ( AppraisalProfile::InqInt(_prof, 0x5Au, &iBoostAmount) )
    {
      _sprintf(numtxt, "Bonus to Healing Skill: %d", iBoostAmount);
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 0);
    }
    rHealKitMod = 1.0;
    if ( AppraisalProfile::InqFloat(_prof, 0x64u, &rHealKitMod) )
    {
      _sprintf(numtxt, "Restoration Bonus: %d%%", (unsigned __int64)(rHealKitMod * 100.0));
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    }
  }
}

//----- (004B2680) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowCapacity(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  ACCWeenieObject *v3; // ecx@3
  int v4; // eax@3
  int v5; // ecx@3
  char *v6; // [sp-10h] [bp-808h]@5
  int iNumPages; // [sp+8h] [bp-7F0h]@11
  int iMaxPages; // [sp+Ch] [bp-7ECh]@10
  char numtxt[2024]; // [sp+10h] [bp-7E8h]@5

  v2 = this;
  if ( ((int (*)(void))this->cur_weenobj->vfptr[29].__vecDelDtor)() && AnimSequenceNode::has_anim(_prof) )
    return;
  v3 = v2->cur_weenobj;
  v4 = v3->pwd._itemsCapacity;
  v5 = v3->pwd._containersCapacity;
  if ( v4 <= 0 )
  {
    if ( v5 <= 0 )
      goto LABEL_10;
    _sprintf(numtxt, "Can hold up to %d containers.", v5);
    v6 = numtxt;
  }
  else if ( v5 <= 0 )
  {
    _sprintf(numtxt, "Can hold up to %d items.", v4);
    v6 = numtxt;
  }
  else
  {
    _sprintf(numtxt, "Can hold up to %d items and %d containers.", v4, v5);
    v6 = numtxt;
  }
  ItemExamineUI::AddItemInfo(v2, v6, 0, 0);
LABEL_10:
  if ( AppraisalProfile::InqInt(_prof, 0xAFu, &iMaxPages) )
  {
    if ( AppraisalProfile::InqInt(_prof, 0xAEu, &iNumPages) )
    {
      _sprintf(numtxt, "%d of %d pages full.", iNumPages, iMaxPages);
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 0);
    }
  }
}

//----- (004B2790) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowLockAppraiseInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  AC1Legacy::PStringBase<char> sStat; // [sp+4h] [bp-7F8h]@6
  int iStat; // [sp+8h] [bp-7F4h]@4
  int locked; // [sp+Ch] [bp-7F0h]@2
  int lsp; // [sp+10h] [bp-7ECh]@5
  char numtxt[2024]; // [sp+14h] [bp-7E8h]@7

  v2 = this;
  if ( !((int (*)(void))this->cur_weenobj->vfptr[29].__vecDelDtor)() )
  {
    if ( AppraisalProfile::InqBool(_prof, 3u, &locked) )
    {
      if ( locked )
      {
        ItemExamineUI::AddItemInfo(v2, "Locked", 0, 0);
        if ( AppraisalProfile::InqInt(_prof, 0x26u, &iStat) )
        {
          if ( AppraisalProfile::InqInt(_prof, 0xADu, &lsp) )
          {
            AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::CaseInsensitiveStringBase<AC1Legacy::PStringBase<char> > *)&sStat);
            if ( AppraisalSystem::LockpickSuccessPercentToString(lsp, &sStat) )
            {
              _sprintf(numtxt, "The lock looks %s to pick (Resistance %d).", sStat.m_buffer->m_data, iStat);
              ItemExamineUI::AddItemInfo(v2, numtxt, 0, 0);
            }
            CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&sStat);
          }
        }
        else
        {
          ItemExamineUI::AddItemInfo(v2, "You can't tell how hard the lock is to pick.", 0, 0);
        }
      }
      else
      {
        ItemExamineUI::AddItemInfo(v2, "Unlocked", 0, 0);
      }
    }
    else if ( AppraisalProfile::InqInt(_prof, 0x26u, &iStat) )
    {
      if ( iStat >= 0 )
      {
        if ( iStat > 0 )
        {
          _sprintf(numtxt, "Bonus to Lockpick Skill: +%d", iStat);
          ItemExamineUI::AddItemInfo(v2, numtxt, 0, 0);
        }
      }
      else
      {
        _sprintf(numtxt, "Bonus to Lockpick Skill: %d", iStat);
        ItemExamineUI::AddItemInfo(v2, numtxt, 0, 0);
      }
    }
  }
}

//----- (004B2920) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowLevelLimitInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // ebx@1
  unsigned int v3; // eax@12
  AC1Legacy::PSRefBuffer<char> *v4; // esi@15
  AC1Legacy::PSRefBuffer<char> *v5; // esi@18
  const char *v6; // [sp-8h] [bp-80Ch]@4
  int v7; // [sp-4h] [bp-808h]@4
  int max; // [sp+Ch] [bp-7F8h]@1
  AC1Legacy::PStringBase<char> portal_dest; // [sp+10h] [bp-7F4h]@11
  int min; // [sp+14h] [bp-7F0h]@1
  AC1Legacy::PStringBase<char> strDest; // [sp+18h] [bp-7ECh]@12
  char numtxt[2024]; // [sp+1Ch] [bp-7E8h]@5

  min = -1;
  max = -1;
  v2 = this;
  AppraisalProfile::InqInt(_prof, 0x56u, &min);
  AppraisalProfile::InqInt(_prof, 0x57u, &max);
  if ( min <= 0 )
  {
    if ( max <= 0 )
      goto LABEL_11;
    v7 = max;
    v6 = "Restricted to characters of Level %d or below.";
    goto LABEL_9;
  }
  if ( max <= 0 )
  {
    _sprintf(numtxt, "Restricted to characters of Level %d or greater.", min);
  }
  else
  {
    if ( min == max )
    {
      v7 = min;
      v6 = "Restricted to characters of Level %d.";
LABEL_9:
      _sprintf(numtxt, v6, v7);
      goto LABEL_10;
    }
    _sprintf(numtxt, "Restricted to characters of Levels %d to %d.", min, max);
  }
LABEL_10:
  ItemExamineUI::AddItemInfo(v2, numtxt, 0, 0);
LABEL_11:
  portal_dest.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( AppraisalProfile::InqString(_prof, 0x26u, &portal_dest) )
  {
    AC1Legacy::PStringBase<char>::PStringBase<char>(&strDest, "Destination: ");
    v3 = portal_dest.m_buffer->m_len;
    if ( v3 != 1 && portal_dest.m_buffer != (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer )
      AC1Legacy::PStringBase<char>::append_n_chars(&strDest, portal_dest.m_buffer->m_data, v3 - 1);
    v4 = strDest.m_buffer;
    ItemExamineUI::AddItemInfo(v2, strDest.m_buffer->m_data, 0, 0);
    if ( !InterlockedDecrement((volatile LONG *)&v4->m_cRef) && v4 )
      v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
  }
  v5 = portal_dest.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&portal_dest.m_buffer->m_cRef) )
  {
    if ( v5 )
      v5->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v5, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B2A70) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowUsageLimitInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  signed int v3; // edi@1
  AC1Legacy::PSRefBuffer<char> *v4; // esi@19
  AC1Legacy::PStringBase<char> skill_str; // [sp+Ch] [bp-7F8h]@8
  unsigned int skill; // [sp+10h] [bp-7F4h]@4
  int level_requirement; // [sp+14h] [bp-7F0h]@1
  unsigned int iskill_level; // [sp+18h] [bp-7ECh]@6
  char numtxt[2024]; // [sp+1Ch] [bp-7E8h]@3

  v2 = this;
  v3 = 0;
  level_requirement = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x171u, &level_requirement) && level_requirement > 0 )
  {
    _sprintf(numtxt, "Use requires level %d.", level_requirement);
    ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    v3 = 1;
  }
  skill = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x16Eu, (int *)&skill)
    && skill
    && AppraisalProfile::InqInt(_prof, 0x16Fu, (int *)&iskill_level)
    && iskill_level )
  {
    skill_str.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( !SkillSystem::InqSkillName(skill, &skill_str) )
      AC1Legacy::PStringBase<char>::set(&skill_str, "Unknown Skill");
    _sprintf(numtxt, "Use requires %s of at least %d.", skill_str.m_buffer->m_data, iskill_level);
    if ( !v3 )
      ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    v3 = 1;
    CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&skill_str);
  }
  skill = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x170u, (int *)&skill) && skill )
  {
    skill_str.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( !SkillSystem::InqSkillName(skill, &skill_str) )
      AC1Legacy::PStringBase<char>::set(&skill_str, "Unknown Skill");
    _sprintf(numtxt, "Use requires specialized %s.", skill_str.m_buffer->m_data);
    if ( !v3 )
      ItemExamineUI::AddItemInfo(v2, &name, 0, 1);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    v4 = skill_str.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&skill_str.m_buffer->m_cRef) )
    {
      if ( v4 )
        v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B2C90) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowShortMagicInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  AppraisalProfile *v2; // esi@1
  PSmartArray<unsigned long> *v3; // eax@1
  PSmartArray<unsigned long> *v4; // edi@3
  signed int v5; // ebx@3
  unsigned int v6; // ebp@4
  unsigned int v7; // esi@5
  ClientMagicSystem *v8; // eax@6
  AC1Legacy::PStringBase<char> *v9; // eax@9
  AC1Legacy::PSRefBuffer<char> *v10; // esi@9
  AC1Legacy::PSRefBuffer<char> *v11; // eax@12
  unsigned int v12; // ecx@12
  AC1Legacy::PSRefBuffer<char> *v13; // esi@15
  AppraisalProfile *v14; // esi@20
  LONG v15; // eax@20
  AC1Legacy::PStringBase<char> strSpellName; // [sp+10h] [bp-Ch]@7
  AC1Legacy::PStringBase<char> v17; // [sp+14h] [bp-8h]@9
  ItemExamineUI *v18; // [sp+18h] [bp-4h]@1

  v2 = _prof;
  v3 = _prof->_spellBook;
  v18 = this;
  if ( v3 )
  {
    if ( _prof->success_flag )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&_prof, "Spells: ");
      v4 = v2->_spellBook;
      v5 = 0;
      if ( v4 && (v6 = 0, v4->m_num) )
      {
        do
        {
          v7 = v4->m_data[v6];
          if ( (v7 & 0x80000000) == 0 )
          {
            v8 = ClientMagicSystem::GetMagicSystem();
            if ( !v8 )
            {
              v14 = _prof;
              v15 = InterlockedDecrement(&_prof->success_flag);
              goto LABEL_22;
            }
            ClientMagicSystem::GetSpellName(v8, &strSpellName, v7 & 0x7FFFFFFF);
            if ( v5 )
            {
              AC1Legacy::PStringBase<char>::PStringBase<char>(&v17, ", ");
              AC1Legacy::PStringBase<char>::operator+=((AC1Legacy::PStringBase<char> *)&_prof, v9);
              v10 = v17.m_buffer;
              if ( !InterlockedDecrement((volatile LONG *)&v17.m_buffer->m_cRef) && v10 )
                v10->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v10, 1u);
            }
            else
            {
              v5 = 1;
            }
            v11 = strSpellName.m_buffer;
            v12 = strSpellName.m_buffer->m_len;
            if ( v12 != 1
              && strSpellName.m_buffer != (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer )
            {
              AC1Legacy::PStringBase<char>::append_n_chars(
                (AC1Legacy::PStringBase<char> *)&_prof,
                strSpellName.m_buffer->m_data,
                v12 - 1);
              v11 = strSpellName.m_buffer;
            }
            v13 = v11;
            if ( !InterlockedDecrement((volatile LONG *)&v11->m_cRef) && v13 )
              v13->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v13, 1u);
          }
          ++v6;
        }
        while ( v6 < v4->m_num );
        if ( !v5 )
          goto LABEL_25;
        v14 = _prof;
        ItemExamineUI::AddItemInfo(v18, (const char *)&_prof->armor_profile, 0, 0);
        v15 = InterlockedDecrement(&v14->success_flag);
      }
      else
      {
LABEL_25:
        v14 = _prof;
        v15 = InterlockedDecrement(&_prof->success_flag);
      }
LABEL_22:
      if ( !v15 )
      {
        if ( v14 )
          v14->vfptr->__vecDelDtor((PackObj *)v14, 1u);
      }
    }
    else
    {
      ItemExamineUI::AddItemInfo(this, "Spells: unknown.", 0, 0);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B2E10) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowMagicInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  PSmartArray<unsigned long> *v2; // eax@1
  PSmartArray<unsigned long> *v3; // eax@3
  bool v4; // zf@4
  AC1Legacy::PSRefBuffer<char> *v5; // edi@5
  AC1Legacy::PSRefBuffer<char> *v6; // esi@5
  unsigned int *v7; // eax@13
  unsigned int v8; // ebx@13
  int v9; // esi@13
  ClientMagicSystem *v10; // eax@13
  ClientMagicSystem *v11; // edi@13
  AC1Legacy::PStringBase<char> *v12; // eax@14
  AC1Legacy::PStringBase<char> *v13; // ST10_4@14
  AC1Legacy::PStringBase<char> *v14; // eax@14
  AC1Legacy::PStringBase<char> *v15; // eax@14
  AC1Legacy::PStringBase<char> *v16; // eax@14
  int v17; // esi@14
  int v18; // esi@17
  int v19; // esi@20
  int v20; // esi@23
  AC1Legacy::PSRefBuffer<char> *v21; // esi@27
  unsigned int v22; // eax@27
  unsigned int v23; // eax@33
  AC1Legacy::PSRefBuffer<char> *v24; // esi@38
  AC1Legacy::PSRefBuffer<char> *v25; // esi@41
  unsigned int v26; // edx@44
  ItemExamineUI *v27; // ebx@47
  AC1Legacy::PSRefBuffer<char> *v28; // esi@48
  AC1Legacy::PSRefBuffer<char> *v29; // esi@51
  long double v30; // st7@59
  char *v31; // [sp-Ch] [bp-840h]@61
  int v32; // [sp-4h] [bp-838h]@61
  AC1Legacy::PStringBase<char> strEnchantments; // [sp+10h] [bp-824h]@3
  int iManaCost; // [sp+14h] [bp-820h]@14
  AC1Legacy::PStringBase<char> strSpellDescriptions; // [sp+18h] [bp-81Ch]@3
  int fAddedSpell; // [sp+1Ch] [bp-818h]@3
  unsigned int i; // [sp+20h] [bp-814h]@4
  int iCurMana; // [sp+24h] [bp-810h]@14
  ItemExamineUI *v39; // [sp+28h] [bp-80Ch]@1
  int iSpellcraft; // [sp+2Ch] [bp-808h]@14
  AC1Legacy::PStringBase<char> strSpellName; // [sp+30h] [bp-804h]@14
  AC1Legacy::PStringBase<char> strSpellDesc; // [sp+34h] [bp-800h]@14
  AC1Legacy::PStringBase<char> strSpellText; // [sp+38h] [bp-7FCh]@14
  PSmartArray<unsigned long> *pSpellList; // [sp+3Ch] [bp-7F8h]@3
  int fAddedEnchantment; // [sp+40h] [bp-7F4h]@3
  long double rManaRate; // [sp+44h] [bp-7F0h]@14
  char numtxt[2024]; // [sp+4Ch] [bp-7E8h]@47

  v2 = _prof->_spellBook;
  v39 = this;
  if ( v2 )
  {
    if ( _prof->success_flag )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&strSpellDescriptions, "Spell Descriptions:");
      AC1Legacy::PStringBase<char>::PStringBase<char>(&strEnchantments, "Enchantments:\n");
      v3 = _prof->_spellBook;
      fAddedSpell = 0;
      fAddedEnchantment = 0;
      pSpellList = v3;
      if ( v3 && (v4 = v3->m_num == 0, i = 0, !v4) )
      {
        while ( 1 )
        {
          v7 = v3->m_data;
          v8 = v7[i] & 0x80000000;
          v9 = v7[i] & 0x7FFFFFFF;
          v10 = ClientMagicSystem::GetMagicSystem();
          v11 = v10;
          if ( !v10 )
            break;
          ClientMagicSystem::GetSpellName(v10, &strSpellName, v9);
          ClientMagicSystem::GetSpellDescription(v11, &strSpellDesc, v9);
          AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&iSpellcraft, ": ");
          v13 = v12;
          AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&iManaCost, "\n~ ");
          v15 = AC1Legacy::PStringBase<char>::operator+(v14, (AC1Legacy::PStringBase<char> *)&iCurMana, &strSpellName);
          v16 = AC1Legacy::PStringBase<char>::operator+(v15, (AC1Legacy::PStringBase<char> *)&rManaRate, v13);
          AC1Legacy::PStringBase<char>::operator+(v16, &strSpellText, &strSpellDesc);
          v17 = LODWORD(rManaRate);
          if ( !InterlockedDecrement((volatile LONG *)(LODWORD(rManaRate) + 4)) && v17 )
            (**(void (__thiscall ***)(_DWORD, _DWORD))v17)(v17, 1);
          v18 = iCurMana;
          if ( !InterlockedDecrement((volatile LONG *)(iCurMana + 4)) && v18 )
            (**(void (__thiscall ***)(_DWORD, _DWORD))v18)(v18, 1);
          v19 = iManaCost;
          if ( !InterlockedDecrement((volatile LONG *)(iManaCost + 4)) && v19 )
            (**(void (__thiscall ***)(_DWORD, _DWORD))v19)(v19, 1);
          v20 = iSpellcraft;
          if ( !InterlockedDecrement((volatile LONG *)(iSpellcraft + 4)) && v20 )
            (**(void (__thiscall ***)(_DWORD, _DWORD))v20)(v20, 1);
          if ( v8 )
          {
            v21 = strSpellText.m_buffer;
            v22 = strSpellText.m_buffer->m_len;
            if ( v22 != 1
              && strSpellText.m_buffer != (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer )
              AC1Legacy::PStringBase<char>::append_n_chars(&strEnchantments, strSpellText.m_buffer->m_data, v22 - 1);
            fAddedEnchantment = 1;
          }
          else
          {
            if ( !fAddedSpell )
              fAddedSpell = 1;
            v21 = strSpellText.m_buffer;
            v23 = strSpellText.m_buffer->m_len;
            if ( v23 != 1
              && strSpellText.m_buffer != (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer )
              AC1Legacy::PStringBase<char>::append_n_chars(
                &strSpellDescriptions,
                strSpellText.m_buffer->m_data,
                v23 - 1);
          }
          if ( !InterlockedDecrement((volatile LONG *)&v21->m_cRef) )
            v21->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v21, 1u);
          v24 = strSpellDesc.m_buffer;
          if ( !InterlockedDecrement((volatile LONG *)&strSpellDesc.m_buffer->m_cRef) && v24 )
            v24->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v24, 1u);
          v25 = strSpellName.m_buffer;
          if ( !InterlockedDecrement((volatile LONG *)&strSpellName.m_buffer->m_cRef) && v25 )
            v25->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v25, 1u);
          v26 = pSpellList->m_num;
          ++i;
          if ( i >= v26 )
          {
            v5 = strSpellDescriptions.m_buffer;
            if ( fAddedSpell )
            {
              if ( AppraisalProfile::InqInt(_prof, 0x6Au, &iSpellcraft) )
              {
                _sprintf(numtxt, "Spellcraft: %d.", iSpellcraft);
                v27 = v39;
                ItemExamineUI::AddItemInfo(v39, numtxt, 0, 1);
              }
              else
              {
                v27 = v39;
              }
              if ( AppraisalProfile::InqInt(_prof, 0x6Bu, &iCurMana)
                && AppraisalProfile::InqInt(_prof, 0x6Cu, &iManaCost) )
              {
                _sprintf(numtxt, "Mana: %d / %d.", iCurMana, iManaCost);
                ItemExamineUI::AddItemInfo(v27, numtxt, 0, 1);
              }
              if ( AppraisalProfile::InqFloat(_prof, 5u, &rManaRate) )
              {
                v30 = 1.0 / rManaRate;
                if ( 1.0 / rManaRate < 0.0 )
                  v30 = -v30;
                _sprintf(numtxt, "Mana Cost: 1 point per %d seconds.", (unsigned __int64)(v30 + 0.5));
                v32 = 1;
                v31 = numtxt;
LABEL_67:
                ItemExamineUI::AddItemInfo(v27, v31, 0, v32);
              }
              else if ( AppraisalProfile::InqInt(_prof, 0x75u, &iManaCost) )
              {
                if ( iManaCost <= 0 )
                  _sprintf(numtxt, "Mana Cost: %d.", iManaCost);
                else
                  _sprintf(numtxt, "Mana Cost: %d.\n(Can be reduced by the Mana Conversion skill)", iManaCost);
                v32 = 0;
                v31 = numtxt;
                goto LABEL_67;
              }
              ItemExamineUI::AddItemInfo(v27, v5->m_data, 0, 0);
            }
            else
            {
              v27 = v39;
            }
            v6 = strEnchantments.m_buffer;
            if ( fAddedEnchantment )
              ItemExamineUI::AddItemInfo(v27, strEnchantments.m_buffer->m_data, 0, 0);
            goto LABEL_6;
          }
          v3 = pSpellList;
        }
        v28 = strEnchantments.m_buffer;
        if ( !InterlockedDecrement((volatile LONG *)&strEnchantments.m_buffer->m_cRef) && v28 )
          v28->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v28, 1u);
        v29 = strSpellDescriptions.m_buffer;
        if ( !InterlockedDecrement((volatile LONG *)&strSpellDescriptions.m_buffer->m_cRef) && v29 )
          v29->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v29, 1u);
      }
      else
      {
        v5 = strSpellDescriptions.m_buffer;
        v6 = strEnchantments.m_buffer;
LABEL_6:
        if ( !InterlockedDecrement((volatile LONG *)&v6->m_cRef) && v6 )
          v6->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v6, 1u);
        if ( !InterlockedDecrement((volatile LONG *)&v5->m_cRef) )
        {
          if ( v5 )
            v5->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v5, 1u);
        }
      }
    }
    else
    {
      ItemExamineUI::AddItemInfo(this, "Spells: unknown.", 0, 0);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B3270) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowActivationRequirements(ItemExamineUI *this, AppraisalProfile *_prof)
{
  int v2; // eax@1
  signed int v3; // esi@2
  AC1Legacy::PSRefBuffer<char> *v4; // esi@4
  unsigned int v5; // eax@4
  LONG (__stdcall *v6)(volatile LONG *); // edi@7
  AC1Legacy::PSRefBuffer<char> *v7; // esi@15
  unsigned int v8; // eax@15
  AC1Legacy::PSRefBuffer<char> *v9; // edi@27
  AC1Legacy::PSRefBuffer<char> *v10; // ebx@55
  AC1Legacy::PStringBase<unsigned short> *v11; // eax@56
  unsigned int v12; // esi@56
  AC1Legacy::PSRefBuffer<char> *v13; // esi@59
  AC1Legacy::PStringBase<char> *v14; // eax@65
  AC1Legacy::PStringBase<char> *v15; // eax@65
  unsigned int v16; // esi@65
  AC1Legacy::PSRefBuffer<char> *v17; // esi@68
  AC1Legacy::PSRefBuffer<char> *v18; // esi@71
  AC1Legacy::PSRefBuffer<char> *v19; // esi@74
  AC1Legacy::PSRefBuffer<char> *v20; // esi@77
  AC1Legacy::PStringBase<char> header; // [sp+1Ch] [bp-81Ch]@4
  AC1Legacy::PStringBase<char> activator_name; // [sp+20h] [bp-818h]@14
  AC1Legacy::PStringBase<char> activationReqsString; // [sp+24h] [bp-814h]@2
  unsigned int attribute2nd; // [sp+28h] [bp-810h]@33
  unsigned int heritage_req; // [sp+2Ch] [bp-80Ch]@21
  int iAttributeLimit; // [sp+30h] [bp-808h]@39
  ItemExamineUI *v27; // [sp+34h] [bp-804h]@1
  int has_allowed_activator; // [sp+38h] [bp-800h]@63
  int iRank; // [sp+3Ch] [bp-7FCh]@11
  int iSkillLimit; // [sp+40h] [bp-7F8h]@31
  int iAttribute2ndLimit; // [sp+44h] [bp-7F4h]@47
  int iDifficulty; // [sp+48h] [bp-7F0h]@2
  AC1Legacy::PStringBase<char> activator_msg; // [sp+4Ch] [bp-7ECh]@65
  char numtxt[2024]; // [sp+50h] [bp-7E8h]@4

  v2 = _prof->success_flag;
  v27 = this;
  if ( v2 )
  {
    activationReqsString.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    v3 = 0;
    if ( AppraisalProfile::InqInt(_prof, 0x6Du, &iDifficulty) && iDifficulty > 0 )
    {
      _sprintf(numtxt, "Arcane Lore: %d", iDifficulty);
      AC1Legacy::PStringBase<char>::PStringBase<char>(&header, numtxt);
      v4 = header.m_buffer;
      v5 = header.m_buffer->m_len;
      if ( v5 != 1 && header.m_buffer != (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer )
        AC1Legacy::PStringBase<char>::append_n_chars(&activationReqsString, header.m_buffer->m_data, v5 - 1);
      v6 = InterlockedDecrement;
      if ( !InterlockedDecrement((volatile LONG *)&v4->m_cRef) )
        v4->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v4, 1u);
      v3 = 1;
    }
    else
    {
      v6 = InterlockedDecrement;
    }
    if ( AppraisalProfile::InqInt(_prof, 0x6Eu, &iRank) && iRank >= 1 )
    {
      if ( v3 )
      {
        AC1Legacy::PStringBase<char>::PStringBase<char>(&activator_name, ", ");
        AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &activator_name);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&activator_name);
      }
      _sprintf(numtxt, "Allegiance Rank: %d", iRank);
      AC1Legacy::PStringBase<char>::PStringBase<char>(&header, numtxt);
      v7 = header.m_buffer;
      v8 = header.m_buffer->m_len;
      if ( v8 != 1 && header.m_buffer != (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer )
        AC1Legacy::PStringBase<char>::append_n_chars(&activationReqsString, header.m_buffer->m_data, v8 - 1);
      if ( !v6((volatile LONG *)&v7->m_cRef) )
        v7->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v7, 1u);
      v3 = 1;
    }
    heritage_req = 0;
    if ( AppraisalProfile::InqInt(_prof, 0xBCu, (int *)&heritage_req) && heritage_req )
    {
      activator_name.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( AppraisalSystem::InqHeritageGroupDisplayName(heritage_req, &activator_name) )
      {
        if ( v3 )
        {
          AC1Legacy::PStringBase<char>::PStringBase<char>(&header, ", ");
          AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &header);
          CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&header);
        }
        AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &activator_name);
        v3 = 1;
      }
      v9 = activator_name.m_buffer;
      if ( !InterlockedDecrement((volatile LONG *)&activator_name.m_buffer->m_cRef) && v9 )
        v9->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v9, 1u);
      v6 = InterlockedDecrement;
    }
    if ( AppraisalProfile::InqInt(_prof, 0x73u, &iSkillLimit)
      && iSkillLimit > 0
      && AppraisalProfile::InqInt(_prof, 0xB0u, (int *)&attribute2nd) )
    {
      activator_name.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( SkillSystem::InqSkillName(attribute2nd, &activator_name) )
      {
        if ( v3 )
        {
          AC1Legacy::PStringBase<char>::PStringBase<char>(&header, ", ");
          AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &header);
          CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&header);
        }
        _sprintf(numtxt, "%s: %d", activator_name.m_buffer->m_data, iSkillLimit);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&header, numtxt);
        AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &header);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&header);
        v3 = 1;
      }
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&activator_name);
    }
    if ( AppraisalProfile::InqInt(_prof, 0x102u, &iAttributeLimit)
      && iAttributeLimit > 0
      && AppraisalProfile::InqInt(_prof, 0x101u, (int *)&attribute2nd) )
    {
      activator_name.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( SkillSystem::InqAttributeName(attribute2nd, &activator_name) )
      {
        if ( v3 )
        {
          AC1Legacy::PStringBase<char>::PStringBase<char>(&header, ", ");
          AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &header);
          CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&header);
        }
        _sprintf(numtxt, "%s: %d", activator_name.m_buffer->m_data, iAttributeLimit);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&header, numtxt);
        AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &header);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&header);
        v3 = 1;
      }
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&activator_name);
    }
    if ( AppraisalProfile::InqInt(_prof, 0x104u, &iAttribute2ndLimit)
      && iAttribute2ndLimit > 0
      && AppraisalProfile::InqInt(_prof, 0x103u, (int *)&attribute2nd) )
    {
      activator_name.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( SkillSystem::InqAttribute2ndName(attribute2nd, &activator_name) )
      {
        if ( v3 )
        {
          AC1Legacy::PStringBase<char>::PStringBase<char>(&header, ", ");
          AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &header);
          CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&header);
        }
        _sprintf(numtxt, "%s: %d", activator_name.m_buffer->m_data, iAttribute2ndLimit);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&header, numtxt);
        AC1Legacy::PStringBase<char>::operator+=(&activationReqsString, &header);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&header);
      }
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&activator_name);
    }
    v10 = activationReqsString.m_buffer;
    if ( activationReqsString.m_buffer->m_len != 1 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&header, "Activation requires ");
      v11 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                        &header,
                                                        (AC1Legacy::PStringBase<char> *)&attribute2nd,
                                                        &activationReqsString);
      AC1Legacy::PStringBase<unsigned short>::operator=(
        (AC1Legacy::PStringBase<unsigned short> *)&activationReqsString,
        v11);
      v12 = attribute2nd;
      if ( !v6((volatile LONG *)(attribute2nd + 4)) && v12 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v12)(v12, 1);
      ItemExamineUI::AddItemInfo(v27, activationReqsString.m_buffer->m_data, 0, 1);
      v13 = header.m_buffer;
      if ( !v6((volatile LONG *)&header.m_buffer->m_cRef) && v13 )
        v13->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v13, 1u);
      v10 = activationReqsString.m_buffer;
    }
    has_allowed_activator = 0;
    if ( AppraisalProfile::InqBool(_prof, 0x5Eu, &has_allowed_activator) && has_allowed_activator == 1 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&activator_name, "the original owner");
      AppraisalProfile::InqString(_prof, 0x19u, &activator_name);
      AC1Legacy::PStringBase<char>::PStringBase<char>(&header, ".");
      AC1Legacy::PStringBase<char>::PStringBase<char>(&activationReqsString, "This item can only be activated by ");
      v15 = AC1Legacy::PStringBase<char>::operator+(v14, (AC1Legacy::PStringBase<char> *)&attribute2nd, &activator_name);
      AC1Legacy::PStringBase<char>::operator+(v15, &activator_msg, &header);
      v16 = attribute2nd;
      if ( !v6((volatile LONG *)(attribute2nd + 4)) && v16 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v16)(v16, 1);
      v17 = activationReqsString.m_buffer;
      if ( !v6((volatile LONG *)&activationReqsString.m_buffer->m_cRef) && v17 )
        v17->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v17, 1u);
      v18 = header.m_buffer;
      if ( !v6((volatile LONG *)&header.m_buffer->m_cRef) && v18 )
        v18->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v18, 1u);
      v19 = activator_msg.m_buffer;
      ItemExamineUI::AddItemInfo(v27, activator_msg.m_buffer->m_data, 0, 1);
      if ( !v6((volatile LONG *)&v19->m_cRef) && v19 )
        v19->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v19, 1u);
      v20 = activator_name.m_buffer;
      if ( !v6((volatile LONG *)&activator_name.m_buffer->m_cRef) && v20 )
        v20->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v20, 1u);
    }
    if ( !v6((volatile LONG *)&v10->m_cRef) )
    {
      if ( v10 )
        v10->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v10, 1u);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B3900) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowManaStoneInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  int iCurMana; // [sp+8h] [bp-7FCh]@2
  long double rEfficiency; // [sp+Ch] [bp-7F8h]@4
  long double rChanceOfDestruction; // [sp+14h] [bp-7F0h]@6
  char numtxt[2024]; // [sp+1Ch] [bp-7E8h]@3

  v2 = this;
  if ( !_prof->_spellBook )
  {
    iCurMana = 0;
    if ( AppraisalProfile::InqInt(_prof, 0x6Bu, &iCurMana) )
    {
      _sprintf(numtxt, "Stored Mana: %d", iCurMana);
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    }
    rEfficiency = 0.0;
    if ( AppraisalProfile::InqFloat(_prof, 0x57u, &rEfficiency) )
    {
      _sprintf(numtxt, "Efficiency: %d%%", (unsigned __int64)(rEfficiency * 100.0));
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    }
    rChanceOfDestruction = 1.0;
    if ( AppraisalProfile::InqFloat(_prof, 0x89u, &rChanceOfDestruction) )
    {
      _sprintf(numtxt, "Chance of Destruction: %d%%", (unsigned __int64)(rChanceOfDestruction * 100.0));
      ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
    }
  }
}

//----- (004B3A20) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowRemainingUses(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // esi@1
  ACCWeenieObject *v3; // ecx@10
  int unlimited_use; // [sp+Ch] [bp-7F4h]@6
  int iKeys; // [sp+10h] [bp-7F0h]@1
  int iUses; // [sp+14h] [bp-7ECh]@7
  char numtxt[2024]; // [sp+18h] [bp-7E8h]@3

  v2 = this;
  if ( AppraisalProfile::InqInt(_prof, 0xC1u, &iKeys) )
  {
    if ( iKeys == 1 )
      _sprintf(numtxt, "Contains %d key.", 1);
    else
      _sprintf(numtxt, "Contains %d keys.", iKeys);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
  }
  unlimited_use = 0;
  AppraisalProfile::InqBool(_prof, 0x3Fu, &unlimited_use);
  if ( unlimited_use )
  {
    ItemExamineUI::AddItemInfo(v2, "Number of uses remaining:  Unlimited", 0, 1);
  }
  else if ( AppraisalProfile::InqInt(_prof, 0x5Cu, &iUses) )
  {
    _sprintf(numtxt, "Number of uses remaining: %d", iUses);
    ItemExamineUI::AddItemInfo(v2, numtxt, 0, 1);
  }
  else if ( !_prof->success_flag )
  {
    v3 = v2->cur_weenobj;
    if ( v3->pwd._bitfield & 0x30000
      || ((int (*)(void))v3->vfptr[29].__vecDelDtor)()
      && (AppraisalProfile::IsHookedItemHealer(_prof) || AppraisalProfile::IsHookedItemLockpick(_prof)) )
      ItemExamineUI::AddItemInfo(v2, "Number of uses remaining:  Unknown", 0, 0);
  }
}

//----- (004B3B60) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowRareInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  ItemExamineUI *v2; // edi@1
  AC1Legacy::PSRefBuffer<char> *v3; // esi@3
  AppraisalProfile *v4; // esi@7
  int rareUsesTimer; // [sp+10h] [bp-Ch]@1
  AC1Legacy::PStringBase<char> timerText; // [sp+14h] [bp-8h]@3
  int iRareID; // [sp+18h] [bp-4h]@6

  v2 = this;
  rareUsesTimer = 0;
  if ( AppraisalProfile::InqBool(_prof, 0x6Cu, &rareUsesTimer) )
  {
    if ( rareUsesTimer == 1 )
    {
      timerText.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      AC1Legacy::PStringBase<char>::sprintf(
        &timerText,
        "This rare item has a timer restriction of %d minutes. You will not be able to use another rare item with a timer within %d minutes of using this one.",
        3,
        3);
      v3 = timerText.m_buffer;
      ItemExamineUI::AddItemInfo(v2, timerText.m_buffer->m_data, 0, 0);
      if ( !InterlockedDecrement((volatile LONG *)&v3->m_cRef) )
      {
        if ( v3 )
          v3->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v3, 1u);
      }
    }
  }
  if ( AppraisalProfile::InqInt(_prof, 0x11u, &iRareID) )
  {
    _prof = (AppraisalProfile *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&_prof, "Rare #%d", iRareID);
    v4 = _prof;
    ItemExamineUI::AddItemInfo(v2, (const char *)&_prof->armor_profile, 0, 0);
    if ( !InterlockedDecrement(&v4->success_flag) )
    {
      if ( v4 )
        v4->vfptr->__vecDelDtor((PackObj *)v4, 1u);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B3C60) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowItemLevelInfo(ItemExamineUI *this, AppraisalProfile *_prof)
{
  AC1Legacy::PSRefBuffer<char> *v2; // edi@1
  ItemExamineUI *v3; // esi@1
  AppraisalProfile *v4; // ebp@1
  int v5; // eax@7
  int v6; // ebp@7
  int v7; // eax@7
  int v8; // edi@9
  unsigned int v9; // edx@9
  unsigned int v10; // ebx@9
  AC1Legacy::PStringBase<char> text; // [sp+10h] [bp-60h]@1
  int item_max_level; // [sp+14h] [bp-5Ch]@1
  int item_xp_style; // [sp+18h] [bp-58h]@1
  int cloak_proc; // [sp+1Ch] [bp-54h]@10
  unsigned __int64 item_base_xp; // [sp+20h] [bp-50h]@1
  unsigned __int64 item_xp; // [sp+28h] [bp-48h]@1
  char formatted_next_xp[32]; // [sp+30h] [bp-40h]@9
  char formatted_item_xp[32]; // [sp+50h] [bp-20h]@9

  v2 = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  v3 = this;
  item_base_xp = 0i64;
  item_xp = 0i64;
  item_max_level = 0;
  item_xp_style = 0;
  text.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  v4 = _prof;
  if ( AppraisalProfile::InqInt64(_prof, 5u, (__int64 *)&item_base_xp)
    && item_base_xp > 0
    && AppraisalProfile::InqInt(_prof, 0x13Fu, &item_max_level)
    && item_max_level > 0
    && AppraisalProfile::InqInt(_prof, 0x140u, &item_xp_style)
    && item_xp_style > 0 )
  {
    AppraisalProfile::InqInt64(_prof, 4u, (__int64 *)&item_xp);
    v5 = ExperienceSystem::ItemTotalXPToLevel(item_xp, item_base_xp, item_max_level, item_xp_style);
    v6 = v5;
    v7 = v5 + 1;
    if ( v7 > item_max_level )
      v7 = item_max_level;
    v8 = ExperienceSystem::ItemLevelToTotalXP(v7, item_base_xp, item_max_level, item_xp_style);
    v10 = v9;
    ExperienceSystem::XPToString(item_xp, formatted_item_xp);
    ExperienceSystem::XPToString(__PAIR__(v10, v8), formatted_next_xp);
    AC1Legacy::PStringBase<char>::sprintf(&text, "Item Level: %d / %d", v6, item_max_level);
    ItemExamineUI::AddItemInfo(v3, text.m_buffer->m_data, 0, 1);
    AC1Legacy::PStringBase<char>::sprintf(&text, "Item XP: %s / %s", formatted_item_xp, formatted_next_xp);
    v2 = text.m_buffer;
    ItemExamineUI::AddItemInfo(v3, text.m_buffer->m_data, 0, 1);
    ItemExamineUI::AddItemInfo(v3, &name, 0, 1);
    v4 = _prof;
  }
  cloak_proc = 0;
  if ( AppraisalProfile::InqInt(v4, 0x160u, &cloak_proc) && cloak_proc == 2 )
  {
    AC1Legacy::PStringBase<char>::sprintf(
      &text,
      "This cloak has a chance to reduce an incoming attack by %d damage.",
      200);
    v2 = text.m_buffer;
    ItemExamineUI::AddItemInfo(v3, text.m_buffer->m_data, 0, 1);
    ItemExamineUI::AddItemInfo(v3, &name, 0, 1);
  }
  if ( !InterlockedDecrement((volatile LONG *)&v2->m_cRef) )
  {
    if ( v2 )
      v2->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v2, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B3E70) --------------------------------------------------------
void __thiscall BasicCreatureExamineUI::SetLevelValueText(BasicCreatureExamineUI *this, int level)
{
  BasicCreatureExamineUI *v2; // esi@1
  int v3; // edi@2
  int v4; // edi@5
  PStringBase<unsigned short> *v5; // eax@5
  int v6; // esi@5
  int v7; // esi@11

  v2 = this;
  if ( this->m_levelValueText )
  {
    v3 = level;
    if ( level <= 0 )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&level, L"???");
      UIElement_Text::SetText(v2->m_levelValueText, (PStringBase<unsigned short> *)&level);
      v7 = level - 20;
      if ( !InterlockedDecrement((volatile LONG *)(level - 20 + 4)) && v7 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v7)(v7, 1);
    }
    else
    {
      level = AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( !AC1Legacy::PStringBase<char>::convert((AC1Legacy::PStringBase<char> *)&level, v3, 1) )
        AC1Legacy::PStringBase<char>::set((AC1Legacy::PStringBase<char> *)&level, "???");
      v4 = level;
      PStringBase<unsigned short>::PStringBase<unsigned short>(
        (PStringBase<unsigned short> *)&level,
        0,
        (const char *)(level + 20));
      UIElement_Text::SetText(v2->m_levelValueText, v5);
      v6 = level - 20;
      if ( !InterlockedDecrement((volatile LONG *)(level - 20 + 4)) && v6 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v6)(v6, 1);
      if ( !InterlockedDecrement((volatile LONG *)(v4 + 4)) )
      {
        if ( v4 )
          (**(void (__thiscall ***)(_DWORD, _DWORD))v4)(v4, 1);
      }
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B3F70) --------------------------------------------------------
void __thiscall BasicCreatureExamineUI::SetAppraiseInfo(BasicCreatureExamineUI *this, AppraisalProfile *_prof, int is_new)
{
  BasicCreatureExamineUI *v3; // ebx@1
  AppraisalProfile *v4; // edi@1
  unsigned int v5; // esi@1
  CreatureAppraisalProfile cprof; // [sp+Ch] [bp-38h]@1

  v3 = this;
  CreatureAppraisalProfile::CreatureAppraisalProfile(&cprof);
  v4 = _prof;
  v5 = 0;
  if ( AppraisalProfile::InqCreature(_prof, &cprof) )
  {
    _prof = 0;
    AppraisalProfile::InqInt(v4, 0x19u, (int *)&_prof);
    BasicCreatureExamineUI::SetLevelValueText(v3, (int)_prof);
  }
  if ( BasicCreatureExamineUI::m_rgTokens.m_num > 0 )
  {
    do
      ((void (__stdcall *)(_DWORD))BasicCreatureExamineUI::m_rgTokens.m_data[v5++]->vfptr->hits_walkable)(v4);
    while ( v5 < BasicCreatureExamineUI::m_rgTokens.m_num );
  }
  AppraisalProfile::operator=((int)&v3->cur_prof, (int)v4);
}

//----- (004B3FF0) --------------------------------------------------------
void __thiscall CreatureExamineUI::SetAppraiseInfo(CreatureExamineUI *this, AppraisalProfile *_prof, int is_new)
{
  CreatureExamineUI *v3; // ebp@1
  PStringBase<unsigned short> *v4; // eax@4
  char *v5; // edi@4
  UIElement_ListBox *v6; // ecx@10
  UIElement *v7; // ecx@12
  UIElement_Text *v8; // eax@13
  AC1Legacy::PSRefBuffer<char> *v9; // ebx@14
  char *v10; // edi@17
  unsigned int v11; // edi@20
  unsigned int v12; // eax@23
  PStringBase<unsigned short> *v13; // eax@23
  char *v14; // edi@23
  char *v15; // edi@26
  char *v16; // edi@33
  unsigned int v17; // edi@36
  unsigned int v18; // eax@40
  PStringBase<unsigned short> *v19; // eax@40
  char *v20; // edi@40
  char *v21; // edi@43
  char *v22; // edi@49
  unsigned int v23; // edi@52
  PStringBase<unsigned short> *v24; // eax@56
  char *v25; // edi@56
  char *v26; // edi@59
  char *v27; // edi@63
  unsigned int v28; // edi@66
  AC1Legacy::PStringBase<char> strName; // [sp+30h] [bp-6Ch]@3
  unsigned int creatureType; // [sp+34h] [bp-68h]@2
  int crit_damage_rating; // [sp+38h] [bp-64h]@14
  int damage_rating; // [sp+3Ch] [bp-60h]@14
  PStringBase<unsigned short> _label; // [sp+40h] [bp-5Ch]@4
  int crit_damage_resist_rating; // [sp+44h] [bp-58h]@14
  int damage_resist_rating; // [sp+48h] [bp-54h]@14
  int life_resist_rating; // [sp+4Ch] [bp-50h]@14
  int dot_resist_rating; // [sp+50h] [bp-4Ch]@14
  int crit_rating; // [sp+54h] [bp-48h]@14
  int crit_resist_rating; // [sp+58h] [bp-44h]@14
  int healing_boost_rating; // [sp+5Ch] [bp-40h]@14
  PStringBase<unsigned short> v41; // [sp+60h] [bp-3Ch]@23
  CreatureAppraisalProfile cprof; // [sp+64h] [bp-38h]@1

  v3 = this;
  CreatureAppraisalProfile::CreatureAppraisalProfile(&cprof);
  if ( AppraisalProfile::InqCreature(_prof, &cprof) )
  {
    creatureType = 0;
    AppraisalProfile::InqInt(_prof, 2u, (int *)&creatureType);
    if ( creatureType )
    {
      strName.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      if ( AppraisalSystem::InqCreatureDisplayName(creatureType, &strName) )
      {
        PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, strName.m_buffer->m_data);
        UIElement_Text::SetText(v3->m_creatureDisplayName, v4);
        v5 = (char *)&_label.m_charbuffer[-1].m_data[6];
        if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) )
        {
          if ( v5 )
            (**(void (__thiscall ***)(char *, signed int))v5)(v5, 1);
        }
      }
      _label.m_charbuffer = (PSRefBufferCharData<unsigned short> *)strName.m_buffer;
      if ( !InterlockedDecrement((volatile LONG *)&strName.m_buffer->m_cRef) && _label.m_charbuffer )
        (**(void (__stdcall ***)(_DWORD))&_label.m_charbuffer->m_data[0])(1);
    }
  }
  v6 = v3->m_extraInfoList;
  if ( v6 )
    UIElement_ListBox::Flush(v6);
  v7 = v3->m_basicCreatureExamineBaseField;
  if ( v7 )
  {
    v8 = (UIElement_Text *)UIElement::GetChildRecursive(v7, 0x1000053Au);
    UIElement_Text::ClearAllText(v8);
  }
  damage_rating = 0;
  damage_resist_rating = 0;
  crit_rating = 0;
  crit_damage_rating = 0;
  crit_resist_rating = 0;
  crit_damage_resist_rating = 0;
  healing_boost_rating = 0;
  dot_resist_rating = 0;
  life_resist_rating = 0;
  AppraisalProfile::InqInt(_prof, 0x133u, &damage_rating);
  AppraisalProfile::InqInt(_prof, 0x134u, &damage_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x139u, &crit_rating);
  AppraisalProfile::InqInt(_prof, 0x13Au, &crit_damage_rating);
  AppraisalProfile::InqInt(_prof, 0x13Bu, &crit_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x13Cu, &crit_damage_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x143u, &healing_boost_rating);
  AppraisalProfile::InqInt(_prof, 0x15Eu, &dot_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x15Fu, &life_resist_rating);
  v9 = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  strName.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  creatureType = 0;
  if ( damage_rating > 0 || crit_rating > 0 || crit_damage_rating > 0 )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&creatureType, &word_794320);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
    BasicCreatureExamineUI::AddLineToMiscInfo(
      (BasicCreatureExamineUI *)&v3->vfptr,
      &_label,
      (PStringBase<unsigned short> *)&creatureType,
      0);
    v10 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v10 )
      (**(void (__thiscall ***)(char *, signed int))v10)(v10, 1);
    v11 = creatureType - 20;
    if ( !InterlockedDecrement((volatile LONG *)(creatureType - 20 + 4)) && v11 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v11)(v11, 1);
    creatureType = 1;
    AC1Legacy::PStringBase<char>::sprintf(&strName, "%Rating: %d/%d", damage_rating, crit_damage_rating);
    v12 = _wcslen(L"Dmg/CritDmg");
    PStringBase<unsigned short>::allocate_ref_buffer(&_label, v12);
    _wcscpy(_label.m_charbuffer->m_data, L"Dmg/CritDmg");
    v9 = strName.m_buffer;
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v41, 0, strName.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo((BasicCreatureExamineUI *)&v3->vfptr, &_label, v13, 0);
    v14 = (char *)&v41.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v41.m_charbuffer[-1].m_data[8]) && v14 )
      (**(void (__thiscall ***)(char *, signed int))v14)(v14, 1);
    v15 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v15 )
      (**(void (__thiscall ***)(char *, signed int))v15)(v15, 1);
  }
  if ( damage_resist_rating > 0 || crit_resist_rating > 0 || crit_damage_resist_rating > 0 )
  {
    if ( !creatureType )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(
        (PStringBase<unsigned short> *)&creatureType,
        &word_794320);
      PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
      BasicCreatureExamineUI::AddLineToMiscInfo(
        (BasicCreatureExamineUI *)&v3->vfptr,
        &_label,
        (PStringBase<unsigned short> *)&creatureType,
        0);
      v16 = (char *)&_label.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v16 )
        (**(void (__thiscall ***)(char *, signed int))v16)(v16, 1);
      v17 = creatureType - 20;
      if ( !InterlockedDecrement((volatile LONG *)(creatureType - 20 + 4)) && v17 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v17)(v17, 1);
      creatureType = 1;
    }
    AC1Legacy::PStringBase<char>::sprintf(&strName, "%Resist: %d/%d", damage_resist_rating, crit_damage_resist_rating);
    v18 = _wcslen(L"Dmg/CritDmg");
    PStringBase<unsigned short>::allocate_ref_buffer(&_label, v18);
    _wcscpy(_label.m_charbuffer->m_data, L"Dmg/CritDmg");
    v9 = strName.m_buffer;
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v41, 0, strName.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo((BasicCreatureExamineUI *)&v3->vfptr, &_label, v19, 0);
    v20 = (char *)&v41.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v41.m_charbuffer[-1].m_data[8]) && v20 )
      (**(void (__thiscall ***)(char *, signed int))v20)(v20, 1);
    v21 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v21 )
      (**(void (__thiscall ***)(char *, signed int))v21)(v21, 1);
  }
  if ( dot_resist_rating > 0 || life_resist_rating > 0 )
  {
    if ( !creatureType )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(
        (PStringBase<unsigned short> *)&creatureType,
        &word_794320);
      PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
      BasicCreatureExamineUI::AddLineToMiscInfo(
        (BasicCreatureExamineUI *)&v3->vfptr,
        &_label,
        (PStringBase<unsigned short> *)&creatureType,
        0);
      v22 = (char *)&_label.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v22 )
        (**(void (__thiscall ***)(char *, signed int))v22)(v22, 1);
      v23 = creatureType - 20;
      if ( !InterlockedDecrement((volatile LONG *)(creatureType - 20 + 4)) && v23 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v23)(v23, 1);
      creatureType = 1;
    }
    AC1Legacy::PStringBase<char>::sprintf(&strName, "%Resist: %d/%d", dot_resist_rating, life_resist_rating);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"DoT/Life:");
    v9 = strName.m_buffer;
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v41, 0, strName.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo((BasicCreatureExamineUI *)&v3->vfptr, &_label, v24, 0);
    v25 = (char *)&v41.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v41.m_charbuffer[-1].m_data[8]) && v25 )
      (**(void (__thiscall ***)(char *, signed int))v25)(v25, 1);
    v26 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v26 )
      (**(void (__thiscall ***)(char *, signed int))v26)(v26, 1);
  }
  if ( creatureType )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&creatureType, &word_794320);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
    BasicCreatureExamineUI::AddLineToMiscInfo(
      (BasicCreatureExamineUI *)&v3->vfptr,
      &_label,
      (PStringBase<unsigned short> *)&creatureType,
      0);
    v27 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v27 )
      (**(void (__thiscall ***)(char *, signed int))v27)(v27, 1);
    v28 = creatureType - 20;
    if ( !InterlockedDecrement((volatile LONG *)(creatureType - 20 + 4)) && v28 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v28)(v28, 1);
  }
  BasicCreatureExamineUI::SetAppraiseInfo((BasicCreatureExamineUI *)&v3->vfptr, _prof, is_new);
  if ( !InterlockedDecrement((volatile LONG *)&v9->m_cRef) )
  {
    if ( v9 )
      v9->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v9, 1u);
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B45F0) --------------------------------------------------------
void __thiscall CharExamineUI::SetAppraiseInfo(CharExamineUI *this, AppraisalProfile *_prof, int is_new)
{
  CharExamineUI *v3; // edi@1
  PStringBase<unsigned short> *v4; // eax@4
  char *v5; // edi@4
  char v6; // bl@7
  char *v7; // edi@10
  BasicCreatureExamineUI *v8; // ebx@15
  PStringBase<unsigned short> *v9; // eax@15
  char *v10; // edi@15
  PSRefBufferCharData<unsigned short> *v11; // edi@19
  ACCWeenieObject *v12; // ecx@23
  char *v13; // edi@25
  UIElement_ListBox *v14; // ecx@32
  signed int v15; // ebx@34
  InterfaceSystem *v16; // eax@34
  PSRefBufferCharData<unsigned short> *v17; // edi@34
  int v18; // ebp@36
  AC1Legacy::PStringBase<unsigned short> *v19; // eax@61
  int v20; // STA4_4@77
  AC1Legacy::PSRefBuffer<char> *v21; // ebx@77
  PStringBase<unsigned short> *v22; // eax@77
  char *v23; // edi@77
  char *v24; // edi@80
  AC1Legacy::PSRefBuffer<char> *v25; // edi@86
  BasicCreatureExamineUI *v26; // ebp@89
  const char *v27; // eax@89
  PSRefBufferCharData<unsigned short> *v28; // edi@89
  AC1Legacy::PSRefBuffer<char> *v29; // ebx@90
  gmExaminationUI *v30; // edi@97
  PStringBase<unsigned short> *v31; // eax@98
  char *v32; // edi@98
  PStringBase<unsigned short> *v33; // eax@103
  char *v34; // edi@103
  PStringBase<unsigned short> *v35; // eax@110
  PStringBase<unsigned short> *v36; // eax@111
  PStringBase<unsigned short> *v37; // eax@111
  char *v38; // edi@119
  char *v39; // edi@122
  BasicCreatureExamineUI *v40; // ebp@126
  char *v41; // edi@126
  char *v42; // edi@129
  int v43; // eax@132
  int v44; // eax@135
  int v45; // eax@138
  PStringBase<unsigned short> *v46; // eax@141
  char *v47; // edi@141
  char *v48; // edi@144
  int v49; // eax@147
  int v50; // eax@150
  int v51; // eax@153
  PStringBase<unsigned short> *v52; // eax@156
  char *v53; // edi@156
  char *v54; // edi@159
  int v55; // eax@162
  int v56; // eax@165
  int v57; // eax@168
  PSRefBufferCharData<unsigned short> *v58; // ebp@171
  AC1Legacy::PSRefBuffer<char> *v59; // ebx@171
  PStringBase<unsigned short> *v60; // eax@171
  char *v61; // edi@171
  char *v62; // edi@174
  AC1Legacy::PSRefBuffer<char> *v63; // edi@183
  signed int v64; // ebx@186
  BasicCreatureExamineUI *v65; // ebp@189
  char *v66; // edi@189
  char *v67; // edi@192
  PStringBase<unsigned short> *v68; // eax@195
  char *v69; // edi@195
  char *v70; // edi@198
  char *v71; // edi@206
  char *v72; // edi@209
  PStringBase<unsigned short> *v73; // eax@213
  char *v74; // edi@213
  char *v75; // edi@216
  char *v76; // edi@222
  char *v77; // edi@225
  PStringBase<unsigned short> *v78; // eax@229
  char *v79; // edi@229
  char *v80; // edi@232
  char *v81; // edi@236
  char *v82; // edi@239
  PStringBase<unsigned short> *v83; // eax@243
  char *v84; // edi@243
  char *v85; // edi@246
  PStringBase<unsigned short> *v86; // eax@250
  char *v87; // edi@250
  char *v88; // edi@253
  char *v89; // edi@257
  char *v90; // edi@260
  char *v91; // edi@264
  char *v92; // edi@267
  char *v93; // edi@271
  char *v94; // edi@274
  char *v95; // edi@281
  char *v96; // edi@284
  char *v97; // edi@288
  char *v98; // edi@291
  AC1Legacy::PSRefBuffer<char> *v99; // edi@294
  PSRefBufferCharData<unsigned short> *v100; // edi@297
  AC1Legacy::PSRefBuffer<char> *v101; // edi@300
  AC1Legacy::PSRefBuffer<char> *v102; // edi@305
  AC1Legacy::PSRefBuffer<char> *v103; // edi@308
  AC1Legacy::PSRefBuffer<char> *v104; // edi@311
  unsigned int v105; // eax@314
  BasicCreatureExamineUI *v106; // ebx@314
  char *v107; // edi@314
  int v108; // edi@317
  int time_4; // [sp+A0h] [bp-134h]@34
  PStringBase<unsigned short> _label; // [sp+B8h] [bp-11Ch]@4
  PStringBase<unsigned short> ageStr; // [sp+BCh] [bp-118h]@60
  PStringBase<unsigned short> strValueText; // [sp+C0h] [bp-114h]@8
  AC1Legacy::PStringBase<char> armorStr2; // [sp+C4h] [bp-110h]@42
  AC1Legacy::PStringBase<char> armorStr1; // [sp+C8h] [bp-10Ch]@42
  int iStat; // [sp+CCh] [bp-108h]@97
  PStringBase<unsigned short> v116; // [sp+D0h] [bp-104h]@36
  AC1Legacy::PStringBase<char> sStatVal; // [sp+D4h] [bp-100h]@34
  BasicCreatureExamineUI *v118; // [sp+D8h] [bp-FCh]@1
  AC1Legacy::PStringBase<char> genderHeritageStr; // [sp+DCh] [bp-F8h]@4
  int crit_resist_rating; // [sp+E0h] [bp-F4h]@186
  int my_faction_bits; // [sp+E4h] [bp-F0h]@34
  AC1Legacy::PStringBase<char> sStatVal2; // [sp+E8h] [bp-ECh]@34
  int life_resist_rating; // [sp+ECh] [bp-E8h]@186
  unsigned int gender; // [sp+F0h] [bp-E4h]@2
  int crit_damage_resist_rating; // [sp+F4h] [bp-E0h]@186
  int crit_damage_rating; // [sp+F8h] [bp-DCh]@186
  int dot_resist_rating; // [sp+FCh] [bp-D8h]@186
  int damage_resist_rating; // [sp+100h] [bp-D4h]@186
  unsigned int heritage; // [sp+104h] [bp-D0h]@2
  int damage_rating; // [sp+108h] [bp-CCh]@186
  int crit_rating; // [sp+10Ch] [bp-C8h]@186
  AC1Legacy::PStringBase<char> txt; // [sp+110h] [bp-C4h]@34
  unsigned int displayTitleID; // [sp+114h] [bp-C0h]@7
  unsigned int creature; // [sp+118h] [bp-BCh]@2
  int faction_bits; // [sp+11Ch] [bp-B8h]@34
  InterfacePtr<PlayerDesc> playerDesc; // [sp+120h] [bp-B4h]@34
  int healing_boost_rating; // [sp+128h] [bp-ACh]@186
  CAllegianceData alleg_data; // [sp+12Ch] [bp-A8h]@1
  CreatureAppraisalProfile cprof; // [sp+164h] [bp-70h]@1
  CreatureAppraisalProfile cur_cprof; // [sp+19Ch] [bp-38h]@2

  v3 = this;
  v118 = (BasicCreatureExamineUI *)this;
  CreatureAppraisalProfile::CreatureAppraisalProfile(&cprof);
  CAllegianceData::CAllegianceData(&alleg_data);
  if ( !AppraisalProfile::InqCreature(_prof, &cprof) )
    goto LABEL_314;
  CreatureAppraisalProfile::CreatureAppraisalProfile(&cur_cprof);
  AppraisalProfile::InqCreature(&v3->cur_prof, &cur_cprof);
  gender = 0;
  AppraisalProfile::InqInt(_prof, 0x71u, (int *)&gender);
  alleg_data._gender = gender;
  heritage = 0;
  AppraisalProfile::InqInt(_prof, 0xBCu, (int *)&heritage);
  alleg_data._hg = heritage;
  creature = 0;
  if ( !heritage )
    AppraisalProfile::InqInt(_prof, 2u, (int *)&creature);
  genderHeritageStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  AppraisalSystem::InqGenderHeritageDisplay(gender, heritage, creature, &genderHeritageStr);
  PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, genderHeritageStr.m_buffer->m_data);
  UIElement_Text::SetText(v3->m_displayText_Heritage, v4);
  v5 = (char *)&_label.m_charbuffer[-1].m_data[6];
  if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v5 )
    (**(void (__thiscall ***)(char *, signed int))v5)(v5, 1);
  displayTitleID = 0;
  v6 = 0;
  if ( !AppraisalProfile::InqInt(_prof, 0x105u, (int *)&displayTitleID) )
    goto LABEL_323;
  strValueText.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
  if ( CharacterTitleTable::GetCharacterTitleFromID(displayTitleID, &strValueText) )
  {
    UIElement_Text::SetText((UIElement_Text *)v118[1].cur_objid, &strValueText);
    v6 = 1;
  }
  v7 = (char *)&strValueText.m_charbuffer[-1].m_data[6];
  if ( !InterlockedDecrement((volatile LONG *)&strValueText.m_charbuffer[-1].m_data[8]) && v7 )
    (**(void (__thiscall ***)(char *, signed int))v7)(v7, 1);
  if ( v6 )
  {
    v8 = v118;
  }
  else
  {
LABEL_323:
    strValueText.m_charbuffer = (PSRefBufferCharData<unsigned short> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( AppraisalProfile::InqString(_prof, 5u, (AC1Legacy::PStringBase<char> *)&strValueText) )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(
        &_label,
        0,
        (const char *)&strValueText.m_charbuffer->m_data[10]);
      v8 = v118;
      UIElement_Text::SetText((UIElement_Text *)v118[1].cur_objid, v9);
      v10 = (char *)&_label.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v10 )
        (**(void (__thiscall ***)(char *, signed int))v10)(v10, 1);
    }
    else
    {
      v8 = v118;
    }
    v11 = strValueText.m_charbuffer;
    if ( !InterlockedDecrement((volatile LONG *)&strValueText.m_charbuffer->m_data[2]) && v11 )
      (**(void (__thiscall ***)(PSRefBufferCharData<unsigned short> *, signed int))&v11->m_data[0])(v11, 1);
  }
  v12 = v8->cur_weenobj;
  if ( v12 )
  {
    if ( ((int (*)(void))v12->vfptr[8].__vecDelDtor)() )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(&strValueText, L"Player Killer");
      UIElement_Text::SetText((UIElement_Text *)v8[1].cur_weenobj, &strValueText);
      v13 = (char *)&strValueText.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&strValueText.m_charbuffer[-1].m_data[8]) && v13 )
        (**(void (__thiscall ***)(char *, signed int))v13)(v13, 1);
    }
    else
    {
      if ( ((int (*)(void))v8->cur_weenobj->vfptr[9].__vecDelDtor)() )
      {
        PStringBase<unsigned short>::PStringBase<unsigned short>(&strValueText, L"Player Killer Lite");
        UIElement_Text::SetText((UIElement_Text *)v8[1].cur_weenobj, &strValueText);
      }
      else
      {
        PStringBase<unsigned short>::PStringBase<unsigned short>(&strValueText, L"Non-Player Killer");
        UIElement_Text::SetText((UIElement_Text *)v8[1].cur_weenobj, &strValueText);
      }
      PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&strValueText);
    }
  }
  v14 = v8->m_extraInfoList;
  if ( v14 )
    UIElement_ListBox::Flush(v14);
  sStatVal.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  sStatVal2.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  faction_bits = 0;
  my_faction_bits = 0;
  v15 = 0;
  strValueText.m_charbuffer = 0;
  v16 = InterfaceSystem::GetInstance();
  InterfaceSystem::GetClass(v16, (TResult *)&txt, &PlayerDesc_ClassType_7, (Interface **)&strValueText);
  time_4 = (int)strValueText.m_charbuffer;
  v17 = strValueText.m_charbuffer;
  playerDesc.m_pInterface = 0;
  playerDesc.m_trStatus.m_val = 0;
  if ( strValueText.m_charbuffer )
    (*(void (__thiscall **)(PSRefBufferCharData<unsigned short> *))(*(_DWORD *)&strValueText.m_charbuffer->m_data[0] + 16))(strValueText.m_charbuffer);
  v18 = *(_DWORD *)InterfacePtr<PlayerDesc>::_QueryInterface(&playerDesc, (int)&v116, time_4, 0);
  if ( v17 )
    (*(void (__thiscall **)(PSRefBufferCharData<unsigned short> *))(*(_DWORD *)&v17->m_data[0] + 20))(v17);
  if ( (_DWORD)playerDesc.m_pInterface && v18 >= 0 )
    CBaseQualities::InqInt((CBaseQualities *)&playerDesc.m_pInterface->vfptr, 0x119u, &my_faction_bits, 0, 0);
  if ( AppraisalProfile::InqInt(_prof, 0x119u, &faction_bits) )
  {
    strValueText.m_charbuffer = 0;
    AC1Legacy::PStringBase<char>::PStringBase<char>(&armorStr1, &name);
    AC1Legacy::PStringBase<char>::PStringBase<char>(&armorStr2, &name);
    if ( faction_bits & 1 )
    {
      AppraisalProfile::InqInt(_prof, 0x11Fu, (int *)&strValueText);
      AC1Legacy::PStringBase<char>::set(&armorStr1, "Celestial Hand");
      if ( my_faction_bits & 1 )
      {
        v15 = 1;
      }
      else if ( my_faction_bits & 6 )
      {
        v15 = 2;
      }
    }
    else if ( faction_bits & 2 )
    {
      AppraisalProfile::InqInt(_prof, 0x120u, (int *)&strValueText);
      AC1Legacy::PStringBase<char>::set(&armorStr1, "Eldrytch Web");
      if ( my_faction_bits & 2 )
      {
        v15 = 1;
      }
      else if ( my_faction_bits & 5 )
      {
        v15 = 2;
      }
    }
    else if ( faction_bits & 4 )
    {
      AppraisalProfile::InqInt(_prof, 0x121u, (int *)&strValueText);
      AC1Legacy::PStringBase<char>::set(&armorStr1, "Radiant Blood");
      if ( my_faction_bits & 4 )
      {
        v15 = 1;
      }
      else if ( my_faction_bits & 3 )
      {
        v15 = 2;
      }
    }
    else
    {
      AC1Legacy::PStringBase<char>::set(&armorStr1, "???");
    }
    if ( (signed int)strValueText.m_charbuffer >= 1 && (signed int)strValueText.m_charbuffer <= 100 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&ageStr, " ~ Initiate");
LABEL_61:
      v19 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                        &armorStr1,
                                                        (AC1Legacy::PStringBase<char> *)&_label,
                                                        (AC1Legacy::PStringBase<char> *)&ageStr);
LABEL_62:
      AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&armorStr2, v19);
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&_label);
      CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&ageStr);
      goto LABEL_77;
    }
    if ( (signed int)strValueText.m_charbuffer < 101 || (signed int)strValueText.m_charbuffer > 300 )
    {
      if ( (signed int)strValueText.m_charbuffer >= 301 && (signed int)strValueText.m_charbuffer <= 600 )
      {
        AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&ageStr, " ~ Knight");
        v19 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                          &armorStr1,
                                                          (AC1Legacy::PStringBase<char> *)&_label,
                                                          (AC1Legacy::PStringBase<char> *)&ageStr);
        goto LABEL_62;
      }
      if ( (signed int)strValueText.m_charbuffer >= 601 && (signed int)strValueText.m_charbuffer <= 1000 )
      {
        AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&ageStr, " ~ Lord");
        goto LABEL_61;
      }
      if ( (signed int)strValueText.m_charbuffer < 1001 || (signed int)strValueText.m_charbuffer > 1500 )
      {
        AC1Legacy::PStringBase<unsigned short>::operator=(
          (AC1Legacy::PStringBase<unsigned short> *)&armorStr2,
          (AC1Legacy::PStringBase<unsigned short> *)&armorStr1);
LABEL_77:
        PStringBase<unsigned short>::PStringBase<unsigned short>(&ageStr, L"Society:");
        v20 = v15;
        v21 = armorStr2.m_buffer;
        PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, armorStr2.m_buffer->m_data);
        BasicCreatureExamineUI::AddLineToMiscInfo(v118, &ageStr, v22, v20);
        v23 = (char *)&_label.m_charbuffer[-1].m_data[6];
        if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v23 )
          (**(void (__thiscall ***)(char *, signed int))v23)(v23, 1);
        v24 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
        if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v24 )
          (**(void (__thiscall ***)(char *, signed int))v24)(v24, 1);
        if ( !InterlockedDecrement((volatile LONG *)&v21->m_cRef) && v21 )
          v21->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v21, 1u);
        v25 = armorStr1.m_buffer;
        if ( !InterlockedDecrement((volatile LONG *)&armorStr1.m_buffer->m_cRef) && v25 )
          v25->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v25, 1u);
        goto LABEL_89;
      }
      AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&ageStr, " ~ Master");
    }
    else
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&ageStr, " ~ Adept");
    }
    v19 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                      &armorStr1,
                                                      (AC1Legacy::PStringBase<char> *)&_label,
                                                      (AC1Legacy::PStringBase<char> *)&ageStr);
    goto LABEL_62;
  }
LABEL_89:
  v26 = v118;
  v27 = ACCWeenieObject::GetObjectName(v118->cur_weenobj, NAME_APPROPRIATE, 0);
  AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&_label, v27);
  v28 = _label.m_charbuffer;
  if ( alleg_data._name.m_buffer != (AC1Legacy::PSRefBuffer<char> *)_label.m_charbuffer )
  {
    v29 = alleg_data._name.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&alleg_data._name.m_buffer->m_cRef) && v29 )
      v29->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v29, 1u);
    alleg_data._name.m_buffer = (AC1Legacy::PSRefBuffer<char> *)v28;
    InterlockedIncrement((volatile LONG *)&v28->m_data[2]);
  }
  if ( !InterlockedDecrement((volatile LONG *)&v28->m_data[2]) && v28 )
    (**(void (__thiscall ***)(PSRefBufferCharData<unsigned short> *, signed int))&v28->m_data[0])(v28, 1);
  iStat = 0;
  AppraisalProfile::InqInt(_prof, 0x1Eu, &iStat);
  alleg_data._rank = iStat;
  AllegianceData::GetFullName((AllegianceData *)&alleg_data.vfptr, &sStatVal);
  v30 = v26->m_pParentElement;
  if ( v30->m_displayedNameText )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, sStatVal.m_buffer->m_data);
    UIElement_Text::SetText(v30->m_displayedNameText, v31);
    v32 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) )
    {
      if ( v32 )
        (**(void (__thiscall ***)(char *, signed int))v32)(v32, 1);
    }
  }
  txt.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  UIElement_Text::ClearAllText((UIElement_Text *)v26[1].cur_prof.vfptr);
  if ( iStat < 1 )
    goto LABEL_125;
  if ( AppraisalProfile::InqString(_prof, 0x2Fu, &sStatVal) )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, sStatVal.m_buffer->m_data);
    UIElement_Text::SetText((UIElement_Text *)v26[1].cur_prof.vfptr, v33);
    v34 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) )
    {
      if ( v34 )
        (**(void (__thiscall ***)(char *, signed int))v34)(v34, 1);
    }
  }
  if ( !AppraisalProfile::InqString(_prof, 0x15u, &sStatVal) )
  {
    if ( !AppraisalProfile::InqInt(_prof, 0x23u, &iStat) || iStat < 0 )
      iStat = 0;
    strValueText.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
    if ( iStat == 1 )
      PStringBase<unsigned short>::sprintf(&strValueText, L"%d Follower", 1);
    else
      PStringBase<unsigned short>::sprintf(&strValueText, L"%d Followers", iStat);
    PStringBase<unsigned short>::PStringBase<unsigned short>(
      (PStringBase<unsigned short> *)&armorStr2,
      L"Alleg. Monarch:");
    BasicCreatureExamineUI::AddLineToMiscInfo(v26, (PStringBase<unsigned short> *)&armorStr2, &strValueText, 0);
    v38 = (char *)&armorStr2.m_buffer[-1].m_cRef;
    if ( !InterlockedDecrement((volatile LONG *)&armorStr2.m_buffer[-1].m_cRef + 1) && v38 )
      (**(void (__thiscall ***)(char *, signed int))v38)(v38, 1);
    v39 = (char *)&strValueText.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&strValueText.m_charbuffer[-1].m_data[8]) && v39 )
      (**(void (__thiscall ***)(char *, signed int))v39)(v39, 1);
    goto LABEL_125;
  }
  if ( AppraisalProfile::InqString(_prof, 0x23u, &sStatVal2) )
  {
    if ( !AC1Legacy::PStringBase<char>::operator==(&sStatVal, &sStatVal2) )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(&strValueText, L"Monarch:");
      PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, sStatVal.m_buffer->m_data);
      BasicCreatureExamineUI::AddLineToMiscInfo(v26, &strValueText, v36, 0);
      PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&_label);
      PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&strValueText);
      PStringBase<unsigned short>::PStringBase<unsigned short>(&strValueText, L"Patron:");
      PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, sStatVal2.m_buffer->m_data);
      BasicCreatureExamineUI::AddLineToMiscInfo(v26, &strValueText, v37, 0);
      PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&_label);
      PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&strValueText);
      goto LABEL_125;
    }
    PStringBase<unsigned short>::PStringBase<unsigned short>(&strValueText, L"Monarch/Patron:");
  }
  else
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&strValueText, L"Monarch:");
  }
  PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, 0, sStatVal.m_buffer->m_data);
  BasicCreatureExamineUI::AddLineToMiscInfo(v26, &strValueText, v35, 0);
  PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&_label);
  PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&strValueText);
LABEL_125:
  strValueText.m_charbuffer = (PSRefBufferCharData<unsigned short> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( _prof->base_armor_chest > 0
    || _prof->base_armor_hand > 0
    || _prof->base_armor_head > 0
    || _prof->base_armor_wrist > 0
    || _prof->base_armor_bicep > 0
    || _prof->base_armor_shin > 0
    || _prof->base_armor_foot > 0
    || _prof->base_armor_groin > 0
    || _prof->base_armor_thigh > 0 )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&ageStr, &word_794320);
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&armorStr2, &word_794320);
    v40 = v118;
    BasicCreatureExamineUI::AddLineToMiscInfo(v118, (PStringBase<unsigned short> *)&armorStr2, &ageStr, 0);
    v41 = (char *)&armorStr2.m_buffer[-1].m_cRef;
    if ( !InterlockedDecrement((volatile LONG *)&armorStr2.m_buffer[-1].m_cRef + 1) && v41 )
      (**(void (__thiscall ***)(char *, signed int))v41)(v41, 1);
    v42 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v42 )
      (**(void (__thiscall ***)(char *, signed int))v42)(v42, 1);
    armorStr1.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    armorStr2.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    ageStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    v43 = _prof->base_armor_head;
    if ( v43 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf(&armorStr1, "%d", _prof->base_armor_head);
    else
      AC1Legacy::PStringBase<char>::sprintf(&armorStr1, "*%d", v43 - 9999);
    v44 = _prof->base_armor_chest;
    if ( v44 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "%d", _prof->base_armor_chest);
    else
      AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "*%d", v44 - 9999);
    v45 = _prof->base_armor_groin;
    if ( v45 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&ageStr, "%d", _prof->base_armor_groin);
    else
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&ageStr, "*%d", v45 - 9999);
    AC1Legacy::PStringBase<char>::sprintf(
      (AC1Legacy::PStringBase<char> *)&strValueText,
      "AL: %s/%s/%s",
      armorStr1.m_buffer->m_data,
      armorStr2.m_buffer->m_data,
      &ageStr.m_charbuffer->m_data[10]);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Head/Chest/Groin");
    PStringBase<unsigned short>::PStringBase<unsigned short>(
      &v116,
      0,
      (const char *)&strValueText.m_charbuffer->m_data[10]);
    BasicCreatureExamineUI::AddLineToMiscInfo(v40, &_label, v46, 0);
    v47 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v47 )
      (**(void (__thiscall ***)(char *, signed int))v47)(v47, 1);
    v48 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v48 )
      (**(void (__thiscall ***)(char *, signed int))v48)(v48, 1);
    v49 = _prof->base_armor_bicep;
    if ( v49 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf(&armorStr1, "%d", _prof->base_armor_bicep);
    else
      AC1Legacy::PStringBase<char>::sprintf(&armorStr1, "*%d", v49 - 9999);
    v50 = _prof->base_armor_wrist;
    if ( v50 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "%d", _prof->base_armor_wrist);
    else
      AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "*%d", v50 - 9999);
    v51 = _prof->base_armor_hand;
    if ( v51 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&ageStr, "%d", _prof->base_armor_hand);
    else
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&ageStr, "*%d", v51 - 9999);
    AC1Legacy::PStringBase<char>::sprintf(
      (AC1Legacy::PStringBase<char> *)&strValueText,
      "AL: %s/%s/%s",
      armorStr1.m_buffer->m_data,
      armorStr2.m_buffer->m_data,
      &ageStr.m_charbuffer->m_data[10]);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Bicep/Wrist/Hand");
    PStringBase<unsigned short>::PStringBase<unsigned short>(
      &v116,
      0,
      (const char *)&strValueText.m_charbuffer->m_data[10]);
    BasicCreatureExamineUI::AddLineToMiscInfo(v40, &_label, v52, 0);
    v53 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v53 )
      (**(void (__thiscall ***)(char *, signed int))v53)(v53, 1);
    v54 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v54 )
      (**(void (__thiscall ***)(char *, signed int))v54)(v54, 1);
    v55 = _prof->base_armor_thigh;
    if ( v55 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf(&armorStr1, "%d", _prof->base_armor_thigh);
    else
      AC1Legacy::PStringBase<char>::sprintf(&armorStr1, "*%d", v55 - 9999);
    v56 = _prof->base_armor_shin;
    if ( v56 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "%d", _prof->base_armor_shin);
    else
      AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "*%d", v56 - 9999);
    v57 = _prof->base_armor_foot;
    if ( v57 < 9999 )
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&ageStr, "%d", _prof->base_armor_foot);
    else
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&ageStr, "*%d", v57 - 9999);
    v58 = ageStr.m_charbuffer;
    v59 = armorStr2.m_buffer;
    AC1Legacy::PStringBase<char>::sprintf(
      (AC1Legacy::PStringBase<char> *)&strValueText,
      "AL: %s/%s/%s",
      armorStr1.m_buffer->m_data,
      armorStr2.m_buffer->m_data,
      &ageStr.m_charbuffer->m_data[10]);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Thigh/Shin/Foot");
    PStringBase<unsigned short>::PStringBase<unsigned short>(
      &v116,
      0,
      (const char *)&strValueText.m_charbuffer->m_data[10]);
    BasicCreatureExamineUI::AddLineToMiscInfo(v118, &_label, v60, 0);
    v61 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v61 )
      (**(void (__thiscall ***)(char *, signed int))v61)(v61, 1);
    v62 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v62 )
      (**(void (__thiscall ***)(char *, signed int))v62)(v62, 1);
    if ( !InterlockedDecrement((volatile LONG *)&v58->m_data[2]) && v58 )
      (**(void (__thiscall ***)(PSRefBufferCharData<unsigned short> *, signed int))&v58->m_data[0])(v58, 1);
    if ( !InterlockedDecrement((volatile LONG *)&v59->m_cRef) && v59 )
      v59->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v59, 1u);
    v63 = armorStr1.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&armorStr1.m_buffer->m_cRef) && v63 )
      v63->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v63, 1u);
  }
  v64 = 0;
  damage_rating = 0;
  damage_resist_rating = 0;
  crit_rating = 0;
  crit_damage_rating = 0;
  crit_resist_rating = 0;
  crit_damage_resist_rating = 0;
  healing_boost_rating = 0;
  dot_resist_rating = 0;
  life_resist_rating = 0;
  AppraisalProfile::InqInt(_prof, 0x133u, &damage_rating);
  AppraisalProfile::InqInt(_prof, 0x134u, &damage_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x139u, &crit_rating);
  AppraisalProfile::InqInt(_prof, 0x13Au, &crit_damage_rating);
  AppraisalProfile::InqInt(_prof, 0x13Bu, &crit_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x13Cu, &crit_damage_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x143u, &healing_boost_rating);
  AppraisalProfile::InqInt(_prof, 0x15Eu, &dot_resist_rating);
  AppraisalProfile::InqInt(_prof, 0x15Fu, &life_resist_rating);
  armorStr2.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( damage_rating <= 0 && crit_rating <= 0 && crit_damage_rating <= 0 )
  {
    v65 = v118;
  }
  else
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&ageStr, &word_794320);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
    v65 = v118;
    BasicCreatureExamineUI::AddLineToMiscInfo(v118, &_label, &ageStr, 0);
    v66 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v66 )
      (**(void (__thiscall ***)(char *, signed int))v66)(v66, 1);
    v67 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v67 )
      (**(void (__thiscall ***)(char *, signed int))v67)(v67, 1);
    v64 = 1;
    AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "%Rating: %d/%d", damage_rating, crit_damage_rating);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Dmg/CritDmg");
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v116, 0, armorStr2.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, v68, 0);
    v69 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v69 )
      (**(void (__thiscall ***)(char *, signed int))v69)(v69, 1);
    v70 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v70 )
      (**(void (__thiscall ***)(char *, signed int))v70)(v70, 1);
  }
  if ( damage_resist_rating > 0 || crit_resist_rating > 0 || crit_damage_resist_rating > 0 )
  {
    if ( !v64 )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(&ageStr, &word_794320);
      PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
      BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
      v71 = (char *)&_label.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v71 )
        (**(void (__thiscall ***)(char *, signed int))v71)(v71, 1);
      v72 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v72 )
        (**(void (__thiscall ***)(char *, signed int))v72)(v72, 1);
      v64 = 1;
    }
    AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "%Resist: %d/%d", damage_resist_rating, crit_damage_resist_rating);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Dmg/CritDmg");
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v116, 0, armorStr2.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, v73, 0);
    v74 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v74 )
      (**(void (__thiscall ***)(char *, signed int))v74)(v74, 1);
    v75 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v75 )
      (**(void (__thiscall ***)(char *, signed int))v75)(v75, 1);
  }
  if ( dot_resist_rating > 0 || life_resist_rating > 0 )
  {
    if ( !v64 )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(&ageStr, &word_794320);
      PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
      BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
      v76 = (char *)&_label.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v76 )
        (**(void (__thiscall ***)(char *, signed int))v76)(v76, 1);
      v77 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v77 )
        (**(void (__thiscall ***)(char *, signed int))v77)(v77, 1);
      v64 = 1;
    }
    AC1Legacy::PStringBase<char>::sprintf(&armorStr2, "%Resist: %d/%d", dot_resist_rating, life_resist_rating);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"DoT/Life:");
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v116, 0, armorStr2.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, v78, 0);
    v79 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v79 )
      (**(void (__thiscall ***)(char *, signed int))v79)(v79, 1);
    v80 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v80 )
      (**(void (__thiscall ***)(char *, signed int))v80)(v80, 1);
  }
  if ( v64 )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&ageStr, &word_794320);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, &word_794320);
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
    v81 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v81 )
      (**(void (__thiscall ***)(char *, signed int))v81)(v81, 1);
    v82 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v82 )
      (**(void (__thiscall ***)(char *, signed int))v82)(v82, 1);
  }
  if ( AppraisalProfile::InqString(_prof, 0xAu, &sStatVal) )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Fellowship:");
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v116, 0, sStatVal.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, v83, 0);
    v84 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v84 )
      (**(void (__thiscall ***)(char *, signed int))v84)(v84, 1);
    v85 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v85 )
      (**(void (__thiscall ***)(char *, signed int))v85)(v85, 1);
  }
  if ( AppraisalProfile::InqString(_prof, 0x2Bu, &sStatVal) )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Arrived in Dereth:");
    PStringBase<unsigned short>::PStringBase<unsigned short>(&v116, 0, sStatVal.m_buffer->m_data);
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, v86, 0);
    v87 = (char *)&v116.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&v116.m_charbuffer[-1].m_data[8]) && v87 )
      (**(void (__thiscall ***)(char *, signed int))v87)(v87, 1);
    v88 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v88 )
      (**(void (__thiscall ***)(char *, signed int))v88)(v88, 1);
  }
  if ( AppraisalProfile::InqInt(_prof, 0x7Du, &iStat) )
  {
    ageStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
    ClientUISystem::DeltaTimeToString((double)iStat, &ageStr);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Time in Dereth:");
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
    v89 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v89 )
      (**(void (__thiscall ***)(char *, signed int))v89)(v89, 1);
    v90 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v90 )
      (**(void (__thiscall ***)(char *, signed int))v90)(v90, 1);
  }
  if ( AppraisalProfile::InqInt(_prof, 0xB5u, &iStat) )
  {
    ageStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
    PStringBase<unsigned short>::sprintf(&ageStr, L"%d", iStat);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Chess Rank:");
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
    v91 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v91 )
      (**(void (__thiscall ***)(char *, signed int))v91)(v91, 1);
    v92 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v92 )
      (**(void (__thiscall ***)(char *, signed int))v92)(v92, 1);
  }
  if ( AppraisalProfile::InqInt(_prof, 0xC0u, &iStat) )
  {
    ageStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
    PStringBase<unsigned short>::sprintf(&ageStr, L"%d", iStat);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Fishing Skill:");
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
    v93 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v93 )
      (**(void (__thiscall ***)(char *, signed int))v93)(v93, 1);
    v94 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v94 )
      (**(void (__thiscall ***)(char *, signed int))v94)(v94, 1);
  }
  if ( AppraisalProfile::InqInt(_prof, 0x2Bu, &iStat) )
  {
    if ( iStat <= 0 )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(&ageStr, L"Has never died");
    }
    else
    {
      ageStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
      PStringBase<unsigned short>::sprintf(&ageStr, L"%d", iStat);
    }
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Deaths:");
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
    v95 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v95 )
      (**(void (__thiscall ***)(char *, signed int))v95)(v95, 1);
    v96 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v96 )
      (**(void (__thiscall ***)(char *, signed int))v96)(v96, 1);
  }
  if ( AppraisalProfile::InqInt(_prof, 0x106u, &iStat) )
  {
    ageStr.m_charbuffer = (PSRefBufferCharData<unsigned short> *)PStringBase<unsigned short>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
    PStringBase<unsigned short>::sprintf(&ageStr, L"%d", iStat);
    PStringBase<unsigned short>::PStringBase<unsigned short>(&_label, L"Titles Earned:");
    BasicCreatureExamineUI::AddLineToMiscInfo(v65, &_label, &ageStr, 0);
    v97 = (char *)&_label.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&_label.m_charbuffer[-1].m_data[8]) && v97 )
      (**(void (__thiscall ***)(char *, signed int))v97)(v97, 1);
    v98 = (char *)&ageStr.m_charbuffer[-1].m_data[6];
    if ( !InterlockedDecrement((volatile LONG *)&ageStr.m_charbuffer[-1].m_data[8]) && v98 )
      (**(void (__thiscall ***)(char *, signed int))v98)(v98, 1);
  }
  v99 = armorStr2.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&armorStr2.m_buffer->m_cRef) && v99 )
    v99->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v99, 1u);
  v100 = strValueText.m_charbuffer;
  if ( !InterlockedDecrement((volatile LONG *)&strValueText.m_charbuffer->m_data[2]) && v100 )
    (**(void (__thiscall ***)(PSRefBufferCharData<unsigned short> *, signed int))&v100->m_data[0])(v100, 1);
  v101 = txt.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&txt.m_buffer->m_cRef) && v101 )
    v101->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v101, 1u);
  if ( (_DWORD)playerDesc.m_pInterface )
    ((void (*)(void))playerDesc.m_pInterface->vfptr->Release)();
  v102 = sStatVal2.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&sStatVal2.m_buffer->m_cRef) && v102 )
    v102->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v102, 1u);
  v103 = sStatVal.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&sStatVal.m_buffer->m_cRef) && v103 )
    v103->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v103, 1u);
  v104 = genderHeritageStr.m_buffer;
  if ( !InterlockedDecrement((volatile LONG *)&genderHeritageStr.m_buffer->m_cRef) && v104 )
    v104->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v104, 1u);
LABEL_314:
  crit_resist_rating = (int)PStringBase<unsigned short>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)PStringBase<unsigned short>::s_NullBuffer - 4);
  v105 = _wcslen(L"* = Unenchantable");
  PStringBase<unsigned short>::allocate_ref_buffer((PStringBase<unsigned short> *)&genderHeritageStr, v105);
  _wcscpy((wchar_t *)genderHeritageStr.m_buffer, L"* = Unenchantable");
  v106 = v118;
  BasicCreatureExamineUI::AddLineToMiscInfo(
    v118,
    (PStringBase<unsigned short> *)&genderHeritageStr,
    (PStringBase<unsigned short> *)&crit_resist_rating,
    0);
  v107 = (char *)&genderHeritageStr.m_buffer[-1].m_cRef;
  if ( !InterlockedDecrement((volatile LONG *)&genderHeritageStr.m_buffer[-1].m_cRef + 1) && v107 )
    (**(void (__thiscall ***)(char *, signed int))v107)(v107, 1);
  v108 = crit_resist_rating - 20;
  if ( !InterlockedDecrement((volatile LONG *)(crit_resist_rating - 20 + 4)) && v108 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v108)(v108, 1);
  BasicCreatureExamineUI::SetAppraiseInfo(v106, _prof, is_new);
  AllegianceData::~AllegianceData((AllegianceData *)&alleg_data.vfptr);
}
// 7B114C: using guessed type wchar_t aDFollower[12];
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B5E40) --------------------------------------------------------
void __thiscall SpellExamineUI::SetManaText(SpellExamineUI *this, int baseMana, int manaMod)
{
  UIElement_Text *v3; // eax@1
  AC1Legacy::PStringBase<char> *v4; // eax@6
  int v5; // esi@6
  AC1Legacy::PSRefBuffer<char> *v6; // esi@9
  AC1Legacy::PSRefBuffer<char> *v7; // edi@9
  int v8; // edi@17
  AC1Legacy::PStringBase<unsigned short> *v9; // eax@18
  int v10; // esi@18
  int v11; // esi@21
  PStringBase<unsigned short> *v12; // eax@25
  int v13; // edi@25
  AC1Legacy::PStringBase<char> sDisplayStr; // [sp+14h] [bp-Ch]@2
  AC1Legacy::PStringBase<char> result; // [sp+18h] [bp-8h]@6
  SpellExamineUI *v16; // [sp+1Ch] [bp-4h]@1

  v3 = this->m_spellManaText;
  v16 = this;
  if ( v3 )
  {
    sDisplayStr.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( baseMana <= 0 )
    {
      AC1Legacy::PStringBase<char>::set(&sDisplayStr, "0");
    }
    else if ( !AC1Legacy::PStringBase<char>::convert(&sDisplayStr, baseMana, 1) )
    {
      AC1Legacy::PStringBase<char>::set(&sDisplayStr, "???");
    }
    AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&baseMana, "Mana: ");
    AC1Legacy::PStringBase<char>::operator+(v4, &result, &sDisplayStr);
    v5 = baseMana;
    if ( !InterlockedDecrement((volatile LONG *)(baseMana + 4)) && v5 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v5)(v5, 1);
    v6 = sDisplayStr.m_buffer;
    v7 = result.m_buffer;
    if ( sDisplayStr.m_buffer != result.m_buffer )
    {
      if ( !InterlockedDecrement((volatile LONG *)&sDisplayStr.m_buffer->m_cRef) && v6 )
        v6->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v6, 1u);
      v6 = v7;
      sDisplayStr.m_buffer = v7;
      InterlockedIncrement((volatile LONG *)&v7->m_cRef);
    }
    if ( !InterlockedDecrement((volatile LONG *)&v7->m_cRef) && v7 )
      v7->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v7, 1u);
    v8 = manaMod;
    if ( manaMod > 0 )
    {
      baseMana = AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      AC1Legacy::PStringBase<char>::sprintf((AC1Legacy::PStringBase<char> *)&baseMana, " + %d per target", v8);
      v9 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                       &sDisplayStr,
                                                       (AC1Legacy::PStringBase<char> *)&manaMod,
                                                       (AC1Legacy::PStringBase<char> *)&baseMana);
      AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&sDisplayStr, v9);
      v10 = manaMod;
      if ( !InterlockedDecrement((volatile LONG *)(manaMod + 4)) && v10 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v10)(v10, 1);
      v11 = baseMana;
      if ( !InterlockedDecrement((volatile LONG *)(baseMana + 4)) && v11 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v11)(v11, 1);
      v6 = sDisplayStr.m_buffer;
    }
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&baseMana, 0, v6->m_data);
    UIElement_Text::SetText(v16->m_spellManaText, v12);
    v13 = baseMana - 20;
    if ( !InterlockedDecrement((volatile LONG *)(baseMana - 20 + 4)) && v13 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v13)(v13, 1);
    if ( !InterlockedDecrement((volatile LONG *)&v6->m_cRef) )
    {
      if ( v6 )
        v6->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v6, 1u);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B6000) --------------------------------------------------------
void __thiscall SpellExamineUI::AddItemInfo(SpellExamineUI *this, const char *txt)
{
  SpellExamineUI *v2; // edi@1
  UIElement_Text *v3; // eax@1
  char *v4; // esi@3
  PStringBase<unsigned short> *v5; // eax@6
  const char *v6; // esi@6
  PStringBase<unsigned short> _text; // [sp+0h] [bp-4h]@1

  _text.m_charbuffer = (PSRefBufferCharData<unsigned short> *)this;
  v2 = this;
  v3 = this->m_spellDisplayText;
  if ( v3 )
  {
    if ( v3->m_glyphList.m_glyphList._num_elements > 1 )
    {
      PStringBase<unsigned short>::PStringBase<unsigned short>(&_text, L"\n");
      UIElement_Text::AppendText(v2->m_spellDisplayText, &_text);
      v4 = (char *)&_text.m_charbuffer[-1].m_data[6];
      if ( !InterlockedDecrement((volatile LONG *)&_text.m_charbuffer[-1].m_data[8]) )
      {
        if ( v4 )
          (**(void (__thiscall ***)(char *, signed int))v4)(v4, 1);
      }
    }
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&txt, 0, txt);
    UIElement_Text::AppendText(v2->m_spellDisplayText, v5);
    v6 = txt - 20;
    if ( !InterlockedDecrement((volatile LONG *)txt - 4) )
    {
      if ( v6 )
        (**(void (__thiscall ***)(const char *, signed int))v6)(v6, 1);
    }
  }
}

//----- (004B60A0) --------------------------------------------------------
gmExaminationUI *__thiscall gmExaminationUI::`scalar deleting destructor'(gmExaminationUI *this, unsigned int a2)
{
  gmExaminationUI *v2; // esi@1

  v2 = this;
  gmExaminationUI::~gmExaminationUI(this);
  if ( a2 & 1 )
    operator delete(v2);
  return v2;
}

//----- (004B60C0) --------------------------------------------------------
UIElementMessageListenResult __thiscall gmExaminationUI::ListenToElementMessage(gmExaminationUI *this, UIElementMessageInfo *i_rMsg)
{
  UIElementMessageInfo *v2; // edi@1
  gmExaminationUI *v3; // esi@1
  unsigned int v4; // ecx@5
  int v5; // eax@6
  SpellExamineUI *v6; // ecx@10
  unsigned int v7; // eax@10
  UIElementMessageListenResult result; // eax@12
  ItemExamineUI *v9; // ecx@14
  BaseProperty scidProp; // [sp+Ch] [bp-8h]@6

  v2 = i_rMsg;
  v3 = this;
  if ( i_rMsg->idElement == 268435767 )
  {
    if ( i_rMsg->idMessage == 28 && i_rMsg->dwParam1 == 7 )
      ItemExamineUI::HandleInscriptionMousePresses(this->m_itemUI);
    return UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
  }
  if ( i_rMsg->idElement == 268435774 )
  {
    if ( i_rMsg->idMessage == 47 )
    {
      v9 = this->m_itemUI;
      if ( v9 )
      {
        if ( i_rMsg->dwParam1 )
        {
          ItemExamineUI::HandleInscriptionGainingFocus(v9);
          result = UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
        }
        else
        {
          ItemExamineUI::HandleInscriptionLosingFocus(v9);
          result = UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
        }
        return result;
      }
    }
    return UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
  }
  if ( i_rMsg->idElement != 268436269 )
    return UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
  if ( i_rMsg->idMessage != 4 )
    return UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
  v4 = i_rMsg->dwParam2;
  if ( !v4 )
    return UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
  v5 = *(_DWORD *)v4;
  i_rMsg = 0;
  scidProp.m_pcPropertyDesc = 0;
  scidProp.m_pcPropertyValue = 0;
  if ( (unsigned __int8)(*(int (__stdcall **)(signed int, BaseProperty *))(v5 + 208))(268435472, &scidProp)
    && scidProp.m_pcPropertyValue )
    ((void (__stdcall *)(UIElementMessageInfo **))scidProp.m_pcPropertyValue->vfptr[30].__vecDelDtor)(&i_rMsg);
  if ( i_rMsg )
  {
    v6 = v3->m_spellUI;
    SpellExamineUI::GetComponentObjectID((unsigned int)i_rMsg);
    if ( v7 )
    {
      v3->m_examineNewlySelectedItem = 0;
      ACCWeenieObject::SetSelectedObject(v7, 0);
      v3->m_examineNewlySelectedItem = 1;
    }
  }
  BaseProperty::~BaseProperty(&scidProp);
  return UIElement::ListenToElementMessage((UIElement *)&v3->vfptr, v2);
}

//----- (004B6200) --------------------------------------------------------
void __thiscall gmExaminationUI::RecvNotice_SetAppraiseInfo(gmExaminationUI *this, unsigned int i_objid, AppraisalProfile *i_prof)
{
  gmExaminationUI::SetAppraiseInfo((gmExaminationUI *)((char *)this - 1528), i_objid, i_prof);
}

//----- (004B6210) --------------------------------------------------------
int __thiscall SpellExamineUI::ExamineSpell(SpellExamineUI *this, const unsigned int _spellid)
{
  SpellExamineUI *v2; // ebx@1
  int v4; // esi@3
  volatile LONG *v5; // edi@3
  AC1Legacy::PSRefBuffer<char> *v6; // ebp@3
  AC1Legacy::PStringBase<unsigned short> *v7; // eax@8
  LONG (__stdcall *v8)(volatile LONG *); // ebp@8
  int v9; // esi@8
  gmExaminationUI *v10; // esi@11
  PStringBase<unsigned short> *v11; // eax@12
  int v12; // esi@12
  int v13; // esi@15
  AC1Legacy::PStringBase<unsigned short> *v14; // eax@18
  int v15; // esi@18
  PStringBase<unsigned short> *v16; // eax@21
  int v17; // esi@21
  double v18; // st7@24
  PStringBase<unsigned short> *v19; // eax@29
  double v20; // st7@30
  PStringBase<unsigned short> *v21; // eax@32
  int v22; // esi@32
  AC1Legacy::PStringBase<unsigned short> *v23; // eax@35
  int v24; // esi@35
  AC1Legacy::PSRefBuffer<char> *v25; // edi@38
  UIRegion *v26; // ecx@38
  Graphic *v27; // esi@39
  Graphic *v28; // eax@40
  Graphic *v29; // eax@41
  ClientMagicSystem *v30; // eax@44
  char *v31; // esi@49
  int v32; // esi@49
  UIRegion *v33; // ecx@51
  IInputActionCallbackVtbl *v34; // edi@51
  int v35; // eax@51
  int v36; // edi@51
  AC1Legacy::PSRefBuffer<char> *v37; // esi@52
  AC1Legacy::PSRefBuffer<char> *v38; // esi@55
  AC1Legacy::PSRefBuffer<char> *v39; // esi@58
  unsigned int v40; // ebp@68
  int v41; // esi@69
  ClientMagicSystem *v42; // eax@72
  Graphic *v43; // eax@74
  Graphic *v44; // eax@75
  AC1Legacy::PStringBase<char> *v45; // eax@79
  AC1Legacy::PSRefBuffer<char> *v46; // esi@79
  AC1Legacy::PSRefBuffer<char> *v47; // esi@82
  int i; // [sp+30h] [bp-904h]@8
  AC1Legacy::PStringBase<char> sStat; // [sp+34h] [bp-900h]@3
  AC1Legacy::PStringBase<char> comptxt; // [sp+38h] [bp-8FCh]@3
  BaseProperty scidProp; // [sp+3Ch] [bp-8F8h]@70
  int num_comp; // [sp+44h] [bp-8F0h]@49
  AC1Legacy::PStringBase<char> v53; // [sp+48h] [bp-8ECh]@79
  SpellComponentTable *scTable; // [sp+4Ch] [bp-8E8h]@44
  SpellComponentBase sCB; // [sp+50h] [bp-8E4h]@51
  SpellFormula sFormula; // [sp+74h] [bp-8C0h]@49
  CSpellBase sBase; // [sp+98h] [bp-89Ch]@8
  SpellFormula result; // [sp+128h] [bp-80Ch]@49
  char numtxt[2024]; // [sp+14Ch] [bp-7E8h]@27

  v2 = this;
  if ( !_spellid )
    return 0;
  v4 = AC1Legacy::PStringBase<char>::s_NullBuffer;
  v5 = (volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4);
  sStat.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  v6 = (AC1Legacy::PSRefBuffer<char> *)ClientMagicSystem::GetMagicSystem();
  comptxt.m_buffer = v6;
  if ( !v6 )
  {
    if ( !InterlockedDecrement(v5) )
    {
      if ( v4 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v4)(v4, 1);
    }
    return 0;
  }
  CSpellBase::CSpellBase(&sBase);
  ClientMagicSystem::InqSpellBase((ClientMagicSystem *)v6, _spellid, &sBase);
  SpellExamineUI::ClearIcons(v2);
  UIElement_Text::ClearAllText(v2->m_spellDisplayText);
  UIElement_Text::ClearAllText(v2->m_spellDurationText);
  v2->cur_spellid = _spellid;
  v7 = (AC1Legacy::PStringBase<unsigned short> *)SpellComponentBase::InqName(
                                                   (SpellComponentBase *)&sBase,
                                                   (AC1Legacy::PStringBase<char> *)&i);
  AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&sStat, v7);
  v8 = InterlockedDecrement;
  v9 = i;
  if ( !InterlockedDecrement((volatile LONG *)(i + 4)) && v9 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v9)(v9, 1);
  v10 = v2->m_pParentElement;
  if ( v10->m_displayedNameText )
  {
    PStringBase<unsigned short>::PStringBase<unsigned short>(
      (PStringBase<unsigned short> *)&i,
      0,
      sStat.m_buffer->m_data);
    UIElement_Text::SetText(v10->m_displayedNameText, v11);
    v12 = i - 20;
    if ( !InterlockedDecrement((volatile LONG *)(i - 20 + 4)) )
    {
      if ( v12 )
        (**(void (__thiscall ***)(_DWORD, _DWORD))v12)(v12, 1);
    }
  }
  CSpellBase::SchoolEnumToName((AC1Legacy::PStringBase<char> *)&i, sBase._school);
  AC1Legacy::PStringBase<unsigned short>::operator=(
    (AC1Legacy::PStringBase<unsigned short> *)&sStat,
    (AC1Legacy::PStringBase<unsigned short> *)&i);
  v13 = i;
  if ( !InterlockedDecrement((volatile LONG *)(i + 4)) && v13 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v13)(v13, 1);
  v14 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::operator+(
                                                    (AC1Legacy::PStringBase<char> *)&i,
                                                    "School: ",
                                                    &sStat);
  AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&sStat, v14);
  v15 = i;
  if ( !InterlockedDecrement((volatile LONG *)(i + 4)) && v15 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v15)(v15, 1);
  PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&i, 0, sStat.m_buffer->m_data);
  UIElement_Text::SetText(v2->m_magicSchoolText, v16);
  v17 = i - 20;
  if ( !InterlockedDecrement((volatile LONG *)(i - 20 + 4)) && v17 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v17)(v17, 1);
  SpellExamineUI::SetManaText(v2, sBase._base_mana, sBase._mana_mod);
  v18 = CSpellBase::InqDuration(&sBase);
  if ( v18 != -1.0 && v18 > 0.0 )
  {
    if ( v18 >= 60.0 )
      _sprintf(numtxt, "Duration: %u min.", (unsigned __int64)(v18 * 0.01666666666666667));
    else
      _sprintf(numtxt, "Duration: %u sec.", (unsigned __int64)v18);
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&i, 0, numtxt);
    UIElement_Text::SetText(v2->m_spellDurationText, v19);
    PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&i);
  }
  v20 = SpellExamineUI::DetermineSpellRange(&sBase);
  if ( v20 == 0.0 )
  {
    UIElement_Text::ClearAllText(v2->m_spellRangeText);
  }
  else
  {
    _sprintf(numtxt, "Range: %.1f yds.", v20 / 0.9144);
    PStringBase<unsigned short>::PStringBase<unsigned short>((PStringBase<unsigned short> *)&i, 0, numtxt);
    UIElement_Text::SetText(v2->m_spellRangeText, v21);
    v22 = i - 20;
    if ( !InterlockedDecrement((volatile LONG *)(i - 20 + 4)) && v22 )
      (**(void (__thiscall ***)(_DWORD, _DWORD))v22)(v22, 1);
  }
  v23 = (AC1Legacy::PStringBase<unsigned short> *)CSpellBase::InqDescription(&sBase, (AC1Legacy::PStringBase<char> *)&i);
  AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&sStat, v23);
  v24 = i;
  if ( !InterlockedDecrement((volatile LONG *)(i + 4)) && v24 )
    (**(void (__thiscall ***)(_DWORD, _DWORD))v24)(v24, 1);
  v25 = sStat.m_buffer;
  SpellExamineUI::AddItemInfo(v2, sStat.m_buffer->m_data);
  v26 = (UIRegion *)&v2->m_spellIcon->vfptr;
  if ( v26 )
  {
    UIRegion::ClearImage(v26);
    v27 = ClientMagicSystem::GetSpellIcon((ClientMagicSystem *)comptxt.m_buffer, _spellid);
    if ( v27 )
    {
      UIRegion::SetBlitMode((UIRegion *)&v2->m_spellIcon->vfptr, Blit_3Alpha);
      v28 = (Graphic *)operator new(0xCu);
      if ( v28 )
        Graphic::Graphic(v28, v27);
      else
        v29 = 0;
      UIRegion::SetImage((UIRegion *)&v2->m_spellIcon->vfptr, v29);
    }
  }
  v30 = ClientMagicSystem::GetMagicSystem();
  scTable = ClientMagicSystem::GetSpellComponentTable(v30);
  if ( !scTable )
  {
    CSpellBase::~CSpellBase(&sBase);
    if ( !InterlockedDecrement((volatile LONG *)&v25->m_cRef) && v25 )
      v25->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v25, 1u);
    return 0;
  }
  ClientMagicSystem::GetMagicSystem();
  v31 = (char *)ClientMagicSystem::GetAppropriateSpellFormula(&result, &sBase)->_comps;
  sFormula.vfptr = (PackObjVtbl *)&SpellFormula::`vftable';
  qmemcpy(sFormula._comps, v31, sizeof(sFormula._comps));
  v32 = SpellFormula::GetNumSpellComponents(&sFormula);
  num_comp = v32;
  if ( v32 > 0 )
    SpellExamineUI::AddItemInfo(v2, "\nCOMPONENTS:");
  ((void (__stdcall *)(int, int))v2->m_formulaListBox->vfptr[3].OnLoseFocus)(
    v2->m_componentListX - (v32 - 1) * (v2->m_componentListW / 2),
    v2->m_formulaListBox->m_box.m_y0);
  v33 = (UIRegion *)&v2->m_formulaListBox->vfptr;
  v34 = v33->vfptr;
  v35 = UIRegion::GetHeight(v33);
  ((void (__thiscall *)(UIElement_ListBox *, int, int))v34[4].__vecDelDtor)(
    v2->m_formulaListBox,
    v32 * v2->m_componentListW,
    v35);
  SpellComponentBase::SpellComponentBase(&sCB);
  v36 = 0;
  i = 0;
  if ( v32 > 0 )
  {
    while ( 1 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&comptxt, "     ");
      if ( v36 < 0 || v36 >= 8 )
        v36 = 0;
      else
        v36 = sFormula._comps[v36];
      if ( !SpellComponentTable::InqSpellComponentBase(scTable, v36, &sCB) )
        goto LABEL_84;
      v40 = sCB._iconID.id;
      if ( sCB._iconID.id == i_iconID.id )
        break;
      v41 = UIElement_ListBox::AddItemFromTemplateListByID(v2->m_formulaListBox, 0x1000032Eu, 0);
      if ( v41 )
      {
        scidProp.m_pcPropertyDesc = 0;
        scidProp.m_pcPropertyValue = 0;
        BaseProperty::SetPropertyName(&scidProp, 0x10000010u);
        if ( scidProp.m_pcPropertyValue )
        {
          BaseProperty::CheckCopyOnWrite(&scidProp);
          ((void (__stdcall *)(int))scidProp.m_pcPropertyValue->vfptr[31].__vecDelDtor)(v36);
        }
        (*(void (__thiscall **)(int, BaseProperty *))(*(_DWORD *)v41 + 212))(v41, &scidProp);
        UIRegion::ClearImage((UIRegion *)v41);
        v42 = ClientMagicSystem::GetMagicSystem();
        if ( !v42 )
        {
          BaseProperty::~BaseProperty(&scidProp);
          CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&comptxt);
          SpellComponentBase::~SpellComponentBase(&sCB);
          sFormula.vfptr = (PackObjVtbl *)&PackObj::`vftable';
          CSpellBase::~CSpellBase(&sBase);
          CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&sStat);
          return 0;
        }
        v36 = (int)ClientMagicSystem::GetSpellComponentIcon(v42, (IDClass<_tagDataID,32,0>)v40);
        if ( v36 )
        {
          UIRegion::SetBlitMode((UIRegion *)v41, Blit_3Alpha);
          v43 = (Graphic *)operator new(0xCu);
          if ( v43 )
            Graphic::Graphic(v43, (Graphic *)v36);
          else
            v44 = 0;
          UIRegion::SetImage((UIRegion *)v41, v44);
        }
        BaseProperty::~BaseProperty(&scidProp);
      }
      v45 = SpellComponentBase::InqName(&sCB, &v53);
      AC1Legacy::PStringBase<char>::operator+=(&comptxt, v45);
      v46 = v53.m_buffer;
      if ( !InterlockedDecrement((volatile LONG *)&v53.m_buffer->m_cRef) && v46 )
        v46->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v46, 1u);
      v47 = comptxt.m_buffer;
      SpellExamineUI::AddItemInfo(v2, comptxt.m_buffer->m_data);
      v8 = InterlockedDecrement;
LABEL_85:
      if ( !v8((volatile LONG *)&v47->m_cRef) && v47 )
        v47->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v47, 1u);
      ++i;
      if ( i >= num_comp )
        goto LABEL_52;
      v36 = i;
    }
    v8 = InterlockedDecrement;
LABEL_84:
    v47 = comptxt.m_buffer;
    goto LABEL_85;
  }
LABEL_52:
  SpellExamineUI::UpdateComponents(v2, v36, 0);
  v37 = sCB._text.m_buffer;
  if ( !v8((volatile LONG *)&sCB._text.m_buffer->m_cRef) && v37 )
    v37->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v37, 1u);
  v38 = sCB._name.m_buffer;
  if ( !v8((volatile LONG *)&sCB._name.m_buffer->m_cRef) && v38 )
    v38->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v38, 1u);
  sCB.vfptr = (PackObjVtbl *)&PackObj::`vftable';
  sFormula.vfptr = (PackObjVtbl *)&PackObj::`vftable';
  CSpellBase::~CSpellBase(&sBase);
  v39 = sStat.m_buffer;
  if ( !v8((volatile LONG *)&sStat.m_buffer->m_cRef) && v39 )
    v39->vfptr->__vecDelDtor((ReferenceCountTemplate<268435456,0> *)v39, 1u);
  return 1;
}
// 79285C: using guessed type int (__thiscall *PackObj::`vftable')(void *, char);
// 7A3A8C: using guessed type int (__thiscall *SpellFormula::`vftable')(void *, char);
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B6900) --------------------------------------------------------
void __thiscall gmExaminationUI::ExamineSpell(gmExaminationUI *this, const unsigned int _spellid)
{
  gmExaminationUI *v2; // esi@1
  ClientUISystem *v3; // eax@4

  v2 = this;
  if ( this->awaiting_appraisal_ID )
  {
    this->awaiting_appraisal_ID = 0;
    v3 = ClientUISystem::GetUISystem();
    ClientUISystem::DecrementBusyCount(v3);
  }
  else if ( !this->current_appraisal_ID )
  {
    goto LABEL_6;
  }
  v2->current_appraisal_ID = 0;
  CM_Item::Event_Appraise(0);
LABEL_6:
  SpellExamineUI::ExamineSpell(v2->m_spellUI, _spellid);
  if ( v2->m_activeUI != (ExamineSubUI *)v2->m_spellUI )
    gmExaminationUI::SetActiveExamineUI(v2, (ExamineSubUI *)&v2->m_spellUI->vfptr);
  v2->vfptr[2].__vecDelDtor((IInputActionCallback *)v2, 1u);
}

//----- (004B6980) --------------------------------------------------------
void __thiscall gmExaminationUI::RecvNotice_ExamineSpell(gmExaminationUI *this, unsigned int i_spellid)
{
  gmExaminationUI::ExamineSpell((gmExaminationUI *)((char *)this - 1528), i_spellid);
}

//----- (004B6990) --------------------------------------------------------
void __thiscall ItemExamineUI::Appraisal_ShowDescription(ItemExamineUI *this, AppraisalProfile *_prof)
{
  AppraisalProfile *v2; // edi@1
  void *v3; // ebp@1
  int v4; // eax@6
  int v5; // eax@14
  char *v6; // esi@17
  AC1Legacy::PSRefBuffer<char> *v7; // edi@24
  AC1Legacy::PSRefBuffer<char> *v8; // ebp@24
  AppraisalProfile *v9; // esi@24
  AC1Legacy::PStringBase<char> *v10; // eax@26
  AC1Legacy::PStringBase<char> *v11; // eax@26
  PSRefBufferCharData<char> *v12; // esi@29
  AC1Legacy::PStringBase<char> *v13; // eax@29
  AC1Legacy::PStringBase<char> *v14; // eax@29
  const char *v15; // esi@29
  AC1Legacy::PStringBase<char> *v16; // ecx@29
  AC1Legacy::PStringBase<char> *v17; // eax@39
  AC1Legacy::PStringBase<unsigned short> *v18; // eax@39
  int v19; // esi@39
  int v20; // edx@41
  int v21; // esi@42
  int v22; // edx@44
  ReferenceCountTemplate<268435456,0>Vtbl *v23; // edx@47
  ReferenceCountTemplate<268435456,0>Vtbl *v24; // edx@50
  AC1Legacy::PSRefBuffer<char> *v25; // esi@51
  ReferenceCountTemplate<268435456,0>Vtbl *v26; // edx@53
  AC1Legacy::PSRefBuffer<char> *v27; // edi@56
  int v28; // eax@57
  int v29; // eax@57
  int v30; // ecx@57
  AC1Legacy::PSRefBuffer<char> *v31; // esi@60
  ReferenceCountTemplate<268435456,0>Vtbl *v32; // edx@62
  int v33; // eax@64
  int v34; // eax@64
  int v35; // ecx@64
  AC1Legacy::PSRefBuffer<char> *v36; // esi@67
  LONG (__stdcall *v37)(volatile LONG *); // ebx@67
  ReferenceCountTemplate<268435456,0>Vtbl *v38; // edx@69
  int v39; // eax@74
  int v40; // eax@74
  int v41; // ecx@74
  AC1Legacy::PSRefBuffer<char> *v42; // esi@77
  ReferenceCountTemplate<268435456,0>Vtbl *v43; // edx@79
  int v44; // eax@81
  int v45; // eax@81
  int v46; // ecx@81
  AC1Legacy::PSRefBuffer<char> *v47; // esi@84
  ReferenceCountTemplate<268435456,0>Vtbl *v48; // edx@86
  int v49; // eax@88
  int v50; // eax@88
  int v51; // ecx@88
  AC1Legacy::PSRefBuffer<char> *v52; // esi@91
  ReferenceCountTemplate<268435456,0>Vtbl *v53; // edx@93
  ReferenceCountTemplate<268435456,0>Vtbl *v54; // edx@96
  AC1Legacy::PSRefBuffer<char> *v55; // esi@100
  ReferenceCountTemplate<268435456,0>Vtbl *v56; // edx@102
  AC1Legacy::PStringBase<char> *v57[6]; // [sp+Ch] [bp-ECh]@7
  AC1Legacy::PStringBase<char> portalDesc; // [sp+24h] [bp-D4h]@6
  AC1Legacy::PStringBase<char> strAppend; // [sp+28h] [bp-D0h]@4
  PStringBase<char> strMaterial; // [sp+2Ch] [bp-CCh]@26
  int iGemType; // [sp+30h] [bp-C8h]@26
  int remaining_lifespan; // [sp+34h] [bp-C4h]@1
  AC1Legacy::PStringBase<char> v63; // [sp+38h] [bp-C0h]@1
  AC1Legacy::PStringBase<char> strDesc; // [sp+3Ch] [bp-BCh]@20
  int iGemCount; // [sp+40h] [bp-B8h]@25
  int bitfield; // [sp+44h] [bp-B4h]@55
  AC1Legacy::PStringBase<char> strPrepend; // [sp+48h] [bp-B0h]@24
  AC1Legacy::PStringBase<char> gearPlatingName; // [sp+4Ch] [bp-ACh]@21
  int iMaterial; // [sp+50h] [bp-A8h]@27
  int iDecoration; // [sp+54h] [bp-A4h]@23
  unsigned __int64 cost; // [sp+58h] [bp-A0h]@98
  int creationTime; // [sp+60h] [bp-98h]@1
  int lifespan; // [sp+64h] [bp-94h]@1
  StringInfo siText; // [sp+68h] [bp-90h]@99

  v2 = _prof;
  v3 = this;
  v63.m_buffer = (AC1Legacy::PSRefBuffer<char> *)this;
  creationTime = 0;
  remaining_lifespan = 0;
  if ( AppraisalProfile::InqInt(_prof, 0x10Bu, &lifespan)
    && AppraisalProfile::InqInt(_prof, 0x62u, &creationTime)
    && AppraisalProfile::InqInt(_prof, 0x10Cu, &remaining_lifespan) )
  {
    strAppend.m_buffer = (AC1Legacy::PSRefBuffer<char> *)PStringBase<char>::s_NullBuffer.m_charbuffer;
    InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
    if ( remaining_lifespan >= 0 )
    {
      PStringBase<char>::set((PStringBase<char> *)&strAppend, "This item expires in ");
      PStringBase<char>::PStringBase<char>((PStringBase<char> *)&portalDesc, &name);
      v4 = remaining_lifespan;
      if ( remaining_lifespan > 31536000 )
      {
        v57[1] = (AC1Legacy::PStringBase<char> *)(remaining_lifespan / 31536000);
        remaining_lifespan %= 31536000;
        PStringBase<char>::sprintf((PStringBase<char> *)&portalDesc, "%d years, ", v57[1]);
        PStringBase<char>::operator+=((PStringBase<char> *)&strAppend, (PStringBase<char> *)&portalDesc);
        v4 = remaining_lifespan;
      }
      if ( v4 > 86400 )
      {
        remaining_lifespan = v4 % 86400;
        PStringBase<char>::sprintf((PStringBase<char> *)&portalDesc, "%d days, ", v4 / 86400);
        PStringBase<char>::operator+=((PStringBase<char> *)&strAppend, (PStringBase<char> *)&portalDesc);
        v4 = remaining_lifespan;
      }
      if ( v4 > 3600 )
      {
        remaining_lifespan = v4 % 3600;
        PStringBase<char>::sprintf((PStringBase<char> *)&portalDesc, "%d hours, ", v4 / 3600);
        PStringBase<char>::operator+=((PStringBase<char> *)&strAppend, (PStringBase<char> *)&portalDesc);
        v4 = remaining_lifespan;
      }
      if ( v4 > 60 )
      {
        remaining_lifespan = v4 % 60;
        PStringBase<char>::sprintf((PStringBase<char> *)&portalDesc, "%d minutes, ", v4 / 60);
        PStringBase<char>::operator+=((PStringBase<char> *)&strAppend, (PStringBase<char> *)&portalDesc);
        v4 = remaining_lifespan;
      }
      v57[1] = (AC1Legacy::PStringBase<char> *)v4;
      PStringBase<char>::sprintf((PStringBase<char> *)&portalDesc, "%d seconds.", v4);
      v5 = *(_DWORD *)&portalDesc.m_buffer[-1].m_data[0];
      if ( v5 != 1 )
        PStringBase<char>::append_n_chars((PStringBase<char> *)&strAppend, (const char *)portalDesc.m_buffer, v5 - 1);
      PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&portalDesc);
    }
    else
    {
      PStringBase<char>::set((PStringBase<char> *)&strAppend, "This item is in the act of disintegrating.");
    }
    ItemExamineUI::AddItemInfo((ItemExamineUI *)v3, (const char *)strAppend.m_buffer, 0, 1);
    v6 = (char *)&strAppend.m_buffer[-1].m_cRef;
    if ( !InterlockedDecrement((volatile LONG *)&strAppend.m_buffer[-1].m_cRef + 1) && v6 )
      (**(void (__thiscall ***)(char *, signed int))v6)(v6, 1);
  }
  strDesc.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
  InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
  if ( AppraisalProfile::InqString(_prof, 0x10u, &strDesc) )
  {
    gearPlatingName.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( AppraisalProfile::InqString(_prof, 0x34u, &gearPlatingName) )
      AC1Legacy::PStringBase<unsigned short>::operator=(
        (AC1Legacy::PStringBase<unsigned short> *)&strDesc,
        (AC1Legacy::PStringBase<unsigned short> *)&gearPlatingName);
    if ( AppraisalProfile::InqInt(_prof, 0xACu, &iDecoration) )
    {
      v7 = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      strPrepend.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      v8 = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      strAppend.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
      InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
      v9 = _prof;
      if ( iDecoration & 1 && AppraisalProfile::InqInt(_prof, 0x69u, &iGemCount) )
      {
        strMaterial.m_charbuffer = (PSRefBufferCharData<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
        InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
        AppraisalSystem::InqWorkmanshipAdjective(iGemCount, (AC1Legacy::PStringBase<char> *)&strMaterial, 0);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&portalDesc, " ");
        v11 = AC1Legacy::PStringBase<char>::operator+(
                (AC1Legacy::PStringBase<char> *)&strMaterial,
                (AC1Legacy::PStringBase<char> *)&iGemType,
                v10);
        AC1Legacy::PStringBase<char>::operator+=(&strPrepend, v11);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&iGemType);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&portalDesc);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&strMaterial);
        v7 = strPrepend.m_buffer;
      }
      if ( AppraisalProfile::InqInt(_prof, 0x83u, &iMaterial) && iMaterial > 0 )
      {
        strMaterial.m_charbuffer = PStringBase<char>::s_NullBuffer.m_charbuffer;
        InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
        portalDesc.m_buffer = (AC1Legacy::PSRefBuffer<char> *)PStringBase<char>::s_NullBuffer.m_charbuffer;
        InterlockedIncrement((volatile LONG *)&PStringBase<char>::s_NullBuffer.m_charbuffer[-1]);
        AppraisalSystem::InqMaterialName(iMaterial, &strMaterial);
        v12 = strMaterial.m_charbuffer;
        AC1Legacy::PStringBase<char>::PStringBase<char>((AC1Legacy::PStringBase<char> *)&iGemType, " ");
        v14 = AC1Legacy::operator+((AC1Legacy::PStringBase<char> *)&iGemCount, v12->m_data, v13);
        AC1Legacy::PStringBase<char>::operator+=(&strPrepend, v14);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&iGemCount);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&iGemType);
        PStringBase<char>::set((PStringBase<char> *)&portalDesc, strDesc.m_buffer->m_data);
        PStringBase<char>::PStringBase<char>((PStringBase<char> *)&iGemType, &name);
        v15 = PStringBase<char>::replace((PStringBase<char> *)&portalDesc, &strMaterial, (PStringBase<char> *)&iGemType);
        PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&iGemType);
        if ( v15 )
        {
          v57[1] = v16;
          PStringBase<unsigned short>::PStringBase<unsigned short>(
            (CaseInsensitiveStringBase<PStringBase<char> > *)&v57[1],
            &PStringBase<char>::whitespace_string);
          PStringBase<char>::trim((PStringBase<char> *)&portalDesc, 1, 1, (PStringBase<char>)v57[1]);
        }
        AC1Legacy::PStringBase<char>::set(&strDesc, (const char *)portalDesc.m_buffer);
        PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&portalDesc);
        PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&strMaterial);
        v7 = strPrepend.m_buffer;
        v9 = _prof;
      }
      if ( iDecoration & 4
        && AppraisalProfile::InqInt(v9, 0xB1u, &iGemCount)
        && AppraisalProfile::InqInt(v9, 0xB2u, &iGemType) )
      {
        PStringBase<char>::PStringBase<char>(&strMaterial);
        if ( iGemCount == 1 )
          AppraisalSystem::InqMaterialName(iGemType, &strMaterial);
        else
          AppraisalSystem::InqPluralizedGemName(iGemType, &strMaterial);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&portalDesc, ", set with ");
        AC1Legacy::PStringBase<char>::operator+=(&strAppend, &portalDesc);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&portalDesc);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&portalDesc, iGemCount);
        AC1Legacy::PStringBase<char>::operator+=(&strAppend, &portalDesc);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&portalDesc);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&portalDesc, " ");
        AC1Legacy::PStringBase<char>::operator+=(&strAppend, &portalDesc);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&portalDesc);
        AC1Legacy::PStringBase<char>::PStringBase<char>(&portalDesc, strMaterial.m_charbuffer->m_data);
        AC1Legacy::PStringBase<char>::operator+=(&strAppend, &portalDesc);
        CLogonHeader::HandshakeWireData::~HandshakeWireData((CLogonHeader::HandshakeWireData *)&portalDesc);
        PStringBase<char>::~PStringBase<char>((CaseInsensitiveStringBase<PStringBase<char> > *)&strMaterial);
        v8 = strAppend.m_buffer;
      }
      v57[1] = &strAppend;
      v17 = AC1Legacy::PStringBase<char>::operator+(&strPrepend, (AC1Legacy::PStringBase<char> *)&iGemType, &strDesc);
      v18 = (AC1Legacy::PStringBase<unsigned short> *)AC1Legacy::PStringBase<char>::operator+(
                                                        v17,
                                                        (AC1Legacy::PStringBase<char> *)&iGemCount,
                                                        v57[1]);
      AC1Legacy::PStringBase<unsigned short>::operator=((AC1Legacy::PStringBase<unsigned short> *)&strDesc, v18);
      v19 = iGemCount;
      if ( !InterlockedDecrement((volatile LONG *)(iGemCount + 4)) && v19 )
      {
        v20 = *(_DWORD *)v19;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        (*(void (__thiscall **)(int, signed int))v20)(v19, 1);
      }
      v21 = iGemType;
      if ( !InterlockedDecrement((volatile LONG *)(iGemType + 4)) && v21 )
      {
        v22 = *(_DWORD *)v21;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        (*(void (__thiscall **)(int, signed int))v22)(v21, 1);
      }
      if ( !InterlockedDecrement((volatile LONG *)&v8->m_cRef) && v8 )
      {
        v23 = v8->vfptr;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        v23->__vecDelDtor(v8, 1);
      }
      if ( !InterlockedDecrement((volatile LONG *)&v7->m_cRef) && v7 )
      {
        v24 = v7->vfptr;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        v24->__vecDelDtor(v7, 1);
      }
    }
    v3 = v63.m_buffer;
    ItemExamineUI::AddItemInfo((ItemExamineUI *)v63.m_buffer, &name, 0, 1);
    ItemExamineUI::AddItemInfo((ItemExamineUI *)v3, strDesc.m_buffer->m_data, 0, 1);
    v25 = gearPlatingName.m_buffer;
    if ( !InterlockedDecrement((volatile LONG *)&gearPlatingName.m_buffer->m_cRef) && v25 )
    {
      v26 = v25->vfptr;
      v57[1] = (AC1Legacy::PStringBase<char> *)1;
      v26->__vecDelDtor(v25, 1);
    }
    v2 = _prof;
  }
  else if ( AppraisalProfile::InqString(_prof, 0xFu, &strDesc) )
  {
    ItemExamineUI::AddItemInfo((ItemExamineUI *)v3, &name, 0, 1);
    ItemExamineUI::AddItemInfo((ItemExamineUI *)v3, strDesc.m_buffer->m_data, 0, 1);
  }
  bitfield = 0;
  if ( AppraisalProfile::InqInt(v2, 0x6Fu, &bitfield) )
  {
    v27 = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    portalDesc.m_buffer = (AC1Legacy::PSRefBuffer<char> *)AC1Legacy::PStringBase<char>::s_NullBuffer;
    InterlockedIncrement((volatile LONG *)(AC1Legacy::PStringBase<char>::s_NullBuffer + 4));
    if ( bitfield & 2 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&v63, "Player Killers may not use this portal.\n");
      v29 = *(_DWORD *)v28;
      v30 = *(_DWORD *)(v29 + 8);
      if ( v30 != 1 && v29 != AC1Legacy::PStringBase<char>::s_NullBuffer )
      {
        AC1Legacy::PStringBase<char>::append_n_chars(&portalDesc, (const char *)(v29 + 20), v30 - 1);
        v27 = portalDesc.m_buffer;
      }
      v31 = v63.m_buffer;
      if ( !InterlockedDecrement((volatile LONG *)&v63.m_buffer->m_cRef) && v31 )
      {
        v32 = v31->vfptr;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        v32->__vecDelDtor(v31, 1);
      }
    }
    if ( bitfield & 4 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&v63, "Lite Player Killers may not use this portal.\n");
      v34 = *(_DWORD *)v33;
      v35 = *(_DWORD *)(v34 + 8);
      if ( v35 != 1 && v34 != AC1Legacy::PStringBase<char>::s_NullBuffer )
      {
        AC1Legacy::PStringBase<char>::append_n_chars(&portalDesc, (const char *)(v34 + 20), v35 - 1);
        v27 = portalDesc.m_buffer;
      }
      v36 = v63.m_buffer;
      v37 = InterlockedDecrement;
      if ( !InterlockedDecrement((volatile LONG *)&v63.m_buffer->m_cRef) && v36 )
      {
        v38 = v36->vfptr;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        v38->__vecDelDtor(v36, 1);
      }
    }
    else
    {
      v37 = InterlockedDecrement;
    }
    if ( bitfield & 8 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&v63, "Non-Player Killers may not use this portal.\n");
      v40 = *(_DWORD *)v39;
      v41 = *(_DWORD *)(v40 + 8);
      if ( v41 != 1 && v40 != AC1Legacy::PStringBase<char>::s_NullBuffer )
      {
        AC1Legacy::PStringBase<char>::append_n_chars(&portalDesc, (const char *)(v40 + 20), v41 - 1);
        v27 = portalDesc.m_buffer;
      }
      v42 = v63.m_buffer;
      if ( !v37((volatile LONG *)&v63.m_buffer->m_cRef) && v42 )
      {
        v43 = v42->vfptr;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        v43->__vecDelDtor(v42, 1);
      }
    }
    if ( bitfield & 0x20 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&v63, "This portal cannot be recalled nor linked to.\n");
      v45 = *(_DWORD *)v44;
      v46 = *(_DWORD *)(v45 + 8);
      if ( v46 != 1 && v45 != AC1Legacy::PStringBase<char>::s_NullBuffer )
      {
        AC1Legacy::PStringBase<char>::append_n_chars(&portalDesc, (const char *)(v45 + 20), v46 - 1);
        v27 = portalDesc.m_buffer;
      }
      v47 = v63.m_buffer;
      if ( !v37((volatile LONG *)&v63.m_buffer->m_cRef) && v47 )
      {
        v48 = v47->vfptr;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        v48->__vecDelDtor(v47, 1);
      }
    }
    if ( bitfield & 0x10 )
    {
      AC1Legacy::PStringBase<char>::PStringBase<char>(&v63, "This portal cannot be summoned.\n");
      v50 = *(_DWORD *)v49;
      v51 = *(_DWORD *)(v50 + 8);
      if ( v51 != 1 && v50 != AC1Legacy::PStringBase<char>::s_NullBuffer )
      {
        AC1Legacy::PStringBase<char>::append_n_chars(&portalDesc, (const char *)(v50 + 20), v51 - 1);
        v27 = portalDesc.m_buffer;
      }
      v52 = v63.m_buffer;
      if ( !v37((volatile LONG *)&v63.m_buffer->m_cRef) && v52 )
      {
        v53 = v52->vfptr;
        v57[1] = (AC1Legacy::PStringBase<char> *)1;
        v53->__vecDelDtor(v52, 1);
      }
    }
    ItemExamineUI::AddItemInfo((ItemExamineUI *)v3, &name, 0, 1);
    ItemExamineUI::AddItemInfo((ItemExamineUI *)v3, v27->m_data, 0, 1);
    if ( !v37((volatile LONG *)&v27->m_cRef) && v27 )
    {
      v54 = v27->vfptr;
      v57[1] = (AC1Legacy::PStringBase<char> *)1;
      v54->__vecDelDtor(v27, 1);
    }
  }
  else
  {
    v37 = InterlockedDecrement;
  }
  cost = 0i64;
  if ( AppraisalProfile::InqInt64(_prof, 3u, (__int64 *)&cost) )
  {
    StringInfo::StringInfo(&siText);
    StringInfo::SetStringIDandTableEnum(&siText, ID_Examine_Item_AugmentationCost, 268435457);
    StringInfo::AddVariable_Int(&siText, ID_AugmentationCost, cost);
    UIElement_Text::AppendStringInfo(*((UIElement_Text **)v3 + 32), &siText);
    StringInfo::~StringInfo(&siText);
  }
  v55 = strDesc.m_buffer;
  if ( !v37((volatile LONG *)&strDesc.m_buffer->m_cRef) )
  {
    if ( v55 )
    {
      v56 = v55->vfptr;
      v57[1] = (AC1Legacy::PStringBase<char> *)1;
      v56->__vecDelDtor(v55, 1);
    }
  }
}
// 8EE10C: using guessed type int AC1Legacy::PStringBase<char>::s_NullBuffer;

//----- (004B72B0) --------------------------------------------------------
void __thiscall ItemExamineUI::SetAppraiseInfo(ItemExamineUI *this, AppraisalProfile *_prof, int is_new)
{
  ItemExamineUI *v3; // esi@1
  signed int v4; // ebx@1
  UIRegion *v5; // ecx@2
  Graphic *v6; // edi@3
  Graphic *v7; // eax@4
  Graphic *v8; // eax@4
  AppraisalProfile *v9; // edi@7
  UIElement_Text *v10; // ecx@13
  ACCWeenieObject *v11; // ecx@15
  int v12; // ebp@15
  int addValueToText; // [sp+8h] [bp-8h]@2
  int addBurdenToText; // [sp+Ch] [bp-4h]@2

  v3 = this;
  v4 = 0;
  if ( this->cur_weenobj )
  {
    v5 = (UIRegion *)&this->m_itemIcon->vfptr;
    addBurdenToText = 0;
    addValueToText = 0;
    if ( v5 )
    {
      UIRegion::ClearImage(v5);
      UIRegion::SetBlitMode((UIRegion *)&v3->m_itemIcon->vfptr, Blit_3Alpha);
      v6 = (Graphic *)operator new(0xCu);
      if ( v6 )
      {
        v7 = ACCWeenieObject::GetIcon(v3->cur_weenobj);
        Graphic::Graphic(v6, v7);
      }
      else
      {
        v8 = 0;
      }
      UIRegion::SetImage((UIRegion *)&v3->m_itemIcon->vfptr, v8);
    }
    v9 = _prof;
    if ( v3->m_itemValueText )
      ItemExamineUI::SetValueText(v3, _prof);
    else
      addValueToText = 1;
    if ( v3->m_itemBurdenText )
      ItemExamineUI::SetBurdenText(v3, v9);
    else
      addBurdenToText = 1;
    v10 = v3->m_itemDisplayText;
    if ( v10 )
      UIElement_Text::ClearAllText(v10);
    v11 = v3->cur_weenobj;
    v12 = v11->pwd._valid_locations;
    if ( ((int (*)(void))v11->vfptr[29].__vecDelDtor)() )
      v12 = AppraisalProfile::GetHookedItemValidLocations(v9);
    ItemExamineUI::SetInscription(v3, v9);
    if ( addValueToText )
      ItemExamineUI::Appraisal_ShowValueInfo(v3, v9);
    if ( addBurdenToText )
      ItemExamineUI::Appraisal_ShowBurdenInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowTinkeringInfo(v3, v9);
    if ( ItemExamineUI::Appraisal_ShowSet(v3, v9) )
      v4 = 1;
    if ( ItemExamineUI::Appraisal_ShowRatings(v3, v9) || v4 )
      ItemExamineUI::AddItemInfo(v3, &name, 0, 1);
    ItemExamineUI::Appraisal_ShowWeaponAndArmorData(v3, v12, v9);
    ItemExamineUI::Appraisal_ShowDefenseModData(v3, v9);
    ItemExamineUI::Appraisal_ShowArmorMods(v3, v9);
    ItemExamineUI::Appraisal_ShowShortMagicInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowSpecialProperties(v3, v9);
    ItemExamineUI::Appraisal_ShowUsage(v3, v12, v9);
    ItemExamineUI::Appraisal_ShowLevelLimitInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowWieldRequirements(v3, v9);
    ItemExamineUI::Appraisal_ShowUsageLimitInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowItemLevelInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowActivationRequirements(v3, v9);
    ItemExamineUI::Appraisal_ShowCasterData(v3, v9);
    ItemExamineUI::Appraisal_ShowBoostValue(v3, v9);
    ItemExamineUI::Appraisal_ShowHealKitValues(v3, v9);
    ItemExamineUI::Appraisal_ShowCapacity(v3, v9);
    ItemExamineUI::Appraisal_ShowLockAppraiseInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowManaStoneInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowRemainingUses(v3, v9);
    ItemExamineUI::Appraisal_ShowCraftsman(v3, v9);
    _prof = 0;
    if ( AppraisalProfile::InqBool(v9, 0x45u, (int *)&_prof) && !_prof )
      ItemExamineUI::AddItemInfo(v3, "This item cannot be sold.", 0, 1);
    ItemExamineUI::Appraisal_ShowRareInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowMagicInfo(v3, v9);
    ItemExamineUI::Appraisal_ShowDescription(v3, v9);
    if ( is_new )
      UIElement_Text::ScrollToPosition(v3->m_itemDisplayText, 0);
    AppraisalProfile::operator=((int)&v3->cur_prof, (int)v9);
  }
}

