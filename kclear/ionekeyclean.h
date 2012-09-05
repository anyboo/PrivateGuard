// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/********************************************************************
	created:	2010/07/12
	created:	12:7:2010   19:10
	filename: 	ionekeyclean.h
	author:		Jiang Fengbing
	
	purpose:	һ���Ż����ڲ��ӿ�
*********************************************************************/

#ifndef IONEKEYCLEAN_INC_
#define IONEKEYCLEAN_INC_

//////////////////////////////////////////////////////////////////////////

[
    uuid(c8e7fa72-cb34-49b6-bfc1-8b194dc9eefb)
]
interface ICleanCallback
{
    // @brief ��ʼ����
    virtual void __stdcall OnBegin(
        ) = 0;

    // @brief �������
    virtual void __stdcall OnEnd(
        ) = 0;

    // @brief ����ȡ��
    virtual void __stdcall OnCancel(
        ) = 0;

    // @brief ����������Ŀ
    // @param szType: �����ַ���
    // @param szItem: �������ݵ��ַ���
    // @param nSize: ������������������������Ĵ�С����λΪM
    virtual void __stdcall OnCleanEntry(
        /* [in] */ int nType,
        /* [in, size_is(nType)] */const wchar_t* szType,
        /* [in] */ int nItem,
        /* [in, size_is(nItem)] */const wchar_t* szItem,
        /* [in] */ double nSize
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////

[
    uuid(701adf0b-4096-476a-9382-e01a431389d3)
]
interface ICleanTask
{
    // @brief ��������ص�
    virtual void __stdcall SetCallback(
        ICleanCallback* piCallback
        ) = 0;

    // @brief ��ʼ����
    // @param nTask: szTask���ַ�������
    // @param szTask: ��������, ����: "ie_temp,win_temp"
    virtual bool __stdcall StartClean(
        /* [in] */ int nTask,
        /* [in, size_is(nTask)] */const char* szTask
        ) = 0;

    // @brief ֹͣ����
    virtual bool __stdcall StopClean(
        ) = 0;

    // @brief �����Լ�
    virtual void __stdcall Release(
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////

[
    uuid(c8e7fa72-cb34-49b6-bfc1-8b194dc9eefb)
]
interface ICleanCallback2
{
    // @brief ��ʼɨ��
    virtual void __stdcall OnScanBegin(
        ) = 0;

    // @brief ��ʼ����
    virtual void __stdcall OnCleanBegin(
        ) = 0;

    // @brief ɨ�����
    virtual void __stdcall OnScanEnd(
        ) = 0;

    // @brief �������
    virtual void __stdcall OnCleanEnd(
        ) = 0;

    // @brief ɨ�豻ȡ��
    virtual void __stdcall OnScanCancel(
        ) = 0;

    // @brief ����ȡ��
    virtual void __stdcall OnCleanCancel(
        ) = 0;

    // @brief ����ɨ����Ŀ
    // @param szType: �����ַ���
    // @param szItem: �������ݵ��ַ���
    // @param nSize: ��������������������ɨ��Ĵ�С����λΪM
    virtual void __stdcall OnScanEntry(
        /* [in] */ int nType,
        /* [in, size_is(nType)] */const wchar_t* szType,
        /* [in] */ int nItem,
        /* [in, size_is(nItem)] */const wchar_t* szItem,
        /* [in] */ double nSize
        ) = 0;

    // @brief ����������Ŀ
    // @param szType: �����ַ���
    // @param szItem: �������ݵ��ַ���
    // @param nSize: ������������������������Ĵ�С����λΪM
    virtual void __stdcall OnCleanEntry(
        /* [in] */ int nType,
        /* [in, size_is(nType)] */const wchar_t* szType,
        /* [in] */ int nItem,
        /* [in, size_is(nItem)] */const wchar_t* szItem,
        /* [in] */ double nSize
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////

[
    uuid(701adf0b-4096-476a-9382-e01a431389d3)
]
interface ICleanTask2
{
    // @brief ����ɨ�������ص�
    virtual void __stdcall SetCallback(
        ICleanCallback2* piCallback
        ) = 0;

    // @brief ��ʼɨ��
    // @param nTask: szTask���ַ�������
    // @param szTask: ɨ������, ����: "ie_temp,win_temp"
    virtual bool __stdcall StartScan(
        /* [in] */ int nTask,
        /* [in, size_is(nTask)] */const char* szTask
        ) = 0;

    // @brief ��ʼ����
    // @param nTask: szTask���ַ�������
    // @param szTask: ��������, ����: "ie_temp,win_temp"
    virtual bool __stdcall StartClean(
        /* [in] */ int nTask,
        /* [in, size_is(nTask)] */const char* szTask
        ) = 0;

    // @brief ֹͣɨ��
    virtual bool __stdcall StopScan(
        ) = 0;

    // @brief ֹͣ����
    virtual bool __stdcall StopClean(
        ) = 0;

    // @brief �����Լ�
    virtual void __stdcall Release(
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////

typedef bool (__cdecl *GetCleaner_t)(const GUID& riid, void** ppv);
bool __cdecl GetCleaner(const GUID& riid, void** ppv);

//////////////////////////////////////////////////////////////////////////

#endif  // IONEKEYCLEAN_INC_
