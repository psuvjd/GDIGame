// DirectSound.h: interface for the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTSOUND_H__A20FE86F_118F_11D2_9AB3_0060B0CDC13E__INCLUDED_)
#define AFX_DIRECTSOUND_H__A20FE86F_118F_11D2_9AB3_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mmsystem.h>
#include <dsound.h>

#pragma message("linking with Microsoft's DirectSound library ...")
#pragma comment(lib, "dsound.lib")

class CDirectSound
{
public:		// construction/destruction
	CDirectSound();
	virtual ~CDirectSound();

	// If the "pWnd" paramter is NULL, then AfxGetApp()->GetMainWnd() will be used.
	BOOL	Create(LPCTSTR pszResource, CWnd * pWnd = 0);
	BOOL	Create(UINT uResourceID, CWnd * pWnd = 0) {
		return Create(MAKEINTRESOURCE(uResourceID), pWnd);
	}
	// Alternativly you can specify the sound by yourself
	// Note that the class does not copy the entire data ! Instead
	// a pointer to the given data will be stored !
	// You can load an entire WAV file into memory and then call this
	// Create() method.
	BOOL	Create(LPVOID pSoundData, CWnd * pWnd = 0);

public:		// operations
	BOOL			IsValid() const;
	void			Play(DWORD dwStartPosition = 0, BOOL bLoop = FALSE);
	void			Stop();
	void			Pause();
	void			Continue();
	CDirectSound &	EnableSound(BOOL bEnable = TRUE) {
		m_bEnabled = bEnable;
		if (!bEnable)
			Stop();
		return *this;
	}
	BOOL			IsEnabled() const { return m_bEnabled; }

protected:	// implementation
	BOOL SetSoundData(LPVOID pSoundData, DWORD dwSoundSize);
	BOOL CreateSoundBuffer(WAVEFORMATEX * pcmwf);
	BOOL GetWaveData(void * pRes, WAVEFORMATEX * & pWaveHeader, void * & pbWaveData, DWORD & cbWaveSize);

private:	// data member
	LPVOID m_pTheSound;
	DWORD m_dwTheSound;
	LPDIRECTSOUNDBUFFER m_pDsb;
	BOOL m_bEnabled;
	static LPDIRECTSOUND m_lpDirectSound;
	static DWORD m_dwInstances;
};

#endif // !defined(AFX_DIRECTSOUND_H__A20FE86F_118F_11D2_9AB3_0060B0CDC13E__INCLUDED_)
