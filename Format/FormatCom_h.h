

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Sep 05 16:30:11 2012
 */
/* Compiler settings for .\FormatCom.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __FormatCom_h_h__
#define __FormatCom_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITrueCryptFormatCom_FWD_DEFINED__
#define __ITrueCryptFormatCom_FWD_DEFINED__
typedef interface ITrueCryptFormatCom ITrueCryptFormatCom;
#endif 	/* __ITrueCryptFormatCom_FWD_DEFINED__ */


#ifndef __TrueCryptFormatCom_FWD_DEFINED__
#define __TrueCryptFormatCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrueCryptFormatCom TrueCryptFormatCom;
#else
typedef struct TrueCryptFormatCom TrueCryptFormatCom;
#endif /* __cplusplus */

#endif 	/* __TrueCryptFormatCom_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "Password.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __TrueCryptFormatCom_LIBRARY_DEFINED__
#define __TrueCryptFormatCom_LIBRARY_DEFINED__

/* library TrueCryptFormatCom */
/* [version][helpstring][uuid] */ 


EXTERN_C const IID LIBID_TrueCryptFormatCom;

#ifndef __ITrueCryptFormatCom_INTERFACE_DEFINED__
#define __ITrueCryptFormatCom_INTERFACE_DEFINED__

/* interface ITrueCryptFormatCom */
/* [helpstring][oleautomation][object][uuid] */ 


