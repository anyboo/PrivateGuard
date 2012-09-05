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
	created:	2010/10/11
	filename: 	ifcache.h
	author:		Jiang Fengbing
	
	purpose:	Ӳ���ļ���Ϣcache�ӿ�
*********************************************************************/

#pragma once

//////////////////////////////////////////////////////////////////////////

#include <unknwn.h>

//////////////////////////////////////////////////////////////////////////

typedef enum tagFCacheQueryType {
    enumFQT_Top,    // ����Top, ��һ������(ULONG)
    enumFQT_Ext,    // ������չ��, ��һ������(const char*)
    enumFQT_Zone,   // ���շ�Χ, ����������(ULONGLONG*, ULONGLONG*)
    enumFQT_Word,   // ���չؼ���, ��һ������(const wchar_t*)
} FCacheQueryType;

/**
 * @brief Cache��ѯ�������ݵĽӿ�
 */
[
    uuid(6a1ba2d1-08a1-4e02-ae74-ee692b478fa4)
]
interface IFCacheQueryback
{
    /**
     * @brief ����Query��ѯ��������
     */
    virtual void OnData(
        FCacheQueryType nQueryType,
        LPCWSTR lpFilePath,
        ULONGLONG qwFileSize
        ) = 0;

    /**
     * @brief ����QueryTopExt��ѯ��������
     */
    virtual void OnExtData(
        LPCWSTR lpExt,
        ULONGLONG qwSize,
        ULONGLONG qwCount
        ) = 0;
};

/**
 * @biref cache�ӿ�, ��BeginAdd, Ȼ��AddFile, ���EndAdd
 */
[
    uuid(45f1e12b-1a5f-402f-8264-3458cb4aafb4)
]
interface IFCache : IUnknown
{
    /**
     * @brief ��ʼ��
     */
    virtual BOOL __cdecl Initialize(
        ) = 0;

    /**
     * @brief ����ʼ��
     */
    virtual BOOL __cdecl UnInitialize(
        ) = 0;

    /**
     * @brief ��ʼ�������
     */
    virtual BOOL __cdecl BeginAdd(
        ) = 0;

    /**
     * @brief �����������
     */
    virtual BOOL __cdecl EndAdd(
        ) = 0;

    /**
     * @brief ȡ���������
     */
    virtual BOOL __cdecl CancelAdd(
        ) = 0;

    /**
     * @brief ����ļ���Ϣ
     */
    virtual BOOL __cdecl AddFile(
        LPCWSTR lpFilePath,
        ULONGLONG qwFileSize
        ) = 0;

    /**
     * @brief ɾ���ļ���Ϣ
     */
    virtual BOOL __cdecl DelFile(
        LPCWSTR lpFilePath
        ) = 0;

    /**
     * @brief ɾ��ĳ��Ŀ¼����������ļ���Ϣ
     */
    virtual BOOL __cdecl DelDir(
        LPCWSTR lpDir
        ) = 0;

    /**
     * @brief ����ܵĴ�С
     */
    virtual BOOL __cdecl GetTotalInfo(
        ULONGLONG& qwTotalSize,
        ULONGLONG& qwTotalCount
        ) = 0;

    /**
     * @brief �����ѯ
     */
    virtual BOOL __cdecl Query(
        IFCacheQueryback* piQueryback,
        FCacheQueryType queryType,
        void* pParam1,
        void* pParam2
        ) = 0;

    /**
     * @brief ���Cache
     */
    virtual BOOL __cdecl Clean(
        ) = 0;

    /**
     * @brief ����ļ��Ĵ�С
     */
    virtual BOOL __cdecl GetFileSize(
        LPCWSTR lpFilePath,
        ULONGLONG& qwSize
        ) = 0;

    /**
     * @brief ���Ŀ¼��С
     */
    virtual BOOL __cdecl GetDirInfo(
        LPCWSTR lpDir,
        ULONGLONG& qwSize,
        ULONGLONG& qwCount
        ) = 0;

    /**
     * @brief �����չ��Top��
     */
    virtual BOOL __cdecl QueryTopExt(
        IFCacheQueryback* piQueryback,
        int nTop
        ) = 0;

    /**
     * @brief ��¼ɨ���Ƿ�������ɨ��ʱ��
     */
    virtual BOOL __cdecl SetCacheInfo(
        const SYSTEMTIME& scanTime,
        BOOL bFullCache
        ) = 0;

    /**
     * @brief ���ɨ���Ƿ�������ɨ��ʱ��
     */
    virtual BOOL __cdecl GetCacheInfo(
        SYSTEMTIME& scanTime,
        BOOL& bFullCache
        ) = 0;
};

//////////////////////////////////////////////////////////////////////////

/**
 * @brief ���Cache���ʽӿ�
 * @param riid: in __uuidof(IFCache)
 * @param ppvObject: out ����ʵ��
 * @param cVol: in �̷�
 */
typedef BOOL (__cdecl *GetFCache_t)(REFIID riid, void** ppvObject, char cVol);

BOOL __cdecl GetFCache(REFIID riid, void** ppvObject, char cVol);

//////////////////////////////////////////////////////////////////////////
