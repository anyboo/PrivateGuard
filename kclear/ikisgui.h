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

#pragma once

interface IMainWndNotify;
interface ISettingPage;
interface IModule;

[ uuid("124799F9-74B1-431a-B203-FB0BFC81695B") ]
interface IModuleMgr : IUnknown
{
	virtual HRESULT __stdcall GetModuleCnt(int* pnModuleCnt) = 0;
	virtual HRESULT __stdcall CreateModule(int nIndex, IModule** ppIModule) = 0;
};

[ uuid("37A8CFDE-3A7E-4183-9E25-836412E2C374") ]
interface IModule : IUnknown
{
	virtual HRESULT __stdcall Init() = 0;
	virtual HRESULT __stdcall Uninit() = 0;
	virtual HRESULT __stdcall Create(HWND hwndParent, RECT rect, HWND* phwndCreated) = 0;
	virtual HRESULT __stdcall Show(BOOL bShow) = 0;
	virtual HRESULT __stdcall Move(RECT rect) = 0;


	//Ӧ�ó����˳�ǰ��ѯ�ʸ���ģ���Ƿ���δ��������ݺ�δ��ɲ���������û�ѡ��ȡ���������˳���
	//pbCondition ���� 1 ��ʾ���˳������򷵻� 0
	virtual HRESULT __stdcall CanQuitNow(int* pbCondition) = 0;


	//ģ���������������ʱ��ͨ��IMainWndNotify�ӿڷ���
	virtual HRESULT __stdcall SetMainWndNotify(IMainWndNotify* pNotify) = 0;

	//�и����ַ����Ժ���չ
	//������ʾ����lpszNameΪnullʱ��len������Ҫ��buffer��С������'\0'�����ַ�Ϊ��λ
	virtual HRESULT	__stdcall GetName(LPTSTR lpszName, UINT* len) = 0;

	// ����ģ�����
	virtual HRESULT	__stdcall SetParam(LPCTSTR lpcszParam) = 0;
};


#define STATE_SOFTWARE_UPDATE	0

interface IMainWndNotify
{
	// ֪ͨ������ѡ��ָ��tabҳ��nTabIndex ��tab������nSubTabIndex ����tab������lpcszParam ģ�����
	virtual HRESULT __stdcall SelectPage(int nTabIndex, int nSubTabIndex, LPCTSTR lpcszParam) = 0;

	//����Ҫ��ʾĳ������ҳ��ʱ������֪ͨ��������ʾ��ҳ��
	//pModule��ʶ�ĸ�ģ�飬pPage��ʶ�ĸ�����ҳ��
	virtual HRESULT __stdcall ShowSettingPage(IModule* pModule, ISettingPage* pPage) = 0;

	//����Ҫ��̨����ʱ��֪ͨ������
	virtual HRESULT __stdcall RunInBackground(IModule* pModule) = 0;//pModule��ʶ�ĸ�ģ����Ҫ��̨����

	//֪ͨ������ĳЩ�������ĵ�״̬����
	//��Ҫ�Ǹ������������Ķ�̬������ƣ�˳�㿴����û��������չ��;
	virtual HRESULT __stdcall StateChanged(IModule* pModule, UINT whichState, void* pData) = 0;
};




//���Թܼһ�ͳһ����ģ������õ�һ�����棨��ȫ����������ܼҵȣ�
//
//ISettingPage��Ӧ��һ����������ý��棬���簲ȫ��������Ĳ�ɱľ��
//
//IModuleSetting��Ӧ��һ����Ĺ���ģ�飬�����õ����е�����ҳ��
//
//
interface IDirtyCallback : IUnknown
{
	virtual HRESULT __stdcall SetDirty(BOOL bDirty) = 0;
};

interface ISettingPage : IUnknown
{
	//������ʾ����lpszNameΪnullʱ��len������Ҫ��buffer��С������'\0'�����ַ�Ϊ��λ
	virtual HRESULT	__stdcall GetName(LPTSTR lpszName, UINT* len) = 0;

	virtual HRESULT __stdcall GetPageRect(RECT* pRect) = 0;//���ڴ�С�����ޣ���Ҫ�ڴ���ǰ��֧��
	virtual HRESULT __stdcall SetDirtyCallback(IDirtyCallback* pICallback) = 0;//�����洫��Ľӿڣ�������֪ͨ���������øı���
	virtual HRESULT __stdcall Apply() = 0;

	virtual HRESULT __stdcall Create(HWND hwndParent, RECT rect, HWND* phwndPage) = 0;
	virtual HRESULT __stdcall Show(BOOL bShow) = 0;
	virtual HRESULT __stdcall Move(RECT rect) = 0;//����resize�����֧�֣�
};

[ uuid("0909C3DC-3C87-4f1d-ABDD-D7465C19674C") ]
interface IModuleSetting : IUnknown
{
	//������ʾ����lpszNameΪnullʱ��len������Ҫ��buffer��С������'\0'�����ַ�Ϊ��λ
	virtual HRESULT	__stdcall GetName(LPTSTR lpszName, UINT* len) = 0;

	//���ppISettingPageΪNULL,pFetched����֧�ֶ��ٸ������Ӵ���,������Ȼ��Ѻ�����ô���ISettingPage*�������ٴδ���
	virtual HRESULT __stdcall GetPages(ISettingPage** ppISettingPage, ULONG* pFetched) = 0;
};