EXTERN_C const IID IID_ITrueCryptFormatCom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9EE02955-174A-48F1-820C-022F327BE109")
    ITrueCryptFormatCom : public IUnknown
    {
    public:
        virtual int STDMETHODCALLTYPE AnalyzeHiddenVolumeHost( 
            LONG_PTR hwndDlg,
            int *driveNo,
            __int64 hiddenVolHostSize,
            int *realClusterSize,
            __int64 *nbrFreeClusters) = 0;
        
        virtual DWORD STDMETHODCALLTYPE CallDriver( 
            DWORD ioctl,
            BSTR input,
            BSTR *output) = 0;
        
        virtual DWORD STDMETHODCALLTYPE CopyFile( 
            BSTR sourceFile,
            BSTR destinationFile) = 0;
        
        virtual DWORD STDMETHODCALLTYPE DeleteFile( 
            BSTR file) = 0;
        
        virtual BOOL STDMETHODCALLTYPE FormatNtfs( 
            int driveNo,
            int clusterSize) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsPagingFileActive( 
            BOOL checkNonWindowsPartitionsOnly) = 0;
        
        virtual DWORD STDMETHODCALLTYPE ReadWriteFile( 
            BOOL write,
            BOOL device,
            BSTR filePath,
            BSTR *bufferBstr,
            unsigned __int64 offset,
            unsigned __int32 size,
            DWORD *sizeDone) = 0;
        
        virtual DWORD STDMETHODCALLTYPE RegisterFilterDriver( 
            BOOL registerDriver,
            int filterType) = 0;
        
        virtual DWORD STDMETHODCALLTYPE RegisterSystemFavoritesService( 
            BOOL registerService) = 0;
        
        virtual DWORD STDMETHODCALLTYPE SetDriverServiceStartType( 
            DWORD startType) = 0;
        
        virtual DWORD STDMETHODCALLTYPE WriteLocalMachineRegistryDwordValue( 
            BSTR keyPath,
            BSTR valueName,
            DWORD value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrueCryptFormatComVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrueCryptFormatCom * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrueCryptFormatCom * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrueCryptFormatCom * This);
        
        int ( STDMETHODCALLTYPE *AnalyzeHiddenVolumeHost )( 
            ITrueCryptFormatCom * This,
            LONG_PTR hwndDlg,
            int *driveNo,
            __int64 hiddenVolHostSize,
            int *realClusterSize,
            __int64 *nbrFreeClusters);
        
        DWORD ( STDMETHODCALLTYPE *CallDriver )( 
            ITrueCryptFormatCom * This,
            DWORD ioctl,
            BSTR input,
            BSTR *output);
        
        DWORD ( STDMETHODCALLTYPE *CopyFile )( 
            ITrueCryptFormatCom * This,
            BSTR sourceFile,
            BSTR destinationFile);
        
        DWORD ( STDMETHODCALLTYPE *DeleteFile )( 
            ITrueCryptFormatCom * This,
            BSTR file);
        
        BOOL ( STDMETHODCALLTYPE *FormatNtfs )( 
            ITrueCryptFormatCom * This,
            int driveNo,
            int clusterSize);
        
        BOOL ( STDMETHODCALLTYPE *IsPagingFileActive )( 
            ITrueCryptFormatCom * This,
            BOOL checkNonWindowsPartitionsOnly);
        
        DWORD ( STDMETHODCALLTYPE *ReadWriteFile )( 
            ITrueCryptFormatCom * This,
            BOOL write,
            BOOL device,
            BSTR filePath,
            BSTR *bufferBstr,
            unsigned __int64 offset,
            unsigned __int32 size,
            DWORD *sizeDone);
        
        DWORD ( STDMETHODCALLTYPE *RegisterFilterDriver )( 
            ITrueCryptFormatCom * This,
            BOOL registerDriver,
            int filterType);
        
        DWORD ( STDMETHODCALLTYPE *RegisterSystemFavoritesService )( 
            ITrueCryptFormatCom * This,
            BOOL registerService);
        
        DWORD ( STDMETHODCALLTYPE *SetDriverServiceStartType )( 
            ITrueCryptFormatCom * This,
            DWORD startType);
        
        DWORD ( STDMETHODCALLTYPE *WriteLocalMachineRegistryDwordValue )( 
            ITrueCryptFormatCom * This,
            BSTR keyPath,
            BSTR valueName,
            DWORD value);
        
        END_INTERFACE
    } ITrueCryptFormatComVtbl;

    interface ITrueCryptFormatCom
    {
        CONST_VTBL struct ITrueCryptFormatComVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrueCryptFormatCom_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITrueCryptFormatCom_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITrueCryptFormatCom_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITrueCryptFormatCom_AnalyzeHiddenVolumeHost(This,hwndDlg,driveNo,hiddenVolHostSize,realClusterSize,nbrFreeClusters)	\
    ( (This)->lpVtbl -> AnalyzeHiddenVolumeHost(This,hwndDlg,driveNo,hiddenVolHostSize,realClusterSize,nbrFreeClusters) ) 

#define ITrueCryptFormatCom_CallDriver(This,ioctl,input,output)	\
    ( (This)->lpVtbl -> CallDriver(This,ioctl,input,output) ) 

#define ITrueCryptFormatCom_CopyFile(This,sourceFile,destinationFile)	\
    ( (This)->lpVtbl -> CopyFile(This,sourceFile,destinationFile) ) 

#define ITrueCryptFormatCom_DeleteFile(This,file)	\
    ( (This)->lpVtbl -> DeleteFile(This,file) ) 

#define ITrueCryptFormatCom_FormatNtfs(This,driveNo,clusterSize)	\
    ( (This)->lpVtbl -> FormatNtfs(This,driveNo,clusterSize) ) 

#define ITrueCryptFormatCom_IsPagingFileActive(This,checkNonWindowsPartitionsOnly)	\
    ( (This)->lpVtbl -> IsPagingFileActive(This,checkNonWindowsPartitionsOnly) ) 

#define ITrueCryptFormatCom_ReadWriteFile(This,write,device,filePath,bufferBstr,offset,size,sizeDone)	\
    ( (This)->lpVtbl -> ReadWriteFile(This,write,device,filePath,bufferBstr,offset,size,sizeDone) ) 

#define ITrueCryptFormatCom_RegisterFilterDriver(This,registerDriver,filterType)	\
    ( (This)->lpVtbl -> RegisterFilterDriver(This,registerDriver,filterType) ) 

#define ITrueCryptFormatCom_RegisterSystemFavoritesService(This,registerService)	\
    ( (This)->lpVtbl -> RegisterSystemFavoritesService(This,registerService) ) 

#define ITrueCryptFormatCom_SetDriverServiceStartType(This,startType)	\
    ( (This)->lpVtbl -> SetDriverServiceStartType(This,startType) ) 

#define ITrueCryptFormatCom_WriteLocalMachineRegistryDwordValue(This,keyPath,valueName,value)	\
    ( (This)->lpVtbl -> WriteLocalMachineRegistryDwordValue(This,keyPath,valueName,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITrueCryptFormatCom_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TrueCryptFormatCom;

#ifdef __cplusplus

class DECLSPEC_UUID("777DCDFD-C330-480B-B582-B02B57580CC9")
TrueCryptFormatCom;
#endif
#endif /* __TrueCryptFormatCom_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


