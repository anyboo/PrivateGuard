#ifndef _GDIPLUSIMAGE_H
#define _GDIPLUSIMAGE_H

#include "gdiplus.h"
#include "bkres\bkpngpool.h"

#pragma comment(lib, "gdiplus.lib")


class CGdiPlusImage
{
	class CInitGdiPlus
	{
	public:
		CInitGdiPlus() throw()
			: m_dwToken(0)
			, m_dwLastError(S_OK)
		{
			Gdiplus::GdiplusStartupInput input;
			Gdiplus::GdiplusStartupOutput output;
			Gdiplus::Status status = Gdiplus::GdiplusStartup( &m_dwToken, &input, &output );
		}
		
		~CInitGdiPlus() throw()
		{
			Gdiplus::GdiplusShutdown( m_dwToken );
		}
		
		
	private:
		ULONG_PTR m_dwToken;
		DWORD m_dwLastError;
	};
	
	public:
		CGdiPlusImage()
			: m_pImage(NULL)
			, m_lSubImageWidth(0)
		{
			
		}
		
		~CGdiPlusImage()
		{
			
		}

		BOOL Attach(Gdiplus::Image *pImage)
		{
			if (NULL == pImage)
				return FALSE;

			m_pImage = pImage;

			return TRUE;
		}

		Gdiplus::Image *Detach()
		{
			Gdiplus::Image *pImage = m_pImage;

			return pImage;
		}

		BOOL IsNull()
		{
			return m_pImage == NULL;
		}

		CGdiPlusImage& operator=( __in const UINT uResID)
		{
			Attach(BkPngPool::Get(uResID));

			return( *this );
		}

		BOOL GetImageSize(SIZE &sizeImage)
		{
            if (m_pImage)
            {
                sizeImage.cx = m_pImage->GetWidth();
                sizeImage.cy = m_pImage->GetHeight();

                return m_pImage->GetLastStatus() == Gdiplus::Ok;
            }

            return FALSE;
		}
		
		void SetSubImageWidth(LONG lWidth)
		{
			m_lSubImageWidth = lWidth;
		}
		
		LONG GetSubImageWidth()
		{
			return m_lSubImageWidth;
		}
		
		BOOL Draw(HDC hDC, int nDesX, int nDesY, int nSubImage = -1/* All */)
		{
			BOOL bResult = FALSE;
			int nDrawWidth = 0, nDrawHeight = 0, nSrcPosX = 0, nSrcPosY = 0;
			Gdiplus::Graphics graphics(hDC);
			CSize szImg;
			
// 			if (0 == m_lSubImageWidth && -1 != nSubImage)
// 				goto Exit0;
			
			if (!GetImageSize(szImg))
				goto Exit0;
			
			nDrawHeight = szImg.cy;
			
			if (-1 == nSubImage)
			{
				nDrawWidth = szImg.cx;
			}
			else
			{
				nDrawWidth = m_lSubImageWidth;
				nSrcPosX = nSubImage * m_lSubImageWidth;
			}
			
			bResult = Gdiplus::Ok == graphics.DrawImage(m_pImage, Gdiplus::Rect(nDesX, nDesY, nDrawWidth, nDrawHeight), nSrcPosX, 0, nDrawWidth, nDrawHeight, Gdiplus::UnitPixel);
			
Exit0:
			return bResult;
		}
		
		BOOL Draw(HDC hDC, int nDesX, int nDesY, int nDesWidth, int nDesHeight, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight, int nSubImage = -1/* All */)
		{
			BOOL bResult = FALSE;
			Gdiplus::Graphics graphics(hDC);
			CSize szImg;
			
// 			if (0 == m_lSubImageWidth && -1 != nSubImage)
// 				goto Exit0;
			
			if (!GetImageSize(szImg))
				goto Exit0;
			
			if (-1 != nSubImage && 0 != m_lSubImageWidth)
			{
				nSrcX += nSubImage * m_lSubImageWidth;
			}
			
			bResult = Gdiplus::Ok == graphics.DrawImage(m_pImage, Gdiplus::Rect(nDesX, nDesY, nDesWidth, nDesHeight), nSrcX, nSrcY, nSrcWidth, nSrcHeight, Gdiplus::UnitPixel);
			
Exit0:
			return bResult;
		}
		
		
	protected:
		LONG m_lSubImageWidth;
		Gdiplus::Image	*m_pImage;
		static CInitGdiPlus s_initGDIPlus;
};

__declspec(selectany) CGdiPlusImage::CInitGdiPlus CGdiPlusImage::s_initGDIPlus;

#endif
